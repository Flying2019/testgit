#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 33
#define ll long long
using namespace std;
int l[N],id[N];
ll f[N<<3][M];
int main()
{
	int n,c;
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++) scanf("%d",&l[i]);
	sort(l+1,l+n+1);
	for(int i=1;i<n;i++) id[i]=i;
	double ans=0;
	int maxn=1<<(n-1);
	do
	{
		for(int i=0;i<=n*c;i++)
			for(int j=0;j<maxn;j++) f[i][j]=0;
		f[n*l[n]][0]=1;
		for(int i=0;i<n*c;i++)
		if(i%n)
		{
			int u=id[i%n];
			for(int s=0;s<maxn;s++)
			if(!(s&(1<<(u-1))))
			{
				int t=s|(1<<(u-1));
				for(int j=i;j<=n*c;j++)
				f[min(n*c,max(j,i+n*l[u]))][t]+=f[j][s];
			}
		}
		ans+=f[n*c][maxn-1];
	}while(next_permutation(id+1,id+n));
	for(int i=1;i<n;i++) ans/=1.0*i*c;
	printf("%.12f",ans);
	return 0;
}

