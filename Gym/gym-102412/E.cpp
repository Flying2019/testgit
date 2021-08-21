#include<iostream>
#include<cstdio>
#include<cstring>
#define N 18
#define M 101
using namespace std;
int g[N][1<<N];//the number of roads from u to S
int sg[1<<N];//the number of roads inside S
int f[1<<N][M],h[1<<N][M];
inline void chkmax(int &x,int &px,int y,int w){if(x<y) x=y,px=w;}
int a[N];
int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        --u;--v;
        g[u][1<<v]++;g[v][1<<u]++;
    }
    int S=1<<n;
    for(int u=0;u<n;u++)
        for(int s=1;s<S;s++) g[u][s]=g[u][s&(-s)]+g[u][s-(s&(-s))];
    for(int s=1;s<S;s++)
    {
        for(int i=0;i<n;i++) if(s>>i&1) sg[s]+=g[i][s];
        sg[s]/=2;
    }
    memset(f,0xcf,sizeof(f));
    f[0][k]=0;
    for(int s=0;s<S;s++)
        for(int p=k;p>=0;p--)
        {
            int t=__builtin_popcount(s);
            if(p>=n-t) chkmax(f[s][p-(n-t)],h[s][p-(n-t)],f[s][p]+sg[(S-1)^s],s);
            for(int i=0;i<n;i++)
            if(!(s>>i&1)) chkmax(f[s|(1<<i)][p],h[s|(1<<i)][p],f[s][p],s);
        }
    int s=S-1,p=0;
    while(p<k)
    {
        int t=h[s][p];
        if(t!=s){s=t;continue;}
        for(int i=0;i<n;i++)
        if(!(s>>i&1)) a[i]++,p++;
    }
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    return 0;
}