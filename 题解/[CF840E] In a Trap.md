### [链接](http://codeforces.com/problemset/problem/840/E)
小·清·新 分块题。

乍一看好像和分块扯不上关系。我们考虑两种暴力：

第一种显然是最普通的暴力，即我们处理出 $v$ 向上的父亲中的所有权值，然后暴力向上找最值。这样时间复杂度预处理 $O(n)$ 询问 $O(nm)$。

第二种稍微复杂度一点，因为我们发现题目是静态询问，所以用一个数组记录下每个点向上跳的最值。这样时间复杂度预处理 $O(n^2)$ 一次询问 $O(m)$。

这是不是很明显可以用分块来综合复杂度？

首先我们发现对于距离来说，如果我们以256($2^8$)作为块大小，那么块中的所有点的距离对于 $u$ 来说只有后8位数字不同，然后块内采用方案二，块外暴力，就可以做到询问 $O(m\sqrt n)$。但是重点在于如何快速处理出块内的最值。

具体来说我们定义 $f_{u,i}$ 为 $u$ 向上256个点中 $\max_{v}\{val_v\operatorname{xor} d_v\operatorname{xor} i\cdot 2^8\}$，即我们只需要枚举 $i$ 的不同。

转移可以用trie，不过更方便的是先处理出 $i=d_v$ 的结果，然后高维前缀和处理。

复杂度 $O(n2^BB+m2^B+\frac {nm} {2^B})$，取 $B=8$ 可以通过。
```cpp#include<iostream>
#include<cstdio>
#include<cstring>
#define N 50010
#define B 256
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int f[N][B],dep[N],fa[N],ffa[N],w[N];
void dfs(int u,int p)
{
    fa[u]=p;
    dep[u]=dep[p]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)
    {
        int u=i;
        for(int j=0;j<B && u;j++,u=fa[u]) f[i][(B-1)^((w[u]^j)>>8)]=max(f[i][(B-1)^((w[u]^j)>>8)],(w[u]^j)|((B-1)<<8));
        ffa[i]=u;
        for(int j=0;j<8;j++)
            for(int k=0;k<B;k++)
            if(f[i][k^(1<<j)]) f[i][k]=max(f[i][k],f[i][k^(1<<j)]^(1<<(j+8)));
    }
    while(m --> 0)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        int ans=w[u]^(dep[v]-dep[u]),x=v;
        for(int i=0;dep[u]<=dep[ffa[x]];i++,x=ffa[x]) ans=max(ans,f[x][i]);
        for(;dep[u]<=dep[x];x=fa[x]) ans=max(ans,(dep[v]-dep[x])^w[x]);
        printf("%d\n",ans);
    }
    return 0;
}
```
