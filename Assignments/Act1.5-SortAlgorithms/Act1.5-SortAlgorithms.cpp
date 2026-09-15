// Ian Armando Borde Escobar
// A00846007
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
using namespace std;

mt19937 gen(12345);

const int SIZES[3] = {1000, 10000, 100000};
const string ALGOS[7] = {"swapSort", "selectionSort", "bubbleSort", "insertionSort", "mergeSort", "quickSort", "shellSort"};
const string TYPES[3] = {"int", "double", "string"};

long long comparisons = 0;
long long swaps = 0;

template <typename T>
void swapItems(vector<T> &list, int i, int j) {
    T aux = list[i];
    list[i] = list[j];
    list[j] = aux;
    swaps++;
}

template <typename T>
void swapSort(vector<T> &list) {
    for (int i = 0; i < list.size() - 1; i++) {
        for (int j = i + 1; j < list.size(); j++) {
            comparisons++;
            if (list[j] < list[i]) {
                swapItems(list, i, j);
            }
        }
    }
}

template <typename T>
void selectionSort(vector<T> &list) {
    for (int i = 0; i < list.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < list.size(); j++) {
            comparisons++;
            if (list[j] < list[min]) {
                 min = j;
            }
        }
        if (min ! = 1) {
            swapItems(list, i, min);
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &list) {
    bool change = true;
    for (int i = list.size() - 1; i > 0 && change; i--) {
        change = false;
        for (int j = 0; j < i; j++) {
            comparisons++;
            if (list[j] > list[j + 1]) {
                change = true;
                swapItems(list, j, j + 1);
            }
        }
    }
}

template <typename T>
void insertionSort(vector<T> &list) {
    for (int i = 1; i < list.size(); i++) {
        T key = list[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (list[j] <= key) break;
            list[j + 1] = list[j];
            swaps++;
            j--;
        }
        list[j + 1] = key
    }
}

template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {
    vector<T> aux;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) aux.push_back(list[i++]);
        else aux.push_back(list[j++]);
    }
    while (i <= mid) aux.push_back(list[i++]);
    while (j <= right) aux.push_back(list[j++]);
    for (int k = 0; k < aux.size(); k++) list[left + k] = aux[k];
}

template <typename T>
void mergeSortRec(vector<T> &list, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortRec(list, left, mid);
        mergeSortRec(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

template <typename T>
void mergeSort(vector<T> &list) {
    if (list.size() > 1) {
        mergeSortRec(list, 0, list.size() - 1);
    }
}

template <typename T>
int getPivot(vector<T> &list, int left, int right) {
    int aux = left - 1;
    for (int i = left; i < right; i++) {
        if (list[i] < list[right]) {
            aux++;
            swapItems(list, aux, i);
        }
    }
    swapItems(list, aux + 1, right);
    return aux + 1;
}

template <typename T>
void quickSortRec(vector<T> &list, int left, int right) {
    if (left < right) {
        int pivot = getPivot(list, left, right);
        quickSortRec(list, left, pivot - 1);
        quickSortRec(list, pivot + 1, right);
    }
}

template <typename T>
void quickSort(vector<T> &list) {
    if (list.size() > 1) {
        quickSortRec(list, 0, list.size() - 1);
    }
}

template <typename T>
void shellSort(vector<T> &list) {
    int n = list.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T key = list[i];
            int j = i;
            while (j >= gap && list[j - gap] > key) {
                list[j] = list[j - gap];
                j -= gap;
            }
            list[j] = key;
        }
    }
}

template <typename T>
long long sortList(int algo, vector<T> &list) {
    comparisons = 0;
    swaps = 0;
    auto start = chrono::high_resolution_clock::now();
    if (algo == 0) swapSort(list);
    else if (algo == 1) selectionSort(list);
    else if (algo == 2) bubbleSort(list);
    else if (algo == 3) insertionSort(list);
    else if (algo == 4) mergeSort(list);
    else if (algo == 5) quickSort(list);
    else shellSort(list);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}

template <typename T>
void print(vector<T> &list) {
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}

vector<int> createInts(int n) {
    uniform_int_distribution<int> dist(0, 1000000);
    vector<int> v;
    for (int i = 0; i < n; i++) v.push_back(dist(gen));
    return v;
}

vector<double> createDoubles(int n) {
    uniform_real_distribution<double> dist(0, 10000);
    vector<double> v;
    for (int i = 0; i < n; i++) v.push_back(dist(gen));
    return v;
}

vector<string> createStrings(int n) {
    uniform_int_distribution<int> dist(0, 25);
    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s = "";
        for (int k = 0; k < 5; k++) s += (char)('a' + dist(gen));
        v.push_back(s);
    }
    return v;
}

vector<int> intLists[3];
vector<double> doubleLists[3];
vector<string> stringLists[3];
bool created = false;

void createLists() {
    for (int i = 0; i < 3; i++) {
        intLists[i] = createInts(SIZES[i]);
        doubleLists[i] = createDoubles(SIZES[i]);
        stringLists[i] = createStrings(SIZES[i]);
    }
    created = true;
    cout << "Listas creadas: int, double y string de 1000, 10000 y 100000 datos." << endl;
}

template <typename T>
void runSort(vector<T> list, int algo) {
    long long time = sortList(algo, list);
    cout << "Lista ordenada con " << ALGOS[algo] << ":" << endl;
    print(list);
    cout << "Tiempo: " << time << " ns" << endl;
    if (algo < 4) {
        cout << "Comparaciones: " << comparisons << endl;
        cout << "Intercambios: " << swaps << endl;
    }
}

void sortMenu(int algo) {
    if (!created) {
        cout << "Primero crea las listas (opcion 1)." << endl;
        return;
    }
    int type, size;
    cout << "Tipo de dato (1 int, 2 double, 3 string): ";
    cin >> type;
    cout << "Tamano (1 = 1000, 2 = 10000, 3 = 100000): ";
    cin >> size;
    if (type == 1) runSort(intLists[size - 1], algo);
    else if (type == 2) runSort(doubleLists[size - 1], algo);
    else runSort(stringLists[size - 1], algo);
}

void analysis() {
    if (!created) {
        cout << "Primero crea las listas (opcion 1)." << endl;
        return;
    }
    cout << "algoritmo,tipo de dato,tiempo1000,tiempo10000,tiempo100000" << endl;
    for (int a = 0; a < 7; a++) {
        for (int t = 0; t < 3; t++) {
            cout << ALGOS[a] << "," << TYPES[t];
            for (int s = 0; s < 3; s++) {
                long long time;
                if (t == 0) {
                    vector<int> v = intLists[s];
                    time = sortList(a, v);
                } else if (t == 1) {
                    vector<double> v = doubleLists[s];
                    time = sortList(a, v);
                } else {
                    vector<string> v = stringLists[s];
                    time = sortList(a, v);
                }
                cout << "," << time;
                cout.flush();
            }
            cout << endl;
        }
    }
}

int main() {
    int option;
    do {
        cout << endl << "===== MENU =====" << endl;
        cout << "1. Crear listas aleatorias" << endl;
        cout << "2. swapSort" << endl;
        cout << "3. selectionSort" << endl;
        cout << "4. bubbleSort" << endl;
        cout << "5. insertionSort" << endl;
        cout << "6. mergeSort" << endl;
        cout << "7. quickSort" << endl;
        cout << "8. shellSort" << endl;
        cout << "9. Analisis comparativo" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> option;
        if (option == 1) createLists();
        else if (option >= 2 && option <= 8) sortMenu(option - 2);
        else if (option == 9) analysis();
    } while (option != 0);
    return 0;
}
