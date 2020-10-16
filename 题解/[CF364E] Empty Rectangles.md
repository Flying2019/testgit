### [链接](http://codeforces.com/problemset/problem/364/E)
很经典的分治。

首先 $k$ 很小。那么显然有一个 $O(n^3)$ 的枚举，显然也过不去。

考虑优化。我们仿照K-D Tree的做法，即每次枚举一个中点，然后将平面切成两半。

同样，我们也将平面切成两半。不妨假设我们切的是y轴。那么这样我们只需要考虑y轴跨越该中点的区域答案即可。

具体来说，我们枚举 $x$ 轴的左端点，然后右端点移动的同时我们也移动y的两个端点，直接计算即可。

这样时间复杂度看起来是 $O(n^2k^2\log n)$，但实际上应该是 $T(n)=4T(n/2)+O(n^2k^2)$，好像算出来也是 $O(n^2k^2\log n)$，但是常数看起来很小。

主要有14s，肯定跑得过。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2510
#define M 10
using namespace std;
int sum[N][N],n,m,k;
char s[N];
int fl[M],fr[M];
long long ans=0;
int slv(int lx,int ly,int rx,int ry,int o){if(o)swap(lx,ly),swap(rx,ry);return sum[rx][ry]-sum[lx-1][ry]-sum[rx][ly-1]+sum[lx-1][ly-1];}
void work(int lx,int ly,int rx,int ry,int o)
{
	if(lx>rx || ly>ry) return;
	if(rx-lx>ry-ly) swap(lx,ly),swap(rx,ry),o^=1;
	int mid=(ly+ry)>>1;
	for(int i=lx;i<=rx;i++)
	{
		for(int j=0;j<=k;j++) fl[j]=ly,fr[j]=ry;
		for(int j=i;j<=rx;j++)
		{
			for(int p=0;p<=k;p++)
			{
				while(slv(i,fl[p],j,mid,o)>p) fl[p]++;
				while(slv(i,mid+1,j,fr[p],o)>p) fr[p]--;
			}
			for(int p=0;p<=k;p++)
				ans+=((p==0?mid+1:fl[p-1])-fl[p])*(fr[k-p]-(p==k?mid-1:fr[k-p-1]));
		}
	}
	work(lx,ly,rx,mid-1,o),work(lx,mid+1,rx,ry,o);
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++) sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+s[j]-'0';
	}
	work(1,1,n,m,0);
	printf("%lld\n",ans);
	return 0;
}
```
