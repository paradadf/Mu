#ifndef FLX68000_H
#define FLX68000_H

#include <stdint.h>
#include <stdbool.h>

void flx68000Reset(void);
uint32_t flx68000StateSize(void);
void flx68000SaveState(uint8_t* data);
void flx68000LoadState(uint8_t* data);
void flx68000LoadStateFinished(void);

void flx68000Execute(int32_t cycles);
void flx68000SetIrq(uint8_t irqLevel);
bool flx68000IsSupervisor(void);
void flx68000BusError(uint32_t address, bool isWrite);

uint32_t flx68000GetRegister(uint8_t reg);//only for debugging
#define flx68000GetPc() flx68000GetRegister(29/*M68K_REG_PPC*/)//only for debugging
uint64_t flx68000ReadArbitraryMemory(uint32_t address, uint8_t size);//only for debugging

#endif
