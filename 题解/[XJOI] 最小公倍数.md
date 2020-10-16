### [链接](http://115.236.49.52:83/contest/1530/problem/2)
显然分类讨论。当 $n=1$ 时，显然有删掉1最优。可以发现，此时如果 $c=3$ 那么答案是6，否则是4。

考虑当 $n>1,\ c>2$ 时，显然 $\forall \ x\leq n+1,\ 2x\leq n\times c$，根据鸽子原理可以知道此时删掉 $[1,n]$ 最优，那么答案为 $2\times(n+1)$。

考虑剩余的情况。可以发现， $\forall \ x\leq n,\ 2x\leq n\times c$，显然，对于 $x$ 和 $2\times x$，至少需要删掉其中一个。

又因为显然有 $\forall \ y\geq 1,\ lcm(x,y)\leq lcm(2x,y)$，所以显然删掉 $x$ 不会更差。所以直接删掉 $[1,n]$ 最优。也就是我们要算出 $\displaystyle\min_{x,y\in[n+1,2n]}\{lcm(x,y)\}$。

显然当 $n$ 比较小时，我们有一个 $O(Tn^2)$ 的做法。这显然不能通过此题。

可以发现，当 $n$ 足够大时，要使 $x,y$ 尽可能小，我们应当尽可能地使 $gcd(x,y)$ 变大。

具体来说，如果 $x|a,\ x'|b,\ (a<b,\ x'-x=\Delta>0)$，且不存在 $x_0|a,\ x_0'|b$ 满足 $x_0< x,\ x'_0<x'$。

考虑如果要得到最小值，显然要取 $x+a,\ x'+b$。

显然有 $lcm(x,x+a)=\frac {x^2} a+x,\ lcm(x',x'+b)=\frac {x'^2} b+x'$。

由于 $n$ 足够大，$\Delta$ 事实上与 $n$ 相比很小，所以显然后面那个式子更小一些。

显然长度为 $n$ 的最大是 $\lfloor\frac {n+2} 2\rfloor$。可以发现，这种情况下 $x=2\lfloor\frac {n+2} 2\rfloor$，$\text{答案}=6\lfloor\frac {n+2} 2\rfloor$。

当然这个“足够大”其实很小，亲测只有 $n=5$ 时会出锅特判即可。复杂度 $O(T)$。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,c=2;
        scanf("%d%d",&n,&c);
        if(n==1){if(c==3) puts("6");else puts("4");continue;}
        if(c>2){printf("%d\n",(n+1)*2);continue;}
        if(c==2)
        {
            if(n>20){printf("%lld\n",6ll*((n+2)/2));continue;}
            long long ans=1ll*(n+1)*(n+2);
            for(int j=n+1;j<=n*2;j++)
                for(int k=j+1;k<=n*2;k++)
                ans=min(ans,1ll*j*k/gcd(j,k));
            // for(int j=1;j<=n;j++)
            // {
            //     int x=(n/j+1)*j,y=x+j;
            //     ans=min(ans,1ll*x*y/j);
            // }
            printf("%lld\n",ans);
        }
    }
}
```
