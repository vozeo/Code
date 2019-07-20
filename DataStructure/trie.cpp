#include <bits/stdc++.h>
using namespace std;
int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        m = strlen(s + 1); //字符串长度
        for (j = 1, cur = root; j <= m;
             j++) { // root根节点，cur当前节点，j是枚举字符串里的每个字符
            if (!son[s[j] - 'a'][cur]) //如果cur不存在s[j]-'a'这个儿子
                son[s[j] - 'a'][cur] = ++newp;
            cur = son[s[j] - 'a'][cur];
        }
        end[cur] = 1;
    }
}
