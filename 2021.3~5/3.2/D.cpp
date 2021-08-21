#include<iostream>
#include<cstdio>
#include<cstring>
#define N 800010
#define mod 998244353
using namespace std;
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
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
char s[N];
int U[N],L[N],D[N],R[N];
void init(int p[],int n)
{
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) p[i]=s[i]=='1';
}
int fp[N],fs[N],ans;
int calc(int x,int y)//cut x into y pieces
{
    return !x?!y:C(x+y-1,y);
}
int gs[N];
void work(int n,int m)
{
    memset(fs,0,sizeof(fs));
    memset(fp,0,sizeof(fp));
    memset(gs,0,sizeof(gs));
    for(int i=1;i<=n;i++) fp[i]=fp[i-1]+U[i]+D[i];
    for(int i=n;i;i--) fs[i]=fs[i+1]+U[i]+D[i];
    int sl=0,sr=0;
    for(int i=1;i<=m;i++) sl+=L[i],sr+=R[i];
    gs[0]=1;
    for(int i=1;i<=n;i++)
    {
        gs[i]=gs[i-1];if(!U[i] && !D[i]) continue;
        gs[i]=(1ll*gs[i]*(U[i]+D[i])+calc(sl,fp[i]))%mod;
    }
    for(int i=1;i<=n;i++)
    if(U[i] || D[i]) ans=(ans+1ll*calc(sr,fs[i+1])*gs[i-1]*(U[i]+D[i]))%mod;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();init(U,n);init(D,n);init(L,m);init(R,m);
    bool c=0;
    for(int i=1;i<=n;i++) c|=U[i],c|=D[i];
    for(int i=1;i<=m;i++) c|=L[i],c|=R[i];
    if(!c){puts("1");return 0;}
    work(n,m);
    for(int i=1;i<=max(n,m);i++) swap(U[i],L[i]),swap(D[i],R[i]);
    work(m,n);
    printf("%d\n",ans);
    return 0;
}