#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 500010
using namespace std;
vector<int>g[N];
int x[N],y[N],c[N];
int vis[N],T;
bool dfs(int s,int t)
{
    if(vis[s]==T) return false;
    if(s==t) return true;
    vis[s]=T;
    for(int v:g[s]) if(dfs(v,t)) return true;
    return false;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&x[i],&y[i],&c[i]),c[i]--;
    for(int i=1;i<=m;i++)
    if(c[i]==-1)
    {
        for(int u=1;u<=n;u++) g[u].clear();
        for(int j=1;j<=m;j++) if(i!=j)
        {
            if(c[j]!=1) g[x[j]].push_back(y[j]);
            if(c[j]!=0) g[y[j]].push_back(x[j]);
        }
        ++T;
        if(dfs(y[i],x[i])) c[i]=0;
        else c[i]=1;
    }
    for(int i=1;i<=m;i++) printf("%d\n",c[i]);
    return 0;
}