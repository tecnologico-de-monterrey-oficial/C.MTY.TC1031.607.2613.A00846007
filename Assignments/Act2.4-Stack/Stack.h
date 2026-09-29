// Ian Armando Borde Escobar - A00846007
// 29 DE SEPTIEMBRE DE 2026

#ifndef STACK_H
#define STACK_H

#include <string>

template <typename T>
class Stack {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;

        Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
    };

    Nodo* cima;
    int cantidad;

public:
    Stack() : cima(nullptr), cantidad(0) {}

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack() {
        while (cima != nullptr) {
            Nodo* siguiente = cima->siguiente;
            delete cima;
            cima = siguiente;
        }
    }

    bool empty() const {
        return cima == nullptr;
    }

    int size() const {
        return cantidad;
    }

    void push(const T& valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = cima;
        cima = nuevo;
        cantidad++;
    }

    T pop() {
        if (empty())
            throw "La pila esta vacia";

        Nodo* nodo = cima;
        T valor = nodo->dato;
        cima = nodo->siguiente;
        delete nodo;
        cantidad--;

        return valor;
    }

    T top() const {
        if (empty())
            throw "La pila esta vacia";

        return cima->dato;
    }
};

struct PaginaWeb {
    std::string titulo;
    std::string url;
};

#endif