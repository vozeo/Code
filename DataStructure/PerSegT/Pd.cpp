#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 100000;
    int i = 1, cnt = 0;
    while (i <= n)
        i <<= 1, ++cnt;
    //cout << cnt - 1;
    cout << (1 << 16) << " " << n << endl;
        
}
