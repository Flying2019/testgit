### [链接](http://115.236.49.52:83/contest/1534/problem/1)
考虑一种贪心的思路：如果当前在第 $i(i>1)$ 个点，那么最优策略一定是到离 $i$ 最近的已经访问的点。

由于这是一棵树，所以显然可以发现，直接遍历后已经在之前访问的点中第一个被访问的点就是最近的点。

所以显然我们令第一个访问的点为根。剩下的点就是不断跳父亲，直到当前的点被访问过位置。

复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 1000010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],w[N<<1],head[N],cnt;
void add(int u,int v,int w1)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=w1;
    head[u]=cnt;
}
int faw[N],fa[N],dep[N],p[N];
bool gt[N];
void dfs(int u,int f)
{
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==f) continue;
        dfs(v,u);
        faw[v]=w[i];
    }
}
long long ans=0;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w),add(v,u,w);
    }
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    dfs(p[1],0);
    int a=p[1];
    gt[p[1]]=true;
    puts("0");
    for(int i=2;i<=n;i++)
    {
        int u=p[i];
        while(!gt[u])
        {
            ans+=faw[u];
            gt[u]=true;
            u=fa[u];
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
