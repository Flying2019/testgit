### [链接](https://codeforces.com/contest/908/problem/H)
首先可以发现，题目中任意两点至少有一点能到达另一点。所以考虑贪心，首先对于 $A$ 的边可以合并，然后可以发现这些点最优的方案就是连成一个环。

$O$ 其实就是不加限制。所以接下来就只要考虑 $X$ 的边。

考虑最后连成的一定是一颗树，所以我们考虑合并尽可能多的 $size\geq 2$ 的联通块即可。可以发现联通块个数最多为23个，略微推导可以发现这本质是一次超集和变换加上一次卷积，直接套公式即可。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 110
#define M 1<<23
using namespace std;
int fa[N],f[M],g[M],h[M],siz[N],id[N],cnt;
int find(int x){return fa[x]==x?fa[x]:(fa[x]=find(fa[x]));}
void merge(int x,int y)
{
	int hx=find(x),hy=find(y);
	if(hx==hy) return;
	siz[hx]+=siz[hy];
	fa[hy]=hx;
}
char s[N][N];
void fwt(int f[],int n)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int l=0;l<i;l++)
				f[l+i+j]+=f[l+j];
}
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1),fa[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
		if(s[i][j]=='A') merge(i,j);
	memset(id,-1,sizeof(id));
	for(int i=1;i<=n;i++)
	if(fa[i]==i)
	{
		ans+=siz[i];
		if(siz[i]>=2)id[i]=cnt++;
	}
	if(cnt==0)
	{
		printf("%d\n",n-1);
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='X')
			{
				int h1=find(i),h2=find(j);
				if(h1==h2)
				{
					puts("-1");
					return 0;
				}
				if(id[h1]>=0 && id[h2]>=0) f[(1<<id[h1])|(1<<id[h2])]=1;
			}
	int m=1<<cnt;
	for(int s=1;s<m;s++)
		for(int i=0;i<n;i++)
			if(s&(1<<i))
				f[s]|=f[s^(1<<i)];
	for(int i=0;i<m;i++) f[i]^=1;
	fwt(f,m);
	for(int i=0;i<m;i++) g[i]=1;
	for(int i=1;i<m;i<<=1)
		for(int j=0;j<m;j+=(i<<1))
			for(int l=j;l<i+j;l++) g[l]*=-1;
	for(int i=0;i<m;i++) h[i]=1;
	int u=1;
	while(1)
	{
		int res=0;
		for(int j=0;j<m;j++) h[j]*=f[j];
		for(int j=0;j<m;j++) res+=h[j]*g[j];
		if(res)
		{
			printf("%d\n",ans+u-1);
			return 0;
		}
		++u;
	}
	return 0;
}
```
