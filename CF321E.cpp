#include<iostream>
#include<cstdio>
#include<cstring>
#define N 4010
using namespace std;
int a[N][N],s[N][N];
int read()
{
    int ch=0,x=0;
    for(ch=getchar();ch<'0' || ch>'9';ch=getchar());
    for(;ch>='0' && ch<='9';ch=getchar()) x=x*10+(ch-'0');
    return x;
}
double f[N];
int g[N];
int t,n;
double rao(){return rand()*1.0/RAND_MAX*1e-6;}
void work(double x)
{
    g[0]=0;
    for(int i=1;i<=n;i++)
    {
        f[i]=f[i-1]+x+rao(),g[i]=g[i-1]+1;
        for(int j=0;j<i-1;j++)
        if(f[j]+s[j+1][i]+x<f[i]) f[i]=f[j]+s[j+1][i]+x+rao(),g[i]=g[j]+1;
    }
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) a[i][j]=read();
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++) s[i][j]=s[i][j-1]+a[i][j];
    for(int i=n;i>=1;i--)
        for(int j=i;j<=n;j++) s[i][j]+=s[i+1][j];
    double l=-1e9,r=1e9;
    while(r-l>=1e-4)
    {
        double mid=(l+r)/2;
        work(mid);
        if(g[n]==m){printf("%.0f",f[n]-m*mid);return 0;}
        if(g[n]<=m) r=mid;
        else l=mid;
    }
    printf("%.0f",f[n]-g[n]*l);
    return 0;
}