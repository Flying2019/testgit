#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 210
#define ll long long
using namespace std;
vector<int>g[N];
int son[N];
void dfs(int u,int p,int d)
{
    int t=0;
    for(int v:g[u]) if(v!=p) dfs(v,u,d+1),++t;
    son[d]=max(son[d],t);
}
int md;ll ans;
void solve(int u,int v)
{
    if(v==0)
    {
        int d=0;
        memset(son,0,sizeof(son));
        dfs(u,0,1);
        long long res=1;
        for(d=1;son[d];d++) res*=son[d];
        if(d>md) return;
        if(d==md) ans=min(ans,res);
        else md=d,ans=res;
    }
    else
    {
        int d=0;
        memset(son,0,sizeof(son));
        dfs(u,v,1);dfs(v,u,1);son[0]=2;
        long long res=1;
        for(d=0;son[d];d++) res*=son[d];
        if(d>md) return;
        if(d==md) ans=min(ans,res);
        else md=d,ans=res;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
    md=n;
    for(int i=1;i<=n;i++) solve(i,0);
    for(int u=1;u<=n;u++) for(int v:g[u]) if(u<v) solve(u,v);
    printf("%d %lld\n",md,ans);
    return 0;
}