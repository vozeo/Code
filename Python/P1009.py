s , t = 0, 1
n = int(input())
for i in range(1, n + 1):
    t *= i
    s += t
print(s)
