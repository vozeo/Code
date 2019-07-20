#include<bits/stdc++.h>
using namespace std;

struct trie_node {
	trie_node *fail;
	trie_node *son[26];
	int count;
} node[1000007], *root = node;
int cnt_node;

inline void build(char s[]) {
	int len = strlen(s);
	trie_node *now = root;
	for(int i = 0; i < len; i++) {
		if(!now->son[s[i] - 'a'])
			now->son[s[i] - 'a'] = (&node[++cnt_node]);
		now = now->son[s[i] - 'a'];
	}
	now->count++;
}

void get_fail() {
	queue<trie_node*> q;
	for(int i = 0; i < 26; i++) {
		if(root->son[i]) {
			root->son[i]->fail = root;
			q.push(root->son[i]);
		}
	}
	trie_node *now;
	while(!q.empty()) {
		now = q.front();
		q.pop();
		for(int i = 0; i < 26; i++) {
			if(now->son[i]) {
				now->son[i]->fail = now->fail->son[i];
				q.push(now->son[i]);
			}
			else now->son[i] = now->fail->son[i];
		}
	}
}
int query(char s[]) {
	int ans = 0, len = strlen(s);
	trie_node *now = root;
	for(int i = 0; i < len; i++) {
		while(!(now->son[s[i] - 'a']) && now != root)
			now = now->fail;
		now = now->son[s[i] - 'a'];
		for (trie_node *t = now; t != root && ~t->count; t = t->fail) {
			ans += t->count;
			t->count = -1;
		}
	}
	return ans;
}

int n;
char input[1000007];

int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%s", input);
		build(input);
	}
	get_fail();
	scanf("%s", input);
	printf("%d\n", query(input));
	return 0;
}
