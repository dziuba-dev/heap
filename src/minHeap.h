#pragma once
#include "Heap.h"

template<class ValueType>
class MinHeap : public Heap<ValueType>
{
private:
    bool compare(Node<ValueType>* node1, Node<ValueType>* node2);

public:
    MinHeap();
    ~MinHeap() = default;

    void build(ValueType values[]);
    ValueType extract();
    ValueType get();
};

template<class ValueType>
MinHeap<ValueType>::MinHeap() {}

template<class ValueType>
bool MinHeap<ValueType>::compare(Node<ValueType>* node1, Node<ValueType>* node2) {
    return node1->lessThan(node2);
}

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