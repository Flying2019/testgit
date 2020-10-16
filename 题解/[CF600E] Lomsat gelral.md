### [����](https://www.luogu.com.cn/problem/CF600E)
�������⡣����������ñ����Ľⷨ����һ�������¼���е���ɫ���ִ�������¼���ֵ�ͼ�ֵ������ÿ���㶼��һ�飬$O(n^2)$��

������ʵ�ܶ�ĵ㱻���¼����˺ܶ�顣���Է���һ������ʵ���Լ̳���ĳ�������е�������Ϣ�������Ͳ������µݹ鴦��ö��ӡ�����Ȼ�̳����ض��ӵ���Ϣ��Ч����ߡ�����֤��һ���㵽���ڵ��·���ϵ���ߣ����Ӹ��ڵ�����ض��ӵıߣ���� $\log n$ ��������һ�������ᱻ���� $\log n$ �Σ���ʱ�临�Ӷ� $O(n\log n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int son[N],c[N],siz[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
int fa[N];
void get_son(int u,int pre)
{
	fa[u]=pre;
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==pre) continue;
		get_son(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
ll ans[N],tot[N],res,sum;
void dfs(int u,bool esc=false)
{
	tot[c[u]]++;
	if(tot[c[u]]&gt;res) res=tot[c[u]],sum=c[u];
	else if(tot[c[u]]==res) sum+=c[u];
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa[u] || (esc && v==son[u])) continue;
		dfs(v);
	}
}
void clear(int u)
{
	tot[c[u]]--;c[u];
	for(int i=head[u];i;i=nxt[i])
	if(to[i]!=fa[u]) clear(to[i]);
}
void solve(int u)
{
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==son[u] || v==fa[u]) continue;
		solve(v);
		clear(v);
		res=cnt=0;
	}
	if(son[u]) solve(son[u]);
	dfs(u,true);
	ans[u]=sum;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	get_son(1,0);
	solve(1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```
