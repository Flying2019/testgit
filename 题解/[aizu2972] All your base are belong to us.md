### [链接](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2972)
### 题目大意
给定平面上 $n$ 个点，求一个点，使得其到这 $n$ 个点中前 $k$ 远的距离和最小。

要求精度 $\leq 10^{-3}$。
### 题解
好像标算应该是三分之类的算法。但是由于我太菜了，直接采用类似于爬山的算法。

考虑对于$k=n$ 的情况，这时候要求的其实是一个费马点，这个可以采用模拟力学（？的方法。

即假设这是一张桌子，所有点都打了一个洞，连下一根绳子并挂上等重的重物。绳子的另一端捆在一起。

然后不断判断绳结的运动方向然后微调即可。

见[JSOI2004 平衡点](https://www.luogu.com.cn/problem/P1337)。
![](https://cdn.luogu.com.cn/upload/pic/148.png)

而对于其他情况，我们也可以这么做：假设只有最远的 $k$ 个点连了绳子，然后对于这些点模拟一下即可。

同时为了方便，我们规定如果某个点距离绳结和第 $k$ 大的点距离绳结的距离**差不多**，那么我们把这个点也连上绳子。

直接这样做可能会T。考虑一开始当前点距离目标点还很远，可以用类似与模拟退火的思路，开始时移动距离比较大，后来越来越小，这样可以降低运行时间。

复杂度十分玄学。但由于这道题的精度需求十分小，而这样做可以做到 $10^{-6}$ 左右的精度，所以完全没有问题。事实也证明它跑得飞快。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 210
#define db double
#define eps 1e-5
using namespace std;
struct node{
    db x,y;
    node(db X=0,db Y=0):x(X),y(Y){}
    node operator <(const node a)const{return x==a.x?y<a.y:x<a.x;}
    node operator +(const node a)const{return node(x+a.x,y+a.y);}
    node operator -(const node a)const{return node(x-a.x,y-a.y);}
    node operator *(const db a)const{return node(x*a,y*a);}
    node operator /(const db a)const{return node(x*1.0/a,y*1.0/a);}
}p[N];
int n,k;
db dis(node a){return sqrt(a.x*a.x+a.y*a.y);}
node stb(node a){if(abs(a.x)<=eps && abs(a.y)<=eps) return node(0,0);return a/dis(a);}
struct pnode{
    int id;
    db d;
    bool operator <(const pnode a)const{return d<a.d;}
}a[N];
node check(node o)
{
    for(int i=1;i<=n;i++)
    a[i]=(pnode){i,dis(p[i]-o)};
    sort(a+1,a+n+1);
    reverse(a+1,a+n+1);
    node res=node(0,0);
    for(int i=1;i<=k;i++) res=res+stb(p[a[i].id]-o);
    for(int i=k+1;i<=n;i++)
    if(abs(a[i].d-a[k].d)<=eps) res=res+stb(p[a[i].id]-o);
    return res;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    scanf("%f%f",&p[i].x,&p[i].y);
    node ans=p[1];
    db T=10;
    while(abs(T)>eps)
    {
        node o=check(ans);
        if(dis(o)<=1e-5) break;
        o=o*T;
        ans=ans+o;
        T=T*0.995;
    }
    for(int i=1;i<=n;i++)
    a[i]=(pnode){i,dis(p[i]-ans)};
    sort(a+1,a+n+1);
    reverse(a+1,a+n+1);
    db res=0;
    for(int i=1;i<=k;i++) res=res+a[i].d;
    printf("%.4f",res);
    return 0;
}
```
