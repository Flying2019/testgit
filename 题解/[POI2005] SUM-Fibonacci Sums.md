### [链接](https://www.luogu.com.cn/problem/P3424)
显然我们可以把对应数字加起来。可以发现此时数列中只有0,1,2，且2旁边一定都是0。

由于有 $2*f(i)=f(i-2)+f(i+1)$，我们先从大到小处理掉所有的2。因为每处理一次，2一定向前靠，所以复杂度是对的。

再考虑有 $f(i-1)+f(i)=f(i+1)$，所以我们从大到小找第一个连续的1并处理进位以及进位的进位。由于每处理一次1减少1个，所以复杂度也是对的。

总复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
int num[N];
int main()
{
    int n,p;
    scanf("%d",&n);
    for(int i=1,a;i<=n;i++) scanf("%d",&a),num[i]+=a;
    scanf("%d",&p);
    for(int i=1,a;i<=p;i++) scanf("%d",&a),num[i]+=a;
    n=max(n,p);
    while(1)
    {
        int p1=0;
        for(int i=p+3;i>=1;i--)
        if(num[i]>=2)
        {
            if(i>2) num[i-2]++,num[i+1]++,num[i]-=2,i+=2,p1=max(p1,i);
            else if(i==2) num[1]++,num[3]++,num[2]-=2,i+=2;
            else num[2]++,num[i]-=2,i+=2;
            if(num[i] && num[i+1])
            {
                num[i]--;num[i+1]--;
                int j=i+2;
                while(num[j+1]) num[j+1]--,j+=2;
                num[j]++;
            }
        }
        if(!p1) break;
        p=p1;
    }
    for(int i=N-10;i>=1;i--)
    if(num[i] && num[i+1])
    {
        num[i]--;num[i+1]--;
        int j=i+2;
        while(num[j+1]) num[j+1]--,j+=2;
        num[j]++;
    }
    int m=N-10;
    for(;!num[m];m--);
    printf("%d ",m);
    for(int i=1;i<=m;i++) printf("%d ",num[i]);
    return 0;
}
```
