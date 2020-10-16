### [链接](http://codeforces.com/problemset/problem/687/D)
首先考虑贪心：显然我们应该尽可能满足大的边使之可行。具体来说，我们从大往小加边直到图不是一个二分图为止。

这显然可以通过正反集来搞。但是这里有多次询问怎么办？

由于本质上是找奇环。那么整张图我们保留一个树结构，然后剩下的边往上加即可。

具体来说，用带权并查集维护，这里可以直接异或处理然后加上路径压缩。我们合并两张图直接揉在一起就好了。

然后用类似于倍增的思路处理即可。复杂度 $O(n^2+q\log m\times \alpha(n))$。

然而由于常数过大，被 $O(nm)$ 的暴力艹过了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define M 500010
using namespace std;
struct node{
	int x,y,w,id;
	bool operator <(const node a)const{return w>a.w;}
}r[M];
int f[N*2];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&r[i].x,&r[i].y,&r[i].w),r[i].id=i;
	sort(r+1,r+m+1);
	while(q --> 0)
	{
		int lf,rf,w=-1;
		scanf("%d%d",&lf,&rf);
		for(int i=1;i<=n*2;i++) f[i]=i;
		for(int i=1;i<=m;i++)
		if(r[i].id>=lf && r[i].id<=rf)
		{
			int hx=find(r[i].x),hy=find(r[i].y),ix=find(r[i].x+n),iy=find(r[i].y+n);
			if(hx==hy || ix==iy) {w=r[i].w;break;}
			f[hx]=iy,f[hy]=ix;
		}
		printf("%d\n",w);
	}
	return 0;
}
```
