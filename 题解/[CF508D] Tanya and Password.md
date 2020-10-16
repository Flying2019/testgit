### [链接](http://codeforces.com/problemset/problem/508/D)
欧拉回路。

考虑将一个长度为2的字符串看成一个点，那么题目条件就是给定 $n$ 条有向边，求欧拉回路。

比如 $\texttt{abb}$ 就可以看成 $\texttt{ab}\ \rightarrow\ \texttt{bb}$ 的一条边。

而不同的点数总共只有不到10000个，可以直接处理。

对于求欧拉回路，有一种很简便的做法，就是先暴力找一条路径，注意这里如果用的是链式前向星，一定要加 $\&$ 号：
```cpp
void dfs(int u)
{
	for(int &i=head[u];i;)
	{
		int v=to[i];
		i=nxt[i];
		dfs(v);
	}
	ans+=(char)(u&255);
}
```
可以发现这样写之后一条边只会被经过一次，因为修改一个 $i$ 就会导致该点还在系统栈中的所有 $i$ 全部修改。

这样得到的欧拉回路是反的，所以倒过来就好了。

可以证明，这样一定能在 $O(n+m)$ 时间获得一条欧拉回路。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	deg[u]++,deg[v]--;
}
char str[4];
string ans;
void dfs(int u)
{
	for(int &i=head[u];i;)
	{
		int v=to[i];
		i=nxt[i];
		dfs(v);
	}
	ans+=(char)(u&255);
}
int main()
{
	int n;
	scanf("%d",&n);
	int s=0,t=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		int u=str[1]*256+str[2],v=str[2]*256+str[3];
		add(u,v);
		s=u;
	}
	for(int i=0;i<N-10;i++)
	if(deg[i])
	{
		if(deg[i]>1 || deg[i]<-1){puts("NO");return 0;}
		if(deg[i]==1) s=i;
		if(deg[i]==-1){if(t){puts("NO");return 0;}t=i;}
	}
	dfs(s);
	ans+=char(s/256);
	if(ans.size()!=n+2){puts("NO");return 0;}
	puts("YES");
	reverse(ans.begin(),ans.end());
	cout<<ans;
	return 0;
}
```
