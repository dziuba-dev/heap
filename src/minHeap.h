#pragma once
#include "Heap.h"

template<class ValueType>
class MinHeap : public Heap<ValueType>
{
public:
    MinHeap();
    ~MinHeap() = default;

    void insertValue(ValueType value);
    void build(ValueType values[]);
    ValueType extract();
    ValueType get();
};

template<class ValueType>
MinHeap<ValueType>::MinHeap() {}

template<class ValueType>
void MinHeap<ValueType>::insertValue(ValueType value) {}

template<class ValueType>
void MinHeap<ValueType>::build(ValueType values[]) {}

template<class ValueType>
ValueType MinHeap<ValueType>::extract() {
    return 0;
}

template<class ValueType>
ValueType MinHeap<ValueType>::get() {
    return 0;
}