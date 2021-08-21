#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#define N 300010
#define il inline
using namespace std;
int x[N],y[N],w[N];
bool chs[N];
int f[N],sz[N];
int find(int x){return x==f[x]?f[x]:f[x]=find(f[x]);}
il int to(int u,int i){return find(x[i])^u^find(y[i]);}
il bool pbl(int u){return !chs[u] && find(x[u])!=find(y[u]);}
priority_queue<int,vector<int>,greater<int> >q;
struct node{
    int x,id;
    node(int X=0,int I=0):x(X),id(I){}
    bool operator <(const node a)const{return x==a.x?id<a.id:x<a.x;}
};
set<node>g[N];
void check(int u)
{
    auto &s=g[u];
    while(!s.empty())
    {
        auto t=*s.begin();
        int v=to(u,t.id);
        if(!pbl(t.id)) s.erase(t);
        else if(w[t.id]<=sz[u]+sz[v]) q.push(t.id),chs[t.id]=true,s.erase(t);
        else if(t.x<=sz[u])
        {
            int x=(w[t.id]+sz[u]-sz[v]+1)/2;
            s.erase(t);g[v].erase(node(w[t.id]-t.x,t.id));
            s.insert(node(x,t.id));g[v].insert(node(w[t.id]-x,t.id));
        }
        else return;
    }
}
bool merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return false;
    sz[y]=min(2000000,sz[x]+sz[y]);f[x]=y;sz[x]=0;
    if(g[y].size()<g[x].size()) g[y].swap(g[x]);
    for(node u:g[x]) if(pbl(u.id)) g[y].insert(u);
    g[x].clear();check(y);
    return true;
}
int ans[N],tt;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&sz[i]),f[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x[i],&y[i],&w[i]);
        g[x[i]].insert(node(w[i]/2,i));g[y[i]].insert(node(w[i]-w[i]/2,i));
    }
    for(int i=1;i<=n;i++) check(i);
    while(!q.empty())
    {
        int u=q.top();q.pop();
        if(merge(x[u],y[u])) ans[++tt]=u;
    }
    printf("%d\n",tt);
    for(int i=1;i<=tt;i++) printf("%d ",ans[i]);
    return 0;
}