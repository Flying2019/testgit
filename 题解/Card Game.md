### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102661/problem/B)
### 题目大意
你和 $p$ 个人玩一个游戏：每个人一开始有一个印着 $[1,c]$ 的数字的卡片，桌子上也有 $n$ 个这样的卡片。每个人轮流将桌上的一张卡片换成自己手上的卡片。你是第一个操作的。

在游戏前你写下一个数字 $h$，如果最后的桌子上留下的卡片中 $h$ 是**唯一**的众数那么视为你成功。

求你有那几种方案，使得无论如何自己都能成功。
### 题解
考虑一种贪心：假设所有人都针对你，并且都知道你写下的数字 $h$。那么他们肯定想办法换掉桌子上写着 $h$ 的卡片。

所以我们可以直接把除了你之外的所有操作都做好。接下来也就是你能换一张牌，要求**唯一**的众数是 $h$ 有哪几种方案。

直接分类讨论就行了。还有更直接的方法：直接枚举换哪张，然后用线段树统计众数和众数的个数即可。

特别的，当 $n=1$ 时可以发现所有人只有一种选择，而且只要最后留下 $h$ 就是成功。直接特判处理。

复杂度 $O(n\log c)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define N 400010
using namespace std;
int num[N],ans[N],rtot;
int maxn[N],idn[N],cnt[N];
void update(int u)
{
    maxn[u]=max(maxn[u<<1],maxn[u<<1|1]);
    idn[u]=0;
    if(maxn[u]==maxn[u<<1]) idn[u]+=idn[u<<1];
    if(maxn[u]==maxn[u<<1|1]) idn[u]+=idn[u<<1|1];
}
void build(int u,int l,int r,int a[])
{
    if(l==r){maxn[u]=a[l];idn[u]++;return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid,a);
    build(u<<1|1,mid+1,r,a);
    update(u);
}
void insert(int u,int l,int r,int p,int opt)
{
    if(l==r)
    {
        maxn[u]+=opt;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) insert(u<<1,l,mid,p,opt);
    else insert(u<<1|1,mid+1,r,p,opt);
    update(u);
}
int main()
{
    int n,p,c,h,cs=0;
    scanf("%d%d%d%d",&n,&p,&c,&h);
    for(int i=1;i<=n;i++) scanf("%d",&num[i]),cnt[num[i]]++;
    if(n==1)
    {
        int a=0;
        for(int i=1;i<=p;i++) scanf("%d",&a);
        if(a==h) puts("1\n1");
        else puts("0");
        return 0;
    }
    for(int i=1;i<=p;i++)
    {
        int a;
        scanf("%d",&a);
        if(i==1) cs=a;
        else cnt[h]--,cnt[a]++;
    }
    build(1,1,c,cnt);
    // for(int i=1;i<=n*2;i++) printf("%d ",maxn[i]);puts("");
    for(int i=1;i<=n;i++)
    {
        insert(1,1,c,num[i],-1);
        cnt[num[i]]--;
        insert(1,1,c,cs,1);
        cnt[cs]++;
        // printf("%d %d\n",maxn[1],idn[1]);
        if(maxn[1]==cnt[h] && idn[1]==1) ans[++rtot]=i;
        insert(1,1,c,num[i],1);
        insert(1,1,c,cs,-1);
        cnt[cs]--;
        cnt[num[i]]++;
    }
    printf("%d\n",rtot);
    for(int i=1;i<=rtot;i++) printf("%d ",ans[i]);
    return 0;
}
```
