#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=8010,mod=998244353;
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
int C(int a,int b){return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-5)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
namespace ntt{
    const int G=3,Gi=(mod+1)/G;
    int rev[N<<2];
    int init_rev(int n)
    {
        int lim=1,l=0;
        while(lim<=n) lim<<=1,l++;
        for(int i=1;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
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
}
int f[N<<2],g[N<<2],h1[N<<2],h2[N<<2];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    int lim=ntt::init_rev((n+1)*2);
    f[0]=1;
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<=n;j++) g[j]=1ll*f[j]*(1+j+1ll*j*(j-1)/2%mod)%mod;
        for(int j=0;j<=n;j++) h1[j]=1ll*f[j]*inv[j]%mod,h2[j]=inv[j+2];
        h2[0]=0;
        for(int j=n+1;j<=lim;j++) h1[j]=h2[j]=0;
        ntt::ntt(h1,lim,1);ntt::ntt(h2,lim,1);
        for(int j=0;j<lim;j++) f[j]=1ll*h1[j]*h2[j]%mod;
        ntt::ntt(f,lim,-1);
        for(int j=0;j<=n;j++) f[j]=(1ll*fac[j+2]*f[j]+g[j])%mod;
        for(int j=n+1;j<lim;j++) f[j]=0;
    }
    int ans=0;
    for(int i=0;i<=n;i++) ans=(ans+1ll*C(n,i)*f[i])%mod;
    printf("%d\n",ans);
    return 0;
}