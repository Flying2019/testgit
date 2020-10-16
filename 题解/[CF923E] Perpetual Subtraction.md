### [����](https://codeforces.com/contest/923/problem/E)
���ȸ������⣬���ǿ����Ƴ�dpʽ�ӣ��� $f_t(i)$ ��ʾ�� $t$ �β�������֮ǰ������ $i$ �ĸ��ʡ�

��ô��Ȼ�У�

$$f_{t+1}(i)=\sum_{j=i}^{n}\frac{f_t(j)}{j+1}$$

�������ɺ���������

$$F_t(x)=\sum_{i=0}^{n} f_t(i)x^i$$

��Ȼ�У�

$$F_{t+1}(x)=\sum_{i=0}^{n} \sum_{j=0}^{i} \frac{f_t(j)}{j+1}x^i$$

$$F_{t+1}(x)=\sum_{j=0}^{n} \frac{f_t(j)}{j+1}\sum_{i=0}^j x^i$$

$$F_{t+1}(x)= \frac 1 {x+1}\sum_{j=0}^{n} {f_t(j)}\int_{1}^{x}k^j\ \text{d}k$$

$$F_{t+1}(x)= \frac 1 {x+1}\int_{1}^{x}{\sum_{j=0}^{n}f_t(j)}k^j\ \text{d}k$$

$$F_{t+1}(x)=\frac 1 {x+1}\int_{1}^{x}{F_t(k)}\ \text{d}k$$

����ȥ�������½��1������ $G_t(x)=F_t(x+1)$�������Ƴ���

$$G_{t+1}(x)=\frac 1 {x}\int_{0}^{x}{F_t(k+1)}\ \text{d}(k+1)$$

$$G_{t+1}(x)=\sum_{i=0}^{n}\frac {g_t(i)}{i+1}x^i$$

$$g_{t+1}(x)=\frac{g_t(i)}{i+1}$$

$$g_{t+1}(x)=g_1(i)\times{(i+1)^{-t}}$$

��ô����ֻҪ��� $g_1(i)$���Ϳ��Կ������ $g_t(i)$��

���������� $g_1(i)$�����ݶ��壺

$$\sum_{i=0}^n{g_t(i)x^i}=\sum{f_t(i)(x+1)^i}$$

�𿪿ɵã�

$$g_t(i)=\sum_{j=i}^{n}\binom{j}{i}f_t(j)$$

�� $f_1(i)=p_i$�����Կ����� $\text{NTT}$ ���ټ��� $g_1(i)$��

��������� $g_t(i)$ ���� $f_t(i)$�����ö���ʽ���ݿɵã�

$$f_t(i)=\sum_{j=i}^{n}(-1)^{j-1}\binom{j}{i}f_t(j)$$

������Ҳ��һ�������ʽ $\text{NTT}$ �����ɡ����Ӷ� $O(n\log n)$��
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
