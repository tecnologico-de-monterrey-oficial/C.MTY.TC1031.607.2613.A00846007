// Ian Armando Borde Escobar - A00846007

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "LinkedList.h"

template <typename T>
class Queue {
private:
    LinkedList<T> lista;

public:
    void enqueue(const T& valor) {
        lista.addLast(valor);
    }

    T dequeue() {
        if (isEmpty())
            throw std::out_of_range("La fila esta vacia");

        T valor = lista.getData(0);
        lista.deleteAt(0);

        return valor;
    }

    T front() const {
        if (isEmpty())
            throw std::out_of_range("La fila esta vacia");

        return lista.getData(0);
    }

    bool isEmpty() const {
        return lista.getSize() == 0;
    }

    int size() const {
        return lista.getSize();
    }
};

#endif