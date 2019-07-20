typedef unsigned long long u64;
typedef pair<int, int> PII;

const int MaxN = 100000;

inline int hash_handle(
    const char *s, const int &n, const int &l, const int &base,
    const int &mod1, const int &mod2)
{
    int li_n;
    static PII li[MaxN];
    u64 hash_pow_l;
    u64 val;

    hash_pow_l = 1;
    for (int i = 1; i <= l; i++)
        hash_pow_l = (hash_pow_l * base) % mod1;

    li_n = 0;
    val = 0;
    for (int i = 0; i < l; i++)
        val = (val * base + s[i] - 'a') % mod1;
    li[li_n++].first = val;
    
    for (int i = l; i < n; i++)
    {
        val = (val * base + s[i] - 'a') % mod1;
        val = (val + mod1 - ((s[i - l] - 'a') * hash_pow_l) % mod1) % mod1;
        li[li_n++].first = val;
    }

    hash_pow_l = 1;
    for (int i = 1; i <= l; i++)
        hash_pow_l = (hash_pow_l * base) % mod2;

    li_n = 0;
    val = 0;
    for (int i = 0; i < l; i++)
        val = (val * base + s[i] - 'a') % mod2;
    li[li_n++].second = val;
    for (int i = l; i < n; i++)
    {
        val = (val * base + s[i] - 'a') % mod2;
        val = (val + mod2 - ((s[i - l] - 'a') * hash_pow_l) % mod2) % mod2;
        li[li_n++].second = val;
    }

    sort(li, li + li_n);
    li_n = unique(li, li + li_n) - li;
    return li_n;
}