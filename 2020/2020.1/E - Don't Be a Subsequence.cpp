#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
char str[N];
int f[N],p[N][26];
int main()
{
	scanf("%s",str);
	int n=strlen(str);
	for(int i=0;i<26;i++) p[n][i]=n;
	f[n]=1;
	for(int i=n-1;i>=0;i--)
	{
		for(int j=0;j<26;j++) p[i][j]=p[i+1][j];
		p[i][str[i]-'a']=i;
		f[i]=n+1;
		for(int j=0;j<26;j++) f[i]=min(f[i],f[p[i][j]+1]+1);
	}
	int m=f[0],u=0;
	while(m--)
	{
		for(int j=0;j<26;j++)if(f[p[u][j]+1]+1==f[u])
		{
			putchar('a'+j);
			u=p[u][j]+1;
			break;
		}
	}
	return 0;
}
