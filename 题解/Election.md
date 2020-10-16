### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102652/problem/E)
### ��Ŀ����
����һ������ÿ��������һ�����֣�����ÿ���ڵ�Ϊ������������Զ���֮�͡�
### ���
��������Ա��ʾ��Ƕ�ά�������⡣

���Զ�ÿ����ֱ���㹱�ס������������������ֻ��Ҫ�������������·������ĳ�������б���С�ĵ�����

����Ȼǰ��dfsһ�鼴�ɣ�������ɢ�������߶����ϲ�����ڵ����������б���С�ĵ�����ȥ�������ڱ���С�ĵ����Ľ�����������׵��ǿ������б���С�ĵ�����

���Ӷ� $O(n\log n)$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 300010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
ll siz[N];
void dfs1(int u,int pre)
{
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==pre) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
}
int ls[N*40],rs[N*40],val[N*40],tot;
void insert(int &u,int l,int r,int pos)
{
	if(!u) u=++tot;
	if(l==r){val[u]++;return;}
	int mid=(l+r)>>1;
	if(pos<=mid) insert(ls[u],l,mid,pos);
	else insert(rs[u],mid+1,r,pos);
	val[u]=val[ls[u]]+val[rs[u]];
}
int answer(int u,int l,int r,int p)
{
	if(!u || p<l) return 0;
	if(l==r || p>=r) return val[u];
	int mid=(l+r)>>1;
	if(p<=mid) return answer(ls[u],l,mid,p);
	return answer(rs[u],mid+1,r,p)+val[ls[u]];
}
int merge(int x,int y)
{
	if(!x || !y) return x+y;
	val[x]+=val[y];
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	return x;
}
int root[N],n,p[N];
ll aval[N],vs[N];
ll dfs2(int u,int pre)
{
	ll ans=0;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==pre) continue;
		ans+=dfs2(v,u);
		ans+=1ll*(n-siz[v])*answer(root[v],1,n,p[u]-1);
		root[u]=merge(root[u],root[v]);
	}
	insert(root[u],1,n,p[u]);
	ans+=1ll*siz[u]*(p[u]-1-answer(root[u],1,n,p[u]-1));
	return ans;
}
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&vs[i]),aval[i]=vs[i];
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	sort(aval+1,aval+n+1);
	for(int i=1;i<=n;i++) p[i]=lower_bound(aval+1,aval+n+1,vs[i])-aval;
	dfs1(1,0);
	printf("%lld\n",dfs2(1,0));
	return 0;
}
```
