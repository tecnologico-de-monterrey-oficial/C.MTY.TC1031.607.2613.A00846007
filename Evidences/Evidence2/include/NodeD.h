// Ian Armando Borde Escobar - A00846007

#ifndef NODED_H
#define NODED_H

template <typename T>
struct NodeD {
    T data;
    NodeD<T>* next;
    NodeD<T>* prev;

    NodeD(
        const T& value,
        NodeD<T>* nextNode = nullptr,
        NodeD<T>* prevNode = nullptr
    ) : data(value), next(nextNode), prev(prevNode) {}
};

#endif