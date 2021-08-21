#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2000010
using namespace std;
int mod,n;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int inv[N];
bool S[N];
bool checkG(int g){for(int i=1;i<mod-1;i++) if(ksm(g,i)==1) return false;return true;}
namespace NTT{
    const int mod=998244353,G=3,Gi=(mod+1)/G;
    int ksm(int a,int b=mod-2)
    {
        int r=1;
        for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
        return r;
    }
    inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
    inline int dec(int x,int y){return x-y<0?x-y+mod:x-y;}
    int rev[N*2];
    int get_rev(int n)
    {
        int lim=1,l=0;
        while(lim<=n) lim<<=1,l++;
        for(int i=1;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
        return lim;
    }
    void ntt(int f[],int lim,int op=1)
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
    void mul(int f[],int g[],int n)
    {
        int lim=get_rev(n*2);
        ntt(f,lim,1);ntt(g,lim,1);
        for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%mod;
        ntt(f,lim,-1);
    }
}
int t0;
int f1[N*2],f2[N*2],_g[N];
int sq2(int x){return 1ll*x*x%mod;}
bool chk(int x,int y)
{
    if(!sq2(3*x+y) || !sq2(3*x+2*y)) return false;
    return S[(1ll*(sq2(2*x+3*y)+5*sq2(x))*inv[sq2(3*x+y)]+1ll*(sq2(2*x+5*y)+3*sq2(y))*inv[sq2(3*x+2*y)])%mod];
}
int X[N];
int main()
{
    scanf("%d%d",&mod,&n);
    int g=2;
    while(!checkG(g)) g++;
    inv[1]=1;
    for(int i=2;i<mod;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    for(int i=0,j=1;i<mod-1;i++,j=1ll*j*g%mod) _g[j]=i;
    for(int i=0,x;i<n;i++)
    {
        scanf("%d",&x);X[i]=x;
        if(x) f1[_g[x]]++,f2[_g[inv[x]]]++;
        else t0++;
    }
    int m;
    scanf("%d",&m);
    for(int i=0,x;i<m;i++) scanf("%d",&x),S[x]=true;
    long long ans=0;
    if(t0 && n>1)
    {
        for(int i=0;i<n;i++)
        if(X[i]) ans+=chk(0,X[i])+chk(X[i],0);
    }
    NTT::mul(f1,f2,mod-1);
    for(int i=mod-1;i<mod*2-1;i++) f1[i-(mod-1)]+=f1[i];
    for(int i=0,j=1;i<mod-1;i++,j=1ll*j*g%mod)
        if(chk(j,1)) ans+=f1[i];
    printf("%lld\n",ans);
    return 0;
}