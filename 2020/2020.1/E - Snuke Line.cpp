#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300010
using namespace std;
struct node{
	int l,r;
	bool operator <(const node a)const{return r-l<a.r-a.l;}
}p[N];
int tree[N<<2];
inline int lowbit(int x){return x&(-x);}
void insert(int u,int v){for(;u<N<<2;u+=lowbit(u)) tree[u]+=v;}
int answer(int u){int ans=0;for(;u;u-=lowbit(u)) ans+=tree[u];return ans;}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].l,&p[i].r),p[i].l++,p[i].r++;
	sort(p+1,p+n+1);
	int u=1;
	for(int i=1;i<=m;i++)
	{
		while(p[u].r-p[u].l+1<i && u<=n)
		{
			insert(p[u].l,1);
			insert(p[u].r+1,-1);
			u++;
		}
		int ans=n-u+1;
		for(int j=0;j<=m;j+=i) ans+=answer(j+1);
		printf("%d\n",ans);
	}
	return 0;
}

