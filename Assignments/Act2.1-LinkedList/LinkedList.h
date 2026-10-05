// Ian Armando Borde Escobar - A00846007

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdexcept>
#include <utility>
#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
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
    LinkedList() : head(nullptr), size(0) {}

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

        size = 0;
    }

    int getSize() const {
        return size;
    }

    void addFirst(const T& data) {
        head = new Node<T>(data, head);
        ++size;
    }

    void addLast(const T& data) {
        if (!head) {
            addFirst(data);
            return;
        }

        Node<T>* aux = head;

        while (aux->next)
            aux = aux->next;

        aux->next = new Node<T>(data);
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

        aux->next = new Node<T>(data, aux->next);
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
        } else {
            Node<T>* previous = nodeAt(index - 1);

            victim = previous->next;
            previous->next = victim->next;
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