### [链接](https://www.luogu.com.cn/problem/CF1119G)
考虑贪心。首先我们先一直打第一个，然后当第一个的值小于n时我们留下一个专门打最后一点血，剩余的直接打后面的。

由于最后只要额外分配 $m$ 个，正好可行。但是这样总数会很大。考虑差分，即我们考虑我们可以不止留下一个打。

那么我们将所有敌人的剩余血量统计出来，然后排序。我们只需要对两两之差设置一组即可。

对于打击方案直接贪心处理就行了。因为一定存在一个前缀和等于剩余血量。

复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
#define ll long long
using namespace std;
int num[N],h[N];
ll q[N];
ll sum;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",&h[i]);
	int sum=0;
	for(int i=1;i<m;i++) sum+=h[i],q[i]=sum%n;
	q[m]=n;
	sort(q+1,q+m+1);
	for(int i=1;i<=m;i++) num[i]=q[i]-q[i-1];
	printf("%d\n",(sum+h[m]+n-1)/n);
	for(int i=1;i<=m;i++) printf("%d ",num[i]);
	puts("");
	int u=1;
	for(int i=1;i<=m;i++)
	while(h[i]>0)
	{
		h[i]-=num[u++];
		printf("%d ",i);
		if(u==m+1){u=1;puts("");}
	}
	while(u!=1 && u++!=m+1) printf("%d ",m);
	return 0;
}
```
