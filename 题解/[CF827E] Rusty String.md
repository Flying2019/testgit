### [链接](https://www.luogu.com.cn/problem/CF827E)
首先看到带通配符的匹配，大概率就是卷积了。

考虑一种朴素的想法，即 $f_i=[s_i=\texttt{v}],g_i=[s_i=\texttt{k}],h=!(f\times g'+f'\times g)$。

即我们希望每一位都不存在“不匹配”。

但是这样存在问题，即对于循环节 $k$，实际上的要求是 $s_i=s_{i+k}=s_{i+2k}=\dots$，而不仅仅是 $s_i=s_{i+k}$。否则会导致一个通配符匹配两种字符的情况。

但是可以发现，如果 $k$ 是我们错判的一种情况，那么一定存在一个 $a>1$，$s_i\neq s_{i+ak}$。

也就是说 $k$ 成立，当且仅当对于所有 $a\geq 1$，$s_i= s_{i+ak}$ 成立。

这个暴力判断即可，复杂度为调和级数。总复杂度 $O(Tn\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 998244353
#define G 3
#define Gi ((mod+1)/G)
#define N 4000010
using namespace std;
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
int rev[N];
int get_rev(int n)
{
    int lim=1,l=0;
    while(lim<=n*2) lim<<=1,l++;
    for(int i=0;i<lim;i++)
    rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    return lim;
}
void ntt(int f[],int lim,int opt=1)
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
void mul(int f[],int g[],int n)
{
    int lim=get_rev(n);
    for(int i=n+1;i<=lim;i++) f[i]=g[i]=0;
    ntt(f,lim,1),ntt(g,lim,1);
    for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%mod;
    ntt(f,lim,-1);
}
int f[N],g[N];
bool h[N],ans[N];
char s[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d%s",&n,s+1);
        for(int i=0;i<=n;i++) f[i]=g[i]=h[i]=0;
        for(int i=1;i<=n;++i)f[n-i+1]=(s[i]=='K'),g[i]=(s[i]=='V');
        mul(f,g,n);
        for(int i=1;i<n;++i) h[i]|=f[i+n+1];
        for(int i=1;i<=n;++i)f[n-i+1]=(s[i]=='V'),g[i]=(s[i]=='K');
        mul(f,g,n);
        for(int i=1;i<n;++i) h[i]|=f[i+n+1];
        int tot=0;
        for(int i=1;i<=n;i++)
        {
            ans[i]=true;
            for(int j=i;j<=n && ans[i];j+=i) ans[i]&=!h[j];
            tot+=ans[i];
        }
        printf("%d\n",tot);
        for(int i=1;i<=n;i++)
        if(ans[i]) printf("%d ",i);
        puts("");
    }
    return 0;
}
```
