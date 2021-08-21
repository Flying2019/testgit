#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 1000010
#define mod 998244353
#define S(a) ((int)a.size())
#define R(a) a.resize(n+1)
#define il inline
using namespace std;
il int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int dec(int x,int y){return x-y<0?x-y+mod:x-y;}
typedef vector<int> poly;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int n,c[N],ci[N];
void init()
{
    c[1]=0;
    for(int i=2;i<=n;i++)
    {
        if(!c[i]) c[i]=1;
        ci[i]=ksm(c[i]);
        for(int j=2;i*j<=n;j++) c[i*j]=c[i]+c[j];
    }
}
poly operator +(poly a,poly b)
{
    R(a);R(b);
    poly c(n+1);
    for(int i=1;i<=n;i++) c[i]=add(a[i],b[i]);
    return c;
}
poly operator -(poly a,poly b)
{
    R(a);R(b);
    poly c(n+1);
    for(int i=1;i<=n;i++) c[i]=dec(a[i],b[i]);
    return c;
}
poly operator *(poly a,int b){for(int i=0;i<S(a);i++) a[i]=1ll*a[i]*b%mod;return a;}
poly operator *(poly a,poly b)
{
    R(a);R(b);
    poly f(n+1);
    for(int i=1;i<=n;i++)
        for(int j=1;i*j<=n;j++) f[i*j]=(f[i*j]+1ll*a[i]*b[j])%mod;
    return f;
}
poly operator /(poly a,poly b)
{
    R(a);R(b);
    poly f(n+1);
    for(int i=1,r=ksm(b[1]);i<=n;i++) f[i]=1ll*a[i]*r%mod;
    for(int i=1;i<=n;i++)
        for(int j=2;i*j<=n;j++) f[i*j]=dec(f[i*j],1ll*f[i]*b[j]%mod)%mod;
    return f;
}
poly Der(poly a){for(int i=1;i<=n;i++) a[i]=1ll*a[i]*c[i]%mod;return a;}
poly Int(poly a){for(int i=1;i<=n;i++) a[i]=1ll*a[i]*ci[i]%mod;return a;}
poly ln(poly a){R(a);return Int(Der(a)/a);}
poly exp(poly a)
{
    poly f=Der(a),d=f;
    d[1]=1;
    for(int i=2;i<=n;i++)
    {
        d[i]=1ll*d[i]*ci[i]%mod;
        for(int j=2;i*j<=n;j++) d[i*j]=add(d[i*j],1ll*f[j]*d[i]%mod)%mod;
    }
    return d;
}
poly ksm(poly a,int k){return exp(ln(a)*k);}
poly f;
int main()
{
    int k;
    scanf("%d%d",&n,&k);
    init();
    R(f);
    for(int i=1;i<=n;i++) scanf("%d",&f[i]);
    f=ksm(f,ksm(k));
    for(int i=1;i<=n;i++) printf("%d ",f[i]);
    return 0;
}