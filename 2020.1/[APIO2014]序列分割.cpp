#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 100010
#define M 210
using namespace std;
ll f[N],g[N],sum[N];
int q[N],h,t,pre[M][N];
inline ll solve(int x){return g[x]-sum[x]*sum[x];}
double slope(int x,int y)
{
	if(sum[x]==sum[y]) return 1e16;
	return (solve(y)-solve(x))*1.0/(sum[x]-sum[y]);
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1,a;i<=n;i++) scanf("%d",&a),sum[i]=sum[i-1]+a;
	for(int i=1;i<=k;i++)
	{
		memcpy(g,f,sizeof(f));
		h=t=0;
		for(int j=1;j<=n;j++)
		{
			while(t>h+1 && slope(q[h],q[h+1])<=sum[j]) h++;
			f[j]=0;
			if(t>h)
			{
				pre[i][j]=q[h];
				f[j]=solve(q[h])+sum[q[h]]*sum[j];
			}
			while(t>h+1 && slope(q[t-1],q[t-2])>=slope(j,q[t-1])) t--;
			q[t++]=j;
		}
	}
	printf("%lld\n",f[n]);
	int p=pre[k][n];
	while(k--)
	{
		printf("%d ",p);
		p=pre[k][p];
	}
	return 0;
}

