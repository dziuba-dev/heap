#pragma once
#include "Heap.h"

template<class ValueType>
class MaxHeap : public Heap<ValueType> 
{
public:
    MaxHeap();
    ~MaxHeap() = default;

    void insertValue(ValueType value);
    void build(ValueType values[]);
    ValueType extract();
    ValueType get();
};

template<class ValueType>
MaxHeap<ValueType>::MaxHeap() {}

template<class ValueType>
void MaxHeap<ValueType>::insertValue(ValueType value) {}

template<class ValueType>
void MaxHeap<ValueType>::build(ValueType values[]) {}

template<class ValueType>
ValueType MaxHeap<ValueType>::extract() {
    return 0;
}

template<class ValueType>
ValueType MaxHeap<ValueType>::get() {
    return 0;
}