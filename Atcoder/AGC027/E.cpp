#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200010
using namespace std;
vector<int>g[N];
int dep[N];
int mx[N],mx2[N],top[N],val[N];
void dfs(int u,int p)
{
    dep[u]=dep[p]+1;
    mx[u]=mx[p];mx2[u]=mx2[p];
    if(u>mx[u]) mx2[u]=mx[u],mx[u]=u,top[u]=u;
    else if(u>mx2[u]) mx2[u]=u;
    if(dep[mx2[u]]>dep[mx[u]]) ++val[top[u]];
    else ++val[mx[u]];
    for(int v:g[u]) if(v!=p)
    {
        top[v]=(mx[u]==u?v:top[u]);
        dfs(v,u);
    }
}
void push(int u,int p)
{
    val[u]+=val[p];
    for(int v:g[u]) if(v!=p) push(v,u);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
    dfs(1,0);push(1,0);
    for(int i=2;i<=n;i++) printf("%d ",val[i]-1);
    return 0;
}