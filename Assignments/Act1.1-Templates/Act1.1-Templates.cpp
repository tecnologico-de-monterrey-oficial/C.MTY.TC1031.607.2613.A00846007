#include <iostream>
using namespace std;

#include "List.h"

// int sum(int a, int b) {
//     return a + b;
// }

// double sum(double a, double b) {
//     return a + b;
// }

// string sum(string a, string b) {
//     return a + b;
// }

template <typename T>
T sum(T a, T b) {
    return a + b;
}

int main() {

//    string a= "hola ";
//    string b= "crayola";
//    cout << "Sum of " << a << " and " << b << " is: " << sum(a, b) << endl;
//    int c= 5;
//    int d= 10;
//    cout << "Sum of " << c << " and " << d << " is: " << sum(c, d) << endl;
//    double e= 5.5;
//    double f= 10.5;
//    cout << "Sum of " << e << " and " << f << " is: " << sum(e, f) << endl;

List<int> list;
list.insert(5);
list.insert(10);
list.insert(15);

List<string> things;
things.insert("Laptop");
things.insert("bottle");

cout << "--- Lista de enteros ---" << endl;
list.print();

cout << "Size: " << list.getSize() << endl;
cout << "Max: " << list.getMax() << endl;
cout << "getData(1): " << list.getData(1) << endl;

cout << "insertAt(1, 99):" << endl;
list.insertAt(1, 99);
list.print();

cout << "removeAt(0):" << endl;
list.removeAt(0);
list.print();

cout << "removeLast():" << endl;
list.removeLast();
list.print();

cout << "insertAt(100, 1):" << endl;
list.insertAt(100, 1);

cout << "removeAt(100):" << endl;
list.removeAt(100);

cout << "--- Lista de strings ---" << endl;
things.print();

cout << "Size: " << things.getSize() << endl;
cout << "Max (alfabético): " << things.getMax() << endl;

cout << "insertAt(1, \"mouse\"):" << endl;
things.insertAt(1, "mouse");
things.print();

cout << "removeAt(0):" << endl;
things.removeAt(0);
things.print();

List<int> vacia;
cout << "removeLast() en lista vacía:" << endl;
vacia.removeLast();

return 0;
}