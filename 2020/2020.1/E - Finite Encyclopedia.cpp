#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
using namespace std;
int num[N];
int main()
{
	int n,k;
	scanf("%d%d",&k,&n);
	if(k&1)
	{
		for(int i=1;i<=n;i++) num[i]=(k+1)/2;
		int u=n;
		for(int i=1;i<=n/2;i++)
		if(num[u]==1) u--;
		else 
		{
			num[u]--;
			for(int j=u+1;j<=n;j++) num[j]=k;
			u=n;
		}
		for(int i=1;i<=u;i++) printf("%d ",num[i]); 
	}
	else
	{
		printf("%d ",k/2);
		for(int i=1;i<n;i++) printf("%d ",k);
	}
	return 0;
}

