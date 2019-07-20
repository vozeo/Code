#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define read(x)
{
    int b = x ^= x;
    while (*f < '0' && *f != '-')
        ++f;
    if (*f == '-')
        ++f, b = 1;
    while (*f >= '0')
        x = (x << 1) + (x << 3) + (*f ^ '0'), ++f;
    if (b)
        x = -x;
}
using namespace std;
vector<int> a;

int main()
{
    int fd = fileno(stdin);
    struct stat sb;
    fstat(fd, &sb);
    register char *f = (char *)mmap(0, sb.st_size, 3, 2, fd, 0);

    int n, op, x;
    read(n);
    while (n--)
    {
        read(op);
        read(x);
        switch (op)
        {
        case (1):
            a.insert(upper_bound(a.begin(), a.end(), x), x);
            break;
        case (2):
            a.erase(lower_bound(a.begin(), a.end(), x));
            break;
        case (3):
            cout << lower_bound(a.begin(), a.end(), x) - a.begin() + 1 << endl;
            break;
        case (4):
            cout << a[x - 1] << endl;
            break;
        case (5):
            cout << *lower_bound(a.begin(), a.end(), x) - 1 << endl;
            break;
        case (6):
            cout << *upper_bound(a.begin(), a.end(), x) << endl;
            break;
        }
    }
    return 0;
}