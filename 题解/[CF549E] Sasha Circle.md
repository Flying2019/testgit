### [链接](https://codeforces.com/contest/549/problem/E)
毒瘤题。。。

首先考虑一种暴力：对于 $A$ 中的每个点对，假设圆经过该点对，对于除此之外的每个点都有一个圆周角区间限制，即包含/不包含，判断有无合法解即可。可以发现这样的复杂度是 $O(n^3)$。

考虑一个性质：一个三维中 $z=x^2+y^2$ 的抛物面被 $ax+by+cz=1$ 所截所得的图形在 $z=0$ 的投影一定是一个圆。

可以证明，这个平面上任何一个圆都与 $ax+by+cz=1$ 面一一对应。

考虑这个性质有什么作用：我们把所有点映射到这个抛物面上（即 $(x,y,x^2+y^2)$），可以发现，由于抛物面在从原点出发任意一个方向上都是单调递增的，所以如果一个点在圆内，那么映射后的点一定在截面 $ax+by+cz=1$ 下方。反之一定在上方。

这样题目就变成：存不存在一个截面，使 $A$ 中的点都在下方，$B$ 中的点都在上方。这样处理后，显然我们只需要留下其中的三维凸包即可（当然不必建出来）。

这个还是很难处理。其实我们只需要留下上凸包即可。观察抛物面的性质可以发现，上凸包一定是一个面！而且很显然这个面上至少有两个 $A$ 的点。我们要做的就是找到这个面。

也就是说，我们可以随机地找到凸包上的两个点，不妨认为是 $1,n$ ，先判断是否存在圆符合条件。如果不符合，那么贪心地找到扬角最大的那一个点 $k$，显然这个圆是包含所有的 $A$ 中的点的。

因为这个圆是能取到的解中最大的，所以不存在一个点 $u$，使得点对 $(1,u)$ 存在一个圆满足条件而 $(1,k)$ 不满足。

所以我们递归处理区间 $[1,k)$ 和区间 $[k,n)$，判断是否满足条件即可。

复杂度比较玄学。由于所有点为整点的凸包大小是 $O(C^{\frac 23})$ 的，这里 $C$ 表示整点的范围。而这里 $C$ 与 $n$ 同阶。

有 $T(x)=T(y)+T(x-y-1)+O(n)$，可以发现 $T(n^{\frac 2 3})=O(n^{\frac 3 5})$。

这里 $n=20000$（因为需要查询 $A,B$ 两个凸包中的所有点），常数不要太大均能通过。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 20010
#define ll long long
#define ld long double
#define eps 1e-9
using namespace std;
struct point{
    int x,y;
    point(ll X=0,ll Y=0):x(X),y(Y){}
    point operator +(const point a)const{return point(x+a.x,y+a.y);}
    point operator -(const point a)const{return point(x-a.x,y-a.y);}
    bool operator <(const point a)const{return x==a.x?y<a.y:x<a.x;}
    int operator *(const point a)const{return x*a.x+y*a.y;}
    int operator ^(const point a)const{return x*a.y-y*a.x;}
}pa[N],pb[N],pc[N];
inline int cross(point a,point o,point b){return (a-o)^(b-o);}
inline ld slope(point a,point o,point b){return 1.0L*((a-o)*(b-o))/cross(a,o,b);}
int n,m;
bool check(point x,point y)
{
    ld l=-1e50,r=1e50;
    for(int i=1;i<=n;i++)
    if(cross(x,pa[i],y))
    {
        ld sl=slope(x,pa[i],y);
        if(cross(pa[i],x,y)<0) l=max(l,sl);
        else r=min(r,sl);
    }
    for(int i=1;i<=m;i++)
    {
        if(cross(x,pb[i],y))
        {
            ld sl=slope(x,pb[i],y);
            if(cross(pb[i],x,y)>0) l=max(l,sl);
            else r=min(r,sl);
        }
        else if(pb[i].x>=min(x.x,y.x) && pb[i].x<=max(x.x,y.x) && pb[i].y>=min(x.y,y.y) && pb[i].y<=max(x.y,y.y)) return false;
    }
    return r-l>eps;
}
bool dfs(int l,int r)
{
    if(check(pc[l],pc[r])) return true;
    if(r-l<=1) return false;
    int u=0;
    ld v=1e50;
    for(int i=l+1;i<r;i++)
    {
        ld sl=slope(pc[l],pc[i],pc[r]);
        if(sl<v) v=sl,u=i;
    }
    return dfs(l,u) || dfs(u,r);
}
int tot=0;
bool get_convex()
{
    tot=0;
    for(int i=1;i<=n;i++)
    {
        while(tot>1 && cross(pc[tot],pc[tot-1],pa[i])<=0) tot--;
        pc[++tot]=pa[i];
    }
    int s=tot;
    for(int i=n-1;i;i--)
    {
        while(tot>s && cross(pc[tot],pc[tot-1],pa[i])<=0) tot--;
        pc[++tot]=pa[i];
    }
    --tot;
    return dfs(1,tot);
}
int main()
{
    scanf("%d%d",&n,&m);
    if(n==1 || m==1){puts("YES");return 0;}
    for(int i=1;i<=n;i++) scanf("%d%d",&pa[i].x,&pa[i].y);
    for(int i=1;i<=m;i++) scanf("%d%d",&pb[i].x,&pb[i].y);
    sort(pa+1,pa+n+1);sort(pb+1,pb+m+1);
    if(get_convex()){puts("YES");return 0;}
    swap(n,m);
    for(int i=1;i<=max(n,m);i++) swap(pa[i],pb[i]);
    if(get_convex()){puts("YES");return 0;}
    puts("NO");
    return 0;
}
```
