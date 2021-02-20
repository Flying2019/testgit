#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define N 60
#define inf 1000000000
using namespace std;
int n;
struct matrix{
    bool a[N][N];
    matrix(int c=0){memset(a,0,sizeof(a));for(int i=1;i<=n;i++) a[i][i]=c;}
    bool* operator [](int b){return a[b];}
    friend matrix operator *(matrix a,matrix b)
    {
        matrix c;
        for(int i=1;i<=n;i++)
            for(int k=1;k<=n;k++)
                for(int j=1;j<=n;j++) c[i][j]|=a[i][k]&b[k][j];
        return c;
    }
    friend matrix operator |(matrix a,matrix b)
    {
        matrix c;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) c[i][j]=a[i][j]|b[i][j];
        return c;
    }
}r[33];
int g[N][N];
int main()
{
    int m,p,s,t;
    scanf("%d%d%d%d%d",&n,&m,&p,&s,&t);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        r[0][u][v]=true;
    }
    for(int i=1;i<p;i++) r[i]=r[i-1]*r[i-1];
    for(int i=1;i<p;i++) r[0]=r[0]|r[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(i==j) g[i][j]=0;
        else if(r[0][i][j]) g[i][j]=1;
        else g[i][j]=inf;
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    printf("%d\n",g[s][t]>=inf?-1:g[s][t]);
    return 0;
}