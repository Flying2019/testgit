#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int d[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    for(int u=1;u<=n;u++)
    if(d[u]==0)
    {
        bool can=true;
        for(int i=head[u];i;i=nxt[i])
        if(d[to[i]]==2){can=false;break;}
        if(can){printf("%d\n",u);return 0;}
    }
    return 0;
}