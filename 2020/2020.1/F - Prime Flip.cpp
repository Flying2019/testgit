#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#define N 210
#define M 10000020
using namespace std;
int prime[M],link[N],tot;
bool p[M],vis[N];
int n;
bool can[N][N],s[M];
vector<int>v[2];
bool check(int u)
{
	for(int i=1;i<=v[1].size();i++)
	if(can[u][i] && !vis[i])
	{
		vis[i]=1;
		if(!link[i] || check(link[i]))
 		{
			link[i]=u;
			return true;
		}
	}
	return false;
}
int main()
{
	p[1]=true;
	for(int i=2;i<=M-10;i++)
	{
		if(!p[i]) prime[++tot]=i;
		for(int j=1;j<=tot && i*prime[j]<=M-10;j++)
		{
			p[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int u;
		scanf("%d",&u);
		s[u]=true;
	}
	for(int i=1;i<=M-10;i++)
	if(s[i]^s[i-1]) v[i&1].push_back(i);
	for(int i=0;i<v[0].size();i++)
		for(int j=0;j<v[1].size();j++)
		if(!p[abs(v[0][i]-v[1][j])]) can[i+1][j+1]=true;
	int ans=0;
    for(int i=0;i<v[0].size();i++)
	{
		memset(vis,0,sizeof(vis));
		ans+=check(i+1);
	}
	int tmp=ans;
	ans+=(v[0].size()-ans)/2*2+(v[1].size()-ans)/2*2;
    if((v[0].size()&1)!=(tmp&1)) ans+=3;
	printf("%d",ans);
	return 0;
}
