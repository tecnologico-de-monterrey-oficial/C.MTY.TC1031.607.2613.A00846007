// Ian Armando Borde Escobar - A00846007
// 29 DE SEPTIEMBRE DE 2026

#ifndef QUEUE_H
#define QUEUE_H

#include <string>

template <typename T>
class Queue {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
    };

    Nodo* primero;
    Nodo* ultimo;
    int cantidad;

public:
    Queue() : primero(nullptr), ultimo(nullptr), cantidad(0) {}

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    ~Queue() {
        while (primero != nullptr) {
            Nodo* siguiente = primero->siguiente;
            delete primero;
            primero = siguiente;
        }
    }

    bool empty() const {
        return primero == nullptr;
    }

    int size() const {
        return cantidad;
    }

    void add(const T& valor) {
        Nodo* nuevo = new Nodo(valor);

        if (empty())
            primero = nuevo;
        else
            ultimo->siguiente = nuevo;

        ultimo = nuevo;
        cantidad++;
    }

    T remove() {
        if (empty())
            throw "La fila esta vacia";

        Nodo* nodo = primero;
        T valor = nodo->dato;

        primero = nodo->siguiente;
        delete nodo;
        cantidad--;

        if (empty())
            ultimo = nullptr;

        return valor;
    }

    T getFirst() const {
        if (empty())
            throw "La fila esta vacia";

        return primero->dato;
    }

    template <typename Mostrar>
    void print(Mostrar mostrar) const {
        Nodo* actual = primero;

        while (actual != nullptr) {
            mostrar(actual->dato);
            actual = actual->siguiente;
        }
    }

    void push(const T& valor) {
        add(valor);
    }

    T pop() {
        return remove();
    }

    T front() const {
        return getFirst();
    }
};

struct Cliente {
    std::string nombre;
    int boletos;
};

#endif