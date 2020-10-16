### [链接](https://codeforces.com/problemset/problem/566/G)
结论题。

首先可以发现，由于是Max想要最后 $(x,y)$ 均为正数，而Max又先走，所以最后的结论就是假如Max的某个点被Min的上右凸包完全包含，那么这个点就不可行，否则就可行。

这里上右凸包的定义是添加 $(0,y_{max}),(x_{max},0),(0,0)$，再求一遍上凸包得到。

因为假如Max选了若干次这里的节点，同样Min可以通过选若干次凸包上的节点做到使 $(x,y)$ 都减少。

所以最后只要看Max是否存在点不被凸包包含。这个显然可以直接二分。复杂度 $O((n+m)\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
struct node{
	ll x,y;
	node(ll X=0,ll Y=0):x(X),y(Y){}
	node operator +(const node a)const{return node(x+a.x,y+a.y);}
	node operator -(const node a)const{return node(x-a.x,y-a.y);}
	ll operator *(const node a)const{return x*a.y-y*a.x;}
	bool operator <(const node a)const{return x==a.x?y<a.y:x<a.x;}
}p[N],q[N],s[N];
ll cross(node a,node o,node b){return (a-o)*(b-o);}
int main()
{
	int n,m;
	scanf("%d%d%*d%*d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&q[i].x,&q[i].y);
	for(int i=1;i<=m;i++) scanf("%lld%lld",&p[i].x,&p[i].y);
	sort(p+1,p+m+1);
	int t=0;
	for(int i=1;i<=m;i++)
	{
		while(t && s[t].x<=p[i].x && s[t].y<=p[i].y) --t;
		while(t>1 && cross(s[t],s[t-1],p[i])>=0) --t;
		s[++t]=p[i];
	}
	s[0].x=0,s[0].y=s[1].y;
	s[t+1].x=s[t].x,s[t+1].y=0;
	for(int i=1;i<=n;i++)
	{
		int l=0,r=t,ans=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(q[i].x>=s[mid].x) ans=mid,l=mid+1;
			else r=mid-1;
		}
		if(ans==-1 || cross(q[i],s[ans],s[ans+1])<=0){puts("Max");return 0;}
	}
	puts("Min");
	return 0;
}
```
