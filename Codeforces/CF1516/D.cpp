#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int a[N],r[N];
int rt[N],f[N][21],_2[N];
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=N-10;i++) rt[i]=n+1;
    r[n+1]=n+1;
    for(int i=n;i>=1;i--)
    {
        r[i]=n+1;
        int u=a[i];
        for(int j=2;1ll*j*j<=u;j++)
        if(u%j==0)
        {
            r[i]=min(r[i],rt[j]);
            while(u%j==0) u/=j;
            rt[j]=i;
        }
        if(u>1)
        {
            r[i]=min(r[i],rt[u]);
            rt[u]=i;
        }
        r[i]=min(r[i],r[i+1]);
    }
    for(int i=2;i<=n+1;i++) _2[i]=_2[i>>1]+1;
    int m=_2[n+1];
    for(int i=1;i<=n+1;i++) f[i][0]=r[i];
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n+1;j++)
        f[j][i]=f[f[j][i-1]][i-1];
    while(q --> 0)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int t=0;
        for(int i=m;i>=0;i--)
        if(f[l][i]<=r) l=f[l][i],t+=1<<i;
        if(l<=r) t++;
        printf("%d\n",t);
    }
    return 0;
}