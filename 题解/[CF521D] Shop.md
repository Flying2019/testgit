### [链接](http://codeforces.com/problemset/problem/521/D)
贪心。

首先考虑如果只有乘怎么做？由于最后求的是全部的成绩，显然直接取最大的 $k$ 个就可以了。

考虑如何处理加法。首先对于一个点，按照贪心我们显然会从大的开始加。我们考虑把加法换成乘法，即每次加就是 $\times \frac{a_i+v}{a_i}$，而由于贪心，对于 $v$ 来说 $a_i$ 是确定的。如果先加 $v$ 改变顺序，可以发现这样计算只会导致结果更差，所以贪心处理后转乘全是乘处理即可。

考虑处理赋值。首先按照贪心我们最多只会赋值那个最大的，而这个操作也等价于加法，所以直接转换成加法即可。

复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
struct node{
	double x;
	int id;
	node(double X=0.0,int ID=0):x(X),id(ID){}
	bool operator <(const node a)const{return x>a.x;}
}c[N];
int a[N],opt[N];
vector<node>ad[N],mul;
int ans[N];
bool cmp(int x,int y){return opt[x]<opt[y];}
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d%d",&opt[i],&x,&y);
		if(opt[i]==1) c[x]=min(c[x],node(y,i));
		if(opt[i]==2) ad[x].push_back(node(y,i));
		if(opt[i]==3) mul.push_back(node(y,i));
	}
	for(int i=1;i<=n;i++)
	if(c[i].x>a[i]) ad[i].push_back(node(c[i].x-a[i],c[i].id));
	for(int i=1;i<=n;i++)
	{
		sort(ad[i].begin(),ad[i].end());
		ll w=a[i];
		for(auto v:ad[i]) mul.push_back(node((w+v.x)/w,v.id)),w+=v.x;
	}
	sort(mul.begin(),mul.end());
	printf("%d\n",k=min(k,(int)mul.size()));
	for(int i=0;i<k;i++) ans[i]=mul[i].id;
	sort(ans,ans+k,cmp);
	for(int i=0;i<k;i++) printf("%d ",ans[i]);
	return 0;
}
```
