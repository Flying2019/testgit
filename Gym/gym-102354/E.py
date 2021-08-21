a=1
b=9
for i in range(1,200):
    a,b=a*b,b*10+9
print(a)