// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <vector>
using namespace std;

// O(n) - Iterativo
int sumaImparesIterativo(const vector<int>& v) {
    int suma = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] % 2 != 0) {
            suma += v[i];
        }
    }
    return suma;
}

// O(n) - Recursivo
int sumaImparesRecursivo(const vector<int>& v, int i = 0) {
    if (i == v.size())
        return 0;
    int actual = (v[i] % 2 != 0) ? v[i] : 0;
    return actual + sumaImparesRecursivo(v, i + 1);
}

int main() {

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "La suma de los impares iterativa es: " << sumaImparesIterativo(nums) << endl;
    cout << "La suma de los impares recursiva es: " << sumaImparesRecursivo(nums) << endl;


    return 0;
}