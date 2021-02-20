#include<iostream>
#include<cstdio>
#include<cstring>
#define N 12
#define M 90
using namespace std;
int in[1<<N],deg[1<<N];
long long C[M][M],f[1<<N][M],g[1<<N][M];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	C[0][0]=1;
    for(int i=1;i<=m;i++)
	{
	    C[i][0]=1;
	    for(int j=1;j<=i;j++)
		C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int i=1;i<=m;i++)
	{
	    int u,v;
	    scanf("%d%d",&u,&v);
	    u--,v--;
		in[(1<<u)|(1<<v)]++;
	}
	int p=1<<n;
    C[0][0]=1;
    for(int u=1;u<p;u++)
	    for(int t=u;t;t=t-1&u)
		    deg[u]+=in[t];
	for(int s=1;s<p;s++)
	{
	    for(int i=0;i<=deg[s];i++)
		{
		    for(int t=s-1&s;t;t=t-1&s)
			if(t&(s&-s))
			{
				for(int j=0;j<=min(i,deg[t]);j++)
					f[s][i]+=g[t][j]*C[deg[s^t]][i-j];
			}
		    g[s][i]=C[deg[s]][i]-f[s][i];
		}
	}
	double ans=0;
	for(int i=0;i<=m;i++) ans+=f[p-1][i]*1.0/C[m][i];
	printf("%.6f\n",ans/(m+1.0));
	return 0;
}


