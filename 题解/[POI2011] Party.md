### [链接](https://www.luogu.com.cn/problem/P3524)
根据定义，$n$ 个节点的团中不存在两点之间没有边相连，反过来说如果两点之间没有边相连，那么这两点一定不同时存在与团内。

由于我们只需要得到大小为 $n$ 的团，那么我们不妨每次找到一对没有边相邻的点，然后删掉这两个点。可以发现删掉 $n$ 对点后剩下的 $n$ 个点一定是团。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 3010
#define M N*N/2
using namespace std;
struct node{
    int x,y;
}q[M];
bool mp[N][N],vis[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        mp[x][y]=mp[y][x]=true;
    }
    int tot=0;
    for(int i=1;i<=n && tot<n/3;i++)
    if(!vis[i])
        for(int j=i+1;j<=n;j++)
        if(!mp[i][j] && !vis[j])
        {
            vis[i]=vis[j]=true;
            tot++;
            break;
        }
    int p=n/3;
    for(int i=1;i<=n && p;i++)
    if(!vis[i])printf("%d ",i),--p;
    return 0;
}
```
