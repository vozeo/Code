#include <bits/stdc++.h>
using namespace std;

struct Node{
	Node *ch[2];
	int siz;
	Node() {}
	Node(Node *l, Node *r) { ch[0] = l, ch[1] = r; }
	void ins(int x) {
		int bit;
		per (i, 30, 0) {
			bit = (x >> i) & 1;
			if (!o->ch[bit])
				o->ch[bit] = new (tcur++) Node;
			o = o->ch[bit];
		}
		o->siz++;
	}
}
