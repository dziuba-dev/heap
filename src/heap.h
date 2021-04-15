#pragma once
#include "Node.h"
#include <string>
#include <windows.h>

template<class ValueType>
class Heap
{
private:
    Node<ValueType>* root;
    int heapSize;
    int height;

    int calculateHeapHeight(int size);
    Node<ValueType>* addNode(ValueType value, Node<ValueType>* node, int level);
    void rebuild(Node<ValueType>* node);
    void swapNodes(Node<ValueType>* node1, Node<ValueType>* node2);
    void deleteHeap(Node<ValueType>* node);
    void showNode(Node<ValueType>* node, int level, int widthStart, int widthEnd, int maxNodeWidth);
    int maxValueWidth(Node<ValueType>* node);

protected:
    bool virtual compare(Node<ValueType> node1, Node<ValueType> node2) = 0;

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
Heap<ValueType>::Heap() : heapSize(0), height(0), root(nullptr) {}

template<class ValueType>
void Heap<ValueType>::insertValue(ValueType value) {
    if (root == nullptr) {
        heapSize = 1;
        height = calculateHeapHeight(heapSize);
        root = new Node<ValueType>(value);
    }
    else {
        heapSize++;
        height = calculateHeapHeight(heapSize);
        Node<ValueType>* insertedNode = addNode(value, root, 1);
        rebuild(insertedNode);
    }
}

template<class ValueType>
int Heap<ValueType>::calculateHeapHeight(int size) {
    return ceil(log2(size + 1));
}

template<class ValueType>
Node<ValueType>* Heap<ValueType>::addNode(ValueType value, Node<ValueType>* node, int level){
    if (level == height - 1 && (node->left == nullptr || node->right == nullptr)) {
        return new Node<ValueType>(value, node);
    }
    else if (level == height - 1) {
        return nullptr;
    }

    Node<ValueType>* insertedNode = addNode(value, node->left, level + 1);

    if (insertedNode == nullptr) {
        insertedNode = addNode(value, node->right, level + 1);
    }

    return insertedNode;
}

template<class ValueType>
void Heap<ValueType>::rebuild(Node<ValueType>* node) {
    Node<ValueType>* nodeTemp = node;

    while (nodeTemp->parent != nullptr) {
        if (compare(*nodeTemp, *(nodeTemp->parent))) {
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
        delete node;
        return;
    }

    deleteHeap(node->left);

    if (node->right != nullptr) {
        deleteHeap(node->right);
    }

    delete node;

    return;
}

void goToXY(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int valueWidth (std::string value) {
    return value.length();
}

int valueWidth(int value) {
    return std::to_string(value).length();
}

int valueWidth(float value) {
    return std::to_string(value).length();
}

template<class ValueType>
void Heap<ValueType>::show() {
    int height = ceil(log2(heapSize + 1));
    int maxNodesInRow = pow(2, (height - 1));
    int maxNodeWidth = maxValueWidth(root);
    int spacesBetweenNodes = maxNodesInRow + 1;
    int width = (maxNodesInRow + spacesBetweenNodes) * maxNodeWidth;
    showNode(root, 1, 1, width, maxNodeWidth);
    goToXY(0, height * 2 + 2);
}

template<class ValueType>
void Heap<ValueType>::showNode(Node<ValueType>* node, int level, int widthStart, int widthEnd, int maxNodeWidth) {
    if (node != nullptr) {
        int widthMiddle = (widthStart + widthEnd) / 2;
        int nodeWidth = valueWidth(node->getValue());
        int spaceBeforeValue = (maxNodeWidth - nodeWidth) / 2;

        goToXY((widthMiddle + spaceBeforeValue), (2 * level));
        std::cout << node;

        if (node->left != nullptr) {
            goToXY((widthMiddle - 1), (2 * level + 1));
            std::cout << '/';

            showNode(node->left, level+1, widthStart, widthMiddle, maxNodeWidth);
        }

        if (node->right != nullptr) {
            goToXY((widthMiddle + maxNodeWidth), (2 * level + 1));
            std::cout << '\\';

            showNode(node->right, level+1, widthMiddle, widthEnd, maxNodeWidth);
        }
    }
}

template<class ValueType>
int Heap<ValueType>::maxValueWidth(Node<ValueType>* node) {
    if (node != nullptr) {
        int nodeWidth = valueWidth(node->getValue());
        int leftWidth = maxValueWidth(node->left);
        int rightWidth = maxValueWidth(node->right);
        return max(nodeWidth, max(leftWidth, rightWidth));
    }
    else {
        return 0;
    }
}