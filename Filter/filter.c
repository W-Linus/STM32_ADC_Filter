#include <filter.h>

uint8_t filterCounter=0;
uint32_t filterBuffer[FILTER_BUFFER_SIZE];

uint32_t filteredData;


uint8_t FilterDataAcquire(uint32_t data){
    if(filterCounter<FILTER_BUFFER_SIZE){
        filterBuffer[filterCounter]=data;
        filterCounter++;
        return 0;
    }else{
        qsort(filterBuffer,FILTER_BUFFER_SIZE,sizeof(filterBuffer[0]),cmp);
        filterCounter=0;
        return 1;
    }
}

uint8_t Filter(uint32_t data,uint32_t *result){
    if(FilterDataAcquire(data)){
        filteredData=DataCompute(filterBuffer,FILTER_BUFFER_SIZE);
        *result=filteredData;
        return 1;
    }else{
        return 0;
    }
}


int cmp(const void* a,const void* b){
    return *(int*)a - *(int*)b;
}


uint32_t DataCompute(uint32_t *originDataBuffer,uint16_t size){
    uint32_t calcTemp=0;
    double resultTemp=0;
    for(uint32_t i=2;i<size-2;i++){
        calcTemp+=originDataBuffer[i];
    }
    resultTemp=calcTemp/((size-4)*1.0);
    return (uint32_t)resultTemp;
}