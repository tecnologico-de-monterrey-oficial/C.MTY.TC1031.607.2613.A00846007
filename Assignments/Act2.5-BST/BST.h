// Ian Armando Borde Escobar - A00846007

#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include "NodeT.h"

template <typename T>
class BST {
private:
    NodeT<T>* root;
    void clear(NodeT<T>* node);
    NodeT<T>* clone(const NodeT<T>* node);
    void printTree(const NodeT<T>* node, std::string prefix, bool isRight, bool isRoot) const;
    void preOrder(const NodeT<T>* node) const;
    void inOrder(const NodeT<T>* node) const;
    void postOrder(const NodeT<T>* node) const;
    void levelOrder() const;
    int height(const NodeT<T>* node) const;

public:
    BST() : root(nullptr) {}
    BST(const BST<T>& other) : root(clone(other.root)) {}
    BST<T>& operator=(const BST<T>& other);
    ~BST() { clear(root); }
    void insert(const T& data);
    bool find(const T& data) const;
    void remove(const T& data);
    void print() const;
    void visit(int method) const;
    void visit(const std::string& method) const;
    int height() const;
    void ancestors(const T& data) const;
    int whatLevelAmI(const T& data) const;
};

template <typename T>
void BST<T>::clear(NodeT<T>* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
NodeT<T>* BST<T>::clone(const NodeT<T>* node) {
    if (node == nullptr) return nullptr;
    NodeT<T>* copy = new NodeT<T>(node->data);
    try {
        copy->left = clone(node->left);
        copy->right = clone(node->right);
    } catch (...) {
        clear(copy);
        throw;
    }
    return copy;
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& other) {
    if (this != &other) {
        NodeT<T>* copy = clone(other.root);
        clear(root);
        root = copy;
    }
    return *this;
}

template <typename T>
void BST<T>::insert(const T& data) {
    NodeT<T>** link = &root;
    while (*link != nullptr) {
        if ((*link)->data == data) return;
        link = (data < (*link)->data) ? &(*link)->left : &(*link)->right;
    }
    *link = new NodeT<T>(data);
}

template <typename T>
bool BST<T>::find(const T& data) const {
    const NodeT<T>* node = root;
    while (node != nullptr) {
        if (node->data == data) return true;
        node = (data < node->data) ? node->left : node->right;
    }
    return false;
}

template <typename T>
void BST<T>::remove(const T& data) {
    NodeT<T>** link = &root;
    while (*link != nullptr && !((*link)->data == data)) {
        link = (data < (*link)->data) ? &(*link)->left : &(*link)->right;
    }
    if (*link == nullptr) throw std::out_of_range("El nodo a borrar no existe");
    NodeT<T>* node = *link;
    if (node->left != nullptr && node->right != nullptr) {
        NodeT<T>** predecessor = &node->left;
        while ((*predecessor)->right != nullptr) {
            predecessor = &(*predecessor)->right;
        }
        node->data = (*predecessor)->data;
        NodeT<T>* removed = *predecessor;
        *predecessor = removed->left;
        delete removed;
    } else {
        *link = (node->left != nullptr) ? node->left : node->right;
        delete node;
    }
}

template <typename T>
void BST<T>::printTree(const NodeT<T>* node, std::string prefix, bool isRight, bool isRoot) const {
    if (node == nullptr) return;
    printTree(node->right, prefix + (isRoot ? "" : (isRight ? "      " : "|     ")), true, false);
    std::cout << prefix << (isRoot ? "" : (isRight ? ".---- " : "`---- ")) << node->data << '\n';
    printTree(node->left, prefix + (isRoot ? "" : (isRight ? "|     " : "      ")), false, false);
}

template <typename T>
void BST<T>::print() const {
    if (root == nullptr) {
        std::cout << "(arbol vacio)\n";
        return;
    }
    printTree(root, "", false, true);
}

template <typename T>
void BST<T>::preOrder(const NodeT<T>* node) const {
    if (node == nullptr) return;
    std::cout << node->data << ' ';
    preOrder(node->left);
    preOrder(node->right);
}

template <typename T>
void BST<T>::inOrder(const NodeT<T>* node) const {
    if (node == nullptr) return;
    inOrder(node->left);
    std::cout << node->data << ' ';
    inOrder(node->right);
}

template <typename T>
void BST<T>::postOrder(const NodeT<T>* node) const {
    if (node == nullptr) return;
    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->data << ' ';
}

template <typename T>
void BST<T>::levelOrder() const {
    if (root == nullptr) return;
    std::queue<const NodeT<T>*> pending;
    pending.push(root);
    while (!pending.empty()) {
        const NodeT<T>* node = pending.front();
        pending.pop();
        std::cout << node->data << ' ';
        if (node->left != nullptr) pending.push(node->left);
        if (node->right != nullptr) pending.push(node->right);
    }
}

template <typename T>
void BST<T>::visit(int method) const {
    if (method < 1 || method > 4) throw std::invalid_argument("Recorrido invalido");
    if (method == 1) preOrder(root);
    else if (method == 2) inOrder(root);
    else if (method == 3) postOrder(root);
    else levelOrder();
    std::cout << '\n';
}

template <typename T>
void BST<T>::visit(const std::string& method) const {
    if (method == "preOrder") visit(1);
    else if (method == "inOrder") visit(2);
    else if (method == "postOrder") visit(3);
    else if (method == "levelOrder") visit(4);
    else throw std::invalid_argument("Recorrido invalido");
}

template <typename T>
int BST<T>::height(const NodeT<T>* node) const {
    if (node == nullptr) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <typename T>
int BST<T>::height() const {
    return height(root);
}

template <typename T>
void BST<T>::ancestors(const T& data) const {
    if (!find(data)) {
        std::cout << "El nodo no existe\n";
        return;
    }
    if (root->data == data) {
        std::cout << "La raiz no tiene ancestros\n";
        return;
    }
    const NodeT<T>* node = root;
    while (!(node->data == data)) {
        std::cout << node->data << ' ';
        node = (data < node->data) ? node->left : node->right;
    }
    std::cout << '\n';
}

template <typename T>
int BST<T>::whatLevelAmI(const T& data) const {
    const NodeT<T>* node = root;
    int level = 1;
    while (node != nullptr) {
        if (node->data == data) return level;
        node = (data < node->data) ? node->left : node->right;
        ++level;
    }
    return -1;
}

#endif
