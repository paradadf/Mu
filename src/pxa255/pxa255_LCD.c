#include "pxa255_LCD.h"
#include "pxa255_mem.h"
#include "pxa255.h"
#include "../armv5te/mem.h"

#define UNMASKABLE_INTS		0x7C8E

static void pxa255lcdPrvUpdateInts(Pxa255lcd* lcd){
	
	UInt16 ints = lcd->lcsr & lcd->intMask;
	
	if((ints && !lcd->intWasPending) || (!ints && lcd->intWasPending)){
			
		lcd->intWasPending = !!ints;
		pxa255icInt(lcd->ic, PXA255_I_LCD, !!ints);
	}
}

Boolean pxa255lcdPrvMemAccessF(void* userData, UInt32 pa, UInt8 size, Boolean write, void* buf){

	Pxa255lcd* lcd = userData;
	UInt32 val = 0;
	UInt16 v16;
	
	if(size != 4) {
		err_str(__FILE__ ": Unexpected ");
	//	err_str(write ? "write" : "read");
	//	err_str(" of ");
	//	err_dec(size);
	//	err_str(" bytes to 0x");
	//	err_hex(pa);
	//	err_str("\r\n");
		return true;		//we do not support non-word accesses
	}
	
	pa = (pa - PXA255_LCD_BASE) >> 2;
	
	if(write){
		val = *(UInt32*)buf;
		
		switch(pa){
			case 0:
				if((lcd->lccr0 ^ val) & 0x0001){		//something changed about enablement - handle it
					
					lcd->enbChanged = 1;
				}
				lcd->lccr0 = val;
				//recalc intMask
				v16 = UNMASKABLE_INTS;
				if(val & 0x00200000UL){	//output fifo underrun
					v16 |= 0x0040;
				}
				if(val & 0x00100000UL){	//branch int
					v16 |= 0x0200;
				}
				if(val & 0x00000400UL){	//quick disable
					v16 |= 0x0001;
				}
				if(val & 0x00000040UL){	//end of frame
					v16 |= 0x0080;
				}
				if(val & 0x00000020UL){	//input fifo underrun
					v16 |= 0x0030;
				}
				if(val & 0x00000010UL){	//start of frame
					v16 |= 0x0002;
				}
				lcd->intMask = v16;
				pxa255lcdPrvUpdateInts(lcd);
				break;
			
			case 1:
				lcd->lccr1 = val;
				break;
			
			case 2:
				lcd->lccr2 = val;
				break;
			
			case 3:
				lcd->lccr3 = val;
				break;
			
			case 8:
				lcd->fbr0 = val;
				break;
			
			case 9:
				lcd->fbr1 = val;
				break;
			
			case 14:
				lcd->lcsr &=~ val;
				pxa255lcdPrvUpdateInts(lcd);
				break;
			
			case 15:
				lcd->liicr = val;
				break;
			
			case 16:
				lcd->trgbr = val;
				break;
			
			case 17:
				lcd->tcr = val;
				break;
			
			case 128:
				lcd->fdadr0 = val;
				break;
			
			case 132:
				lcd->fdadr1 = val;
				break;
		}
	}
	else{
		switch(pa){
			case 0:
				val = lcd->lccr0;
				break;
			
			case 1:
				val = lcd->lccr1;
				break;
			
			case 2:
				val = lcd->lccr2;
				break;
			
			case 3:
				val = lcd->lccr3;
				break;
			
			case 8:
				val = lcd->fbr0;
				break;
			
			case 9:
				val = lcd->fbr1;
				break;
			
			case 14:
				val = lcd->lcsr;
				break;
			
			case 15:
				val = lcd->liicr;
				break;
			
			case 16:
				val = lcd->trgbr;
				break;
			
			case 17:
				val = lcd->tcr;
				break;
			
			case 128:
				val = lcd->fdadr0;
				break;
			
			case 129:
				val = lcd->fsadr0;
				break;
			
			case 130:
				val = lcd->fidr0;
				break;
			
			case 131:
				val = lcd->ldcmd0;
				break;
			
			case 132:
				val = lcd->fdadr1;
				break;
			
			case 133:
				val = lcd->fsadr1;
				break;
			
			case 134:
				val = lcd->fidr1;
				break;
			
			case 135:
				val = lcd->ldcmd1;
				break;
		}
		*(UInt32*)buf = val;
	}
	
	return true;
}

#define pxa255PrvGetWord(x, addr) mmio_read_word(addr)

static void pxa255LcdPrvDma(Pxa255lcd* lcd, void* dest, UInt32 addr, UInt32 len){

	UInt32 t;
	UInt8* d = dest;

	//we assume aligntment here both on part of dest and of addr

	while(len){
		
		t = pxa255PrvGetWord(lcd, addr);
		if(len--) *d++ = t;
		if(len--) *d++ = t >> 8;
		if(len--) *d++ = t >> 16;
		if(len--) *d++ = t >> 24;
		addr += 4;
	}
}

static _INLINE_ void pxa255LcdScreenDataPixel(Pxa255lcd* lcd, UInt8* buf){
   static UInt16 pixelX = 0;
   static UInt16 pixelY = 0;

   if(pixelX == 640){
      pixelY++;
      pixelX = 0;
   }

   if(pixelY == 480){
      pixelY = 0;
      pixelX = 0;
   }

   if(pixelX < 320 && pixelY < 420)
      pxa255Framebuffer[pixelY * 320 + pixelX] = buf[0] || buf[1] << 8;
}

static void pxa255LcdScreenDataDma(Pxa255lcd* lcd, UInt32 addr/*PA*/, UInt32 len){
   UInt8 data[4];
   UInt32 i, j;
   void* ptr;

   len /= 4;
   while(len--){
      pxa255LcdPrvDma(lcd, data, addr, 4);
      addr += 4;

      switch((lcd->lccr3 >> 24) & 7){

         case 0:		//1BPP

            ptr = lcd->palette + ((data[i] >> j) & 1) * 2;
            for(i = 0; i < 4; i += 1) for(j = 0; j < 8; j += 1) pxa255LcdScreenDataPixel(lcd, ptr);
            break;

         case 1:		//2BPP

            ptr = lcd->palette + ((data[i] >> j) & 3) * 2;
            for(i = 0; i < 4; i += 1) for(j = 0; j < 8; j += 2) pxa255LcdScreenDataPixel(lcd, ptr);
            break;

         case 2:		//4BPP

            ptr = lcd->palette + ((data[i] >> j) & 15) * 2;
            for(i = 0; i < 4; i += 1) for(j = 0; j < 8; j += 4) pxa255LcdScreenDataPixel(lcd, ptr);
            break;

         case 3:		//8BPP

            ptr = lcd->palette + (data[i] * 2);
            for(i = 0; i < 4; i += 1) pxa255LcdScreenDataPixel(lcd, ptr);
            break;

         case 4:		//16BPP

            for(i = 0; i < 4; i +=2 ) pxa255LcdScreenDataPixel(lcd, data + i);
            break;

         default:

            ;//BAD
      }
   }
}

void pxa255lcdFrame(Pxa255lcd* lcd){
	//every other call starts a frame, the others end one [this generates spacing between interrupts so as to not confuse guest OS]
	
	if(lcd->enbChanged){
		
		if(lcd->lccr0 & 0x0001){	//just got enabled
			
			//TODO: perhaps check settings?
		}
		else{				// we just got quick disabled - kill current frame and do no more
		
			lcd->lcsr |= 0x0080;	//quick disable happened
			lcd->state = LCD_STATE_IDLE;
		}
		lcd->enbChanged = false;			
	}
	
	if(lcd->lccr0 & 0x0001){			//enabled - do a frame
		
		UInt32 descrAddr, len;
		
		switch(lcd->state){
			
			case LCD_STATE_IDLE:
				
				if(lcd->fbr0 & 1){	//branch
					
					lcd->fbr0 &=~ 1UL;
					if(lcd->fbr0 & 2) lcd->lcsr |= 0x0200;
					descrAddr = lcd->fbr0 &~ 0xFUL;
				} else descrAddr = lcd->fdadr0;
				lcd->fdadr0 = pxa255PrvGetWord(lcd, descrAddr + 0);
				lcd->fsadr0 = pxa255PrvGetWord(lcd, descrAddr + 4);
				lcd->fidr0  = pxa255PrvGetWord(lcd, descrAddr + 8);
				lcd->ldcmd0 = pxa255PrvGetWord(lcd, descrAddr + 12);
			
				lcd->state = LCD_STATE_DMA_0_START;
				break;
			
			case LCD_STATE_DMA_0_START:
				
				if(lcd->ldcmd0 & 0x00400000UL) lcd->lcsr |= 0x0002;	//set SOF is DMA 0 started
				len = lcd->ldcmd0 & 0x000FFFFFUL;
				
				if(lcd->ldcmd0 & 0x04000000UL){	//pallette data
					
               if(len > sizeof(lcd->palette)){

                  len = sizeof(lcd->palette);

                  pxa255LcdPrvDma(lcd, lcd->palette, lcd->fsadr0, len);
               }
				}
				else{
					
					lcd->frameNum++;
					if(!(lcd->frameNum & 63)) pxa255LcdScreenDataDma(lcd, lcd->fsadr0, len);
				}
				
				lcd->state = LCD_STATE_DMA_0_END;
				break;
				
			case LCD_STATE_DMA_0_END:
				
				if(lcd->ldcmd0 & 0x00200000UL) lcd->lcsr |= 0x0100;	//set EOF is DMA 0 finished
				lcd->state = LCD_STATE_IDLE;
				break;
		}
	}
	pxa255lcdPrvUpdateInts(lcd);
}

void pxa255lcdInit(Pxa255lcd* lcd, Pxa255ic* ic){
	__mem_zero(lcd, sizeof(Pxa255lcd));
	
	lcd->ic = ic;
	lcd->intMask = UNMASKABLE_INTS;
}
