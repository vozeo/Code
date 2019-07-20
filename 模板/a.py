#x = 0
n = input()
a, b = 1, 3
#while 
#a = [105]
#a = [0, 1, 3]
i = 1
while i < n :
    a, b = b, a + b
    i = i + 1
#for i in range(1, n) :
    #a, b = b, a + b
    #a[i + 2] = a[i] + a[i + 1]
if n % 2 == 0 :
    print(a * a - 4)
else :
    print(a * a)