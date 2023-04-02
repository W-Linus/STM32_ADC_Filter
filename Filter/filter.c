#include <filter.h>

/// @brief 队列计数器
uint8_t filterCounter=0;

/// @brief 原始数据队列数组
uint32_t filterBuffer[FILTER_BUFFER_SIZE];

/// @brief 滤波后数据
uint32_t filteredData;


/// @brief 获取ADC原始值，将其填入待处理队列。队列满了以后对队列中数据进行快速排序
/// @param data ADC原始采样值
/// @return 队列是否已满
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

/// @brief ADC滤波主函数，实际使用中只需要调用这个即可
/// @param data 需要进入队列滤波的ADC原始值
/// @param result 用于返回的滤波后结果，通过传地址方式直接获取数据
/// @return 滤波是否完成，完成后可直接使用返回结果
uint8_t Filter(uint32_t data,uint32_t *result){
    if(FilterDataAcquire(data)){
        filteredData=DataCompute(filterBuffer,FILTER_BUFFER_SIZE);
        *result=filteredData;
        return 1;
    }else{
        return 0;
    }
}


/// @brief std库快速排序所需的比较函数
/// @param a 
/// @param b 
/// @return 
int cmp(const void* a,const void* b){
    return *(int*)a - *(int*)b;
}


/// @brief 滤波核心程序，使用的是中位值平均滤波法。此算法有利于抑制脉冲性干扰，缺点在于占用RAM较大，计算时间较长。
/// @param originDataBuffer 原始数据队列
/// @param size 原始数据队列长度，用于算平均值
/// @return 滤波后结果
uint32_t DataCompute(uint32_t *originDataBuffer,uint16_t size){
    uint32_t calcTemp=0;
    double resultTemp=0;
    for(uint32_t i=2;i<size-2;i++){
        calcTemp+=originDataBuffer[i];
    }
    resultTemp=calcTemp/((size-4)*1.0);
    return (uint32_t)resultTemp;
}