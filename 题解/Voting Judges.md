### [链接](https://www.luogu.com.cn/problem/AT5693)
考虑贪心。可以发现，如果某个数可以最后进入前 $p$ 大，那么比这个数大的数一定可以进入前 $p$ 大。所以显然先从大到小排序。

那么考虑怎么判断一个数能否进入前 $p$ 大。首先，如果 $a_i-a_p>m$，显然 $i$ 就没戏了。

再考虑如果满足，并且 $n-i\geq v$，显然直接取它之后的 $v$ 个即可。

再考虑其他情况。因为不得不将比他大的点加上一些数，显然希望这些数不超过 $a_p$ 。所以考虑将这些加的数分配到每个数上，使 $a_p$ 到 $a_{i-1}$ 尽可能平均，然后判断即可。

复杂度 $O(n)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 200010
#define ll long long
using namespace std;
ll num[N],n,q,l,r;
struct node{
	ll opt,x,s,t;
}p[N];
short int check(ll x)
{
	for(int i=1;i<=q;i++)
	{
		if(p[i].opt==1 && x>=p[i].x) x=(x+p[i].s)*p[i].t;
		else if(p[i].opt==2 && x<=p[i].x) x=(x-p[i].s)/p[i].t;
	}
	if(x<l) return -1;
	if(x>r) return 1;
	return 0;
}
int main()
{
	scanf("%lld%lld%lld%lld",&n,&q,&l,&r);
	for(int i=1;i<=n;i++) scanf("%lld",&num[i]);
	sort(num+1,num+n+1);
	for(int i=1;i<=q;i++)
	scanf("%lld%lld%lld%lld",&p[i].opt,&p[i].x,&p[i].s,&p[i].t);
	int l=1,r=n,p=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		int t=check(num[mid]);
		if(t==1) r=mid-1;
		else if(t==-1) l=mid+1;
		else{p=mid;break;}
	}
	if(!p){puts("0");return 0;}
	l=p+1,r=n;
	int rf=p;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(num[mid])==0) l=mid+1,rf=mid;
		else r=mid-1;
	}
	l=1,r=p-1;
	int lf=p;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(num[mid])==0) r=mid-1,lf=mid;
		else l=mid+1;
	}
	printf("%d\n",rf-lf+1);
	return 0;
}
```
