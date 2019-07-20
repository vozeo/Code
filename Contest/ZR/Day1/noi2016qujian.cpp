#include <cstdio>
#include <iostream>
#include <algorithm>
#define ls (o << 1)
#define rs ((o << 1) | 1)

struct Node
{
    int l, r, sum;
} node[500005 << 3];

void pushup(int o)
{
    sum[o] = sum[ls] + sum[rs];
}

void build(int l, int r, int o)
{
    Node v = &node[o];
    v.l = l, v.r = r;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    pushup(o);
}

void modify(int l, int r, int o, int val)
{
    Node v = node[o];
    if (v.l <= l && )
}