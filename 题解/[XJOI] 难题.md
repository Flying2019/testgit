### [链接](http://115.236.49.52:83/contest/1561/problem/2)
考虑枚举最后留下的球的颜色，要求的是最后留下该球的期望步数。

注意这是一个条件期望，即答案 $ans=\sum_{i=1}^{n}{E(\text{步数}\ |\ \text{最后留下的是i颜色的球})}$

设 $f_i$ 表示有 $i$ 种该颜色的球，可以列出方程 $f_i=p\times{(f_{i-1}+f_{i+1})}+(1-2p)\times{f_i}+w\ ,\ f_s=0$，$w$ 就是期望贡献。

可以发现由于这是一个条件期望，即不应该计算最后变成 $f_0$ 的概率。可以发现 $f_i$ 变成 $f_{i+1}$ 的概率和变成 $f_{i-1}$ 的概率相同，易得此时 $f_i$ 到 $f_s$ 的概率为 $\frac{i}{s}$。

也就是对于 $f_i$ 来说，这里的期望只有 $\frac{i}{s}$ 的部分对答案**有贡献**，所以 $w=\frac{i}{s}$。

接下来由于 $f_0=0,f_n=0$（因为不计任何贡献），可得 $f_1=\frac{(s-1)^2}{s}$，然后递推得出其他式子即可。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define mod 1000000007
#define ll long long
using namespace std;
ll f[N];
int a[N];
ll ksm(ll a,ll b=mod-2)
{
    ll r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=r*a%mod;
        a=a*a%mod;
    }
    return r;
}
int main()
{
    int n,m=0;
    ll s=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),s+=a[i],m=max(m,a[i]);
    f[0]=0,f[1]=1ll*(s-1)*(s-1)%mod*ksm(s)%mod;
    f[2]=2*f[1]-1;
    for(int i=1;i<m;i++)
    f[i+1]=(2*f[i]-f[i-1]-1ll*(s-1)*ksm(s-i)%mod+mod)%mod;
    ll ans=0;
    for(int i=1;i<=n;i++) ans=(ans+f[a[i]]+mod)%mod;
    printf("%lld\n",ans);
    return 0;
}
```
