#ifndef __FILTER_H_
#define __FILTER_H_

#include <main.h>

#define FILTER_BUFFER_SIZE 40

uint8_t Filter(uint32_t data,uint32_t *result);

uint8_t FilterDataAcquire(uint32_t data);

uint32_t DataCompute(uint32_t *originDataBuffer,uint16_t size);

int cmp(const void* a,const void* b);


#endif
