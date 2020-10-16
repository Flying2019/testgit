### [����](https://loj.ac/problem/3285)
�����⡣

���Ⱥ����ԣ���Щ��ţ����һЩ�ǿ��Ի����û��ġ�������Щ�û��ĵ��С�ֱ�Ϊ $s_i$����ô��Ϊ $\binom n {s_1,s_2,\cdots s_k}$��

����ĳһ���� $[l,r]$ ���� $k$ �� $l\rightarrow r$ ·������С����ô��Ȼ�� $l\rightarrow r$ ��һ���û���ֱ�����ϼ��ɡ�����Ҫ�� $l\rightarrow r$ ·���ϲ�������������2��ȵĵ㣬�� $l,r$ ����ȳ���3��

����֤����ֻ���������������²Ŵ��� $l,r$ �û���

������dfsһ�鴦�����������Ȼ��ö�� $k$ �Ӵ�С����һ�鼴�ɡ�

���Ӷ� $O(n\log n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
#define mod 1000000007
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N],f[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int siz[N],val[N];
void merge(int x,int y,int w)
{
	x=find(x),y=find(y);
	if(x==y) return;
	f[x]=y;
	siz[y]+=siz[x]-2;
	val[y]+=val[x]+w-1;
}
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	deg[u]++;
}
int ksm(int a,int b=mod-2)
{
	int r=1;
	for(;b;b>>=1)
	{
		if(b&1) r=1ll*r*a%mod;
		a=1ll*a*a%mod;
	}
	return r;
}
int fac[N],inv[N];
struct node{
	int s,t,w;
	node(int x=0,int y=0,int z=0):s(x),t(y),w(z){}
	bool operator <(const node a)const{return w<a.w;}
}p[N];
int tot;
void dfs(int u,int pre,int s,int d)
{
	if(deg[u]!=2){if(s) p[++tot]=node(s,u,d);d=1,s=u;}
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==pre) continue;
		dfs(v,u,s,d+1);
	}
}
int g[N],ans[N];
int main()
{
	int n;
	scanf("%d",&n);
	fac[0]=1;
	for(int i=1;i<=n*2;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[n*2]=ksm(fac[n*2]);
	for(int i=n*2-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	int ptot=0;
	for(int i=1;i<=n;i++)
	if(deg[i]!=2) f[i]=i,siz[i]=deg[i],g[++ptot]=i;
	int rt=g[1];
	dfs(rt,0,0,1);
	sort(p+1,p+tot+1);
	int u=1;
	for(int k=n-1;k>=1;k--)
	{
		for(;u<=tot && k<n-p[u].w;u++) merge(p[u].s,p[u].t,p[u].w);
		int qtot=0;
		ans[k]=fac[k];
		for(int i=1;i<=ptot;i++)
		{
			int u=g[i];
			if(f[u]!=u) continue;
			g[++qtot]=u;
			ans[k]=1ll*ans[k]*inv[k-n+1+val[u]-siz[u]*(k-n+1)]%mod;
		}
		ptot=qtot;
	}
	ans[n]=fac[n];
	for(int k=1;k<=n;k++) printf("%d\n",ans[k]);
	return 0;
}
```
