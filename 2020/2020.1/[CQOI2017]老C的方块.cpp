#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#define N 20010
#define M 200010
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
#define inf 1000000000
using namespace std;
struct node{
	int nxt,to,w;
}road[M];
int head[N],cnt=1;
void add(int u,int v,int w)
{
	road[++cnt]=(node){head[u],v,w};
	head[u]=cnt;
	road[++cnt]=(node){head[v],u,0};
	head[v]=cnt;
}
int dep[N],cur[N];
queue<int>q;
bool bfs(int s,int t)
{
	memset(dep,127,sizeof(dep));
	memcpy(cur,head,sizeof(cur));
	dep[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=road[i].nxt)
		{
			int v=road[i].to;
			if(dep[v]>=inf && road[i].w)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t]<=inf;
}
int dfs(int u,int t,int flow)
{
	if(u==t || !flow) return flow;
	int ans=0;
	for(int i=head[u];i;i=road[i].nxt)
	{
		int v=road[i].to,f=0;
		if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(flow,road[i].w))))
		{
			flow-=f;
			ans+=f;
			road[i].w-=f;
			road[i^1].w+=f;
			if(!flow) break;
		}
	}
	return ans;
}
int dinic(int s,int t)
{
	int ans=0;
	while(bfs(s,t)) ans+=dfs(s,t,inf);
	return ans;
}
int get_id(int x,int y){return ((y-1)%2)*4+(x-1)%4;}
/*
0|1|2|3 s->3 3->0 0->1 1->2 2->t
4|5|6|7

0||3|2|1|0|3
------------x
3||0|1|2|3|0
0||3|2|1|0|3
3||0|1|2|3|0
 y
*/
map<P,int>mp;
int px[N],py[N],pv[N];
inline void add_e(int u,int x,int y)
{
	if(mp.count(MP(x,y)))
	{
		int v=mp[MP(x,y)];
		add(u,v,min(pv[u],pv[v]));
	}
}
inline void add_inf(int u,int x,int y)
{
	if(mp.count(MP(x,y)))
	{
		int v=mp[MP(x,y)];
		add(u,v,inf);
	}
}
int s,t;
void work(int u)
{
	switch(get_id(px[u],py[u]))
	{
		case 0:{add_e(u,px[u]+1,py[u]);break;}
		case 1:{add_inf(u,px[u]+1,py[u]);add_inf(u,px[u],py[u]+1);add_inf(u,px[u],py[u]-1);break;}
		case 2:{add(u,t,pv[u]);break;}
		case 3:{add(s,u,pv[u]);add_inf(u,px[u]+1,py[u]);add_inf(u,px[u],py[u]+1);add_inf(u,px[u],py[u]-1);break;}
		case 4:{add(s,u,pv[u]);add_inf(u,px[u]-1,py[u]);add_inf(u,px[u],py[u]+1);add_inf(u,px[u],py[u]-1);break;}
		case 5:{add(u,t,pv[u]);break;}
		case 6:{add_inf(u,px[u]-1,py[u]);add_inf(u,px[u],py[u]+1);add_inf(u,px[u],py[u]-1);break;}
		case 7:{add_e(u,px[u]-1,py[u]);break;}
	}
}
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	s=q+1,t=s+1;
	for(int i=1;i<=q;i++)scanf("%d%d%d",&px[i],&py[i],&pv[i]),mp[MP(px[i],py[i])]=i;
	for(int i=1;i<=q;i++) work(i);
	printf("%d\n",dinic(s,t));
	return 0;
}

