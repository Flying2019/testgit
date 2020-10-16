### [链接](https://codeforces.com/contest/923/problem/E)
首先根据题意，我们可以推出dp式子：令 $f_t(i)$ 表示第 $t$ 次操作进行之前数字是 $i$ 的概率。

那么显然有：

$$f_{t+1}(i)=\sum_{j=i}^{n}\frac{f_t(j)}{j+1}$$

考虑生成函数，即：

$$F_t(x)=\sum_{i=0}^{n} f_t(i)x^i$$

显然有：

$$F_{t+1}(x)=\sum_{i=0}^{n} \sum_{j=0}^{i} \frac{f_t(j)}{j+1}x^i$$

$$F_{t+1}(x)=\sum_{j=0}^{n} \frac{f_t(j)}{j+1}\sum_{i=0}^j x^i$$

$$F_{t+1}(x)= \frac 1 {x+1}\sum_{j=0}^{n} {f_t(j)}\int_{1}^{x}k^j\ \text{d}k$$

$$F_{t+1}(x)= \frac 1 {x+1}\int_{1}^{x}{\sum_{j=0}^{n}f_t(j)}k^j\ \text{d}k$$

$$F_{t+1}(x)=\frac 1 {x+1}\int_{1}^{x}{F_t(k)}\ \text{d}k$$

考虑去掉积分下界的1，即令 $G_t(x)=F_t(x+1)$，可以推出：

$$G_{t+1}(x)=\frac 1 {x}\int_{0}^{x}{F_t(k+1)}\ \text{d}(k+1)$$

$$G_{t+1}(x)=\sum_{i=0}^{n}\frac {g_t(i)}{i+1}x^i$$

$$g_{t+1}(x)=\frac{g_t(i)}{i+1}$$

$$g_{t+1}(x)=g_1(i)\times{(i+1)^{-t}}$$

那么我们只要求出 $g_1(i)$，就可以快速求出 $g_t(i)$。

考虑如何求出 $g_1(i)$。根据定义：

$$\sum_{i=0}^n{g_t(i)x^i}=\sum{f_t(i)(x+1)^i}$$

拆开可得：

$$g_t(i)=\sum_{j=i}^{n}\binom{j}{i}f_t(j)$$

而 $f_1(i)=p_i$，所以可以用 $\text{NTT}$ 快速计算 $g_1(i)$。

考虑如何用 $g_t(i)$ 反推 $f_t(i)$。利用二项式反演可得：

$$f_t(i)=\sum_{j=i}^{n}(-1)^{j-1}\binom{j}{i}f_t(j)$$

发现这也是一个卷积形式 $\text{NTT}$ 处理即可。复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 800010
#define mod 998244353
#define G 3
#define Gi ((mod+1)/G)
using namespace std;
int ksm(int a,long long b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
int rev[N];
int get_rev(int n)
{
    int lim=1,l=0;
    while(lim<=n*2) lim<<=1,l++;
    for(int i=0;i<lim;i++)
    rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    return lim;
}
void ntt(int f[],int lim,int opt)
{
    for(int i=0;i<lim;i++)
    if(i<rev[i]) swap(f[i],f[rev[i]]);
    for(int mid=1;mid<lim;mid<<=1)
    {
        int r=ksm(opt==1?G:Gi,(mod-1)/(mid*2));
        for(int i=0;i<lim;i+=mid*2)
            for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
            {
                int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
                f[i+j]=(x+y)%mod;
                f[i+j+mid]=(x-y+mod)%mod;
            }
    }
    if(opt==-1)
    {
        int r=ksm(lim);
        for(int i=0;i<lim;i++) f[i]=1ll*f[i]*r%mod;
    }
}
int p[N],fac[N],inv[N],f[N],g[N],h[N];
int main()
{
    int n;
    long long m;
    scanf("%d%lld",&n,&m);
    for(int i=0;i<=n;i++) scanf("%d",&p[i]);
    fac[0]=1;
    for(int i=1;i<=n+1;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n+1]=ksm(fac[n+1]);
    for(int i=n;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=0;i<=n;i++) f[i]=inv[i],g[i]=1ll*fac[n-i]*p[n-i]%mod;
    int lim=get_rev(n);
    ntt(f,lim,1),ntt(g,lim,1);
    for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%mod;
    ntt(f,lim,-1);
    for(int i=0;i<=n;i++) h[i]=1ll*inv[i]*f[n-i]%mod*ksm(ksm(i+1,m))%mod;
    for(int i=0;i<=n;i++)
    {
        f[i]=((i&1)?mod-1:1)*1ll*inv[i]%mod;
        g[i]=1ll*fac[n-i]*h[n-i]%mod;
    }
    for(int i=n+1;i<lim;i++) f[i]=g[i]=0;
    ntt(f,lim,1),ntt(g,lim,1);
    for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%mod;
    ntt(f,lim,-1);
    for(int i=0;i<=n;i++) printf("%lld ",1ll*inv[i]*f[n-i]%mod);
    return 0;
}
```
