#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int siz[N],n;
ll f[N];
void dfs0(int u,int p)
{
    siz[u]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs0(v,u);
        siz[u]+=siz[v];
        f[u]+=f[v];
    }
    f[u]+=siz[u];
}
ll ans=0;
void dfs(int u,int p,ll ps)
{
    ll fv=ps+f[u]-siz[u]+n;
    ans=max(ans,fv);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u,fv-siz[v]-f[v]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs0(1,0);
    dfs(1,0,0);
    printf("%lld\n",ans);
    return 0;
}