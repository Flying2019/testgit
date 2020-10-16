### [链接](https://codeforces.com/problemset/problem/1107/F)
首先题目的要求很少，先考虑贪心。显然，最后每种贷款有三种结果：不用，付完全部，还未付完。

考虑贪心：显然如果有贷款还未付完就买车，那么买车的时间一定会尽可能提前。

考虑更多的性质：如果有两个贷款都是还未付完，因为一天只能使用一个贷款，很显然，我们应该让每天付款多的那个贷款先贷（这样显然可以最后少付钱）。

所以，先按 $b_i$ 从大到小排序，用 $f_{i,j}$ 表示前 $i$ 个贷款，其中还未付完的贷款有 $j$ 个，显然可以得出 $dp$ 方程。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 510
using namespace std;
ll f[N][N];
struct node{
	ll a,b,k;
	bool operator <(const node a)const{return b>a.b;}
}p[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&p[i].a,&p[i].b,&p[i].k);
	sort(p+1,p+n+1);
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		f[i][0]=0;
		for(int j=0;j<=i;j++)
		{
			f[i][j]=max(f[i][j],f[i-1][j]+max(p[i].a-p[i].b*p[i].k,0ll));
			if(j) f[i][j]=max(f[i][j],f[i-1][j-1]+p[i].a-(j-1)*p[i].b);
			ans=max(ans,f[i][j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
