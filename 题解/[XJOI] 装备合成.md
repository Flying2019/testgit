### [链接](http://115.236.49.52:83/contest/1561/problem/1)
首先考虑暴力做法，可以发现对于每次修改暴力赋值，可以做到 $O(nq)$。

考虑80分做法。可以发现所有数值只有两种选择，由于 $k\leq 12$，所以本质不同的 $n$ 的个数其实只有 $2^k$ 个，暴力对这些修改，可以做到 $O(2^kn)$。空间可以用bitset优化到 $O(\frac{2^kn}{\omega})$。

考虑如何处理一般情况。可以发现，如果我们钦定询问节点的答案 $\geq a$，那么我们让 $< a$ 的数字变成0，$\geq a$ 的数字变成1。显然，1的数量越多结果越可能是1，所以直接暴力枚举 $a$，找到最大的 $a$ 使结果是1，那么 $a$ 就是答案。

时间复杂度 $O(2^kn+nk)$。
```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#include<cstring>
#define N 100015
#define M 13
using namespace std;
int a[M][N],f[N];
struct node{
    int x,y;
}q[N];
int num[N][110];
bitset<5010>g[N];
int main()
{
    int n,m,p;
    scanf("%d%d%d",&m,&n,&p);
    bool onli=true;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&a[i][j]),f[i]=1<<i,onli=onli && (a[i][j]==1 || a[i][j]==2);
    int t=n;
    if(onli)
    {
        for(int i=0;i<1<<n;i++)
            for(int j=1;j<=n;j++)
            if((i>>(j-1))&1) g[j][i]=1;
        for(int i=1;i<=m;i++) f[i]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            if(a[i][j]==2) f[j]|=1<<(i-1);
        for(int j=1;j<=p;j++)
        {
            int opt,x,y;
            scanf("%d%d%d",&opt,&x,&y);
            if(opt==1) g[++t]=g[x]|g[y];
            else if(opt==2) g[++t]=g[x]&g[y];
            else if(opt==3) printf("%d\n",g[x].test(f[y])+1);
        }
        return 0;
    }
    if(m<=100)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) num[i][j]=a[i][j];
        for(int i=1;i<=p;i++)
        {
            int opt,x,y;
            scanf("%d%d%d",&opt,&x,&y);
            if(opt==1)
            {
                ++t;
                for(int j=1;j<=m;j++) num[t][j]=max(num[x][j],num[y][j]);
            }
            else if(opt==2)
            {
                ++t;
                for(int j=1;j<=m;j++) num[t][j]=min(num[x][j],num[y][j]);
            }
            else if(opt==3) printf("%d\n",num[x][y]);
        }
        return 0;
    }
    for(int i=0;i<1<<n;i++)
        for(int j=1;j<=n;j++)
        if((i>>(j-1))&1) g[j][i]=1;
    for(int i=1;i<=m;i++) f[i]=0;
    for(int j=1;j<=p;j++)
    {
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==1) g[++t]=g[x]|g[y];
        else if(opt==2) g[++t]=g[x]&g[y];
        else if(opt==3)
        {
            int s=0;
            while(1)
            {
                int mx=0,id=0;
                for(int i=1;i<=n;i++)
                if(!((s>>(i-1))&1) && mx<a[i][y]) mx=a[i][y],id=i;
                s|=(1<<(id-1));
                if(g[x][s]){printf("%d\n",mx);break;}
            }
        }
    }
    return 0;
}
```
