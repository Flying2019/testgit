#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<set>
#define N 100010
#define ll long long
using namespace std;
ll res;int n;
bool vis[N];
void dfs(int u,int v)
{
    if(vis[v]) return;
    if(u==n) res++;
    vis[v]=true;
    dfs(u+1,(v+u)%n);
    dfs(u+1,(v-u+n)%n);
    vis[v]=false;
}
int ans[]={0,1,2,2,4,2,4,4,8,2,4,6,8,2,8,6,16,2,4,6,8,4,12,6,16,4,4,4,16,2,12,10,32,4,4,8,8,2,12,6,16,2,8,6,24,6,12,8,32,6,8,6,8,2,8,10,32,4,4,6,24,2,20,6,64,6,8,8,8,4,16,6,16,2,4,8,24,14,12,6,32};
int main()
{
    int t;scanf("%d",&t);
    while(t --> 0)
    {
        int n;scanf("%d",&n);
        printf("%d\n",ans[n]);
    }
    return 0;
}