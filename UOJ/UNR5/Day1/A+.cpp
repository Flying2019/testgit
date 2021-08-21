#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define mod 998244353
using namespace std;
const int N=2510;
using namespace std;
struct node{
    int f0,f1,f2,h,w0,w1;
    node(int F0=0,int F1=0,int F2=0,int H=0,int W0=0,int W1=0):f0(F0%mod),f1(F1%mod),f2(F2%mod),h(H%mod),w0(W0%mod),w1(W1%mod){}
};
const node O(1),R(1,1),B(1,0,1,0,1);
node operator +(const node u,const node v){return node(u.f0+v.f0,u.f1+v.f1,u.f2+v.f2,u.h+v.h,u.w0+v.w0,u.w1+v.w1);}
node operator -(const node u,const node v){return node(u.f0-v.f0,u.f1-v.f1,u.f2-v.f2,u.h-v.h,u.w0-v.w0,u.w1-v.w1);}
node operator *(const node u,const node v)
{
    node a;
    a.w1=(1ll*u.w1*v.f0%mod+1ll*u.f0*v.w1%mod+1ll*u.f1*v.w0%mod+1ll*u.w0*v.f1%mod+2ll*u.h*v.f2%mod+2ll*v.h*u.f2%mod)%mod;
    a.w0=(1ll*u.w0*v.f0%mod+2ll*u.f2*v.f2+1ll*u.f0*v.w0)%mod;
    a.h=(1ll*u.h*v.f0%mod+1ll*u.f0*v.h%mod+1ll*u.f1*v.f2%mod+1ll*u.f2*v.f1%mod)%mod;
    a.f1=(1ll*u.f1*v.f0+1ll*u.f0*v.f1)%mod;
    a.f2=(1ll*u.f2*v.f0+1ll*u.f0*v.f2)%mod;
    a.f0=1ll*u.f0*v.f0%mod;
    return a;
}
vector<int>g[N];
int cr,cb,n,dep[N];
int ton[N],tt;char opt[6];
node f[N][N];//f_{i,j} : i 到根路径上有 j 个 R
void dfs(int u,int p)
{
    dep[u]=dep[p]+1;
    int bl=max(dep[u]-cb,0),br=min(cr,dep[u]);
    for(int i=bl;i<=br;i++) f[u][i]=O;
    for(int v:g[u])
    {
        dfs(v,u);
        for(int i=0;i<=dep[u];i++) f[u][i]=f[u][i]*f[v][i];
    }
    if(u==0) return;
    for(int i=1;i<=dep[u];i++) f[u][i-1]=f[u][i-1]*B+f[u][i]*R;
    // printf("%d\n",u);
    // for(int i=0;i<=n;i++) printf("%d ",f[u][i].f0);puts("");
}
int main()
{
    scanf("%d%d%d",&n,&cr,&cb);
    for(int i=1,t=0;i<=2*n;i++)
    {
        scanf("%s",opt);
        if(opt[1]=='u')
        {
            ++t;
            g[ton[tt]].push_back(t);
            ton[++tt]=t;
        }
        else --tt;
    }
    dep[0]=-1;
    dfs(0,0);
    printf("%d\n",(f[0][0].w1+mod)%mod);
    return 0;
}