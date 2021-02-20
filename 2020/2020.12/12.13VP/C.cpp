#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
void dfs(int u,int p,int &t,int &l)
{
    t=u;l=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int t1=0,l1=0,v=to[i];
        if(v==p) continue;
        dfs(v,u,t1,l1);
        if(l1+1>l) l=l1+1,t=t1;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    int t=0,l=0;
    dfs(1,0,t,l);
    dfs(t,0,t,l);
    puts(l%3==2?"Second":"First");
    return 0;
}