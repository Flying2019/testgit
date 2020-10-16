### [链接](http://codeforces.com/problemset/problem/724/G)
小清新线性基题。

考虑类似于[最大XOR和路径](https://www.luogu.com.cn/problem/P4151)的做法。我们找出原图的一个dfs树，可以很方便地求出一条返祖边造成的环的大小。

然后我们把所有环扔进一个线性基里，那么线性基表示的所有元素就是所有可行环的大小。

考虑异或的优秀性质，$u\rightarrow v=d_u\oplus d_v\oplus C$，其中 $C\in \text{线性基}$。

但是这个所有 $(u,v)$ 很难统计。按照套路，我们按位统计。

首先这位要产生贡献，显然需要是1。所以我们只需要统计出所有组合中包含1的数量即可。

首先，由于线性基可以表示 $2^t$ 中的所有元素。对于某一位，如果其在线性基中存在基底，那么一定有 $2^{t-1}$ 的元素该位为0，$2^{t-1}$ 的元素该位为1。

显然这样对于任意一组 $(u,v)$ 都有 $2^{t-1}$ 个元素符合条件。贡献数量为 $2^{t-1}\frac {n(n-1)} 2$。

如果线性基中不存在，说明该位中线性基的所有元素均为0，所以要求 $(u,v)$ 路径上该位为1。也就是 $d_u$ 和 $d_v$ 恰有一个为1。

那么我们统计出该位 $d_u=1$ 的数量 $w$，那么贡献数量为 $2^{t}w(n-w)$。

当然以上默认的都是联通块。对于不同联通块单独统计，最后求和即可。

复杂度 $O(n\log^2 w)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
#define mod 1000000007
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
ll w[N<<1];
void add(int u,int v,ll w1)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=w1;
    head[u]=cnt;
}
ll b[62],bt;
void insert(ll x)
{
    for(int i=60;i>=0;i--)
    if((x>>i)&1)
    {
        if(!b[i]){b[i]=x;++bt;return;}
        else x^=b[i];
    }
}
bool vis[N];
ll dis[N];
int qid[N],tot;
void dfs(int u)
{
    qid[++tot]=u;
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(vis[v]){insert(dis[u]^dis[v]^w[i]);continue;}
        dis[v]=dis[u]^w[i];
        dfs(v);
    }
}
void clear(){memset(b,0,sizeof(b));tot=bt=0;}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        ll w;
        scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w),add(v,u,w);
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
    if(!vis[i])
    {
        clear();
        dfs(i);
        bt=1ll<<bt;
        for(int j=0;j<=60;j++)
        {
            bool have=0;
            ll res=0;
            for(int k=0;k<=60;k++) if((b[k]>>j)&1) have=true;
            if(have) res=1ll*tot*(tot-1)/2%mod*(bt/2%mod)%mod;
            else
            {
                for(int k=1;k<=tot;k++) res+=(dis[qid[k]]&gt;>j)&1;
                res=1ll*bt%mod*res%mod*(tot-res)%mod;
            }
            ans=(ans+res*((1ll<<j)%mod))%mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
