#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define N 1000010
using namespace std;
struct node{
	ll x,y;
	node(ll X=0,ll Y=0):x(X),y(Y){}
	node operator +(const node a)const{return node(x+a.x,y+a.y);}
	node operator -(const node a)const{return node(x-a.x,y-a.y);}
	ll operator *(const node a)const{return x*a.y-y*a.x;}
}p[N],a[N],s,t;
bool down[N],dr[N];
int id[N];
int f[2][N],q[2][2],nxt[N];
ll cross(node o,node a,node b){return (a-o)*(b-o);}
double dis(node a,node b){return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));}
bool cmp(int x,int y){return p[x].x<p[y].x;}
int main()
{
	int n;
	scanf("%d%lld%lld",&n,&t.x,&t.y);
	for(int i=1;i<=n;i++)
	{
		double l,r,a;
		scanf("%lld%lld%lf",&p[i].x,&p[i].y,&a);
		l=atan2(s.y-p[i].y,s.x-p[i].x);
		r=atan2(t.y-p[i].y,t.x-p[i].x);
		if(l<r) down[i]=l<a && a<r;
		else down[i]=!(r<a && a<l);
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	int tot=0;
	a[++tot]=s;
	for(int i=1;i<=n && a[id[i]].x<t.x;i++)
	if(p[id[i]].x>s.x) a[++tot]=p[id[i]],dr[tot]=down[id[i]];
	a[++tot]=t;
	f[0][0]=f[1][0]=1;
	for(int i=1;i<=tot;i++)
	{
		bool u=dr[i];
		int &l0=q[0][u],&r0=q[1][u],&l1=q[0][u^1],&r1=q[1][u^1];
		int res=u?-1:1;
		if(l1<r1 && cross(a[f[u^1][l1]],a[i],a[f[u^1][l1+1]])*res>=0)
		{
			while(l1<r1 && cross(a[f[u^1][l1]],a[i],a[f[u^1][l1+1]])*res>=0) l1++;
			l0=r0=r0+1;
			f[u][r0]=f[u^1][l1];
			nxt[i]=f[u^1][l1];
		}
		else
		{
			while(l0<r0 && cross(a[f[u][r0-1]],a[i],a[f[u][r0]])*res>=0) r0--;
			nxt[i]=f[u][r0];
		}
		f[u][++r0]=i;
	}
	double ans=0;
	for(int i=tot;i>1;i=nxt[i]) ans+=dis(a[i],a[nxt[i]]);
	printf("%.10f",ans);
	return 0;
}
