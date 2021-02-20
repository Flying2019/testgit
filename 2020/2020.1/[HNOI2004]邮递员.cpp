#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define N 22
#define M 22
#define maxn 234567
#define ull unsigned long long
#define ll __int128
#define chg(x) (1<<mi[x])
#define get(x,y) (x>>mi[y])%4
using namespace std;
int mp[N][N],mi[N+1];
ull f[2][maxn];
ll g[2][maxn];
int ton[maxn],tot[2],k,n,m,endn,endm;
void insert(ull sta,ll num)
{
	int key=sta%maxn;
	while(ton[key])
	{
		if(f[k][ton[key]]==sta)
		{
			g[k][ton[key]]+=num;
			return;
		}
		key++;
		if(key==maxn) key=0;
	}
	ton[key]=++tot[k];
	f[k][ton[key]]=sta;
	g[k][ton[key]]=num;
}
void read()
{
	scanf("%d%d",&n,&m);
	if(n<m) swap(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			{
				mp[i][j]=1;
				endn=i;
				endm=j;
			}
	for(int i=1;i<=N;i++) mi[i]=i*2;
}
ll ans;
void work()
{
	read();
    if(n==1 || m==1)
    {
        puts("1");
        exit(0);
    }
	g[0][1]=1;
	tot[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			k^=1;
			tot[k]=0;
			memset(f[k],0,sizeof(f[k]));
			memset(g[k],0,sizeof(g[k]));
			memset(ton,0,sizeof(ton));
			for(int u=1;u<=tot[k^1];u++)
			{
				ull sta=f[k^1][u];
				ll num=g[k^1][u];
				int l=get(sta,j-1),r=get(sta,j);
				if(!mp[i][j])
				{
					if(!l && !r) insert(sta,num);
				}
				else if(!l)
				{
					if(!r)
					{
						if(mp[i][j+1] && mp[i+1][j]) insert(sta+chg(j-1)+2*chg(j),num);
					}
					else
					{
						if(mp[i][j+1]) insert(sta,num);
						if(mp[i+1][j]) insert(sta-r*chg(j)+r*chg(j-1),num);
					}
				}
				else if(l==1)
				{
					if(!r)
					{
						if(mp[i+1][j]) insert(sta,num);
						if(mp[i][j+1]) insert(sta-l*chg(j-1)+l*chg(j),num);
					}
					if(r==1)
					{
						int st,left=1;
						for(int a=j+1;a<=m;a++)
						{
							st=get(sta,a);
							if(st==1) left++;
							if(st==2) left--;
							if(!left)
							{
								st=sta-l*chg(j-1)-r*chg(j)-1*chg(a);
								break;
							}
						}
						insert(st,num);
					}
					if(r==2)
					{
						if(i==endn && j==endm) ans+=num;
					}
				}
				else if(l==2)
				{
					if(!r)
					{
						if(mp[i+1][j]) insert(sta,num);
						if(mp[i][j+1]) insert(sta-l*chg(j-1)+l*chg(j),num);
					}
					if(r==1)
					{
						insert(sta-l*chg(j-1)-r*chg(j),num);
					}
					if(r==2)
					{
						int st,right=1;
						for(int a=j-2;a>=1;a--)
						{
							st=get(sta,a);
							if(st==2) right++;
							if(st==1) right--;
							if(!right)
							{
								st=sta-l*chg(j-1)-r*chg(j)+1*chg(a);
								break;
							}
						}
						insert(st,num);
					}
				}
			}
		}
		for(int j=1;j<=tot[k];j++)
		f[k][j]=f[k][j]<<2;
	}
}
void print_(ll a)
{
	if(a>9) print_(a/10);
    putchar(a%10+'0');
}
int main()
{
	work();
	print_(ans*2);
	return 0;
}
