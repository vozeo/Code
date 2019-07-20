n = int(input())
a, b = 1, 3
i = 1
while i < n :
    a, b = b, a + b
    i = i + 1
if n % 2 == 0 :
    print(a * a - 4)
else :
    print(a * a)
