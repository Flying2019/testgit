### [链接](http://115.236.49.52:83/contest/1534/problem/3)
推式子：
$$\text{原式}=\sum_{d}d^k\sum_{i|d}\sum_{j|d}[\ gcd(i,j)=d\ ]$$
由 $\sum_{i=1}^n\mu(i)=[n=1]$
$$\text{原式}=\sum_{d}d^k\sum_{i=1}^{\lfloor\frac n d\rfloor}\sum_{j=1}^{\lfloor\frac m d\rfloor}\sum_{k|i\ ,\ k|j}\mu(k)$$
不妨令 $n<m$，交换求和顺序可得
$$\text{原式}=\sum_{d}d^k\sum_{k=1}^{\lfloor\frac n d\rfloor}\mu(k)\lfloor\frac n {dk}\rfloor\lfloor\frac m {dk}\rfloor$$
$$=\sum_{x=1}^{n}\lfloor\frac n {x}\rfloor\lfloor\frac m {x}\rfloor\sum_{d|x}\mu(\frac x d)d^k$$
后面那个式子看着很复杂，不妨令 $f(x)=\sum_{d|x}\mu(\frac x d)d^k$。但是我们考虑设 $gcd(x_1,x_2)=1$。
$$f(x_1)\times f(x_2)=(\sum_{d|x_1}\mu(\frac {x_1} d)d^k)\times (\sum_{d|x_2}\mu(\frac {x_2} d)d^k)$$
$$=\sum_{d_1d_2|x_1x_2}(\mu(\frac {x_1x_2} {d_1d_2}) {d_1d_2}^k)$$
$$=f(x_1x_2)$$
我们又可以发现对于素数的次幂，有
$$f(p^x)=\sum_{1\leq d\leq x}\mu(p^{x-d})x^{dk}$$
由于对于 $d<x-1$，$\mu(p^{x-d})=0$，所以 $f(p^x)=p^{xk}-p^{xk-k}$，直接线性筛即可。

最后再套上一个数论分块，复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5000010
#define ll long long
#define mod 1000000007
using namespace std;
int p[N],tot;
bool pr[N];
ll f[N],fk[N],k;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
void init(int n=N-10)
{
    pr[1]=true;
    f[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]) p[++tot]=i,f[i]=(fk[tot]=ksm(i,k))-1;
        for(int j=1;j<=tot && i*p[j]<=n;j++)
        {
            pr[i*p[j]]=true;
            if(i%p[j]==0){f[i*p[j]]=1ll*f[i]*fk[j]%mod;break;}
            f[i*p[j]]=1ll*f[i]*f[p[j]]%mod;
        }
    }
    for(int i=1;i<=n;i++) f[i]=(f[i]+f[i-1])%mod;
}
int main()
{
    int n,m;
    scanf("%d%d%d",&n,&m,&k);
    if(n>m) swap(n,m);
    init(m);
    int l=1,r=1;
    ll ans=0;
    for(l=1;l<=min(n,m);l=r+1)
    {
        r=min(n/(n/l),m/(m/l));
        ans=(ans+(f[r]-f[l-1]+mod)*(n/r)%mod*(m/r)%mod+mod)%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
```
