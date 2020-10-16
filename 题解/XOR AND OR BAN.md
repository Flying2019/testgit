### [链接](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2991)
首先可以发现 $(x\oplus X)\oplus X=x$，而要求 $x$ 不能和 $x\oplus X$ 同时放入集合。所以 $Xor$ 条件下不存在其他限制。

而且题目要求 $2^{n+1}$ 元素中有一半（$2\oplus n$）选中。根据鸽子原理，必须每组 $(x,x\oplus X)$ 中有且仅有一个被选中。对应了[2-sat](https://www.luogu.com.cn/problem/P4782)模型。

可以发现，对于 $And,\ Or$ 的限制，本质是一个子集/超集，总限制对数为 $O(3^n)$，而2-sat是 $O(n+m)$，直接连边跑2-sat复杂度 $O(2^n+3^n)$，可以接受。

所以对于每组 $Ans,\ Or$ 限制，直接连边 $x\rightarrow y\oplus X,y\rightarrow x\oplus X$，对于2-sat直接套板子即可。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N (1<<15)+10
#define M 1<<26
using namespace std;
int dfn[N],low[N],in[N];
int stack[N],top,cnt;
int nxt[M],to[M],head[N];
int s[N],num,n;
void add(int u,int v)
{
	++u,++v;
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
void tarjan(int now)
{
	dfn[now]=low[now]=++cnt;
	stack[top++]=now;
	in[now]=true;
	for(int i=head[now];i;i=nxt[i])
	{
		int v=to[i];
		if(!dfn[v])
		{
			tarjan(v);
			low[now]=min(low[v],low[now]);
		}
		else if(in[v])low[now]=min(dfn[v],low[now]);
	}
	if(low[now]==dfn[now])
	{
		int u;
		++num;
		do
		{
			u=stack[--top];
			in[u]=false;
			s[u]=num;
		}
		while(u!=now);
	}
}
int wx,wa,wo;
bool can(void)
{
	for(int i=1;i<=n;i++)
	if(!dfn[i]) tarjan(i);
	for(int i=0;i<n;i++) s[i]=s[i+1];
	for(int i=0;i<n;i++) if(s[i]==s[i^wx]) return false;
	return true;
}
int ans[N],tot;
int main()
{
	scanf("%d%d%d%d",&n,&wx,&wa,&wo);
	if(!wx){puts("No");return 0;}
	int m=1<<(n+1);
	for(int s=0;s<m;s++)
	{
		if((s&wa)==wa)
		{
			int s0=(m-1)&(~s);
			for(int t=s0;;t=(t-1)&s0)
			{
				int u=wa|t;
				add(s,u^wx);
				add(u,s^wx);
				if(!t) break;
			}
		}
		if((s|wo)==wo)
		{
			for(int t=s;;t=(t-1)&s)
			{
				int u=(wo^s)|t;
				add(s,u^wx);
				add(u,s^wx);
				if(!t) break;
			}
		}
	}
	n=m;
	if(!can()) printf("No");
	else
	{
		puts("Yes");
		for(int i=0;i<m;i++)
		if(s[i]<s[i^wx]) ans[++tot]=i;
		for(int i=1;i<=tot;i++) printf("%d%s",ans[i],i==tot?"\n":" ");
	}
	return 0;
}
```
