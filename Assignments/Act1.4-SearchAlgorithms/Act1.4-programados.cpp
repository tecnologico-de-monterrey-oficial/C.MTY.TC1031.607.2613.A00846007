// Ian Armando Borde Escobar
// A00846007

#include <iostream>
#include <string>
using namespace std;
 
int seqUnique(const string &s, int &comps) {
    comps = 0;
    for (int i = 0; i + 1 < (int)s.size(); i += 2) {
        comps++;
        if (s[i] != s[i + 1]) {
            return i;
        }
    }
    return s.size() - 1;
}
 
int binUnique(const string &s, int &comps) {
    comps = 0;
    int left = 0;
    int right = (s.size() - 1) / 2;
    while (left < right) {
        int mid = left + (right - left) / 2;
        comps++;
        if (s[2 * mid] == s[2 * mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return 2 * left;
}
 
int main() {
    int n;
    if (!(cin >> n)) return 0;
 
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        int seqComps, binComps;
        char a = s[seqUnique(s, seqComps)];
        char b = s[binUnique(s, binComps)];
        cout << a << " " << seqComps << " " << b << " " << binComps << endl;
    }
    return 0;
}