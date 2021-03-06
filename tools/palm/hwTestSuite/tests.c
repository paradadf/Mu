#include <PalmOS.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "testSuite.h"
#include "testSuiteConfig.h"
#include "specs/dragonballVzRegisterSpec.h"
#include "specs/sed1376RegisterSpec.h"
#include "debug.h"
#include "tools.h"
#include "cpu.h"
#include "ugui.h"
#include "undocumentedApis.h"


var testButtonInput(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   uint8_t oldPkdata = readArbitraryMemory8(HW_REG_ADDR(PKDATA));
   
   if(firstRun){
      debugSafeScreenClear(C_WHITE);
      firstRun = false;
   }
   
   if(getButton(buttonUp) && !getButton(buttonDown)){
      firstRun = true;
      exitSubprogram();
   }
   
   UG_PutString(0, y, "Press Up but not Down to exit this test.");
   y += (FONT_HEIGHT + 1) * 2;
   
   UG_PutString(0, y, "This requirement is to allow button testing.");
   y += (FONT_HEIGHT + 1) * 2;
   
   writeArbitraryMemory8(HW_REG_ADDR(PKDATA), 0xC0 | oldPkdata & 0x1F);
   StrPrintF(sharedDataBuffer, "PKDATA Key Bits = 110");
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   writeArbitraryMemory8(HW_REG_ADDR(PKDATA), 0xA0 | oldPkdata & 0x1F);
   StrPrintF(sharedDataBuffer, "PKDATA Key Bits = 101");
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   writeArbitraryMemory8(HW_REG_ADDR(PKDATA), 0x60 | oldPkdata & 0x1F);
   StrPrintF(sharedDataBuffer, "PKDATA Key Bits = 011");
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   writeArbitraryMemory8(HW_REG_ADDR(PKDATA), oldPkdata);
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var listDataRegisters(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   StrPrintF(sharedDataBuffer, "PBDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PBDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PCDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PCDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PEDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PEDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PFDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PFDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PGDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PGDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PJDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PJDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PKDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PKDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PMDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PMDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var listRegisterFunctions(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   StrPrintF(sharedDataBuffer, "PBSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PBSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PCSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PCSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PESEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PESEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PFSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PFSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PGSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PGSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PJSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PJSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PKSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PKSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PMSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PMSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var listRegisterDirections(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   StrPrintF(sharedDataBuffer, "PBDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PBDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PCDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PCDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PEDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PEDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PFDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PFDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PGDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PGDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PJDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PJDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PKDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PKDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PMDIR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PMDIR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var checkSpi2EnableBitDelay(void){
   static Boolean firstRun = true;
   
   if(firstRun){
      uint16_t y = 0;
      uint16_t osSpi2Control = readArbitraryMemory16(HW_REG_ADDR(SPICONT2)) & 0xE030;/*use data rate, phase and polarity from OS*/
      
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      
      /*disable SPI2*/
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control);/*disable*/
      
      /*try to enable and shift at the same time*/
      writeArbitraryMemory16(HW_REG_ADDR(SPIDATA2), 0xD4 << 8);/*write control byte, 0xD4 means read channel 5 in 12 bit reference mode*/
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control | 0x0200/*enable*/ | 0x0100/*exchange*/ | 0x000F);/*enable + exchange*/
      while(readArbitraryMemory16(HW_REG_ADDR(SPICONT2)) & 0x0100);/*wait on transfer*/
      StrPrintF(sharedDataBuffer, "Enable + Shift:");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "SPIDATA2:0x%02X", readArbitraryMemory16(HW_REG_ADDR(SPIDATA2)));
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control);/*disable*/
      
      /*try to disable and shift at the same time*/
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control | 0x0200/*enable*/);/*enable*/
      writeArbitraryMemory16(HW_REG_ADDR(SPIDATA2), 0xD4 << 8);/*write control byte, 0xD4 means read channel 5 in 12 bit reference mode*/
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control | 0x0100/*exchange*/ | 0x000F);/*disable + exchange*/
      while(readArbitraryMemory16(HW_REG_ADDR(SPICONT2)) & 0x0100);/*wait on transfer*/
      StrPrintF(sharedDataBuffer, "Disable + Shift:");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "SPIDATA2:0x%02X", readArbitraryMemory16(HW_REG_ADDR(SPIDATA2)));
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      
      /*enable, shift then disable*/
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control | 0x0200/*enable*/);/*enable*/
      writeArbitraryMemory16(HW_REG_ADDR(SPIDATA2), 0xD4 << 8);/*write control byte, 0xD4 means read channel 5 in 12 bit reference mode*/
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control | 0x0200/*enable*/ | 0x0100/*exchange*/ | 0x000F);/*exchange*/
      while(readArbitraryMemory16(HW_REG_ADDR(SPICONT2)) & 0x0100);/*wait on transfer*/
      StrPrintF(sharedDataBuffer, "Enable, Shift, Disable:");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "SPIDATA2:0x%02X", readArbitraryMemory16(HW_REG_ADDR(SPIDATA2)));
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      writeArbitraryMemory16(HW_REG_ADDR(SPICONT2), osSpi2Control);/*disable*/
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var tstat1GetSemaphoreLockOrder(void){
   static Boolean firstRun = true;
   uint16_t testWriteValue = 0xF0F1;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   StrPrintF(sharedDataBuffer, "TSTAT1:0x%04X", readArbitraryMemory16(HW_REG_ADDR(TSTAT1)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   writeArbitraryMemory16(HW_REG_ADDR(TSTAT1), testWriteValue);
   StrPrintF(sharedDataBuffer, "Write TSTAT1:0x%04X", testWriteValue);
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "New TSTAT1:0x%04X", readArbitraryMemory16(HW_REG_ADDR(TSTAT1)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   writeArbitraryMemory16(HW_REG_ADDR(TSTAT1), 0xFFFF);
   StrPrintF(sharedDataBuffer, "Clear Semaphore");
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "New TSTAT1:0x%04X", readArbitraryMemory16(HW_REG_ADDR(TSTAT1)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var ads7846Read(void){
   static Boolean firstRun = true;
   static Boolean referenceMode;
   static Boolean mode8Bit;
   static uint16_t ads7846ChannelValues[8];
   static uint16_t touchDrawX;
   static uint16_t touchDrawY;
   uint8_t ads7846Channel;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      referenceMode = false;
      mode8Bit = false;
      memset(ads7846ChannelValues, 0x00, 8 * sizeof(uint16_t));
      touchDrawX = 0xFFFF;
      touchDrawY = 0xFFFF;
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonSelect)){
      if(!referenceMode && !mode8Bit){
         referenceMode = true;
      }
      else if(referenceMode && !mode8Bit){
         referenceMode = false;
         mode8Bit = true;
      }
      else if(!referenceMode && mode8Bit){
         referenceMode = true;
      }
      else{
         referenceMode = false;
         mode8Bit = false;
      }
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   if(getButton(buttonLeft)){
      for(ads7846Channel = 0; ads7846Channel < 8; ads7846Channel++)
         ads7846ChannelValues[ads7846Channel] = ads7846GetValue(ads7846Channel, referenceMode, mode8Bit);
      
      touchDrawX = (1.0 - (float)(ads7846ChannelValues[5]) / 0xFFF) * 160;
      touchDrawY = (1.0 - (float)(ads7846ChannelValues[1]) / 0xFFF) * 220;
   }
   
   StrPrintF(sharedDataBuffer, "Left To Refresh");
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "Select To Change Mode");
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "Ref Mode:%d, 8bit:%d", referenceMode, mode8Bit);
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   for(ads7846Channel = 0; ads7846Channel < 8; ads7846Channel++){
      StrPrintF(sharedDataBuffer, "Ch:%d Value:0x%04X", ads7846Channel, ads7846ChannelValues[ads7846Channel]);
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
   }
   
   /*show estimated touch coord*/
   if(touchDrawX < 160 && touchDrawY < 220)
      UG_DrawPixel(touchDrawX, touchDrawY, C_BLACK);
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var ads7846ReadOsVersion(void){
   static Boolean firstRun = true;
   static uint16_t mode;
   uint8_t ads7846Channel;
   uint16_t channelData[8];
   uint16_t y = 0;
   
   
   if(firstRun){
      firstRun = false;
      mode = 0;
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonSelect)){
      mode++;/*modes 0-8 are valid, 9 is to test invalid args*/
      if(mode > 9)
         mode = 0;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   memset(channelData, 0x00, 8 * sizeof(uint16_t));
   customCall_HwrADC(mode, channelData);
   
   StrPrintF(sharedDataBuffer, "Mode:%d", mode);
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   for(ads7846Channel = 0; ads7846Channel < 8; ads7846Channel++){
      StrPrintF(sharedDataBuffer, "Ch:%d Value:0x%04X", ads7846Channel, channelData[ads7846Channel]);
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var getClk32Frequency(void){
   static Boolean firstRun = true;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      StrPrintF(sharedDataBuffer, "CLK32 Freq:%s", (readArbitraryMemory16(HW_REG_ADDR(RTCCTL)) & 0x0020) ? "38.4khz" : "32.7khz");
      UG_PutString(0, 0, sharedDataBuffer);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var getDeviceInfo(void){
   static Boolean firstRun = true;
   
   if(firstRun){
      char deviceId[5];
      uint16_t y = 0;
      
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      FtrGet(sysFtrCreator, sysFtrNumOEMDeviceID, deviceId);
      deviceId[4] = '\0';/*Palm OS sprintf doesnt support %.*s string length modifyers*/
      StrPrintF(sharedDataBuffer, "Device ID:%s", &deviceId);
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "OS String:%s", SysGetOSVersionString());
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var getCpuInfo(void){
   static Boolean firstRun = true;
   
   if(firstRun){
      uint16_t y = 0;
      
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      StrPrintF(sharedDataBuffer, "CPU Type:%s", getCpuString());
      UG_PutString(0, y, sharedDataBuffer);
      y += (FONT_HEIGHT + 1) * 5;
      StrPrintF(sharedDataBuffer, "SCR:0x%02X", readArbitraryMemory8(HW_REG_ADDR(SCR)));
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "CPU ID(IDR):0x%08lX", readArbitraryMemory32(HW_REG_ADDR(IDR)));
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var getInterruptInfo(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   
   if(firstRun){
      debugSafeScreenClear(C_WHITE);
      firstRun = false;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }

   StrPrintF(sharedDataBuffer, "IMR:0x%08lX", readArbitraryMemory32(HW_REG_ADDR(IMR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "IPR:0x%08lX", readArbitraryMemory32(HW_REG_ADDR(IPR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "ISR:0x%08lX", readArbitraryMemory32(HW_REG_ADDR(ISR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "ILCR:0x%04X", readArbitraryMemory16(HW_REG_ADDR(ILCR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "ICR:0x%04X", readArbitraryMemory16(HW_REG_ADDR(ICR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDIRQEN:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDIRQEN)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDIRQEG:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDIRQEG)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDKBEN:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PDKBEN)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var getIcrInversion(void){
   static Boolean firstRun = true;
   uint16_t oldIcr;
   uint8_t portDValues[2];
   uint16_t y = 0;
   
   if(firstRun){
      debugSafeScreenClear(C_WHITE);
      firstRun = false;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   turnInterruptsOff();
   oldIcr = readArbitraryMemory16(HW_REG_ADDR(ICR));
   
   /*not inverted*/
   portDValues[0] = readArbitraryMemory8(HW_REG_ADDR(PDDATA));
   
   writeArbitraryMemory16(HW_REG_ADDR(ICR), oldIcr | 0xF000);
   
   /*inverted*/
   portDValues[1] = readArbitraryMemory8(HW_REG_ADDR(PDDATA));
   
   writeArbitraryMemory16(HW_REG_ADDR(ICR), oldIcr);
   
   turnInterruptsOn();
   
   StrPrintF(sharedDataBuffer, "PDDATA Normal:0x%02X", portDValues[0]);
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PDDATA Inverted:0x%02X", portDValues[1]);
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var doesIsrClearChangePinValue(void){
   static Boolean firstRun = true;
   
   if(firstRun){
      uint8_t oldPdirqeg;
      uint8_t oldPdirqen;
      uint16_t y = 0;
      Boolean testSd;
      
      turnInterruptsOff();
      
      debugSafeScreenClear(C_WHITE);
      
      StrPrintF(sharedDataBuffer, "Select = Test SD");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "Back = Skip SD");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      forceFrameRedraw();
      while(true){
         testSd = readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x0C;
         if(testSd)
            break;
      }
      
      /*test if SD pin is cleared on write to ICR*/
      if(testSd & 0x08){
         uint16_t oldIcr = readArbitraryMemory16(HW_REG_ADDR(ICR));
         
         debugSafeScreenClear(C_WHITE);
         y = 0;
         
         if(!(readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20)){
            StrPrintF(sharedDataBuffer, "Remove SD Card");
            UG_PutString(0, y, sharedDataBuffer);
            y += FONT_HEIGHT + 1;
            forceFrameRedraw();
            while(!(readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20));/*SD is still inserted*/
         }
         
         /*set to edge triggered mode and reset IRQ2, trigger on insert event*/
         writeArbitraryMemory16(HW_REG_ADDR(ICR), (oldIcr | 0x0400) & 0xBFFF);
         writeArbitraryMemory32(HW_REG_ADDR(ISR), 0x00020000);
         StrPrintF(sharedDataBuffer, "IRQ2 Pin:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20) ? "true " : "false");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         StrPrintF(sharedDataBuffer, "ISR IRQ2:%s", (readArbitraryMemory32(HW_REG_ADDR(ISR)) & 0x00020000) ? "true " : "false");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         forceFrameRedraw();
         
         StrPrintF(sharedDataBuffer, "Insert SD Card");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         forceFrameRedraw();
         while(readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20);/*SD is not inserted*/
         StrPrintF(sharedDataBuffer, "IRQ2 Pin:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20) ? "true " : "false");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         StrPrintF(sharedDataBuffer, "ISR IRQ2:%s", (readArbitraryMemory32(HW_REG_ADDR(ISR)) & 0x00020000) ? "true " : "false");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         
         writeArbitraryMemory32(HW_REG_ADDR(ISR), 0x00020000);
         StrPrintF(sharedDataBuffer, "IRQ2 Cleared");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         StrPrintF(sharedDataBuffer, "IRQ2 Pin:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20) ? "true " : "false");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         StrPrintF(sharedDataBuffer, "ISR IRQ2:%s", (readArbitraryMemory32(HW_REG_ADDR(ISR)) & 0x00020000) ? "true " : "false");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         
         StrPrintF(sharedDataBuffer, "Select = Continue");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         forceFrameRedraw();
         while(!(readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x08));
         
         writeArbitraryMemory16(HW_REG_ADDR(ICR), oldIcr);
      }
      
      /*test if Notes button pin is cleared on write to ICR*/
      debugSafeScreenClear(C_WHITE);
      y = 0;
      
      oldPdirqeg = readArbitraryMemory8(HW_REG_ADDR(PDIRQEG));
      oldPdirqen = readArbitraryMemory8(HW_REG_ADDR(PDIRQEN));
      
      if(readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x08){
         StrPrintF(sharedDataBuffer, "Release Select");
         UG_PutString(0, y, sharedDataBuffer);
         y += FONT_HEIGHT + 1;
         forceFrameRedraw();
         while(readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x08);
      }
      
      /*set to edge triggered mode and reset INT3, trigger on button down*/
      writeArbitraryMemory8(HW_REG_ADDR(PKDATA), readArbitraryMemory8(HW_REG_ADDR(PKDATA)) & 0x1F);/*enable all button rows*/
      writeArbitraryMemory8(HW_REG_ADDR(PDIRQEN), 0x00);/*turn INT* off first to prevent glitches*/
      writeArbitraryMemory8(HW_REG_ADDR(PDIRQEG), 0x0F);
      writeArbitraryMemory8(HW_REG_ADDR(PDIRQEN), 0x0F);
      writeArbitraryMemory32(HW_REG_ADDR(ISR), 0x00000800);/*clear any interrupt that may have triggered*/
      StrPrintF(sharedDataBuffer, "INT3 Pin:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x08) ? "true " : "false");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "ISR INT3:%s", (readArbitraryMemory32(HW_REG_ADDR(ISR)) & 0x00000800) ? "true " : "false");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      
      StrPrintF(sharedDataBuffer, "Press Select");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      forceFrameRedraw();
      while(!(readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x08));
      /*
      StrPrintF(sharedDataBuffer, "Release Select");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "3sec Wait");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      forceFrameRedraw();
      SysTaskDelay(SysTicksPerSecond() * 3);
      */
      StrPrintF(sharedDataBuffer, "INT3 Pin:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x08) ? "true " : "false");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "ISR INT3:%s", (readArbitraryMemory32(HW_REG_ADDR(ISR)) & 0x00000800) ? "true " : "false");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      
      writeArbitraryMemory32(HW_REG_ADDR(ISR), 0x00000800);
      StrPrintF(sharedDataBuffer, "INT3 Cleared");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "INT3 Pin:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x08) ? "true " : "false");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "ISR INT3:%s", (readArbitraryMemory32(HW_REG_ADDR(ISR)) & 0x00000800) ? "true " : "false");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      
      forceFrameRedraw();
      
      writeArbitraryMemory8(HW_REG_ADDR(PDIRQEG), oldPdirqeg);
      writeArbitraryMemory8(HW_REG_ADDR(PDIRQEN), oldPdirqen);
      
      turnInterruptsOn();
      
      firstRun = false;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var toggleBacklight(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      StrPrintF(sharedDataBuffer, "Left = SED1376");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "Right = Port G");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      StrPrintF(sharedDataBuffer, "Select = Port K");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   if(getButtonPressed(buttonLeft)){
      writeArbitraryMemory8(0x1FF80000 + GPIO_CONT_0, readArbitraryMemory8(0x1FF80000 + GPIO_CONT_0) ^ 0x10);
   }
   
   if(getButtonPressed(buttonRight)){
      writeArbitraryMemory8(HW_REG_ADDR(PGDATA), readArbitraryMemory8(HW_REG_ADDR(PGDATA)) ^ 0x02);
   }
   
   if(getButtonPressed(buttonSelect)){
      writeArbitraryMemory8(HW_REG_ADDR(PKDATA), readArbitraryMemory8(HW_REG_ADDR(PKDATA)) ^ 0x02);
   }
   
   y = (FONT_HEIGHT + 1) * 3;
   StrPrintF(sharedDataBuffer, "PGDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PGDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PKDATA:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PKDATA)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PGSEL:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PGSEL)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PGPUEN:0x%02X", readArbitraryMemory8(HW_REG_ADDR(PGPUEN)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var toggleMotor(void){
   static Boolean firstRun = true;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      StrPrintF(sharedDataBuffer, "Select = Toggle Motor");
      UG_PutString(0, 0, sharedDataBuffer);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   if(getButtonPressed(buttonSelect)){
      writeArbitraryMemory8(HW_REG_ADDR(PKDATA), readArbitraryMemory8(HW_REG_ADDR(PKDATA)) ^ 0x10);
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var toggleAlarmLed(void){
   static Boolean firstRun = true;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      StrPrintF(sharedDataBuffer, "Select = Toggle Alarm LED");
      UG_PutString(0, 0, sharedDataBuffer);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   if(getButtonPressed(buttonSelect)){
      writeArbitraryMemory8(HW_REG_ADDR(PBDATA), readArbitraryMemory8(HW_REG_ADDR(PBDATA)) ^ 0x40);
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var watchPenIrq(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      writeArbitraryMemory8(HW_REG_ADDR(PFDIR), readArbitraryMemory8(HW_REG_ADDR(PFDIR)) & 0xFD);
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   if(getButtonPressed(buttonSelect)){
      writeArbitraryMemory16(HW_REG_ADDR(ICR), readArbitraryMemory16(HW_REG_ADDR(ICR)) ^ 0x0080);
   }
   
   StrPrintF(sharedDataBuffer, "Select = Toggle ICR POL5");
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "IPR:0x%08lX", readArbitraryMemory32(HW_REG_ADDR(IPR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "ICR:0x%02X", readArbitraryMemory16(HW_REG_ADDR(ICR)));
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "PENIRQ State:%s", (readArbitraryMemory8(HW_REG_ADDR(PFDATA)) & 0x02) ? "true " : "false");/*"true " needs the space to clear the e from "false"*/
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var getPenPosition(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   PointType rawPen;
   PointType screenPen;
   
   if(firstRun){
      firstRun = false;
      writeArbitraryMemory8(HW_REG_ADDR(PFDIR), readArbitraryMemory8(HW_REG_ADDR(PFDIR)) & 0xFD);
      debugSafeScreenClear(C_WHITE);
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   PenGetRawPen(&rawPen);
   screenPen = rawPen;
   PenRawToScreen(&screenPen);
   
   StrPrintF(sharedDataBuffer, "Raw X:%d    ", rawPen.x);/*"true " needs the space to clear the e from "false"*/
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "Raw Y:%d    ", rawPen.y);/*"true " needs the space to clear the e from "false"*/
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "Screen X:%d    ", screenPen.x);/*"true " needs the space to clear the e from "false"*/
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   StrPrintF(sharedDataBuffer, "Screen Y:%d    ", screenPen.y);/*"true " needs the space to clear the e from "false"*/
   UG_PutString(0, y, sharedDataBuffer);
   y += FONT_HEIGHT + 1;
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var playConstantTone(void){
   /*static const uint16_t testFreq = 10000;*/
   static const uint8_t samples[10] = {0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0x90, 0x80, 0x70, 0x60};/*this buffer needs to pe played testFreq times a second*/
   static Boolean firstRun = true;
   static uint8_t count;
#if 0
   uint32_t basePwm1ClockSpeed = 33161216 / 1/*REPEAT*/ / 2/*CLKSEL*/;
   uint32_t neededPwm1ClockSpeed = (uint32_t)testFreq * 0xFF/*period*/ * 10/*samples*/;
   uint8_t prescaler = basePwm1ClockSpeed / neededPwm1ClockSpeed
#endif
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      StrPrintF(sharedDataBuffer, "Squealing In Progress");
      UG_PutString(0, 0, sharedDataBuffer);
      forceFrameRedraw();
      writeArbitraryMemory16(HW_REG_ADDR(PWMC1), 0x0F10);
      writeArbitraryMemory8(HW_REG_ADDR(PWMP1), 0xFF);
      count = 0;
   }
   
   while(true){
      while(readArbitraryMemory16(HW_REG_ADDR(PWMC1)) & 0x0020){
         /*add audio samples*/
         writeArbitraryMemory8(HW_REG_ADDR(PWMS1 + 1), samples[count]);
         count++;
         if(count >= 10)
            count = 0;
      }
      
      if(KeyCurrentState() & buttonBack)
         break;
   }
   
   writeArbitraryMemory16(HW_REG_ADDR(PWMC1), 0x0000);
   firstRun = true;
   exitSubprogram();
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var unaligned32bitAccess(void){
   static Boolean firstRun = true;

   if(firstRun){
      uint8_t buffer[10];
      uint8_t* align16Buffer = buffer;
      uint32_t* test;
      
      //make sure its 16 bit aligned but not 32 bit aligned
      while(((uint32_t)align16Buffer & 0x3) != 0x2)
         align16Buffer++;
      
      test = align16Buffer;
      
      *test = 0xF1EAF1EA;
      if(*test == 0xF1EAF1EA){
         debugSafeScreenClear(C_WHITE);
         StrPrintF(sharedDataBuffer, "It works!");
         UG_PutString(0, 0, sharedDataBuffer);
      }
      
      firstRun = false;
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }

   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var isIrq2AttachedToSdCardChipSelect(void){
   static Boolean firstRun = true;
   uint16_t y = 0;
   
   if(firstRun){
      firstRun = false;
      debugSafeScreenClear(C_WHITE);
      
      turnInterruptsOff();
      
      StrPrintF(sharedDataBuffer, "IRQ2 value:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20) ? "true " : "false");/*"true " needs the space to clear the e from "false"*/
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      
      writeArbitraryMemory8(HW_REG_ADDR(PJDATA), readArbitraryMemory8(HW_REG_ADDR(PJDATA)) ^ 0x08);
      StrPrintF(sharedDataBuffer, "Chip Select Toggled");
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      
      StrPrintF(sharedDataBuffer, "IRQ2 value:%s", (readArbitraryMemory8(HW_REG_ADDR(PDDATA)) & 0x20) ? "true " : "false");/*"true " needs the space to clear the e from "false"*/
      UG_PutString(0, y, sharedDataBuffer);
      y += FONT_HEIGHT + 1;
      
      writeArbitraryMemory8(HW_REG_ADDR(PJDATA), readArbitraryMemory8(HW_REG_ADDR(PJDATA)) ^ 0x08);/*restore old chip select state*/
      turnInterruptsOn();
   }
   
   if(getButtonPressed(buttonBack)){
      firstRun = true;
      exitSubprogram();
   }
   
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}

var callSysUnimplemented(void){
   /*used to test the SysUnimplemented handler in MuExpDriver*/
   SysUnimplemented();
   return makeVar(LENGTH_0, TYPE_NULL, 0);
}
