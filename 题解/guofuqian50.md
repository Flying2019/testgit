### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102657/problem/C)
### ��Ŀ����
����һ������ͼ��ÿ����������Ȩ��ÿ�����е�Ȩ $w_i$����һЩ�㱻��ǡ�����ĳһ���ܼ���Ϊ $r_i$����ô����һ���� $u$ ��Σ�նȾ��� $\sum{[\ v\text{�����}\ ]\ [\ dis(v,u)\leq r_i\ ]}$��

���һ�����Σ�ն�С�����ĵ�Ȩ����ô��������ǰ�ȫ�ġ�

�������� $n$ �죬�� $i$ ���ܼ���Ϊ $r_i$������ÿ���㣬����ж�����õ��°�ȫ�ġ�
### ���
���������кܶ࣬��ʵ���Է��ֶ���һ���� $i$��ֻҪ�� $t$ ����ܼ��� $r_t$ С���� $i$ �� $w_i$ ���ı�ǵ㵽 $i$ ����̾��룬��ô�����ǰ�ȫ�ġ�

��������ֻҪ�ҵ����� $i$ �� $w_i$ ���ĵ㼴�ɡ�

������� $w_i=1$������ֻ��Ҫ��ÿ����ǵ�ѹ�����ȶ��У���һ�����·���ɡ�

���Է���������� $w_i\leq 20$��������ת���м���һά�����õ�������һ���� $u$ Ϊ���ת�ƹ����ġ�����õ��Ѿ� $u$ ��ת�ƹ�����ôֱ��������

��Ȼ�����һ���� $i$ �Ѿ���20����ͬ�����ת�Ƶ��ˣ���ô��Ȼ֮��ת�Ƶ����������㲻���Ϊ�� $i$ �� $w_i$ ���ĵ㣬Ҳ����� $i$ ֮��ĵ�������ף�ֱ���������ɡ�

���Է��֣����������һ����ֻ�ᱻѹ�����ȶ������� $20$ �Σ�ʱ�临�Ӷ� $O(w\times m\log n)$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<map>
#define N 100010
#define M 200010
#define ll long long
using namespace std;
int nxt[M<<1],to[M<<1],head[N],cnt;
ll w[M<<1];
void add(int u,int v,ll w1)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=w1;
	head[u]=cnt;
}
map<int,ll>dis[N];
struct node{
	ll a;
	int s,u;
	node(int S=0,int U=0,ll A=0):a(A),s(S),u(U){}
	bool operator <(const node b)const{return a>b.a;}
};
priority_queue<node>q;
bool in[N],sp[N];
int tot,n,m;
struct pnode{
	int x;
	ll v;
	bool operator <(const pnode a)const{return v<a.v;}
}swp[23];
int kth[N];
ll kth_dis[N];
void dij()
{
	for(int i=1;i<=n;i++)
	if(sp[i]) q.push(node(i,i,0));
	while(!q.empty())
	{
		node p=q.top();
		q.pop();
		int u=p.u;
		if(dis[u].count(p.s)) continue;
		if(dis[u].size()>20) continue;
		dis[u][p.s]=p.a;
		for(int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			if(dis[v].count(p.s)) continue;
			q.push((node){p.s,v,p.a+w[i]});
		}
	}
	for(int i=1;i<=n;i++)
	{
		tot=0;
		for(auto u:dis[i]) swp[++tot]=(pnode){u.first,u.second};
		sort(swp+1,swp+tot+1);
		kth_dis[i]=kth[i]>tot?1e18:swp[kth[i]].v;
	}
}
ll num[N];
int ptot;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	int k;
	scanf("%d",&k);
	for(int i=1,a;i<=k;i++) scanf("%d",&a),sp[a]=true;
	for(int i=1;i<=n;i++) scanf("%d",&kth[i]);
	dij();
	scanf("%d",&ptot);
	for(int i=1;i<=ptot;i++) scanf("%lld",&num[i]);
	sort(num+1,num+ptot+1);
	for(int i=1;i<=n;i++) printf("%lld ",lower_bound(num+1,num+ptot+1,kth_dis[i])-num-1);
	return 0;
}
```
