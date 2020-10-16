### [链接](https://vjudge.net/problem/Aizu-2971/origin)
### 题目大意
给定一些互相的转换倍数关系，如 $a_1=2\times a_2,\ a_2=2\times a_3$，问是否存在矛盾。
### 题解
首先，对于不同的联通块显然要分类讨论。

如果不考虑数字大小，显然我们可以先确定一个“单位1”，不妨假设为1号节点。然后所有节点表示成1号节点的倍数形式。

显然，如果一条关系所链接的两个点已经存在倍数关系，且与当前关系不符，显然存在矛盾。所以直接dfs一遍，然后对于所有边判断是否存在矛盾即可。

那么接下来考虑一个问题：这里倍数时指数级别的，高精度显然会 $\text{TLE}$。而直接取 $\log$ 显然存在精度不足的问题。

考虑我们并不需要知道某个点具体是1号节点的几倍。我们只需要知道一个数字和另一个数字是否相等即可。所以直接 $\text{Hash}$ 一下即可。

注意这里单 $\text{Hash}$ 可能被卡，写双 $\text{Hash}$ 即可。

复杂度 $O(n+m)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#define ll long long
#define ld long double
#define N 400010
#define eps 1e-12
using namespace std;
int nxt[N],to[N],head[N],cnt;
ll mods[4]={998244353,19260817,1000000007,1000000009},w[N];
bool vis[N];
ll ksm(ll a,ll b,ll mod)
{
    ll r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=r*a%mod;
        a=a*a%mod;
    }
    return r;
}
struct hs_4{
    ll a[4];
    hs_4(){a[0]=a[1]=a[2]=a[3]=1;}
    ll& operator [](int c){return a[c];}
    bool operator ==(hs_4 b){return a[0]==b[0] && a[1]==b[1] && a[2]==b[2] && a[3]==b[3];}
    bool operator !=(hs_4 b){return a[0]!=b[0] || a[1]!=b[1] || a[2]!=b[2] || a[3]!=b[3];}
    void operator *=(ll c){for(int i=0;i<4;i++) a[i]=a[i]*c%mods[i];}
    void operator /=(ll c)
    {
        for(int i=0;i<4;i++) a[i]=a[i]*ksm(c,mods[i]-2,mods[i])%mods[i];
    }
}dis[N];
void add(int u,int v,ll w1)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=w1;
    head[u]=cnt;
}
void dfs(int u)
{
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        hs_4 d=dis[u];
        if(w[i]>0) d*=w[i];
        else d/=-w[i];
        if(vis[v]){if(d!=dis[v]){puts("No");exit(0);} continue;}
        dis[v]=d;
        dfs(v);
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        ll w;
        scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w);
        add(v,u,-w);
    }
    for(int i=1;i<=n;i++)
    if(!vis[i])dfs(i);
    puts("Yes");
    return 0;
}
```
