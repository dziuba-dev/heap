#pragma once
#include "Node.h"
#include <string>
#include <windows.h>
#include <string>
#include <windows.h>

template<class ValueType>
class Heap
{
private:
    Node<ValueType>* root;
    int heapSize;
    ValueType defaultValue;

    int calculateHeapHeight(int size);
    Node<ValueType>* addNode(ValueType value, Node<ValueType>* node, int level);
    void rebuild(Node<ValueType>* node);
    void swapNodes(Node<ValueType>* node1, Node<ValueType>* node2);
    void deleteHeap(Node<ValueType>* node);
    Node<ValueType>* findNodeByOrder(std::string orderNumber, Node<ValueType>* node);
    void heapDown(Node<ValueType>* node);
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
    ValueType extract();
    ValueType virtual get() = 0;
};

template<class ValueType>
Heap<ValueType>::Heap() : heapSize(0), root(nullptr) {}

template<class ValueType>
void Heap<ValueType>::insertValue(ValueType value) {
    if (root == nullptr) {
        heapSize = 1;
        root = new Node<ValueType>(value);
    }
    else {
        heapSize++;
        Node<ValueType>* insertedNode = addNode(value, root, 1);
        rebuild(insertedNode);
    }
}

template<class ValueType>
int Heap<ValueType>::calculateHeapHeight(int size) {
    return ceil(log2(size + 1));
}

template<class ValueType>
Node<ValueType>* Heap<ValueType>::addNode(ValueType value, Node<ValueType>* node, int level) {
    int height = calculateHeapHeight(heapSize);
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
void Heap<ValueType>::show() {}


std::string decimalToBinary(int number) {
    std::string binaryNumber = "";
    int rest;

    while (number > 0) {
        rest = number % 2;
        number /= 2;
        binaryNumber = std::to_string(rest) + binaryNumber;
    }
    return binaryNumber;
}


template<class ValueType>
ValueType Heap<ValueType>::extract() {
    if (heapSize > 1) {
        ValueType rootValue = root->getValue();
        std::string binaryNumber = decimalToBinary(heapSize);
        binaryNumber.erase(0, 1);
        Node<ValueType>* lastNode = findNodeByOrder(binaryNumber, root);

        swapNodes(lastNode, root);
        Node<ValueType>* lastNodeParent = lastNode->parent;
        if (lastNodeParent->right != nullptr) {
            lastNodeParent->right = nullptr;
        }
        else {
            lastNodeParent->left = nullptr;
        }
        delete lastNode;
        heapSize--;

        heapDown(root);
        return rootValue;
    }
    else if (heapSize == 1) {
        ValueType rootValue = root->getValue();
        delete root;
        root = nullptr;
        heapSize--;
        return rootValue;
    }
    else {
        return defaultValue;
    }
}


template<class ValueType>
Node<ValueType>* Heap<ValueType>::findNodeByOrder(std::string orderNumber, Node<ValueType>* node) {
    if (orderNumber.length() == 0) {
        return node;
    }
    else if (orderNumber[0] == '0') {
        orderNumber.erase(0, 1);
        return findNodeByOrder(orderNumber, node->left);
    }
    else {
        orderNumber.erase(0, 1);
        return findNodeByOrder(orderNumber, node->right);
    }
}


template<class ValueType>
void Heap<ValueType>::heapDown(Node<ValueType>* node) {
    if (node != nullptr) {
        if (node->left != nullptr && compare(*(node->left), *node)) {
            if (node->right != nullptr && compare(*(node->left), *(node->right)) || node->right == nullptr) {
                swapNodes(node->left, node);
                heapDown(node->left);
                return;
            }
        }

        if (node->right != nullptr && compare(*(node->right), *node)) {
            if (node->left != nullptr && !compare(*(node->left), *(node->right))) {
                swapNodes(node->right, node);
                heapDown(node->right);
                return;
            }
        }
    }
}

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