#pragma once
#include "Heap.h"
#include <math.h>

template<class ValueType>
class MaxHeap : public Heap<ValueType> 
{
private:
    bool compare(Node<ValueType> node1, Node<ValueType> node2);

public:
    MaxHeap();
    ~MaxHeap() = default;

    void build(ValueType values[]);
    ValueType extract();
    ValueType get();
};

template<class ValueType>
MaxHeap<ValueType>::MaxHeap() {}

template<class ValueType>
void MaxHeap<ValueType>::build(ValueType values[]) {}

template<class ValueType>
bool MaxHeap<ValueType>::compare(Node<ValueType> node1, Node<ValueType> node2) {
    return node1 > node2;
}

template<class ValueType>
ValueType MaxHeap<ValueType>::extract() {
    return 0;
}

template<class ValueType>
ValueType MaxHeap<ValueType>::get() {
    return 0;
}
