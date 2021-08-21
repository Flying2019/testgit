#include<iostream>
#include<cstdio>
#include<cstring>
#define N 210
#define mod 998244353
#define ll long long
using namespace std;
const int G=3,Gi=(mod+1)/G,inv2=(mod+1)/2;
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
    for(;lim<=n;lim<<=1) l++;
    for(int i=1;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    return lim;
}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int dec(int x,int y){return x-y<0?x-y+mod:x-y;}
void ntt(int f[],int lim,int opt)
{
    for(int i=0;i<lim;i++)
    if(i<rev[i]) swap(f[rev[i]],f[i]);
    for(int mid=1;mid<lim;mid<<=1)
    {
        int r=ksm(opt==1?G:Gi,(mod-1)/(mid*2));
        for(int i=0;i<lim;i+=mid<<1)
            for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
            {
                int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
                f[i+j]=add(x,y);f[i+j+mid]=dec(x,y);
            }
    }
    if(opt==-1)
    {
        int r=ksm(lim);
        for(int i=0;i<lim;i++) f[i]=1ll*f[i]*r%mod;
    }
}
void mul(int f[],int g[],int lim)
{
    ntt(f,lim,1);ntt(g,lim,1);
    for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%mod;
    ntt(f,lim,-1);
}
void ntt_mul(int f[],const int g[],int n)
{
    static int h[N];
    for(int i=0;i<n;i++) h[i]=g[i];
    int lim=get_rev(n*2);
    ntt(f,lim,1);ntt(h,lim,1);
    for(int i=0;i<lim;i++) f[i]=1ll*f[i]*h[i]%mod;
    ntt(f,lim,-1);
}
void inv(int f[],int g[],int n)
{
    if(n==1){g[0]=ksm(f[0]);return;}
    inv(f,g,(n+1)>>1);
    static int h[N];
    int lim=get_rev(n<<1);
    for(int i=0;i<n;i++) h[i]=f[i];
    for(int i=n;i<lim;i++) h[i]=0;
    ntt(h,lim,1);ntt(g,lim,1);
    for(int i=0;i<lim;i++) g[i]=(2ll-1ll*h[i]*g[i]%mod+mod)%mod*g[i]%mod;
    ntt(g,lim,-1);
    for(int i=n;i<lim;i++) g[i]=0;
}
void dn(int f[],int g[],int n){for(int i=1;i<n;i++) g[i-1]=1ll*f[i]*i%mod;g[n-1]=0;}
void up(int f[],int g[],int n){for(int i=1;i<n;i++) g[i]=1ll*f[i-1]*ksm(i)%mod;g[0]=0;}
void eps(int f[],int g[],int n)
{
    static int h[N],v[N];
    for(int i=0;i<=n<<2;i++) h[i]=v[i]=0;
    dn(f,h,n),inv(f,v,n);
    int lim=get_rev(n*2);
    mul(h,v,lim);
    up(h,g,lim);
}
void exp(int f[],int g[],int n)
{
    if(n==1){g[0]=1;return;}
    exp(f,g,(n+1)>>1);
    static int h[N];
    for(int i=0;i<n<<2;i++) h[i]=0;
    eps(g,h,n);
    for(int i=0;i<n;i++) h[i]=dec(f[i],h[i]);
    h[0]=(h[0]+1)%mod;
    int lim=get_rev(n*2);
    mul(g,h,lim);
    for(int i=n;i<=lim;i++) g[i]=0;
}
int f[N],g[N],b[N],b2[N],b3[N],s[N],fac[N],iv[N];
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    iv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) iv[i]=1ll*iv[i+1]*(i+1)%mod;
}
inline ll C2(int x){return 1ll*x*(x-1)/2%mod;}
void init_forest(int n)
{
    static int h[N];
    h[1]=1;
    for(int i=2;i<n;i++) h[i]=1ll*iv[i]*ksm(i,i-2)%mod;
    exp(h,f,n);
    for(int i=2;i<n;i++) g[i]=1ll*ksm(i,i-2)*C2(i)%mod*iv[i]%mod;
    ntt_mul(g,f,n);
    for(int i=1;i<n;i++) b[i]=1ll*ksm(i,i)*iv[i]%mod;
    for(int i=0;i<n;i++) b2[i]=b3[i]=b[i];
    ntt_mul(b2,b,n);ntt_mul(b3,b2,n);
    for(int i=0;i<n;i++) s[i]=(b2[i]+b3[i]*2ll)%mod;
    ntt_mul(s,f,n);
    for(int i=1;i<n;i++)
    f[i]=1ll*f[i]*fac[i]%mod,g[i]=1ll*g[i]*fac[i]%mod,s[i]=1ll*s[i]*fac[i]%mod;
}
int an[N],am[N],mxn;
int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++) scanf("%d%d",&an[i],&am[i]),mxn=max(mxn,an[i]);
    init();init_forest(mxn);
    for(int i=1;i<=t;i++)
    {
        int n=an[i],m=am[i];
        m=1ll*m*m%mod*(C2(n)*f[n]%mod-s[n]+mod)%mod;
        printf("%lld\n",1ll*ksm(f[n])*(m+1ll*s[n]*inv2%mod)%mod);
    }
    return 0;
}