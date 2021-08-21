#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define mod 998244353
using namespace std;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int p[N],pt;bool pr[N];
void init(int n=N-10)
{
    pr[1]=true;
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]) p[++pt]=i;
        for(int j=1;j<=pt && i*p[j]<=n;j++){pr[i*p[j]]=true;if(i%p[j]==0) break;}
    }
}
void add_miu(int f[],int n)
{
    for(int i=pt;i;i--)
        for(int j=n/p[i];j;j--) f[p[i]*j]=(f[p[i]*j]-f[j]+mod)%mod;
}
void dec_miu(int f[],int n)
{
    for(int i=1;i<=pt;i++)
        for(int j=1;j*p[i]<=n;j++) f[j]=(f[j]-f[p[i]*j]+mod)%mod;
}
int f[N],g[N],b[N],iB[N],c,d;
int main()
{
    int n,q;
    scanf("%d%d%d%d",&n,&c,&d,&q);c%=mod-1;d%=mod-1;
    init();
    for(int i=1;i<=n;i++) iB[i]=ksm(i,mod-1-d),g[i]=ksm(i,mod-1+c-d);
    add_miu(g,n);
    for(int i=1;i<=n;i++) g[i]=ksm(g[i]);
    while(q --> 0)
    {
        for(int i=1;i<=n;i++) scanf("%d",&b[i]),b[i]=1ll*b[i]*iB[i]%mod;
        add_miu(b,n);
        bool can=true;
        for(int i=1;i<=n;i++) if(g[i]==0 && b[i]){can=false;break;}
        if(!can){puts("-1");continue;}
        for(int i=1;i<=n;i++) b[i]=1ll*b[i]*g[i]%mod;
        dec_miu(b,n);
        for(int i=1;i<=n;i++) printf("%d ",1ll*b[i]*iB[i]%mod);puts("");
    }
    return 0;
}