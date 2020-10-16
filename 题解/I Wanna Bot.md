### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102661/problem/F)
### 题目大意
给一个图，求一种四色染色方案，要求每个点最多与其相邻的一个点同色。

保证每个点度数不超过7。
### 题解
考虑度数的限制有什么用：很明显，根据鸽子原理，对于与一个点相邻的点中，~~至少有一个bot被放鸽子~~ 至少存在一种颜色只出现至多一次。也就是说至少存在一种可行方案。

所以我们考虑一种策略：对于每个点，如果它不符合要求，就修改成只出现至多一次的颜色。

如何证明这样可行？注意到每次修改都是对不符合要求的点修改，也就是至少存在两条同色边。而修改后至多存在一条同色边。而同色边的数量是 $O(m)$ 的，所以总时间复杂度取决于找不符合要求的点。

考虑一个点**变成**不符合要求必要前提是它周围的点修改成与它同色。所以考虑用bfs的思路，每次修改点后检测是否存在相邻的同色点，如果存在就加入队列修改判断即可。

复杂度 $O(m?)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#define N 100010
using namespace std;
vector<int>r[N];
int col[N];
queue<int>q;
bool in[N];
int n,m;
void work(int u)
{
    int swp[5]={0,0,0,0,0};
    for(int v:r[u])
    if(swp[col[v]])swp[col[v]]=-1;
    else swp[col[v]]=v;
    if(swp[col[u]]!=-1) return;
    for(int _=1;_<=4;_++)
    if(swp[_]>=0)
    {
        col[u]=_;
        if(swp[_] && !in[swp[_]])q.push(swp[_]),in[swp[_]]=true;
    }
}
void bfs()
{
    for(int i=1;i<=n;i++) q.push(i),in[i]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        in[u]=false;
        work(u);
    }
}
int main()
{
    scanf("%d%d",&m,&n);
    srand(n);
    for(int i=1;i<=n;i++) col[i]=rand()%4+1;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        r[u].push_back(v),r[v].push_back(u);
    }
    bfs();
    for(int i=1;i<=n;i++,puts(""))
        for(int _=1;_<=4;_++)
        if(col[i]!=_) printf("%d ",_);
    return 0;
}
```
