### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102683/problem/A)
如果 $m=1$，很明显就是一个双指针裸题了。

但是这道题要求询问 $m$ 次，显然直接处理会T。考虑我们最后这个答案有点问题：为什么要取 $\log$ 而不取模。

可以发现 $\log n^2$ 最多只有40左右，也就是说答案的种数最多只有40。而相同的答案一定构成一段区间，也就是说我们只要找到区间之间的端点即可。

考虑二分答案，即对于答案 $k$，找到第一个数字 $\geq k$ 的值并记录，最后再在记录的答案中二分即可。

复杂度 $O(n\log^2 a+m\log n)$。
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
