### [链接](https://codeforces.com/problemset/problem/1394/B)
~~中国选手出的FST专场。~~

首先考虑合法答案的性质：很明显，要求每一个点能回到它自己，就是正好每个点的入度/出度均为一。

很明显对于每个 $c_i$ 你有一个决策，由于 $k$ 很小，完全可以暴力枚举这个决策来判断。

接下来主要问题在于如何判断。可以发现，每个 $c_i=x$ 对应同样数量的出边，不妨把这些出边到的点的信息用Hash处理起来。

我们让不同的点拥有不同的Hash值，那么如果答案符合条件，每个点的Hash值应当恰好出现一次。

所以直接将所有决策的Hash值相加，看一下是否和 $1\cdots n$ 的所有Hash值相加相同即可。复杂度 $O(n+m+k!)$。

还是那句话，CF上写单Hash的都是勇士。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define ll long long
#define P pair<ll,ll>
#define MP make_pair
#define fi first
#define se second
#define mod 1000000007
using namespace std;
P operator +(const P a,const P b){return MP((a.fi+b.fi)%mod,(a.se+b.se)%mod);}
P operator +(const P a,const int b){return MP((a.fi+b)%mod,(a.se+b)%mod);}
P operator -(const P a,const P b){return MP((a.fi-b.fi+mod)%mod,(a.se-b.se+mod)%mod);}
P operator *(const P a,const P b){return MP((a.fi*b.fi)%mod,(a.se*b.se)%mod);}
const P bs=MP(233333,2333333);
P h[N],all;
struct node{
    int v,w;
    bool operator <(const node a)const{return w<a.w;}
};
vector<node>r[N];
int k;
ll ans=0;
P s[11][11];
void dfs(int u,P hs)
{
    if(u>k){ans+=hs==all;return;}
    for(int i=0;i<u;i++)
    {
        P v=hs+s[u][i];
        dfs(u+1,v);
    }
}
int main()
{
    int n,m;
    scanf("%d%d%d",&n,&m,&k);
    h[0]=MP(1,1);
    for(int i=1;i<=n;i++) h[i]=h[i-1]*bs,all=all+h[i];
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        r[u].push_back((node){v,w});
    }
    for(int i=1;i<=n;i++)
    {
        sort(r[i].begin(),r[i].end());
        int p=r[i].size();
        for(int j=0;j<p;j++) s[p][j]=s[p][j]+h[r[i][j].v];
    }
    dfs(1,MP(0,0));
    printf("%lld\n",ans);
    return 0;
}
```
