// Ian Armando Borde Escobar - A00846007

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "NodeD.h"
#include <ostream>
#include <stdexcept>
#include <utility>

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size;
    NodeD<T>* nodeAt(int index) const;
    void removeNode(NodeD<T>* node);
    void swap(DoublyLinkedList<T>& other) noexcept;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);

    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteAt(int index);
    int findData(T data) const;
    bool deleteData(T data);
    T getData(int index) const;
    void updateData(T data, T newData);
    void updateAt(int index, T data);
    T& operator[](int index);
    void clear() noexcept;
    void sort();
    void duplicate();
    void removeDuplicates();
    void print(std::ostream& out) const;
};
template <typename T>
NodeD<T>* DoublyLinkedList<T>::nodeAt(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice invalido");
    }
    if (index <= (size - 1) / 2) {
        NodeD<T>* aux = head;
        for (int i = 0; i < index; ++i) aux = aux->next;
        return aux;
    }
    NodeD<T>* aux = tail;
    for (int i = size - 1; i > index; --i) aux = aux->prev;
    return aux;
}
template <typename T>
void DoublyLinkedList<T>::removeNode(NodeD<T>* node) {
    if (node->prev) node->prev->next = node->next;
    else head = node->next;
    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;
    delete node;
    --size;
}

template <typename T>
void DoublyLinkedList<T>::swap(DoublyLinkedList<T>& other) noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : DoublyLinkedList() {
    DoublyLinkedList<T> copy;
    for (NodeD<T>* aux = other.head; aux; aux = aux->next) {
        copy.addLast(aux->data);
    }
    swap(copy);
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this != &other) {
        DoublyLinkedList<T> copy(other);
        swap(copy);
    }
    return *this;
}
template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    NodeD<T>* aux = new NodeD<T>(data, head, nullptr);
    if (head) head->prev = aux;
    else tail = aux;
    head = aux;
    ++size;
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    NodeD<T>* aux = new NodeD<T>(data, nullptr, tail);
    if (tail) tail->next = aux;
    else head = aux;
    tail = aux;
    ++size;
}
template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    NodeD<T>* aux = nodeAt(index);
    if (aux == tail) {
        addLast(data);
        return;
    }
    NodeD<T>* auxNew = new NodeD<T>(data, aux->next, aux);
    aux->next->prev = auxNew;
    aux->next = auxNew;
    ++size;
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) return false;
    removeNode(nodeAt(index));
    return true;
}
template <typename T>
int DoublyLinkedList<T>::findData(T data) const {
    int index = 0;
    for (NodeD<T>* aux = head; aux; aux = aux->next, ++index) {
        if (aux->data == data) return index;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    for (NodeD<T>* aux = head; aux; aux = aux->next) {
        if (aux->data == data) {
            removeNode(aux);
            return true;
        }
    }
    return false;
}

template <typename T>
T DoublyLinkedList<T>::getData(int index) const {
    return nodeAt(index)->data;
}

template <typename T>
void DoublyLinkedList<T>::updateData(T data, T newData) {
    for (NodeD<T>* aux = head; aux; aux = aux->next) {
        if (aux->data == data) {
            aux->data = newData;
            return;
        }
    }
    throw std::out_of_range("El dato no se encuentra en la lista");
}

template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T data) {
    nodeAt(index)->data = data;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    return nodeAt(index)->data;
}

template <typename T>
void DoublyLinkedList<T>::clear() noexcept {
    while (head) {
        NodeD<T>* aux = head;
        head = head->next;
        delete aux;
    }
    tail = nullptr;
    size = 0;
}
template <typename T>
void DoublyLinkedList<T>::sort() {
    if (!head) return;
    for (NodeD<T>* current = head->next; current; current = current->next) {
        NodeD<T>* aux = current;
        while (aux->prev && aux->data < aux->prev->data) {
            std::swap(aux->data, aux->prev->data);
            aux = aux->prev;
        }
    }
}
template <typename T>
void DoublyLinkedList<T>::duplicate() {
    NodeD<T>* aux = head;
    while (aux) {
        NodeD<T>* nextOriginal = aux->next;
        NodeD<T>* copy = new NodeD<T>(aux->data, nextOriginal, aux);
        if (nextOriginal) nextOriginal->prev = copy;
        else tail = copy;
        aux->next = copy;
        ++size;
        aux = nextOriginal;
    }
}
template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    sort();
    NodeD<T>* aux = head;
    while (aux && aux->next) {
        if (aux->data == aux->next->data) removeNode(aux->next);
        else aux = aux->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::print(std::ostream& out) const {
    out << '[';
    for (NodeD<T>* aux = head; aux; aux = aux->next) {
        out << aux->data;
        if (aux->next) out << " <-> ";
    }
    out << ']';
}

#endif
