// Ian Armando Borde Escobar - A00846007

#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "LinkedList.h"

template <typename T>
class Stack {
private:
    LinkedList<T> lista;

public:
    void push(const T& valor) {
        lista.addFirst(valor);
    }

    T pop() {
        if (isEmpty())
            throw std::out_of_range("La pila esta vacia");

        T valor = lista.getData(0);
        lista.deleteAt(0);

        return valor;
    }

    T peek() const {
        if (isEmpty())
            throw std::out_of_range("La pila esta vacia");

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