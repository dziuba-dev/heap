#pragma once
#include "Node.h"

template<class ValueType>
class Heap
{
private:
    Node<ValueType>* root;
    int size;
    int height;

    int calculateHeapHeight(int size);
    Node<ValueType>* insertValue(ValueType value, Node<ValueType>* node, int level);
    void rebuild(Node<ValueType>* node);
    void swapNodes(Node<ValueType>* node1, Node<ValueType>* node2);
    void deleteHeap(Node<ValueType>* node);

protected:
    bool virtual compare(Node<ValueType>* node, Node<ValueType>* toCompare) = 0;

public:
    Heap();
    virtual ~Heap();

    void show();
    void insertValue(ValueType value);
    void virtual build(ValueType values[]) = 0;
    ValueType virtual extract() = 0;
    ValueType virtual get() = 0;
};

template<class ValueType>
Heap<ValueType>::Heap() : size(0), height(0), root(nullptr) {}

template<class ValueType>
void Heap<ValueType>::insertValue(ValueType value) {
    size++;
    height = calculateHeapHeight(this->size);

    if (root == nullptr) {
        root = new Node<ValueType>(value);
    }
    else {
        Node<ValueType>* insertedNode = insertValue(value, root, 1);
        rebuild(insertedNode);
    }
}

template<class ValueType>
int Heap<ValueType>::calculateHeapHeight(int size) {
    return ceil(log2(size + 1));
}

template<class ValueType>
Node<ValueType>* Heap<ValueType>::insertValue(ValueType value, Node<ValueType>* node, int level){
    if (level == height - 1 && (node->left == nullptr || node->right == nullptr)) {
        return new Node<ValueType>(value, node);
    }
    else if (level == height - 1) {
        return nullptr;
    }

    Node<ValueType>* insertedNode = insertValue(value, node->left, level + 1);

    if (insertedNode == nullptr) {
        insertedNode = insertValue(value, node->right, level + 1);
    }

    return insertedNode;
}

template<class ValueType>
void Heap<ValueType>::rebuild(Node<ValueType>* node) {
    Node<ValueType>* nodeTemp = node;

    while (nodeTemp->parent != nullptr) {
        if (compare(nodeTemp, nodeTemp->parent)) {
            swapNodes(nodeTemp, nodeTemp->parent);
        }
        nodeTemp = nodeTemp->parent;
    }
}

template<class ValueType>
void Heap<ValueType>::swapNodes(Node<ValueType>* node1, Node<ValueType>* node2) {
    ValueType temp = node1->getValue();
    node1->setValue(node2->getValue());
    node2->setValue(temp);
}

template<class ValueType>
Heap<ValueType>::~Heap() {
    if (root != nullptr) {
        deleteHeap(root);
    }
}

template<class ValueType>
void Heap<ValueType>::deleteHeap(Node<ValueType>* node) {
    if (node->left == nullptr) {
        node->parent = nullptr;
        delete node;
        return;
    }

    deleteHeap(node->left);
    node->left = nullptr;

    if (node->right != nullptr) {
        deleteHeap(node->right);
        node->right = nullptr;
    }

    return;
}

template<class ValueType>
void Heap<ValueType>::show() {}