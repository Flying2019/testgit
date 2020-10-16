### [链接](http://codeforces.com/problemset/problem/598/C)
这道题难点就在于卡精度。。。

首先可以发现，我们可以直接钦定 $x$ 轴为基准线，用叉积求出 $x$ 轴上方和下方的排序，然后合并起来即可。

当然，这里用 $\text{atan}$ 也是可以的。

然后用点积 $\cos\theta=\frac{a\cdot b}{|a||b|}$ ，由于 $\cos$ 在 $[0,\pi)$ 单调递减，所以直接求就行了。

当然，这里还是用 $\text{atan}$。

但是这样有一个问题：double(或 long long) 只有16 (18)位精度，而这里 $|a|,|b|$ 要用到浮点数计算，必然损失精度。而如果直接平方又会导致 $20$ 位的数字。

当然使用__int128是办法之一。另外用long double也可以吗，不过我不太会用。

时间复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 100010
#define ll long long
using namespace std;
struct point{
	ll x,y;
	int id;
	point (ll X=0,ll Y=0):x(X),y(Y){}
	point operator +(const point a)const{return point(x+a.x,y+a.y);}
	point operator -(const point a)const{return point(x-a.x,y-a.y);}
	ll operator ^(const point a)const{return x*a.y-y*a.x;}
	ll operator *(const point a)const{return x*a.x+y*a.y;}
}p[N];
ll dis(point a){return a.x*a.x+a.y*a.y;}
bool cmp(point a,point b)
{
	if(a.y*b.y<0) return b.y<0;
	return (a^b)>0;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i].x,&p[i].y),p[i].id=i;
	sort(p+1,p+n+1,cmp);
	p[++n]=p[1];
	__int128 ans;
	int a1=0;
	for(int i=2;i<=n;i++)
	if(!a1 || ans*dis(p[i])*dis(p[i-1])<(__int128)(p[i]*p[i-1])*(p[i]*p[i-1])*((p[i]*p[i-1])<0?-1:1)*dis(p[a1])*dis(p[a1-1]))
	{
		ans=(p[i]*p[i-1])*(p[i]*p[i-1])*((p[i]*p[i-1])<0?-1:1);
		a1=i;
	}
	printf("%d %d\n",p[a1].id,p[a1-1].id);
	return 0;
}
```
