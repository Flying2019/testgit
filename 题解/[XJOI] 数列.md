### [链接](http://115.236.49.52:83/contest/1523/problem/3)
首先可以发现，对于每个 $l=a\times b\ ,\ gcd(a,b)=1$，有 $len(l)=lcm(len(a),len(b))$。

所以我们不妨对所有素数 $m=p$ 进行考虑。

可以发现 $f_n=\left(\left(\sum_{i<n}{a^i\times c}\right)+x\times a^n\right)\bmod m$。

也就是我们要找到最小的 $n$ 满足 $\left(\sum_{i<n}{a^i\times c}\right)+x\times a^n \equiv x (\bmod m)$。

接下来就是分类讨论了。首先 $a\equiv 0(\bmod m)$，这种比较好处理，显然有循环节=1。

然后我们就可以继续化简式子。
$$c\cdot\frac{a^n-1}{n-1}\equiv x(a^n-1)(\bmod m)$$
然后再考虑，如果有 $a\equiv 1(\bmod m)$ 的情况，由于 $m$ 为素数，显然 $n=1\text{ 或 }m-1$

对于剩余情况，我们可以发现有 $n=m-1$ 成立。但是这并不是唯一解。可以发现如果有对于 $n=a$ 成立，一定有 $n=ak$ 成立。

所以我们不妨筛出所有数的最小质因子，对 $m-1$ 的所有质因子进行试除，那么结果就是答案。

对于 $m=p^k$，可以发现其循环节要么和 $m=p^{k-1}$ 相等，要么再乘上 $p$，验证一下即可。

特别的，对于某些 $m$ 如果循环节为1需要特判。

复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 5000010
#define int long long
#define ll long long
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
ll mod;
ll x;
struct F{
    int x,y;
    F(int X=0,int Y=0):x(X),y(Y){}
    F operator *(const F a){return F(1ll*x*a.x%mod,(1ll*x*a.y+y)%mod);}
};
ll nxt(F a){return 1ll*a.x*x+a.y;}
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1){if(b&1) r=1ll*r*a%mod;a=1ll*a*a%mod;}
    return r;
}
F operator ^(F a,int b)
{
    F r(1,0);
    for(;b;b>>=1){if(b&1) r=r*a;a=a*a;}
    return r;
}
void operator ^=(F &a,int b){a=a^b;}
int lcm(int a,int b){return a/gcd(a,b)*b;}
int pr[N],sp[N],tot;
bool p[N];
void pre(int n)
{
    p[1]=true;
    for(int i=2;i<=n;i++)
    {
        if(!p[i]) pr[++tot]=i,sp[i]=i;
        for(int j=1;j<=tot && i*pr[j]<=n;j++)
        {
            p[i*pr[j]]=true;
            sp[i*pr[j]]=pr[j];
            if(i%pr[j]==0) break;
        }
    }
}
ll f[N];
signed main()
{
    int a,c,n;
    scanf("%lld%lld%lld%lld",&x,&a,&c,&n);
    F x0(a,c);
    pre(n);
    for(int i=1;i<=tot;i++)
    {
        mod=pr[i];
        while(mod*pr[i]<=n) mod*=pr[i];
        F x1(a%mod,c%mod);
        if(a%pr[i]==0) for(ll t=pr[i];t<=n;t*=pr[i]) f[t]=1;
        else if((a-1)%pr[i]==0)
        {
            ll l=0;
            if(nxt(x0)%pr[i]==x%pr[i]) l=1;
            else l=pr[i],x1^=pr[i];
            f[pr[i]]=l;
            for(ll t=1ll*pr[i]*pr[i];t<=n;t*=pr[i])
            {
                if(nxt(x1)%t!=x%t) l*=pr[i],x1^=pr[i];
                f[t]=l;
            }
        }
        else
        {
            ll l=pr[i]-1;
            for(ll u=l;u>1;u/=sp[u])
            if(ksm(a,l/sp[u])%pr[i]==1) l/=sp[u];
            f[pr[i]]=l;
            if(nxt(x0)%pr[i]==x%pr[i]) f[pr[i]]=1;
            x1^=l;
            for(ll t=1ll*pr[i]*pr[i];t<=n;t*=pr[i])
            {
                if(nxt(x1)%t!=x%t) l*=pr[i],x1^=pr[i];
                f[t]=l;
                if(nxt(x0)%t==x%t) f[t]=1;
            }
        }
    }
    ll ans=0;
    f[1]=1;
    for(int i=2;i<=n;i++)
    if(!f[i]){int x=i,y=1; for(;sp[x]==sp[i];x/=sp[i],y*=sp[i]);f[i]=lcm(f[x],f[y]);}
    for(int i=1;i<=n;i++) ans+=f[i];
    printf("%lld\n",ans);
    return 0;
}
```
