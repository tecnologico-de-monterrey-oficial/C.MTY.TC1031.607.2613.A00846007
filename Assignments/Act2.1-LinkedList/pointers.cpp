// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <memory>
#include "Fraction.h"

int main() {
    int x = 42;
    int* p = &x;

    std::cout << x << '\n'
              << &x << '\n'
              << p << '\n'
              << *p << '\n';

    int* q = new int(5);

    std::cout << "Valores de q\n"
              << q << '\n'
              << *q << '\n';

    delete q;
    q = nullptr;

    std::cout << "q despues de borrar: "
              << q << '\n';

    Fraction* f = new Fraction(2, 3);

    f->print();

    delete f;
    f = nullptr;

    auto g = std::make_unique<Fraction>(3, 4);
    g->print();

    return 0;
}