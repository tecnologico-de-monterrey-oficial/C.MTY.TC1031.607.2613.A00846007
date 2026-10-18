// Ian Armando Borde Escobar - A00846007

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <utility>
#include "NodeD.h"

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size;

    void swap(DoublyLinkedList<T>& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }

public:
    DoublyLinkedList()
        : head(nullptr), tail(nullptr), size(0) {}

    DoublyLinkedList(const DoublyLinkedList<T>& other)
        : DoublyLinkedList() {
        DoublyLinkedList<T> copy;

        for (NodeD<T>* aux = other.head; aux; aux = aux->next)
            copy.addLast(aux->data);

        swap(copy);
    }

    ~DoublyLinkedList() {
        clear();
    }

    DoublyLinkedList<T>& operator=(
        const DoublyLinkedList<T>& other
    ) {
        if (this != &other) {
            DoublyLinkedList<T> copy(other);
            swap(copy);
        }

        return *this;
    }

    int getSize() const {
        return size;
    }

    NodeD<T>* getHead() {
        return head;
    }

    const NodeD<T>* getHead() const {
        return head;
    }

    NodeD<T>* getTail() {
        return tail;
    }

    const NodeD<T>* getTail() const {
        return tail;
    }

    void addFirst(const T& data) {
        NodeD<T>* nuevo = new NodeD<T>(data, head, nullptr);

        if (head)
            head->prev = nuevo;
        else
            tail = nuevo;

        head = nuevo;
        ++size;
    }

    void addLast(const T& data) {
        NodeD<T>* nuevo = new NodeD<T>(data, nullptr, tail);

        if (tail)
            tail->next = nuevo;
        else
            head = nuevo;

        tail = nuevo;
        ++size;
    }

    void insertAfter(NodeD<T>* node, const T& data) {
        if (!node)
            throw std::invalid_argument("El nodo no puede ser nulo");

        if (node == tail) {
            addLast(data);
            return;
        }

        NodeD<T>* nuevo = new NodeD<T>(
            data, node->next, node
        );

        node->next->prev = nuevo;
        node->next = nuevo;
        ++size;
    }

    bool removeNode(NodeD<T>* node) {
        if (!node)
            return false;

        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;

        delete node;
        --size;

        return true;
    }

    void clear() noexcept {
        while (head) {
            NodeD<T>* aux = head;
            head = head->next;
            delete aux;
        }

        tail = nullptr;
        size = 0;
    }

    void print(std::ostream& out = std::cout) const {
        out << "[";

        for (const NodeD<T>* aux = head; aux; aux = aux->next) {
            out << aux->data;

            if (aux->next)
                out << ", ";
        }

        out << "]\n";
    }

    void printReverse(std::ostream& out = std::cout) const {
        out << "[";

        for (const NodeD<T>* aux = tail; aux; aux = aux->prev) {
            out << aux->data;

            if (aux->prev)
                out << ", ";
        }

        out << "]\n";
    }
};

#endif