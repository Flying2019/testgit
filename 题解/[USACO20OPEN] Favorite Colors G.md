### [����](https://www.luogu.com.cn/problem/P6279)
ת�����⣺ÿ�ο��Խ�һ��һ������������е�ϲ���һ���㣬�����ÿ����ĺϲ���Ϣ��

�������ʣ�µĵ㣬ÿ������������ֻ��һ���㡣�������ǲ����ն�һ���㣬��������ϲ����������ȥ��

��������ö��ÿ���㣬���κϲ��������ڵ�ϲ���֮���ӽڵ�Ҳ��Ҫ�ݹ�ϲ�������ӽڵ���һ�������ܻ���Ҫ�ϲ���Ρ�

�ر�ģ�������Ի����ϲ�����Ļ�Ҳ�㣩��Ҫ���С�

���Ƹ��ӶȺܼ٣�����ÿ�κϲ���Ȼ��ϲ������㣬���Ժϲ������� $O(n)$ �ġ�

�ܸ��Ӷ� $O(n\cdot\alpha(n))$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
int f[N],tf[N],tot;
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
void dfs(int);
void merge(int u,int v)
{
	u=find(u),v=find(v);
	if(u==v) return;
	f[u]=v;
	if(!tf[u] || !tf[v]){tf[v]|=tf[u];return;}
	merge(tf[u],tf[v]);
}
bool sf[N];
void dfs(int u)
{
	if(tf[u]) return;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=find(to[i]);
		if(!tf[u]) tf[u]=v;
		dfs(v);
		merge(tf[u],v);
	}
}
int vis[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;i++) f[i]=i;
	for(int x=1;x<=n;x++)
	{
		int u=find(x);
		for(int i=head[x];i;i=nxt[i]) sf[u]|=find(to[i])==u;
		if(!sf[u]) u=(tf[u]?tf[u]:(tf[u]=to[head[x]]));
		for(int i=head[x];i;i=nxt[i]) merge(to[i],u);
	}
	int t=0;
	for(int i=1;i<=n;i++)
	{
		if(!vis[find(i)]) vis[find(i)]=++t;
		printf("%d\n",vis[find(i)]);
	}
	return 0;
}
/*
9 10
1 2
2 3
3 1
2 4
5 4
5 6
6 7
7 8
8 9
9 5
*/
```
