// Ian Borde
// A00846007

#include <iostream>
using namespace std;

int sumIterative(int n) {
    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i;
    }
    return suma;
}

int sumRecursive(int n) {
    if (n == 1) {
        return 1;
    }
    return n + sumRecursive(n - 1);
}

int sumFormula(int n) {
    return (n * (n + 1)) / 2;
}

int fibonacciIterative(int n) {
    if (n <= 2) return 1;

    int actual = 1, anterior = 1;
    for (int i = 3; i <= n; i++){
        int siguiente = anterior + actual;
        anterior = actual;
        actual = siguiente;
    }
    return actual;

}

int fibonacciRecursive(int n) {
    if (n <= 2) return 1;
    return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
}

int bacteriasIterative(int n) {
    double nacio = 3.78, murio = 2.34;
    int suma = 1;
    
    for (int i = 1; i <= n; i++) {
        int bacteriaNacio = suma * nacio;
        int bacteriaMurio = suma * murio;
        suma += bacteriaNacio - bacteriaMurio;
    }
    return suma;
}

int bacteriasRecursiva(int n) {
    if (n == 0) {
        return 1;
    }
    int bacteria = bacteriasRecursiva(n - 1);
    int bacteriaNacio = bacteria * 3.78;
    int bacteriaMurio = bacteria * 2.34;
    return bacteria + bacteriaNacio - bacteriaMurio;
}

double investmentIterative(int n, double amount) {
    for (int i = 0; i < n; i++) {
        amount = amount * 1.1875;
    }
    return amount;
}

double investmentRecursive(int n, double amount) {
    if (n == 0) {
        return amount;
    }
    return investmentRecursive(n - 1, amount * 1.1875);
}

double powIterative(double n, int y) {
    double resultado = 1;
    for (int i = 0; i < y; i++) {
        resultado = resultado * n;
    }
    return resultado;
}

double powRecursive(double n, int y) {
    if (y == 0) {
        return 1;
    }
    return n * powRecursive(n, y - 1);
}

int main() {

    cout << "La suma iterativa de 1 a 5 es: " << sumIterative(5) << endl;
    cout << "La suma recursiva de 1 a 5 es: " << sumRecursive(5) << endl;
    cout << "La suma con fórmula de 1 a 5 es: " << sumFormula(5) << endl;
    cout << "El fibonacci iterativo de 6 es: " << fibonacciIterative(8) << endl;
    cout << "El fibonacci recursivo de 6 es: " << fibonacciRecursive(8) << endl;
    cout << "la bacteria iterativa de 5 es: " << bacteriasIterative(5) << endl;
    cout << "la bacteria recursiva de 5 es: " << bacteriasRecursiva(100000) << endl;
    cout << "la inversión iterativa de 5 años con $1000 es: " << investmentIterative(5, 1000) << endl;
    cout << "la inversión recursiva de 5 años con $1000 es: " << investmentRecursive(5, 1000) << endl;
    cout << "la potencia iterativa de 2^5 es: " << powIterative(2, 5) << endl;
    cout << "la potencia recursiva de 2^5 es: " << powRecursive(2, 5) << endl;


    return 0;
}