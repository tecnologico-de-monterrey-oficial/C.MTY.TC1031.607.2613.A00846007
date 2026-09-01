// Ian Armando Borde Escobar
// A00846007

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>
using namespace std;
 
template <typename T>
int seqSearch(vector<T> &list, T data) {
    for (int i = 0; i < (int)list.size(); i++) {
        if (list[i] == data) {
            return i;
        }
    }
    throw out_of_range("no se encontro el valor");
}
 
template <typename T>
int binarySearch(vector<T> &list, T data) {
    int left = 0;
    int right = list.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data == list[mid]) {
            return mid;
        } else {
            if (data < list[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    throw out_of_range("no se encontro el valor");
}
 
int main() {
    const int N = 10000;
    const int MIN = 1, MAX = 1000000;
 
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(MIN, MAX);
    vector<int> list(N);
    for (int i = 0; i < N; i++) {
        list[i] = dist(gen);
    }
    sort(list.begin(), list.end());
 
    cout << "Vector de " << N << " numeros aleatorios entre " << MIN << " y " << MAX << " (ordenado)." << endl;
 
    int data;
    while (true) {
        cout << "\nIngresa un numero entre 1 y 1000000 (0 para salir): ";
        if (!(cin >> data)) break;
        if (data == 0) break;
        if (data < MIN || data > MAX) {
            cout << "Numero fuera de rango." << endl;
            continue;
        }
 
        auto t1 = chrono::high_resolution_clock::now();
        int seqIndex = -1;
        try {
            seqIndex = seqSearch(list, data);
        } catch (const out_of_range &e) {}
        auto t2 = chrono::high_resolution_clock::now();
 
        auto t3 = chrono::high_resolution_clock::now();
        int binIndex = -1;
        try {
            binIndex = binarySearch(list, data);
        } catch (const out_of_range &e) {}
        auto t4 = chrono::high_resolution_clock::now();
 
        double seqTime = chrono::duration<double, nano>(t2 - t1).count();
        double binTime = chrono::duration<double, nano>(t4 - t3).count();
 
        if (seqIndex == -1) {
            cout << "El numero " << data << " NO se encuentra en la lista." << endl;
        } else {
            cout << "El numero " << data << " SI se encuentra en la lista." << endl;
            cout << "  Indice (secuencial): " << seqIndex << endl;
            cout << "  Indice (binaria):    " << binIndex << endl;
        }
        cout << "  Tiempo busqueda secuencial: " << seqTime << " ns" << endl;
        cout << "  Tiempo busqueda binaria:    " << binTime << " ns" << endl;
    }
 
    cout << "Programa terminado." << endl;
    return 0;
}