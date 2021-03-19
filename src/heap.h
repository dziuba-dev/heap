#pragma once
#include "Node.h"

template<class ValueType>
class Heap
{
private:
    int heapSize;
    Node<ValueType>* root;

protected:
    void swapNodes(Node<ValueType>* node1, Node<ValueType>* node2);

public:
    Heap();
    virtual ~Heap() = default;

    void show();
    void virtual insertValue(ValueType value) = 0;
    void virtual build(ValueType values[]) = 0;
    ValueType virtual extract() = 0;
    ValueType virtual get() = 0;
};

template<class ValueType>
Heap<ValueType>::Heap() : heapSize(0), root(nullptr) {}

template<class ValueType>
void Heap<ValueType>::swapNodes(Node<ValueType>* node1, Node<ValueType>* node2) {}

template<class ValueType>
void Heap<ValueType>::show() {}