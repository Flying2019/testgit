#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
#define mod 998244353
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v){nxt[++cnt]=head[u];to[cnt]=v;head[u]=cnt;}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add(u,v),add(v,u);
        }
        for(int i=1;i<=n;i++) head[i]=0;
        cnt=0;
    }
    return 0;
}