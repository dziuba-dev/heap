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

    Node(ValueType v);
    Node(ValueType v, Node<ValueType>* p);
    ~Node() = default;

    ValueType getValue();
    void setValue(ValueType v);

    friend std::ostream& operator<<(std::ostream& str, Node<ValueType>& n) {
        return (str << n.value);
    };
    friend std::ostream& operator<<(std::ostream& str, Node<ValueType>* n) {
        return (str << n->value);
    };
};

// Constructor with value
template<class ValueType>
Node<ValueType>::Node(ValueType v) : value(v), parent(nullptr), left(nullptr), right(nullptr) {}

// Constructor with value and pointer to parent node
template<class ValueType>
Node<ValueType>::Node(ValueType v, Node<ValueType>* p) : value(v), parent(p), left(nullptr), right(nullptr) {
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
void Node<ValueType>::setValue(ValueType v) {
    value = v;
}