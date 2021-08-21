#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1100010
#define inf 1000000000
#define ll long long
using namespace std;
int a[N],b[N],f[N],g[N],c[22],x;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int mx=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),mx=max(mx,a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]),mx=max(mx,b[i]);
    int S=1,t=0;
    while(S<=mx) S<<=1,t++;S--;
    for(int i=1;i<=n;i++) f[S^a[i]]++;
    for(int i=1;i<=m;i++) g[S^b[i]]++;
    for(int i=0;i<t;i++)
        for(int s=0;s<=S;s++) if((s>>i)&1) f[s^(1<<i)]+=f[s],g[s^(1<<i)]+=g[s];
    ll ans=0;
    for(int i=t-1;i>=0;i--)
    {
        c[i]=inf;
        for(int s=1<<i;s<=S;s+=2<<i)
        {
            int rf=n-f[s],rg=m-g[s];
            for(int j=i+1;j<t;j++) if((s>>j)&1) rf-=c[j],rg-=c[j];
            c[i]=min(c[i],min(rf,rg));
        }
        ans+=(ll)c[i]<<i;
    }
    printf("%lld\n",ans);
    return 0;
}