#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define db double
#define N 310
#define eps 1e-9
using namespace std;
db num[N][N],ans[N],_2[N];
void gauss(int n)
{
	for(int i=1;i<=n;i++)
	{
		int id=i;
		for(int j=i+1;j<=n;j++)
		if(abs(num[id][i])<abs(num[j][i])) id=j;
		if(id!=i) swap(num[id],num[i]);
		for(int j=i+1;j<=n;j++)
		if(abs(num[j][i])>=eps)
		{
			db res=num[j][i]/num[i][i];
			for(int k=i;k<=n+1;k++) num[j][k]-=num[i][k]*res;
		}
	}
	for(int i=n;i;i--)
	{
		for(int j=i+1;j<=n;j++) num[i][n+1]-=num[i][j]*ans[j];
		ans[i]=num[i][n+1]/num[i][i];
	}
}
#define base 233
#define ull unsigned long long
ull bases[N];
ull l[N][N],r[N][N];
char str[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	bases[0]=1;
	_2[0]=1;
	for(int i=1;i<=m;i++)
	bases[i]=bases[i-1]*base,_2[i]=_2[i-1]*0.5;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for(int j=1;j<=m;j++)
		l[i][j]=l[i][j-1]+(ull)str[j]*bases[j],r[i][j]=(r[i][j-1]+str[m-j+1])*base;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=m;k++)
			if(l[i][k]==r[j][k])
            num[i][j]+=_2[m-k];
    for(int i=1;i<=n;i++) num[i][n+1]=-_2[m],num[n+1][i]=1;
	num[n+1][n+2]=1;
    gauss(n+1);
    for(int i=1;i<=n;i++)
    printf("%.8lf\n",ans[i]);
	return 0;
}
