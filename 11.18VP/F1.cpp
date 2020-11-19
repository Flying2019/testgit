#include<iostream>
#include<cstdio>
#include<cstring>
#define N 510
#define mod 998244353
using namespace std;
int f[N][N],n;
int a[N];
int F(int l,int r)
{
    if(l>=r) return 1;
    if(f[l][r]) return f[l][r];
    int mn=n+1,p=0;
    for(int i=l;i<=r;i++)
    if(a[i]<mn) mn=a[i],p=i;
    int s1=0,s2=0;
    for(int k=l;k<=p;k++) s1=(s1+1ll*F(l,k-1)*F(k,p-1)%mod)%mod;
    for(int k=p;k<=r;k++) s2=(s2+1ll*F(p+1,k)*F(k+1,r)%mod)%mod;
    return f[l][r]=1ll*s1*s2%mod;
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    printf("%d\n",F(1,n));
    return 0;
}