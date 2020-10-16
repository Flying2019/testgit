### [链接](http://codeforces.com/problemset/problem/706/E)

乍一看好像很数据结构的样子。实际上并没有这么难。

考虑我们只需要知道最后的结果，而不需要知道其中间的处理过程以及任何的询问。所以树套树之类的数据结构就没有什么必要了。

由于我们可以散状排列，那么一个很显然的想法就是链表。

这里需要用到的就是单向十字链表。即每个点有一个右指针和左指针。

我们每次找到两个矩形对应的左上角，然后按边界“剪下来”，即把边界上的指针交换即可。

这样复杂度 $O(q(n+m))$ 可以通过。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define D(x) (t[x].d)
#define R(x) (t[x].r)
#define N 1010
#define M N*N
using namespace std;
struct node{
    int r,d,v;
}t[M];
int n,m,q;
int id(int x,int y){return x*(m+1)+y;}
int get(int x,int y){int u=0;for(;x;x--,u=D(u));for(;y;y--,u=R(u));}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&t[id(i,j)].v);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++) t[id(i,j)].r=id(i,j+1),t[id(i,j)].d=id(i+1,j);
    while(q --> 0)
    {
        int xl,xr,yl,yr,x,y;
        scanf("%d%d%d%d%d%d",&xl,&yl,&xr,&yr,&x,&y);
        int p1=get(xl-1,yl-1),p2=get(xr-1,yr-1);
        int u1=p1,u2=p2;
        for(int i=1;i<=y;i++) swap(t[u1=R(u1)].d,t[u2=R(u2)].d);
        for(int i=1;i<=x;i++) swap(t[u1=D(u1)].r,t[u2=D(u2)].r);
        u1=p1,u2=p2;
        for(int i=1;i<=x;i++) swap(t[u1=D(u1)].r,t[u2=D(u2)].r);
        for(int i=1;i<=y;i++) swap(t[u1=R(u1)].d,t[u2=R(u2)].d);
    }
    int u=D(0);
    for(int i=1;i<=n;i++,u=D(u),puts(""))
        for(int j=1,p=R(u);j<=m;j++,p=R(p)) printf("%d ",t[p].v);
    return 0;
}
```
