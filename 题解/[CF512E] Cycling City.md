### [链接](https://www.luogu.com.cn/problem/CF521E)
可以发现，如果 $s,t$ 之间存在三条互不相交的路径，那么这三条路径可以构成两个环。

我们不妨先建出dfs树，可以发现，所有非树边都是反祖边。

可以发现，如果某条边已经位于一个环中，又发现它在另一个环中，那么这一定是一组合法的点。

考虑每次发现反祖边时暴力跳链，将所有链上的点打上标记，说明其已经处于一个环中。

可以发现，如果此时访问到一个已经被打上标记的点，那么就意味着得到答案。

对于输出答案，直接暴力跳边即可。虽然每次反祖边都要打一次tag，但是可以发现每个点最多被打一次，否则就已经得到答案。复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int fa[N],dep[N];
int res[N],tot;
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(;dep[x]!=dep[y];x=fa[x]);for(;x!=y;x=fa[x],y=fa[y]);
    return x;
}
void print(){printf("%d",tot); for(int i=1;i<=tot;i++) printf(" %d",res[i]); puts("");tot=0;}
void get_pa(int x,int y){for(;x!=y;x=fa[x]) res[++tot]=x; res[++tot]=y;}
void work(int a,int x,int b,int y)
{
    if(dep[x]>dep[y]) swap(a,b),swap(x,y);
    int l=lca(a,b);
    puts("YES");
    get_pa(l,y),reverse(res+1,res+tot+1);print();
    get_pa(y,x),get_pa(a,l);print();
    res[++tot]=y;get_pa(b,l);print();
}
bool vis[N],in[N];
int s1[N],s2[N];
void dfs(int u,int p)
{
    fa[u]=p;
    dep[u]=dep[p]+1;
    in[u]=vis[u]=true;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        if(!vis[v]) dfs(v,u);
        else if(in[v])
        {
            for(int x=u;x!=v;x=fa[x])
            if(s1[x]){work(s1[x],s2[x],u,v);exit(0);} 
            else s1[x]=u,s2[x]=v;
        }
    }
    in[u]=false;
} 
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;i++)
    if(!vis[i]) dfs(i,0);
    puts("NO");
    return 0;
}
```
