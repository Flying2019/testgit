#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100
using namespace std;
int n,num[N+10];
bool f[N+10][N+10][N+10][2];
bool work()
{
	memset(f,0,sizeof(f));
	for(int i=1;i<=N;i++) scanf("%d",&num[i]);
	f[0][0][0][0]=1;
	for(int i=1;i<=N;i++)
		for(int j=0;j<=num[i-1];j++)
			for(int k=0;k<=num[i];k++)
			{
				if((k>=2 && f[i][j][k-2][0]) ||
				(k>=3 && f[i][j][k-3][1]) ||
				(k>=4 && f[i][j][k-4][1]) ||
				(j>=k && (i<2?0:num[i-2])>=k && f[i-1][(i<2?0:num[i-2])-k][j-k][1])) f[i][j][k][1]=true;
				if((k>=3 && f[i][j][k-3][0]) ||
				(k>=4 && f[i][j][k-4][0]) ||
				(j>=k && (i<2?0:num[i-2])>=k && f[i-1][(i<2?0:num[i-2])-k][j-k][0])) f[i][j][k][0]=true;
			}
	return f[N][num[N-1]][num[N]][1];
}
int main()
{
	int t;
    scanf("%d",&t);
    while(t --> 0) puts(work()?"Yes":"No");
    return 0;
}
