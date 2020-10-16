### [链接](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2976)
### 题目大意
给定棋盘上一些“车”，如果一个“车”的同一排或同一列有另一个“车”，就可以移动过去并吃掉那个“车”。如果没有“车”会被吃掉则终止操作。

问最后被吃掉的“车”的数量的最大值和最小值。
### 题解
显然要分类讨论。可以发现“吃”的本质可以看成将直接将当前的“车”移除。

不妨将可以互相吃掉的“车”之间连一条边，很明显最大值就是总数减去联通块数量。因为一个联通块至少要剩一个。

再考虑最大值，这显然是一个平面最大独立子集问题，直接行列建点跑一边二分图匹配即可。

复杂度 $O(n^2)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 2010
using namespace std;
int f[N],link[N],n;
bool vis[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
struct node{
    int x,y;
}p[N];
vector<int>g[N];
bool check(int x)
{
    vis[x]=true;
    for(int v:g[x])
    {
        if(!link[v] || (!vis[link[v]] && check(link[v])))
        {
            link[v]=x;
            return true;
        }
    }
    return false;
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    int k=m;
    for(int i=1;i<=m;i++) scanf("%d%d",&p[i].x,&p[i].y),f[i]=i;
    for(int i=1;i<=m;i++)
        for(int j=i+1;j<=m;j++)
        if(p[i].x==p[j].x || p[i].y==p[j].y)
        {
            int hx=find(i),hy=find(j);
            if(hx!=hy) f[hx]=hy,--k;
        }
    for(int i=1;i<=m;i++)
    g[p[i].x].push_back(p[i].y);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if(check(i)) ++ans;
    }
    printf("%d %d\n",m-ans,m-k);
    return 0;
}
```
