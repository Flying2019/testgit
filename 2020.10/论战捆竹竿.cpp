#include<iostream>
#include<cstdio>
#include<cstring>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#define N 500010
#define ll long long
#define inf 2000000000000000000ll
using namespace std;
int nxt[N],q[N<<1],qt,sq[N],st,bd[N],bt,pos[N];
ll f[N],g[N],h[N],ans;
char s[N];
int n;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
void get_fail(void)
{
    nxt[0]=nxt[1]=0;
    for(int i=1;i<n;i++)
    {
        int u=nxt[i];
        for(;u && s[u]!=s[i];u=nxt[u]);
        nxt[i+1]=s[u]==s[i]?u+1:0;
    }

    for(int u=nxt[n];u;u=nxt[u]) bd[++bt]=n-u;
    bd[++bt]=n;
}
int pre,qh,qd;
ll qu[N];
void pre_work(int mod)
{
    int c=gcd(mod,pre);
    for(int i=0;i<pre;i++) g[i]=f[i];
    for(int i=0;i<mod;i++) f[i]=inf;
    for(int i=0;i<pre;i++) f[g[i]%mod]=min(f[g[i]%mod],g[i]);
    for(int i=0;i<c;i++)
    {
        qt=0;q[++qt]=i;
        for(int u=(i+pre)%mod;u!=q[1];u=(u+pre)%mod) q[++qt]=u;
        for(int j=qt+1;j<=qt*2;j++) q[j]=q[j-qt];
        for(int j=2;j<=qt*2;j++) f[q[j]]=min(f[q[j]],f[q[j-1]]+pre);
    }
    pre=mod;
}
void work(int mod,int d,int len)
{
    int c=gcd(mod,d);
    pre_work(mod);
    if(d<0) return;
    for(int i=0;i<c;i++)
    {
        qt=st=0;q[++qt]=i;
        for(int u=(i+d)%mod;u!=q[1];u=(u+d)%mod) q[++qt]=u;
        int v=1;
        for(int j=1;j<=qt;j++)
        if(f[q[j]]<f[q[v]]) v=j;
        for(int j=v;j<=qt;j++) sq[++st]=q[j];
        for(int j=1;j<v;j++) sq[++st]=q[j];
        pos[1]=1;qu[1]=f[sq[1]]-d;
        qh=qd=1;
        for(int j=2;j<=qt;j++)
        {
            for(;qh<=qd && pos[qh]+len<j;++qh);
            if(qh<=qd) f[sq[j]]=min(f[sq[j]],qu[qh]+1ll*j*d+mod);
            for(;qh<=qd && qu[qd]>=f[sq[j]]-1ll*j*d;qd--);
            qu[++qd]=f[sq[j]]-1ll*j*d,pos[qd]=j;
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        ll w;
        scanf("%d%lld%s",&n,&w,s);w-=n;
        memset(f,0x3f,sizeof(ll[n]));
        f[0]=ans=bt=0;
        pre=n;
        get_fail();
        int p=1;
        for(int i=1;i<=bt;i=p)
        {
            for(;bd[p+1]-bd[p]==bd[i+1]-bd[i];p++);
            work(bd[i],bd[i+1]-bd[i],p-i-1);
        }
        for(int i=0;i<pre;i++)
            if(f[i]<=w) ans+=(w-f[i])/pre+1;
        printf("%lld\n",ans);
    }
    return 0;
}