// Ian Armando Borde Escobar - A00846007

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <utility>
#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    Node<T>* nodeAt(int index) const {
        if (index < 0 || index >= size)
            throw std::out_of_range("La posicion no existe");

        Node<T>* aux = head;

        for (int i = 0; i < index; ++i)
            aux = aux->next;

        return aux;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(const LinkedList<T>& other) : LinkedList() {
        try {
            for (Node<T>* aux = other.head; aux; aux = aux->next)
                addLast(aux->data);
        } catch (...) {
            clear();
            throw;
        }
    }

    ~LinkedList() {
        clear();
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            LinkedList<T> copy(other);

            std::swap(head, copy.head);
            std::swap(tail, copy.tail);
            std::swap(size, copy.size);
        }

        return *this;
    }

    void clear() {
        while (head) {
            Node<T>* aux = head;
            head = head->next;
            delete aux;
        }

        tail = nullptr;
        size = 0;
    }

    int getSize() const {
        return size;
    }

    void addFirst(const T& data) {
        head = new Node<T>(data, head);

        if (!tail)
            tail = head;

        ++size;
    }

    void addLast(const T& data) {
        Node<T>* nuevo = new Node<T>(data);

        if (tail)
            tail->next = nuevo;
        else
            head = nuevo;

        tail = nuevo;
        ++size;
    }

    void push_front(const T& data) {
        addFirst(data);
    }

    void push_back(const T& data) {
        addLast(data);
    }

    void insert(int index, const T& data) {
        Node<T>* aux = nodeAt(index);
        Node<T>* nuevo = new Node<T>(data, aux->next);

        aux->next = nuevo;

        if (aux == tail)
            tail = nuevo;

        ++size;
    }

    bool deleteData(const T& data) {
        Node<T>* previous = nullptr;
        Node<T>* current = head;

        while (current) {
            if (current->data == data) {
                if (previous)
                    previous->next = current->next;
                else
                    head = current->next;

                if (current == tail)
                    tail = previous;

                delete current;
                --size;

                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    bool deleteAt(int index) {
        if (index < 0 || index >= size)
            return false;

        Node<T>* victim;

        if (index == 0) {
            victim = head;
            head = head->next;

            if (!head)
                tail = nullptr;
        } else {
            Node<T>* previous = nodeAt(index - 1);

            victim = previous->next;
            previous->next = victim->next;

            if (victim == tail)
                tail = previous;
        }

        delete victim;
        --size;

        return true;
    }

    T getData(int index) const {
        return nodeAt(index)->data;
    }

    void updateData(const T& oldData, const T& newData) {
        int index = findData(oldData);

        if (index == -1)
            throw std::out_of_range("El dato no existe");

        updateAt(index, newData);
    }

    void updateAt(int index, const T& data) {
        nodeAt(index)->data = data;
    }

    int findData(const T& data) const {
        int index = 0;

        for (Node<T>* aux = head; aux; aux = aux->next, ++index) {
            if (aux->data == data)
                return index;
        }

        return -1;
    }

    T& operator[](int index) {
        return nodeAt(index)->data;
    }

    const T& operator[](int index) const {
        return nodeAt(index)->data;
    }

    void print() const {
        std::cout << "[";

        for (Node<T>* aux = head; aux; aux = aux->next) {
            std::cout << aux->data;

            if (aux->next)
                std::cout << ", ";
        }

        std::cout << "]\n";
    }
};

#endif