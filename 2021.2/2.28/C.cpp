#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
#define M 61
#define ll long long
using namespace std;
ll C[M][M],g[M];
int a[M],c[N],f[N];
int main()
{
    int n,t=0,k,l,r;
    scanf("%d%d%d%d",&n,&k,&l,&r);
    int m=0;
    C[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=C[i][0]=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=min(i,k);j++) g[i]+=C[i][j];
    for(int i=1;i<=n;i++)
    {
        int w=0;
        scanf("%d",&w);
        if((w&l)!=l || (w|r)!=r) continue;
        a[++t]=w,m=max(m,w);
    }
    if(t==0){puts("0");return 0;}
    int S=1;while(S<=m) S<<=1;
    ll ans=0;
    c[0]=1;
    for(int s=1;s<S;s++) c[s]=-c[s-(s&(-s))];
    for(int s=0;s<S;s++)
    if((s&l)==l && (s|r)==r)
    {
        ll res=0;
        for(int i=1;i<=t;i++) f[a[i]&s]++;
        for(int i=1;i<=t;i++) if(f[a[i]&s]) res+=g[f[a[i]&s]],f[a[i]&s]=0;
        ans+=c[s^l]*res;
    }
    printf("%lld",ans);
    return 0;
}