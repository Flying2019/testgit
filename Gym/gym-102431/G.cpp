#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 200010
#define mod 1000000007
using namespace std;
int n;
vector<int>g[N];
int siz[N];
void dfs(int u,int p)
{
    siz[u]=1;
    for(int v:g[u])
    if(v!=p)
    {
        dfs(v,u),siz[u]+=siz[v];
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            int u,v;scanf("%d%d",&u,&v);
            g[u].push_back(v);g[v].push_back(u);
        }
    }
    return 0;
}