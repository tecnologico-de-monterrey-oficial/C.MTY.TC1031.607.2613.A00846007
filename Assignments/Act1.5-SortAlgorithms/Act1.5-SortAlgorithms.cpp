// Ian Armando Borde Escobar
// A00846007
#include <iostream>
using namespace std;

template <typename T>
void swap(vector<T> &list, int i, int j) {
    T aux = list[i];
    list[i] = list[j];
    list[j] = aux;
}

template <typename T>
void swapSort(vector<T> &list) {
    for (int i=0; i < list.size()-1; i++) {
        for (int j=i+1; j<list.size(); j++) {
            if (list[j] < list[i]) {
                swap(list, i, j);
            }
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &list) {
    bool change = true;
    for (int i=list.size()-1; i>0 && change; i--) {
        change = false;
        for (int j=0; j<i; j++) {
            if (list[j] > list[j+1]) {
                change = true;
                swap(list, j, j+1);
            }
        }
    }
}

void print(vector<int> &list) {
    for (int i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}

int main() {

    vector<int> list = {15, 7, 3, 9, 12, 5, 2};
    vector<int> listOriginal = list;
    cout << "Lista original: " << endl;
    print(list);
    swapSort(list);
    cout << "Lista ordenada: con Swap Sort" << endl;
    print(list);
    list = listOriginal;
    print(list);
    bubbleSort(list);
    cout << "Lista ordenada: con Bubble Sort" << endl;
    print(list);



    return 0;
}
