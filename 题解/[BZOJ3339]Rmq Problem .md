### [����](https://www.luogu.com.cn/problem/P4137)
ͦ��������⣬��Ȼ�кܶ�������

#### ��������
ֱ������Ī�ӣ��߶����������� $\operatorname{mex}$�����Ӷ� $O(n\sqrt{n}\log n)$���е㿨����

��������Ż�����ʵ������ֻ��Ҫ���� $O(m)$ �β�ѯ�������߶��� $O(\log n)$ �Ĳ�ѯ�����Ǻ��б�Ҫ��

������ֵ��ֿ飬�޸� $O(1)$����ѯ $O(\sqrt{n})$����ʱ�临�Ӷ� $O(m\sqrt{n})$������ͨ����
#### ��������
����һ��ת�����������ѯ������û������ $x$����ô��һ�� $\leq x$��

�ٿ�����δ������Է��֣������һ�μ������������� $[l,r]$ ����һ���� $(l,r)$�����Է��ֲ�ѯ $[L,R]$ ��ͬ�ڲ�ѯ $l\leq L\ ,\ r\geq R$ �ĵ�����Сֵ��

��Ȼ����һ�������ά�������⣬ʱ�ո��Ӷ� $O(n\log^2 n)$��~~�����ռ���~~��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
#define M N*200
#define B 556
using namespace std;
/*
int a[N];
int val[M]={100000000},ls[M],rs[M],root[N],tot;
void insert(int &u,int l,int r,int p,int v)
{
	if(!u) val[u=++tot]=1e8;
	if(l==r){val[u]=min(val[u],v);return;}
	int mid=(l+r)>>1;
	if(p<=mid) insert(ls[u],l,mid,p,v);
	else insert(rs[u],mid+1,r,p,v);
	val[u]=min(val[ls[u]],val[rs[u]]);
}
int answer(int u,int l,int r,int L,int R)
{
	if(!u) return 1e8;
	if(L<=l && r<=R) return val[u];
	int mid=(l+r)>>1,ans=1e8;
	if(L<=mid) ans=min(ans,answer(ls[u],l,mid,L,R));
	if(R>mid) ans=min(ans,answer(rs[u],mid+1,r,L,R));
	return ans;
}
int n;
void add(int x,int y,int v){for(;x<=n;x+=(x&(-x))) insert(root[x],0,n,y,v);}
int query(int x,int y)
{
	int ans=n;
	for(;x;x-=(x&(-x)))
	ans=min(ans,answer(root[x],0,n,y,n));
	return ans;
}
int pre[N];
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	++n;
	for(int i=1;i<n;i++)
	{
		scanf("%d",&a[i]);
		a[i]=min(a[i],n);
		add(pre[a[i]]+1,i-1,a[i]);
		pre[a[i]]=i;
	}
	for(int i=0;i<=n;i++)
		add(pre[i]+1,n,i);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",query(l,r));
	}
	return 0;
}
*/
int a[N],ans[N];
int cnt[B][B],res[B];
void add(int x)
{
	int p=a[x]/B;
	res[p]+=!cnt[p][a[x]-p*B];
	cnt[p][a[x]-p*B]++;
}
void del(int x)
{
	int p=a[x]/B;
	cnt[p][a[x]-p*B]--;
	res[p]-=!cnt[p][a[x]-p*B];
}
int bl[N];
struct ques{
	int l,r,id;
	bool operator <(const ques a)const{return bl[l]==bl[a.l]?r<a.r:bl[l]<bl[a.l];}
}q[N];
int sq[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]=min(a[i],n+1),bl[i]=i/B;
	for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		while(l>q[i].l) add(--l);
		while(l<q[i].l) del(l++);
		for(int j=0;j<B;j++)
		if(res[j]!=B)
		{
			for(int k=0;k<B;k++)
			if(!cnt[j][k]){ans[q[i].id]=j*B+k;break;}
			break;
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```
