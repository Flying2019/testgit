#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N=300010;
typedef pair<int,int> P;
#define fi first
#define se second
#define MP make_pair
vector<int>g[N],e[N];
int fa[N],siz[N],son[N],dep[N];
void dfs1(int u,int p)
{
    fa[u]=p;siz[u]=1;dep[u]=dep[p]+1;
    for(int v:g[u])
    {
        dfs1(v,u);siz[u]+=siz[v];
        if(siz[son[u]]<siz[v]) son[u]=v;
    }
}
int top[N];
void dfs2(int u,int topp)
{
    top[u]=topp;if(son[u]) dfs2(son[u],topp);
    for(int v:g[u]) if(v!=son[u]) dfs2(v,v);
}
int lca(int x,int y){for(;top[x]!=top[y];x=fa[top[x]]) if(dep[top[x]]<dep[top[y]]) swap(x,y);return dep[x]<dep[y]?x:y;}
int p[N],f[N];
int find(int x,int f[]){return f[x]==x?f[x]:(f[x]=find(f[x],f));}
bool merge(int x,int y)
{
    x=find(x,f),y=find(y,f);
    if(x==y) return false;
    f[x]=y;return true;
}
int x[N],y[N],w[N],id[N];
vector<P>ban[N];bool vis[N],cut[N];
int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) f[i]=p[i]=i;
    for(int i=2,u;i<=n;i++) scanf("%d",&u),g[u].push_back(i);
    dfs1(1,0);dfs2(1,1);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&x[i],&y[i],&w[i]),id[i]=i;
    for(int i=1,t,u,v;i<=k;i++) scanf("%d%d%d",&t,&u,&v),ban[t].push_back(MP(u,v));
    sort(id+1,id+m+1,[&](int x,int y){return w[x]<w[y];});
    long long ans=0;
    for(int _=1;_<=m;_++)
    {
        int i=id[_],c=lca(x[i],y[i]),tt=0;
        int d=dep[x[i]]+dep[y[i]]-2*dep[c];
        if(d>ban[i].size())
        {
            c=find(c,p);
            for(int u=find(x[i],p);u!=c;u=find(u,p)) tt+=merge(u,fa[u]),p[u]=fa[u];
            for(int u=find(y[i],p);u!=c;u=find(u,p)) tt+=merge(u,fa[u]),p[u]=fa[u];
            ans+=1ll*w[i]*tt;
            continue;
        }
        vector<int>q;q.reserve(d);q.push_back(c);
        for(int u=x[i];u!=c;u=fa[u]) q.push_back(u);
        for(int u=y[i];u!=c;u=fa[u]) q.push_back(u);
        for(auto &[u,v]:ban[i]) e[u].push_back(v),e[v].push_back(u);
        int rt=0;
        for(int u:q) if(!rt || e[u].size()<e[rt].size()) rt=u;
        for(int v:e[rt]) vis[v]=true;
        for(int u:q) if(u!=rt && !vis[u]) tt+=merge(rt,u);
        for(int u:e[rt])
        {
            int c=e[rt].size()+e[u].size();
            for(int v:e[u]){cut[v]=true;if(vis[v]) --c;}
            if(c<q.size()) tt+=merge(rt,u);
            for(int v:e[rt]) if(!cut[v]) tt+=merge(u,v);
            for(int v:e[u]) cut[v]=false;
        }
        ans+=1ll*w[i]*tt;
        for(int u:q) vis[u]=0,e[u].clear();
    }
    printf("%lld\n",ans);
    return 0;
}