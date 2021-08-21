#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<cassert>
#define N 400010
#define M 600010
#define inf 100000000
using namespace std;
int nxt[M<<2],to[M<<2],w[M<<2],head[N],cnt=1,id[M<<2];
void add(int u,int v,int f,int d)
{
    nxt[++cnt]=head[u];to[cnt]=v;
    id[cnt]=d;w[cnt]=f;head[u]=cnt;
}
void adde(int u,int v,int id=0,int w1=inf,int w2=0){add(u,v,w1,id);add(v,u,w2,id);}
int all,dep[N],cur[N];
queue<int>q;
bool bfs(int s,int t)
{
    for(int i=1;i<=all;i++) dep[i]=0,cur[i]=head[i];
    q.push(s);dep[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
        if(w[i])
        {
            int v=to[i];
            if(!dep[v]) dep[v]=dep[u]+1,q.push(v);
        }
    }
    return dep[t];
}
int dfs(int u,int t,int flow)
{
    if(!flow || u==t) return flow;
    int r=0;
    for(int &i=cur[u];i;i=nxt[i])
    if(w[i])
    {
        int v=to[i],f;
        if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(flow,w[i]))))
        {
            flow-=f,r+=f;
            w[i]-=f,w[i^1]+=f;
            if(!flow) break;
        }
    }
    return r;
}
int s,t,n,m,ans[N];
int dinic(int s,int t){int r=0;while(bfs(s,t)) r+=dfs(s,t,inf),assert(r<=n);return r;}
int x[N],y[N],tt;
int tu[N],tv[N],link[N];
bool vis[N];
void dfs(int u)
{
    for(int i=head[u];i;i=nxt[i])
    if(w[i])
    {
        int v=to[i];
        if(v==s || vis[v]) continue;
        vis[v]=true; ++tt;
        tu[v]=id[i],tv[v]=link[v];
        dfs(x[link[v]]);
    }
}
namespace Con{
    vector<int>g[N];
    int dep[N],fa[N],siz[N];
    void dfs(int u,int p)
    {
        dep[u]=dep[p]+1;fa[u]=p;siz[u]=1;
        for(int v:g[u]) if(v!=p) dfs(v,u),siz[u]+=siz[v];
    }
    void solve()
    {
        for(int i=n+1;i<n*2;i++) g[x[tu[i]]].push_back(x[tv[i]]),g[x[tv[i]]].push_back(x[tu[i]]);
        dfs(1,0);
        for(int i=n+1;i<n*2;i++)
        {
            if(dep[x[tu[i]]]<dep[x[tv[i]]]) swap(tu[i],tv[i]);
            ans[tu[i]]=n-siz[x[tu[i]]];
            ans[tv[i]]=n-ans[tu[i]];
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    s=2*n,t=s+1;all=t;
    for(int i=1;i<=n;i++) adde(s,i,0,1);
    for(int i=1;i<n;i++) adde(i+n,t,0,1);
    for(int i=1;i<=m;i++) scanf("%d%d",&y[i],&x[i]),adde(x[i],y[i]+n,i,1),assert(y[i]<n);
    int res=dinic(s,t);
    if(res!=n-1){puts("-1");return 0;}
    for(int u=n+1;u<n*2;u++)
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];if(v==t || !w[i]) continue;
            link[u]=id[i];
        }
    for(int i=head[s];i;i=nxt[i]) if(w[i]){dfs(to[i]);break;}
    cerr<<tt<<endl;
    if(tt!=n-1){puts("-1");return 0;}
    Con::solve();
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}