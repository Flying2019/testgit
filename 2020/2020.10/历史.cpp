#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 400010
using namespace std;
ll a[N],dsz[N],sz[N];
int fa[N],ch[N][2];
bool nroot(int u){return ch[fa[u]][0]==u || ch[fa[u]][1]==u;}
void update(int u){sz[u]=sz[ch[u][0]]+sz[ch[u][1]]+dsz[u]+a[u];}
void rotate(int u)
{
    int f=fa[u],ff=fa[f],k=ch[f][1]==u,v=ch[u][!k];
    if(nroot(f)) ch[ff][ch[ff][1]==f]=u;
    ch[u][!k]=f;ch[f][k]=v;
    if(v) fa[v]=f;fa[f]=u;fa[u]=ff;
    update(f);
}
void splay(int u)
{
    for(;nroot(u);rotate(u))
    if(nroot(fa[u])) rotate((ch[fa[fa[u]]][0]==fa[u])^(ch[fa[u]][0]==u)?u:fa[u]);
    update(u);
}
ll ans;
int nxt[N<<1],to[N<<1],head[N],cnt;
int op[N];
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
void dfs(int u,int p)
{
    fa[u]=p;
    ll mx=a[u];int md=u;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
        dsz[u]+=sz[v];
        if(mx<sz[v]) mx=sz[v],md=v;
    }
    sz[u]=dsz[u]+a[u];
    if(mx*2>sz[u])
    {
        ans+=(sz[u]-mx)*2;
        if(u!=md) op[u]=0,dsz[u]-=sz[md],ch[u][1]=md;
        else op[u]=1;
    }
    else op[u]=2,ans+=sz[u]-1;
}
void access(int u,ll w)
{
    for(int v=0;u;v=u,u=fa[u])
    {
        splay(u);
        ll s=sz[u]-sz[ch[u][0]];
        if(op[u]==0) ans-=(s-sz[ch[u][1]])*2;
        else if(op[u]==1) ans-=(s-a[u])*2;
        else ans-=s-1;
        s+=w;sz[u]+=w;
        if(v) dsz[u]+=w;else a[u]+=w;
        if(sz[v]*2>s) dsz[u]=dsz[u]+sz[ch[u][1]]-sz[v],ch[u][1]=v;
        if(sz[ch[u][1]]*2>s) op[u]=0,ans+=(s-sz[ch[u][1]])*2;
        else
        {
            dsz[u]+=sz[ch[u][1]],ch[u][1]=0;
            if(a[u]*2>s) op[u]=1,ans+=(s-a[u])*2;
            else op[u]=2,ans+=s-1;
        }
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    printf("%lld\n",ans);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        access(u,v);
        printf("%lld\n",ans);
    }
    return 0;
}