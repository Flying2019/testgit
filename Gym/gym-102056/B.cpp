#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 40010
#define il inline
using namespace std;
int mod,G,Gi;
int fac[N],inv[N];
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
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-5)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    auto check=[&](int x)
    {
        int y=mod-1;
        for(int i=2;1ll*i*i<=y;i++)
        if(y%i==0){if(ksm(x,i)==1 || ksm(x,y/i)==1) return false;}
        return true;
    };
    for(int g=2;;g++) if(check(g)){G=g;Gi=ksm(g);return;}
}
int rev[N];
il int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int dec(int x,int y){return x<y?x-y+mod:x-y;}
il int mul(int x,int y){return 1ll*x*y%mod;}
int get_rev(int n)
{
    int l=0,lim=1;
    for(;lim<=n;lim<<=1) l++;
    for(int i=1;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    return lim;
}
typedef vector<int> poly;
void ntt(poly &f,int lim,int op=1)
{
    for(int i=1;i<lim;i++)
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
    if(op==-1)
    {
        int r=ksm(lim);
        for(int i=0;i<lim;i++) f[i]=1ll*f[i]*r%mod;
    }
}
#define S(a) ((int)a.size())
#define R(a) resize(a)
poly set(const poly &a,int n){poly c(n);for(int i=0;i<min(n,S(a));i++) c[i]=a[i];return c;}
poly operator *(poly a,int b){for(int i=0;i<S(a);i++) a[i]=mul(a[i],b);return a;}
poly operator *(poly a,poly b)
{
    int m=S(a)+S(b)-1,lim=get_rev(m);
    a.R(lim),b.R(lim);ntt(a,lim);ntt(b,lim);
    for(int i=0;i<lim;i++) a[i]=mul(a[i],b[i]);
    ntt(a,lim,-1);
    a.R(m);return a;
}
poly operator +(poly a,poly b){a.R(max(S(a),S(b)));for(int i=0;i<S(b);i++) a[i]=add(a[i],b[i]);return a;}
poly operator -(poly a,poly b){a.R(max(S(a),S(b)));for(int i=0;i<S(b);i++) a[i]=dec(a[i],b[i]);return a;}
poly operator >>(const poly &a,int b){poly c(a.size());for(int i=b;i<S(a);i++) c[i-b]=a[i];return c;}
poly operator <<(const poly &a,int b){poly c(a.size());for(int i=b;i<S(a);i++) c[i]=a[i-b];return c;}
poly Inv(poly a)
{
    int n=S(a);
    if(n==1) return poly({ksm(a[0])});
    int m=(n+1)>>1;
    poly b=Inv(set(a,m));
    return set(set(b,n)*2-set(set(a,m)*b,m)*b,n);
}
poly operator /(const poly &a,const poly &b){return a*Inv(b);}
int main()
{
    int n;
    scanf("%d%d",&n,&mod);++n;
    init();
    poly f({0,1});
    for(int len=2;len<=n;)
    {
        len*=2;
        poly g2=set(f*f,len),g3=set(g2*f,len),g4=set(g3*f,len);
        f.R(len);
        f=f-(g4+g2*2-f-(f<<1)+poly({0,1}))/(g3*4+f*4-poly({1,1}));
    }
    for(int i=1;i<n;i++) printf("%d\n",f[i]);
    // printf("%d\n",f[1]);
    return 0;
}