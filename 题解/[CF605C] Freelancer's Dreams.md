### [链接](http://codeforces.com/problemset/problem/605/C)
首先考虑一个贪心：如果我选择了超过2个向量，那么我一定可以通过选择较优的2个向量去替换其他向量达到更好的效果。

又可以发现，如果一个向量不在凸包上，那么其他向量一定存在一组组合，使得其方向与当前向量相等且效果更优。

所以我们先求出凸包。那么凸包上的点就意味着不存在以上替换。由于是整点凸包，这样直接做 $O(C^{\frac 4 3})$，其中 $C$ 是值域，有点卡常。

考虑继续挖掘性质：可以发现，由于这些向量已经不能替换，所以我们应当尽可能使他们的夹角变小。所以直接取相邻两个点即可。

其实还有一个结论：凸包边上的两点是最优的当且仅当 $(0,0)\leftrightarrow (x,y)$ 与 $p_i\leftrightarrow p_{i+1}$ 有交点。不过这并不能优化复杂度。

时间复杂度 $O(n\log n)$（瓶颈为求凸包的复杂度）。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
struct point{
	ll x,y;
	point(ll X=0,ll Y=0):x(X),y(Y){}
	friend point operator +(const point a,const point b){return point(a.x+b.x,a.y+b.y);}
	friend point operator -(const point a,const point b){return point(a.x-b.x,a.y-b.y);}
	friend ll operator *(const point a,const point b){return a.x*b.y-a.y*b.x;}
	bool operator <(const point a)const{return x==a.x?y>a.y:x<a.x;}
}p[N],q[N],o;
ll cross(point a,point o,point b){return (a-o)*(b-o);}
double work(point &a,point &b)
{
	ll x0=a*b,x1=a*o,x2=o*b;
	if(x0==0 || 1.0*x1/x0<0 || 1.0*x2/x0<0) return 1e18;
	return 1.0*x1/x0+1.0*x2/x0;
}
int main()
{
	int n,tot=0;
	scanf("%d%lld%lld",&n,&o.x,&o.y);
	ll xm=0,ym=0;
	for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i].x,&p[i].y),xm=max(xm,p[i].x),ym=max(ym,p[i].y);
	double ans=1e18;
	for(int i=1;i<=n;i++) ans=min(ans,max(1.0*o.x/p[i].x,1.0*o.y/p[i].y));
	p[++n]=point(xm,0);p[++n]=point(0,ym);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
	{
		while(tot>1 && cross(q[tot-1],q[tot],p[i])<=0) --tot;
		q[++tot]=p[i];
	}
	for(int i=2;i<=tot;i++) ans=min(ans,work(q[i-1],q[i]));
	printf("%.8f",ans);
	return 0;
}
```
