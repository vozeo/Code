#include <bits/stdc++.h>
using namespace std;
int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        m = strlen(s + 1); //�ַ�������
        for (j = 1, cur = root; j <= m;
             j++) { // root���ڵ㣬cur��ǰ�ڵ㣬j��ö���ַ������ÿ���ַ�
            if (!son[s[j] - 'a'][cur]) //���cur������s[j]-'a'�������
                son[s[j] - 'a'][cur] = ++newp;
            cur = son[s[j] - 'a'][cur];
        }
        end[cur] = 1;
    }
}
