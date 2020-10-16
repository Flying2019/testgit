#include<iostream>
#include<cstdio>
#include<cstring>
#define N 3010
#define M 3010
#define inf 100000000
using namespace std;
int f[N][M],sum[N],num[N],pos[N][M];
inline int get(int l,int r){return sum[r]-sum[l-1];}
int work(int l,int r)
{
    int mid=(l+r+1)>>1;
    return num[mid]*(mid-l+1)-num[mid]*(r-mid)-get(l,mid)+get(mid+1,r);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&num[i]),sum[i]=sum[i-1]+num[i];
    memset(f,30,sizeof(f));
    for(int i=1;i<=n;i++) f[i][1]=work(1,i);
    for(int i=1;i<=m;i++) pos[n][i]=1;
    for(int j=2;j<=m;j++)
	{
	    pos[n+1][j]=n;
	    for(int i=n;i>=1;i--)
		    for(int k=pos[i][j-1];k<=pos[i+1][j];k++)
			    if(f[k][j-1]+work(k+1,i)<f[i][j])
				{
				    f[i][j]=f[k][j-1]+work(k+1,i);
				    pos[i][j]=k;
				}
	}
    printf("%d\n",f[n][m]);
    return 0;
}
