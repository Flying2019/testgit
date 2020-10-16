### [链接](http://codeforces.com/problemset/problem/1009/F)
首先第一眼一看就是dp题。很显然有 $f_{i,0}=1,f_{i,j}=\sum{f_{v,j-1}}$。

直接dp显然是 $O(n^2)$ 的。考虑优化。

这种树形dp优化通常有几种：

1. 线段树合并
2. dsu on tree
3. ~~各种分治乱搞~~

这里 $n$ 只有 $10^6$ 正常点的方法都可以。但是针对这道题，有一个 $O(n)$ 的优化。

具体来说，我们考虑重链剖分的dsu on tree为什么会多1个 $\log$：由于重链不一定是最长的链，所以我们在每个链顶的位置的数组必须开到与深度相同而不是同链长。这样势必会造成 $O(\log n)$ 的空间代价。

考虑怎么优化？我们发现问题在于链长，那么我们直接选取最长那条链不就好了？也就是长链剖分。

可以发现这样一条链能直接合并到主链上去，总链长就是点数。时空复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 1000010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int len[N],son[N],fa[N];
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
void dfs1(int u,int p)
{
    fa[u]=p;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs1(v,u);
        if(len[v]+1>len[u]) son[u]=v,len[u]=len[v]+1;
    }
}
vector<int>f[N];
int ans[N];
void dfs2(int u)
{
    if(!son[u]){f[u].push_back(1);return;}
    dfs2(son[u]);
    f[u].swap(f[son[u]]);
    f[u].push_back(1);
    ans[u]=ans[son[u]];
    if(f[u][ans[u]]==1) ans[u]=len[u];
    for(int o=head[u];o;o=nxt[o])
    {
        int v=to[o];
        if(v==fa[u] || v==son[u]) continue;
        dfs2(v);
        for(int i=len[v];i>=0;i--)
        {
            int j=i+len[u]-len[v]-1;
            f[u][j]+=f[v][i];
            if(f[u][j]>f[u][ans[u]] || (f[u][j]==f[u][ans[u]] && j>ans[u])) ans[u]=j;
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfs1(1,0);
    dfs2(1);
    for(int i=1;i<=n;i++) printf("%d\n",len[i]-ans[i]);
    return 0;
}
```
