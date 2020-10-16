### [链接](https://vjudge.net/problem/Aizu-2970/origin)
### 题目大意
给定两个置换 $A,B$，问最小的 $k$ ，使 $A\times B^k$ 的结果中所有数字单调递增。
### 题解
可以发现，对于 $A$ 的每一个数字，其随 $k$ 的变化是一个循环节。不妨设其为 $r_i$。

又可以发现，对于每一位 $i$ 在某一个 $k$ 出现了 $i$（如果没有出现当然就是无解）。不妨设出现时的最小 $k$ 值为 $t_i$。

可以发现由于 $n$ 并不大，而一定有 $r_i\leq n$，所以完全可以在 $O(n^2)$ 内完成操作。

很明显，我们要求找到一个最小的 $x\in\Bbb Z$，使得满足 $\forall\ 1\leq i\leq n,\ x\equiv t_i\ (\bmod r_i)$。

这显然就是一个excrt，直接上模板就好了。

复杂度 $O(n^2)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1100
#define ll long long
ll mul(ll a,ll b,ll mod)
{
    ll res=0;
    while(b)
    {
        if(b&1) res=(res+a)%mod;
        a=a*2%mod;
        b>>=1;
    }
    return res;
}

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1;y=0;return a;}
    ll g=exgcd(b,a%b,x,y);
    ll p=x;
    x=y;
    y=p-a/b*y;
    return g;
}
int xa[N],xb[N],n;
ll excrt()
{
    ll mod=xb[1],ans=xa[1];
    for(int i=2;i<=n;i++)
    {
        ll x,y;
        ll a=mod,b=xb[i],c=(xa[i]-ans%b+b)%b;
        ll g=exgcd(a,b,x,y);
        if(c%g!=0) return -1;
        x=mul(x,c/g,b/g);
        ans+=x*mod;
        mod*=b/g;
        ans=(ans%mod+mod)%mod;
    }
    return (ans%mod+mod)%mod;
}
int id[N],p1[N],p2[N];
bool vis[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p1[i]),id[p1[i]]=i;
    for(int i=1;i<=n;i++) scanf("%d",&p2[i]);
    memset(xa,-1,sizeof(xa));
    for(int rt=0;rt<=2*n;rt++)
    {
        for(int i=1;i<=n;i++)
        if(p1[i]==i)
        {
            if(xa[i]<0) xa[i]=rt;
            else if(!xb[i]) xb[i]=rt-xa[i];
        }
        for(int i=1;i<=n;i++) p1[i]=p2[p1[i]];
    }
    for(int i=1;i<=n;i++)
    if(!xb[i]){puts("-1");return 0;}
    printf("%lld\n",excrt());
    return 0;
}
```
