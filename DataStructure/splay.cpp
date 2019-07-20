bool is_root(int x) { return !dad[x]; }
void reverse(int x)
{
	rev[x] ^= 1;
	swap(s[0][x], s[1][x]);
	rev[s[0][x]] ^= 1;
	rev[s[1][x]] ^= 1;
}
void update(int x)
{
	sum[x] = sum[s[0][x]] + sum[s[1][x]] + 1;
	mx[x] = x;
	if (V[mx[s[0][x]]] > V[mx[x]])
		mx[x] = mx[s[0][x]];
	if (V[mx[s[1][x]]] > V[mx[x]])
		mx[x] = mx[s[1][x]];
}
//s[i][j]表示点j的第i(0,1)个儿子
//dad[i]表示点i的父亲
void rotate(int x)
{
	int y = dad[x], z = dad[y]; //x的父亲和爷爷
	bool f = s[1][y] == x;		//f表示x是y的哪个儿子 s[f][y]==x
	//s[s[1][z]==y][z]==y
	if (!is_root(y))
		s[s[1][z] == y][z] = x;
	//s[f][y]==x s[!f][x]==B
	s[f][y] = s[!f][x];
	s[!f][x] = y;
	//s[f][y]==B
	dad[x] = z;
	dad[y] = x;
	dad[s[f][y]] = y;
	update(x);
	update(y);
}
void splay(int x)
{
	st[t = 1] = x;
	for (int y = x; !is_root(y); st[++t] = y = dad[y])
		;
	for (; t; t--)
		if (rev[st[t]])
			reverse(st[t]);
	for (; !is_root(x); rotate(x))
		if (!is_root(dad[x]))
			(s[0][dad[x]] == x) ^ (s[0][dad[dad[x]]] == dad[x]) ? rotate(x) : rotate(dad[x]);
	update(x);
}
int find_kth(int x, int k)
{ //sum表示节点的个数
	if (sum[s[0][x]] >= k)
		return find_kth(s[0][x], k);
	if (sum[s[0][x]] + 1 == k)
		return x;
	return find_kth(s[1][x], k - sum[s[0][x]] - 1);
}
int find_k(int x, int k)
{
	if (!x)
		return 0;
	if (val[x] > k)
		return find_k(s[0][x], k);
	if (val[x] == k)
	{
		int t = find_k(s[0][x], k);
		return t ? t : x;
	}
	return find_k(s[1][x], k);
}
void insert(int &x, int k, int y)
{ //插入节点
	if (!x)
	{
		x = ++cnt;
		val[x] = k;
		dad[x] = y;
		splay(x);
		return;
	}
	if (val[x] >= k)
		insert(s[0][x], k, x);
	else
		insert(s[1][x], k, x);
}
int merge(int x, int y)
{ //合并
	splay(find_kth(y, 1));
	s[0][y] = x;
}
int split(int x, int k, int &a, int &b)
{ //分离
	a = find_kth(x, k);
	splay(a);
	b = s[1][a];
	dad[b] = 0;
	s[1][a] = 0;
}
int ask_rank(int x, int k)
{
	int t = find_k(x, k);
	splay(t);
	return sum[s[0][t]] + 1;
}
int del(int x, int k)
{
	int t = find_k(x, k);
	splay(t);
	dad[s[0][t]] = 0;
	dad[s[1][t]] = 0;
	merge(s[0][t], s[1][t]);
}
int find_qianqu(int x, int k)
{
	if (!x)
		return 0;
	if (val[x] < k)
	{
		int t = find_qianqu(s[1][x], k);
		return t ? t : x;
	}
	return find_qianqu(s[0][x], k);
}
int reve(int x, int l, int r)
{
	int L = find_kth(x, l - 1);
	int R = find_kth(x, r + 1);
	splay(L);
	int t = s[1][L];
	dad[t] = 0;
	s[1][L] = 0;
	splay(R);
	rev[s[0][R]] = 1;
	merge(L, R);
	//splay(s[0][R]);
}
