#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define il inline
#define S(a) ((int)a.size())
#define Be(a) a.begin()
#define Ed(a) a.end()
#define R(a,n) (a.resize(n))
#define P(...) poly({__VA_ARGS__})
using namespace std;
const int N=200010,mod=998244353;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int fac[N],inv[N],iv[N];
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    iv[1]=1;
    for(int i=2;i<=n;i++) iv[i]=1ll*(mod-mod/i)*iv[mod%i]%mod;
}
typedef vector<int> poly;
typedef const vector<int>& cpoly;
il int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int dec(int x,int y){return x-y<0?x-y+mod:x-y;}
poly operator +(poly a,poly b)
{
    int m=max(S(a),S(b));R(a,m);R(b,m);
    poly c(m);
    for(int i=0;i<m;i++) c[i]=add(a[i],b[i]);
    return c;
}
poly operator -(poly a,poly b)
{
    int m=max(S(a),S(b));R(a,m);R(b,m);
    poly c(m);
    for(int i=0;i<m;i++) c[i]=dec(a[i],b[i]);
    return c;
}
namespace NTT{
    int rev[N*4];
    const int G=3,Gi=(mod+1)/G;
    int get_rev(int n)
    {
        int lim=1,l=0;
        for(;lim<=n;lim<<=1) l++;
        for(int i=1;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
        return lim;
    }
    void ntt(poly &f,int lim,int op=1)
    {
        for(int i=0;i<lim;i++)
        if(i<rev[i]) swap(f[i],f[rev[i]]);
        for(int mid=1;mid<lim;mid<<=1)
        {
            int r=ksm(op==1?G:Gi,(mod-1)/(mid*2));
            for(int i=0;i<lim;i+=mid<<1)
                for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
                {
                    int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
                    f[i+j]=add(x,y);f[i+j+mid]=dec(x,y);
                }
        }
        if(op==-1){int r=ksm(lim);for(int i=0;i<lim;i++) f[i]=1ll*f[i]*r%mod;}
    }
}
using NTT::get_rev;using NTT::ntt;
poly Set(poly a,int n){if(n>S(a)){R(a,n);return a;}else return poly(Be(a),Be(a)+n);}
poly operator *(poly a,poly b)
{
    int m=S(a)+S(b)-1;
    if(min(S(a),S(b))<=3)
    {
        poly c(m);
        for(int i=0;i<S(a);i++) for(int j=0;j<S(b);j++) c[i+j]=add(c[i+j],1ll*a[i]*b[j]%mod);
        return c;
    }
    int lim=get_rev(m);
    R(a,lim);R(b,lim);
    ntt(a,lim);ntt(b,lim);
    for(int i=0;i<lim;i++) a[i]=1ll*a[i]*b[i]%mod;
    ntt(a,lim,-1);
    return Set(a,m);
}
poly Inv(poly a)
{
    if(S(a)==1) return P(ksm(a[0]));
    int m=(S(a)+1)>>1;
    poly b=Inv(Set(a,m));
    return Set((P(2)-a*b)*b,S(a));
}
poly Der(poly a){for(int i=1;i<S(a);i++) a[i-1]=1ll*a[i]*i%mod;a.pop_back();return a;}
poly Int(poly a){a.push_back(0);for(int i=S(a)-1;i;i--) a[i]=1ll*a[i-1]*iv[i]%mod;a[0]=0;return a;}
poly ln(poly a){return Set(Int(Der(a)*Inv(a)),S(a));}
poly exp(poly a)
{
    if(S(a)==1) return P(1);
    int m=(S(a)+1)>>1;
    poly b=Set(exp(Set(a,m)),S(a));
    return Set(b*(P(1)+a-ln(b)),S(a));
}
poly f,g,h;
void init_tree(int n=N-9)
{
    R(f,n);R(g,n);R(h,n);
    f[1]=1;
    for(int i=2;i<n;i++) f[i]=1ll*ksm(i,i-2)*inv[i]%mod;
    f=exp(f);
    for(int i=2;i<n;i++) g[i]=1ll*C(i,2)%mod*ksm(i,i-2)%mod*inv[i]%mod;
    g=g*f;
    for(int i=1;i<n;i++) h[i]=1ll*ksm(i,i)*inv[i]%mod;
    h=Set(Set(h*h,n)*Set((h+P(ksm(2)))*f,n),n);
    for(int i=1;i<n;i++) f[i]=1ll*f[i]*fac[i]%mod,g[i]=1ll*g[i]*fac[i]%mod,h[i]=1ll*h[i]*fac[i]%mod;
}
int main()
{
    init();
    init_tree();
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        m=1ll*m*m%mod;
        int ans=1ll*m*C(n,2)%mod+1ll*(h[n]-1ll*m*g[n]%mod)*ksm(f[n])%mod;
        printf("%d\n",(ans%mod+mod)%mod);
    }
    return 0;
}