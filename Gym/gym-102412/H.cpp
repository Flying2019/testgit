#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<bitset>
#define N 2010
#define M 4010
using namespace std;
bitset<N>g[N];vector<int>rd[N];
int x[M],y[M];
namespace tarjan{
    vector<int>g[M*2];
    void add(int u,int v){g[u^1].push_back(v);g[v^1].push_back(u);}
    int dfn[M*2],low[M*2],scc[M*2],tt;
    int ton[M*2],tp;
    bool in[M*2];
    void dfs(int u)
    {
        dfn[u]=low[u]=++tt;
        ton[++tp]=u;in[u]=true;
        for(int v:g[u])
        {
            if(!dfn[v]) dfs(v),low[u]=min(low[u],low[v]);
            else if(in[v]) low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u])
        {
            for(int v=ton[tp--];v!=u;v=ton[tp--]) in[v]=false,scc[v]=u;
            scc[u]=u;in[u]=false;
        }
    }
    void clear(int n){for(int i=0;i<2*n;i++) g[i].clear(),dfn[i]=low[i]=scc[i]=0;tt=tp=0;}
    bool solve(int n)
    {
        for(int i=0;i<2*n;i++) if(!dfn[i]) dfs(i);
        for(int i=0;i<2*n;i+=2) if(scc[i]==scc[i+1]) return false;
        return true;
    }
}
using tarjan::clear;
using tarjan::add;
using tarjan::solve;
bool check(int m)
{
    clear(m);
    for(int i=0;i<2*m;i++)
        for(int j=0;j<i;j++)
        if(!g[y[i]][x[j]] && !g[y[j]][x[i]]) add(i,j);
    return solve(m);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n*2;i++)
    {
        scanf("%d%d",&x[i],&y[i]);--x[i];--y[i];
        rd[x[i]].push_back(y[i]);
    }
    for(int i=0;i<n;i++) g[i].set(i);
    for(int u=n-1;~u;u--)
        for(int v:rd[u]) g[u]|=g[v];
    int l=0,r=n,q=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1,q=mid;
        else r=mid-1;
    }
    printf("%d\n",q);
    return 0;
}