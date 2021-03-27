#pragma once
#include<iostream>

template<class ValueType>
class Node
{
private:
    ValueType value;

public:
    Node* parent;
    Node* left;
    Node* right;

    Node(ValueType nodeValue);
    Node(ValueType nodeValue, Node<ValueType>* nodeParent);
    ~Node() = default;

    ValueType getValue();
    void setValue(ValueType newValue);

    bool operator>(Node<ValueType>& node) {
        return value > node.value;
    }

    bool operator<(Node<ValueType>& node) {
        return value < node.value;
    }

    friend std::ostream& operator<<(std::ostream& stream, Node<ValueType>& node) {
        return (stream << node.value);
    };

    friend std::ostream& operator<<(std::ostream& stream, Node<ValueType>* node) {
        return (stream << node->value);
    };
};

// Constructor with value
template<class ValueType>
Node<ValueType>::Node(ValueType nodeValue) 
    : value(nodeValue), parent(nullptr), left(nullptr), right(nullptr) {}

// Constructor with value and pointer to parent node
template<class ValueType>
Node<ValueType>::Node(ValueType nodeValue, Node<ValueType>* nodeParent) 
    : value(nodeValue), parent(nodeParent), left(nullptr), right(nullptr) {
    if (parent->left == nullptr) {
        parent->left = this;
    }
    else if (parent->right == nullptr) {
        parent->right = this;
    }
    else {
        throw "Added 3rd child to a Node";
    }
}

// Return node value
template<class ValueType>
ValueType Node<ValueType>::getValue() {
    return value;
}

// Change node value
template<class ValueType>
void Node<ValueType>::setValue(ValueType newValue) {
    value = newValue;
}