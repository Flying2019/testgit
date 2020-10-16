#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1600
#define C 10
#define mod 1000000007
#define ll long long
using namespace std;
int ch[N][C+2],fail[N],tot=1;
ll f[N][N];
bool end[N];
char str[N];
void insert(char *s)
{
	int n=strlen(s);
	int u=1;
	for(int i=0;i<n;i++)
	{
		if(!ch[u][s[i]-'0']) ch[u][s[i]-'0']=++tot;
		u=ch[u][s[i]-'0'];
	}
	end[u]=true;
}
int q[N],lf,rf;
void work()
{
	for(int i=0;i<C;i++) ch[0][i]=1;
	fail[1]=0;
	q[1]=1;
	lf=rf=1;
	while(lf<=rf)
	{
		int u=q[lf++];
		for(int i=0;i<C;i++)
		if(!ch[u][i]) ch[u][i]=ch[fail[u]][i];
		else fail[ch[u][i]]=ch[fail[u]][i],q[++rf]=ch[u][i];
	}
	for(int i=1;i<=rf;i++) end[q[i]]|=end[fail[q[i]]];
}
int n;
char num[N];
ll dfs(int u,int c,bool sm,bool zero)
{
	if(u>n) return !zero;
	if(sm && f[u][c]>=0) return f[u][c];
	int all=sm?9:num[u]-'0';
	ll res=0;
	for(int i=0;i<=all;i++)
	{
		if(zero && !end[ch[1][i]]) res=(res+dfs(u+1,ch[1][i],sm || i!=all,i==0))%mod;
		else if(!zero && !end[ch[c][i]]) res=(res+dfs(u+1,ch[c][i],sm || i!=all,0))%mod;
	}
	if(sm && !zero) f[u][c]=res;
	return res;
}
int main()
{
	scanf("%s",num+1);
	n=strlen(num+1);
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%s",str),insert(str);
	work();
	memset(f,-1,sizeof(f));
	printf("%lld\n",dfs(1,1,0,1));
	return 0;
}

