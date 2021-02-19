#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310
using namespace std;
int n;
struct FSM{
    int a[N],b[N][3];
    int jp[N][3];
    void nxt(int &x,int &y,int v)
    {
        if(jp[y][v]) x=jp[y][v];
        y=b[y][v];
    }
    void operator =(FSM &c)
    {
        memcpy(a,c.a,sizeof(a));
        memcpy(b,c.b,sizeof(b));
    }
}g[N],o;
int id(int x,int y,int k)
{
    if(!g[x].b[y][k]) return 1;
    if(!g[x].jp[y][k]) return (x-1)*n+g[x].b[y][k];
    else return (g[x].jp[y][k]-1)*n+g[x].b[y][k];
}
int f[N][3],a[N];
char op[3];
int vis[N][N][N];
int main()
{
    // freopen("epic.in","r",stdin);
    // freopen("epic.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%d%d%d",op,&f[i][0],&f[i][1],&f[i][2]);
        a[i]=(op[0]=='R'?0:(op[0]=='P'?1:2));
    }
    for(int i=1;i<=n;i++) o.b[i][a[i]]=f[i][o.a[i]=(a[i]+1)%3];
    int m=1;
    g[1]=o;
    for(int i=2;i<=n;i++)
    {
        int u=i,x=1,y=1;
        while(vis[u][x][y]!=i)
        {
            vis[u][x][y]=i;
            if(!g[x].b[y][a[u]])
            {
                g[++m]=o;
                g[x].jp[y][a[u]]=m;
                g[x].b[y][a[u]]=f[u][g[x].a[y]];
                break;
            }
            int v=u;
            u=f[u][g[x].a[y]];
            g[x].nxt(x,y,a[v]);
        }
    }
    printf("%d\n",n*m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            putchar(g[i].a[j]==0?'R':(g[i].a[j]==1?'P':'S'));
            for(int k=0;k<=2;k++) printf(" %d",id(i,j,k));
            puts("");
        }
    return 0;
}