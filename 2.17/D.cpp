#include<iostream>
#include<cstdio>
#include<cstring>
#define N 110
#define M 16
#define db long double
#define ll long long
#define S (1<<M)
using namespace std;
int sum[S],a[M];
db C[N][N],f[N][1<<M],g[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&a[i]),sum[1<<i]=a[i];
    int t=1<<n;
    for(int i=1;i<t;i++)
    if(!sum[i]) for(int j=0;j<n;j++) if((i>>j)&1){sum[i]=sum[1<<j]+sum[i^(1<<j)];break;}
    for(int i=0;i<=m;i++)
        for(int j=C[i][0]=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    f[0][0]=1;
    for(int i=1;i<=m;i++)
        for(int s=0;s<t;s++)
        if(sum[s]<i)
        {
            db v=f[i-1][s]/(n-__builtin_popcount(s));
            f[i][s]+=v;
            for(int j=0;j<n;j++)
            if(!((s>>j)&1) && sum[s^(1<<j)]<=i) f[i][s^(1<<j)]+=C[i-1-sum[s]][a[j]-1]*v;
        }
    double ans=0;
    for(int s=0;s<t;s++)
    if(sum[s]<=m)
    {
        int r=m-sum[s];
        for(int i=0;i<r;i++) g[i]=0;g[r]=1;
        for(int i=0;i<n;i++)
        if(!((s>>i)&1))
            for(int j=1;j<=r;j++)
                for(int k=1;k<=min(j,a[i]-1);k++) g[j-k]+=g[j]*C[j][k];
        ans+=g[0]*f[m][s]*__builtin_popcount(s);
    }
    printf("%.8lf",ans);
    return 0;
}