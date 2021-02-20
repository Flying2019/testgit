#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 5010
using namespace std;
ll f[N][N],sum[N];
double slope(int x,int l,int r){return (f[x][l]+sum[l]*sum[l]-f[x][r]-sum[r]*sum[r])*1.0/(sum[l]-sum[r]);}
int q[N],l,r;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1,a;i<=n;i++) scanf("%d",&a),sum[i]=sum[i-1]+a;
	for(int i=1;i<=n;i++) f[1][i]=sum[i]*sum[i];
	for(int i=2;i<=m;i++)
	{
		l=1,r=0;
		for(int j=1;j<=n;j++)
		{
			while(l<r && slope(i-1,q[l],q[l+1])-2*sum[j]<0) l++;
			f[i][j]=f[i-1][q[l]]+(sum[q[l]]-sum[j])*(sum[q[l]]-sum[j]);
			while(l<r && slope(i-1,q[r-1],q[r])>slope(i-1,q[r],j)) r--;
			q[++r]=j;
		}
	}
	printf("%lld\n",m*f[m][n]-sum[n]*sum[n]);
	return 0;
}

