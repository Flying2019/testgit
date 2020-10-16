### [链接](https://codeforces.com/contest/535/problem/E)
考虑 $s_i,r_j$ 均为常数，所以 $x,y$ 的次数均为1次。这意味着对于某一个 $x$，对应的 $y$ 下的最大值一定是一段折线。

换句话说，我们把 $(\frac 1 {s_i},\frac {1} r_i)$ 的对应的最大值画出来，可以发现一个点会成为最优点当且仅当其位于左下凸包上。

求完凸包再判断一下重复的部分即可。复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
#define db double
using namespace std;
struct node{
	int x,y,id;
	bool operator <(const node a)const{return x==a.x?y>a.y:x>a.x;}
}p[N];
db slop(node x,node y){return 1.0*(x.y-y.y)*x.x*y.x/(1.0*(x.x-y.x)*x.y*y.y);}
int q[N],qt;
int has[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y),p[i].id=i;
	sort(p+1,p+n+1);
	q[++qt]=1;
	for(int i=2;i<=n;i++)
	if(p[i].x!=p[i-1].x)
	{
		while(qt>1 && slop(p[q[qt]],p[q[qt-1]])>slop(p[i],p[q[qt]])) qt--;
		if(slop(p[i],p[q[qt]])<0) q[++qt]=i;
	}
	for(int i=1;i<=qt;i++) has[p[q[i]].id]=1;
	for(int i=2;i<=n;i++) if(p[i].x==p[i-1].x && p[i].y==p[i-1].y) has[p[i].id]=has[p[i-1].id];
	for(int i=1;i<=n;i++) if(has[i]) printf("%d ",i);
	return 0;
}
```
