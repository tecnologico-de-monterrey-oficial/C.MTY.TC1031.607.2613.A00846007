// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <stdexcept>
#include "../include/LinkedList.h"
#include "../include/Stack.h"
#include "../include/Queue.h"
#include "../include/DoublyLinkedList.h"

void verificar(bool condicion, const char* mensaje) {
    if (!condicion)
        throw std::runtime_error(mensaje);

    std::cout << "OK: " << mensaje << '\n';
}

template <typename Funcion>
void comprobarVacia(Funcion operacion, const char* mensaje) {
    bool detectada = false;

    try {
        operacion();
    } catch (const std::out_of_range& error) {
        detectada = true;
        std::cout << "Mensaje: " << error.what() << '\n';
    }

    verificar(detectada, mensaje);
}

void probarLinkedList() {
    std::cout << "\nLISTA LIGADA SIMPLE\n";

    LinkedList<int> lista;
    lista.print();

    verificar(lista.getSize() == 0, "Lista inicialmente vacia");
    verificar(!lista.deleteAt(0), "Eliminar en vacio no interrumpe");

    lista.addFirst(10);
    lista.print();

    verificar(lista.getSize() == 1, "Insercion de un elemento");
    verificar(lista.getData(0) == 10, "Primer elemento correcto");

    lista.deleteAt(0);
    lista.addLast(20);

    verificar(
        lista.getSize() == 1 && lista.getData(0) == 20,
        "Reinsercion despues de eliminar el unico elemento"
    );

    lista.addFirst(10);
    lista.addLast(30);
    lista.insert(2, 40);
    lista.print();

    verificar(
        lista.getSize() == 4 && lista.getData(3) == 40,
        "Insercion despues del ultimo elemento"
    );

    lista.deleteAt(3);
    lista.addLast(50);

    verificar(lista.getData(3) == 50, "Tail actualizado al borrar por indice");

    lista.deleteData(50);
    lista.addLast(60);

    verificar(lista.getData(3) == 60, "Tail actualizado al borrar por dato");

    lista.deleteAt(0);
    lista.print();

    verificar(lista.getData(0) == 20, "Eliminacion al inicio");

    LinkedList<int> copia(lista);
    copia.addLast(70);

    verificar(
        lista.getSize() == 3 && copia.getSize() == 4,
        "Copia independiente con insercion al final"
    );

    LinkedList<int> asignada;
    asignada.addFirst(-1);
    asignada = lista;
    asignada.addLast(80);

    verificar(
        lista.getSize() == 3 && asignada.getData(3) == 80,
        "Asignacion independiente con tail correcto"
    );

    lista.clear();
    lista.addLast(90);

    verificar(
        lista.getSize() == 1 && lista.getData(0) == 90,
        "Reutilizacion despues de clear"
    );

    lista.deleteData(90);
    lista.addLast(100);

    verificar(
        lista.getSize() == 1 && lista.getData(0) == 100,
        "Reinsercion tras borrar el unico dato"
    );
}

void probarStack() {
    std::cout << "\nPILA\n";

    Stack<int> pila;

    verificar(pila.isEmpty() && pila.size() == 0, "Pila inicialmente vacia");

    comprobarVacia(
        [&]() { pila.pop(); },
        "Pop en vacio muestra mensaje y permite continuar"
    );

    comprobarVacia(
        [&]() { pila.peek(); },
        "Peek en vacio se detecta"
    );

    pila.push(10);

    verificar(pila.size() == 1 && pila.peek() == 10, "Pila con un elemento");
    verificar(pila.pop() == 10 && pila.isEmpty(), "Pop del unico elemento");

    for (int i = 1; i <= 3; ++i)
        pila.push(i * 10);

    verificar(pila.size() == 3, "Size despues de tres push");
    verificar(pila.peek() == 30 && pila.size() == 3, "Peek no elimina");

    std::cout << "Orden LIFO esperado: 30 20 10\n";

    for (int esperado = 30; esperado >= 10; esperado -= 10) {
        int valor = pila.pop();
        std::cout << "Pop: " << valor << '\n';
        verificar(valor == esperado, "Orden LIFO correcto");
    }

    verificar(pila.isEmpty() && pila.size() == 0, "Pila vacia al terminar");
}

void probarQueue() {
    std::cout << "\nFILA\n";

    Queue<int> fila;

    verificar(fila.isEmpty() && fila.size() == 0, "Fila inicialmente vacia");

    comprobarVacia(
        [&]() { fila.dequeue(); },
        "Dequeue en vacio muestra mensaje y permite continuar"
    );

    comprobarVacia(
        [&]() { fila.front(); },
        "Front en vacio se detecta"
    );

    fila.enqueue(10);

    verificar(fila.size() == 1 && fila.front() == 10, "Fila con un elemento");

    verificar(
        fila.dequeue() == 10 && fila.isEmpty(),
        "Dequeue del unico elemento"
    );

    for (int i = 1; i <= 3; ++i)
        fila.enqueue(i * 10);

    verificar(fila.size() == 3, "Size despues de tres enqueue");
    verificar(fila.front() == 10 && fila.size() == 3, "Front no elimina");

    std::cout << "Orden FIFO esperado: 10 20 30\n";

    for (int esperado = 10; esperado <= 30; esperado += 10) {
        int valor = fila.dequeue();
        std::cout << "Dequeue: " << valor << '\n';
        verificar(valor == esperado, "Orden FIFO correcto");
    }

    verificar(fila.isEmpty() && fila.size() == 0, "Fila vacia al terminar");

    fila.enqueue(40);

    verificar(fila.dequeue() == 40, "Fila reutilizable despues de vaciarla");
}

void verificarEnlaces(const DoublyLinkedList<int>& lista) {
    const NodeD<int>* anterior = nullptr;
    const NodeD<int>* actual = lista.getHead();
    int cantidad = 0;

    while (actual) {
        verificar(actual->prev == anterior, "Enlace prev correcto");
        anterior = actual;
        actual = actual->next;

        ++cantidad;

        if (cantidad > lista.getSize())
            throw std::runtime_error("Ciclo en recorrido hacia adelante");
    }

    verificar(anterior == lista.getTail(), "Tail coincide con el ultimo nodo");
    verificar(cantidad == lista.getSize(), "Tamano coincide hacia adelante");

    const NodeD<int>* siguiente = nullptr;
    actual = lista.getTail();
    cantidad = 0;

    while (actual) {
        verificar(actual->next == siguiente, "Enlace next correcto");
        siguiente = actual;
        actual = actual->prev;

        ++cantidad;

        if (cantidad > lista.getSize())
            throw std::runtime_error("Ciclo en recorrido hacia atras");
    }

    verificar(siguiente == lista.getHead(), "Head coincide al recorrer atras");
    verificar(cantidad == lista.getSize(), "Tamano coincide hacia atras");
}

void probarDoublyLinkedList() {
    std::cout << "\nLISTA DOBLEMENTE LIGADA\n";

    DoublyLinkedList<int> lista;
    lista.print();
    lista.printReverse();

    verificar(lista.getSize() == 0, "Lista doble inicialmente vacia");
    verificar(!lista.removeNode(nullptr), "Eliminar nodo nulo no interrumpe");
    verificarEnlaces(lista);

    lista.addFirst(20);

    verificar(
        lista.getHead() == lista.getTail() && lista.getSize() == 1,
        "Lista doble con un elemento"
    );

    lista.print();
    lista.printReverse();
    verificarEnlaces(lista);

    lista.removeNode(lista.getHead());

    verificar(
        !lista.getHead() && !lista.getTail() && lista.getSize() == 0,
        "Eliminar unico nodo actualiza ambos extremos"
    );

    lista.addLast(20);
    lista.addFirst(10);
    lista.addLast(40);
    lista.insertAfter(lista.getHead()->next, 30);
    lista.insertAfter(lista.getTail(), 50);

    std::cout << "Adelante esperado: [10, 20, 30, 40, 50]\n";
    lista.print();

    std::cout << "Atras esperado: [50, 40, 30, 20, 10]\n";
    lista.printReverse();

    const NodeD<int>* actual = lista.getHead();

    for (int esperado = 10; esperado <= 50; esperado += 10) {
        verificar(
            actual && actual->data == esperado,
            "Orden de insercion correcto"
        );

        actual = actual->next;
    }

    verificar(actual == nullptr, "Sin nodos adicionales");
    verificarEnlaces(lista);

    lista.removeNode(lista.getHead());
    lista.removeNode(lista.getTail());
    lista.removeNode(lista.getHead()->next);

    std::cout << "Tras borrar inicio, final e intermedio: [20, 40]\n";
    lista.print();
    lista.printReverse();

    verificar(
        lista.getSize() == 2
            && lista.getHead()->data == 20
            && lista.getTail()->data == 40,
        "Eliminacion en extremos e intermedio"
    );

    verificarEnlaces(lista);

    DoublyLinkedList<int> copia(lista);
    copia.removeNode(copia.getHead());

    verificar(
        lista.getSize() == 2 && copia.getSize() == 1,
        "Copia independiente de lista doble"
    );

    DoublyLinkedList<int> asignada;
    asignada.addLast(-1);
    asignada = lista;
    asignada.addLast(60);

    verificar(
        lista.getSize() == 2 && asignada.getSize() == 3,
        "Asignacion independiente de lista doble"
    );

    verificarEnlaces(copia);
    verificarEnlaces(asignada);

    lista.clear();
    verificarEnlaces(lista);

    lista.addLast(100);

    verificar(
        lista.getSize() == 1
            && lista.getHead() == lista.getTail()
            && lista.getHead()->data == 100,
        "Lista doble reutilizable despues de clear"
    );

    verificarEnlaces(lista);
}

int main() {
    try {
        probarLinkedList();
        probarStack();
        probarQueue();
        probarDoublyLinkedList();

        std::cout << "\nTodas las pruebas terminaron correctamente.\n";
    } catch (const std::exception& error) {
        std::cerr << "\nPrueba fallida: " << error.what() << '\n';
        return 1;
    }

    return 0;
}