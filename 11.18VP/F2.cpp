#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define M 1010
#define mod 998244353
#pragma GCC optimize (2)
using namespace std;
int f[M][M];
int a[N],m,l[N],r[N];
int F(int l,int r)
{
    if(f[l][r]!=-1) return f[l][r];
    f[l][r]=0;
    if(l>r) return f[l][r]=1;
    int mn=m+1,p=0,lf=r,rf=l;
    for(int i=l;i<=r;i++)
    if(a[i]<mn) mn=a[i];
    if(::l[mn]<l || ::r[mn]>r) return f[l][r]=0;
    if(l==r) return f[l][r]=1;
    lf=::l[mn],rf=::r[mn];
    int s1=0,s2=0;
    for(int k=l;k<=lf;k++) s1=(s1+1ll*F(l,k-1)*F(k,lf-1)%mod)%mod;
    for(int k=rf;k<=r;k++) s2=(s2+1ll*F(rf+1,k)*F(k+1,r)%mod)%mod;
    int &u=f[l][r];
    u=1ll*s1*s2%mod;
    p=lf;
    for(int i=lf+1;i<=rf;i++)
    if(a[i]==mn) u=1ll*u*F(p+1,i-1)%mod,p=i;
    return u;
}
int main()
{
    memset(f,-1,sizeof(f));
    int n;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int p=1;
    for(int i=2;i<=n;i++)
    if(a[i]!=a[i-1]) a[++p]=a[i];
    n=p;
    for(int i=1;i<=m;i++) l[i]=n+1,r[i]=0;
    for(int i=1;i<=n;i++) l[a[i]]=min(l[a[i]],i),r[a[i]]=max(r[a[i]],i);
    for(int i=2;i<=m;i++)
        for(int j=1;j<i;j++)
        if((l[i]<l[j] && r[i]>l[j]) || (l[i]>l[j] && r[i]>r[j] && l[i]<r[j]))
        {
            puts("0");
            return 0;
        }
    printf("%d\n",F(1,n));
    return 0;
}