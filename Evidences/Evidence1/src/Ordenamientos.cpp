#include "Ordenamientos.hpp"

#include <stdexcept>
#include <utility>

using namespace std;

void swapSort(vector<Registro>& registros);
void selectionSort(vector<Registro>& registros);
void bubbleSort(vector<Registro>& registros);
void insertionSort(vector<Registro>& registros);
void mergeSort(vector<Registro>& registros);
void quickSort(vector<Registro>& registros);
void shellSort(vector<Registro>& registros);

void mergeSortRec(vector<Registro>& registros, int izquierda, int derecha);
void combinar(
    vector<Registro>& registros,
    int izquierda,
    int medio,
    int derecha
);

void quickSortRec(vector<Registro>& registros, int izquierda, int derecha);
int obtenerPivote(
    vector<Registro>& registros,
    int izquierda,
    int derecha
);

void swapSort(vector<Registro>& registros) {
    for (size_t i = 0; i < registros.size() - 1; ++i) {
        for (size_t j = i + 1; j < registros.size(); ++j) {
            if (compararRegistros(registros[j], registros[i])) {
                swap(registros[i], registros[j]);
            }
        }
    }
}

void selectionSort(vector<Registro>& registros) {
    for (size_t i = 0; i < registros.size() - 1; ++i) {
        size_t menor = i;

        for (size_t j = i + 1; j < registros.size(); ++j) {
            if (compararRegistros(registros[j], registros[menor])) {
                menor = j;
            }
        }

        if (menor != i) {
            swap(registros[i], registros[menor]);
        }
    }
}

void bubbleSort(vector<Registro>& registros) {
    bool cambio = true;

    for (int limite = static_cast<int>(registros.size()) - 1;
         limite > 0 && cambio;
         --limite) {
        cambio = false;

        for (int i = 0; i < limite; ++i) {
            if (compararRegistros(registros[i + 1], registros[i])) {
                swap(registros[i], registros[i + 1]);
                cambio = true;
            }
        }
    }
}

void insertionSort(vector<Registro>& registros) {
    for (size_t i = 1; i < registros.size(); ++i) {
        Registro clave = registros[i];
        int j = static_cast<int>(i) - 1;

        while (j >= 0 && compararRegistros(clave, registros[j])) {
            registros[j + 1] = registros[j];
            --j;
        }

        registros[j + 1] = clave;
    }
}

void combinar(
    vector<Registro>& registros,
    int izquierda,
    int medio,
    int derecha
) {
    vector<Registro> auxiliar;

    int i = izquierda;
    int j = medio + 1;

    while (i <= medio && j <= derecha) {
        if (compararRegistros(registros[j], registros[i])) {
            auxiliar.push_back(registros[j]);
            ++j;
        } else {
            auxiliar.push_back(registros[i]);
            ++i;
        }
    }

    while (i <= medio) {
        auxiliar.push_back(registros[i]);
        ++i;
    }

    while (j <= derecha) {
        auxiliar.push_back(registros[j]);
        ++j;
    }

    for (size_t k = 0; k < auxiliar.size(); ++k) {
        registros[izquierda + static_cast<int>(k)] = auxiliar[k];
    }
}

void mergeSortRec(vector<Registro>& registros, int izquierda, int derecha) {
    if (izquierda >= derecha) {
        return;
    }

    int medio = izquierda + (derecha - izquierda) / 2;

    mergeSortRec(registros, izquierda, medio);
    mergeSortRec(registros, medio + 1, derecha);
    combinar(registros, izquierda, medio, derecha);
}

void mergeSort(vector<Registro>& registros) {
    if (registros.size() > 1) {
        mergeSortRec(
            registros,
            0,
            static_cast<int>(registros.size()) - 1
        );
    }
}

int obtenerPivote(
    vector<Registro>& registros,
    int izquierda,
    int derecha
) {
    Registro pivote = registros[derecha];
    int posicion = izquierda - 1;

    for (int i = izquierda; i < derecha; ++i) {
        if (compararRegistros(registros[i], pivote)) {
            ++posicion;
            swap(registros[posicion], registros[i]);
        }
    }

    swap(registros[posicion + 1], registros[derecha]);

    return posicion + 1;
}

void quickSortRec(vector<Registro>& registros, int izquierda, int derecha) {
    if (izquierda >= derecha) {
        return;
    }

    int pivote = obtenerPivote(registros, izquierda, derecha);

    quickSortRec(registros, izquierda, pivote - 1);
    quickSortRec(registros, pivote + 1, derecha);
}

void quickSort(vector<Registro>& registros) {
    if (registros.size() > 1) {
        quickSortRec(
            registros,
            0,
            static_cast<int>(registros.size()) - 1
        );
    }
}

void shellSort(vector<Registro>& registros) {
    int cantidad = static_cast<int>(registros.size());

    for (int intervalo = cantidad / 2;
         intervalo > 0;
         intervalo /= 2) {
        for (int i = intervalo; i < cantidad; ++i) {
            Registro clave = registros[i];
            int j = i;

            while (
                j >= intervalo &&
                compararRegistros(clave, registros[j - intervalo])
            ) {
                registros[j] = registros[j - intervalo];
                j -= intervalo;
            }

            registros[j] = clave;
        }
    }
}

string nombreAlgoritmo(Algoritmo algoritmo) {
    switch (algoritmo) {
        case Algoritmo::Swap:
            return "Swap Sort";

        case Algoritmo::Insercion:
            return "Insertion Sort";

        case Algoritmo::Seleccion:
            return "Selection Sort";

        case Algoritmo::Burbuja:
            return "Bubble Sort";

        case Algoritmo::Merge:
            return "Merge Sort";

        case Algoritmo::Quick:
            return "Quick Sort";

        case Algoritmo::Shell:
            return "Shell Sort";
    }

    throw invalid_argument("Algoritmo no valido");
}

void ordenar(vector<Registro>& registros, Algoritmo algoritmo) {
    switch (algoritmo) {
        case Algoritmo::Swap:
            swapSort(registros);
            break;

        case Algoritmo::Seleccion:
            selectionSort(registros);
            break;

        case Algoritmo::Burbuja:
            bubbleSort(registros);
            break;

        case Algoritmo::Insercion:
            insertionSort(registros);
            break;

        case Algoritmo::Merge:
            mergeSort(registros);
            break;

        case Algoritmo::Quick:
            quickSort(registros);
            break;

        case Algoritmo::Shell:
            shellSort(registros);
            break;
    }
}

bool estaOrdenado(const vector<Registro>& registros) {
    for (size_t i = 1; i < registros.size(); ++i) {
        if (compararRegistros(registros[i], registros[i - 1])) {
            return false;
        }
    }

    return true;
}