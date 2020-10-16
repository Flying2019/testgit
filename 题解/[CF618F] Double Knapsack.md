### [链接](http://codeforces.com/problemset/problem/618/F)
结论好题。

首先可以证明的是：一定不会存在无解的情况。

首先考虑子集的选取过于麻烦，我们不妨考虑简易版，即选取一个区间。

首先我们假设 $\sum a_i\leq \sum b_i$

我们考虑前缀和，那么最后的要求就是 $\exists\ 0\leq i<j,0\leq k<l\ ,a_j-a_i=b_l-b_k$。

移项得 $a_j-b_l=a_i-b_k$。那么无解相当于 $a_i$ 与 $b_j$ 之间的差互不相同。

但是我们对于每个 $a_i$，取一个 $a_i< b_j\leq a_i+n$，由于所有元素 $\in[1,n]$，这个 $b_j$ 显然存在。

那么这样的 $a_i-b_j$ 总共有 $n+1$ 个，但是不同的数字只有 $n$ 个，所以这样做一定有解。

由于 $a_i$ 单调递增，直接双指针即可。复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define ll long long
using namespace std;
ll a[N],b[N];
int px[N],py[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]+=a[i-1];
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]),b[i]+=b[i-1];
	int fl=0;
	if(b[n]>a[n]) swap(a,b),fl=1;
	int u=0,v=0,x=0;
	memset(px,-1,sizeof(px));
	for(;v<=n;v++)
    {
        for(;a[v]>=b[u+1] && u+1<=n;u++);
        x=a[v]-b[u];
        if(px[x]==-1) px[x]=v,py[x]=u;
        else break;
    }
    if(fl) swap(a,b),swap(v,u),swap(px[x],py[x]);
    printf("%d\n",v-px[x]);
    for(int i=px[x]+1;i<=v;i++) printf("%d ",i);
    puts("");
    printf("%d\n",u-py[x]);
    for(int i=py[x]+1;i<=u;i++) printf("%d ",i);
	return 0;
}
```
