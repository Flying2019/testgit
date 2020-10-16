#### [��Ŀ����](https://www.luogu.com.cn/problem/P4036)
## ��Ŀ����
һ��n*m����������һЩ�㣬һ���������������ͬһ�л�ͬһ�еĵ��ϡ����������յ㡣

��Ҫʹ��㲻�������յ㣬���ٳ��߼����㡣

$n,m\leq 100$
## ����˼·
���ǽ��ܹ����ൽ��ĵ�֮�����ߣ���ĿҪ��ʹɾȥ�������ٵĵ�ʹͼ����ͨ��

ʮ����·�ذ�һ������һ�����ͳ��㣬֮����һ������Ϊ1�ıߣ�ɾȥ����㼴ʹ��ȥ�����ߡ�

Ȼ����������������ˡ�
## ����
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cstring>
#define N 40010
#define M N*100
#define N1 110
#define ll long long
#define inf 1000000000
using namespace std;
struct node{
	int nxt,to;
	ll f;
}road[M];
int head[N],cur[N],cnt=1;
void add(int u,int v,ll f)
{
	road[++cnt]=(node){head[u],v,f};
	head[u]=cnt;
	road[++cnt]=(node){head[v],u,0};
	head[v]=cnt;
}
queue<int>q;
int dep[N];
bool bfs(int s,int t)
{
	memcpy(cur,head,sizeof(cur));
	memset(dep,127,sizeof(dep));
	dep[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=road[i].nxt)
		if(road[i].f>0)
		{
			int v=road[i].to;
			if(dep[v]>=inf)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t]<=inf;
}
ll dfs(int u,int t,ll flow)
{
	if(u==t || !flow) return flow;
	ll ans=0;
	for(int i=cur[u];i;i=road[i].nxt)
	{
		cur[u]=i;
		int v=road[i].to,f=0;
		if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(flow,road[i].f))))
		{
			flow-=f;
			ans+=f;
			road[i].f-=f;
			road[i^1].f+=f;
			if(!flow) break;
		}
	}
	return ans;
}
ll dinic(int s,int t)
{
	ll ans=0;
	while(bfs(s,t)) ans+=dfs(s,t,inf);
	return ans;
}
int n,m;
int id(int x,int y){return (x-1)*m+y;}
int ids(int x,int o){return x*2+o;}
void add_e(int x,int y)
{
	add(ids(x,1),ids(y,0),inf);
	add(ids(y,1),ids(x,0),inf);
}
char str[N1][N1];
int main()
{
	scanf("%d%d",&n,&m);
	int s=(n*m)*2+2,t=s+1;
	for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		if(str[i][j]!='.')
		{
			for(int k=i+1;k<=n;k++)
			if(str[k][j]!='.')
				add_e(id(i,j),id(k,j));
			for(int k=j+1;k<=m;k++)
			if(str[i][k]!='.')
				add_e(id(i,j),id(i,k));
			if(str[i][j]=='S')
				add(s,ids(id(i,j),0),inf),add(ids(id(i,j),0),ids(id(i,j),1),inf);
			else if(str[i][j]=='T')
				add(ids(id(i,j),1),t,inf),add(ids(id(i,j),0),ids(id(i,j),1),inf);
			else add(ids(id(i,j),0),ids(id(i,j),1),1);
		}
	ll ans=dinic(s,t);
	printf("%lld\n",ans>=inf?-1:ans);
	return 0;
}

```
