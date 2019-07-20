#include <cstdio>

int ecgcd(int &x, int &y, int a, int b)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    exgcd(b, a % b, y, x);
    y -= x * (a / b);
    return a;
}

int main()
{
    
}