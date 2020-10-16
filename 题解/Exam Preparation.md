### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102683/problem/F)
首先这种有很少/很多限制条件的题目优先考虑贪心。

可以发现，对于某两个区间 $[l_1,r_1],[l_2,r_2]$，假如他们中间只能选一个，一定选短的那一个。

所以直接按长度排序，再按右端点排序，时间晚的排前面。最后二分答案，即对于每个插入的区间 $[l,r]$ 二分一个长度 $x$，查询 $[x,r]$ 中0的个数是否大于 $r-l+1$ 即可。

复杂度 $O(n\log^2 n)$。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define N 100010
using namespace std;
struct node{
    int p,len;
    bool operator <(const node a)const{return len==a.len?p>a.p:len<a.len;}
}q[N];
int ls[N*20],rs[N*20],val[N*20],tag[N*20],cnt;
void insert(int &u,int l,int r,int L,int R)
{
    if(!u) u=++cnt;
    if(tag[u]) return;
    if(L<=l && r<=R){tag[u]=1;val[u]=r-l+1;return;}
    int mid=(l+r)>>1;
    if(L<=mid) insert(ls[u],l,mid,L,R);
    if(R>mid) insert(rs[u],mid+1,r,L,R);
    val[u]=val[ls[u]]+val[rs[u]];
}
int answer(int u,int l,int r,int L,int R)
{
    if(tag[u]) return R-L+1;
    if(L<=l && r<=R) return val[u];
    if(R<L || !u) return 0;
    int mid=(l+r)>>1;
    if(L>mid) return answer(rs[u],mid+1,r,L,R);
    if(R<=mid) return answer(ls[u],l,mid,L,R);
    return answer(ls[u],l,mid,L,mid)+answer(rs[u],mid+1,r,mid+1,R);
}
int main()
{
    int n,m=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&q[i].p),m=max(m,q[i].p);
    for(int i=1;i<=n;i++) scanf("%d",&q[i].len);
    sort(q+1,q+n+1);
    int tot=0,rt=0;
    for(int i=1;i<=n;i++)
    {
        int l=1,r=q[i].p-q[i].len,res=0;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(q[i].p-mid+1-answer(rt,1,m,mid,q[i].p)>q[i].len) l=mid+1,res=mid;
            else r=mid-1;
        }
        if(res) ++tot,insert(rt,1,m,res,q[i].p);
    }
    printf("%d\n",tot);
    return 0;
}
```
