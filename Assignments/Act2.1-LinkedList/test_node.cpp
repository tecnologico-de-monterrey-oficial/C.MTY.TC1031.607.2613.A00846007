// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <memory>
#include "Node.h"

int main() {
    auto node1 = std::make_unique<Node<int>>(20);

    auto node2 = std::make_unique<Node<int>>(
        10, node1.get()
    );

    std::cout << "node2 data: "
              << node2->data << '\n';

    std::cout << "node2 next data: "
              << node2->next->data << '\n';

    return 0;
}