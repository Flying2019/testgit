### [链接](http://acm.zju.edu.cn/public/problems/11/text)
### 题目大意
平面上有 $n$ 个点，求是否存在至少 $n\times p\%$ 个点共线($20\leq p\leq 100$)。
### 题解
考虑 $p$ 最小也有 $\frac{1}{5}$，可以发现这时候随机选两个点在答案上的概率至少有 $\frac 1 25$，而一次判断是 $O(n)$ 的，多随机几次即可。

复杂度 $O(n\times \text{随机次数})$。可以发现这样没有任何精度问题。
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<vector>
#define ll long long
#define N 100010
using namespace std;
struct node{
	ll x,y;
}p[N];
ll operator *(const node a,const node b){return a.x*b.y-a.y*b.x;}
node operator -(const node a,const node b){return (node){a.x-b.x,a.y-b.y};}
int main()
{
	int n,P;
	scanf("%d%d",&n,&P);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i].x,&p[i].y);
	random_shuffle(p+1,p+n+1);
	while(clock()<=400)
	{
		int u=rand()%n+1;
		int v=rand()%n+1;
		if(u<v) swap(u,v);
		if(u==v) v=(v+1)%n+1;
		int res=2;
		for(int i=1;i<=n;i++)
		if(i!=u && i!=v && (p[i]-p[u])*(p[v]-p[u])==0) res++;
		if(res>=n*P/100.0){printf("possible");return 0;}
	}
	printf("impossible");
	return 0;
}
 
```
