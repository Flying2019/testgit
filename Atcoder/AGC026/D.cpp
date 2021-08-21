#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define mod 1000000007
using namespace std;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
int h[N],n;
int f[N*2][2],tt;
int solve(int l,int r,int lim)
{
    if(l>r) return 0;
    int mn=*min_element(h+l,h+r+1),u=++tt;
    int p=l,c=0;f[u][0]=f[u][1]=1;
    for(int i=l;i<=r+1;i++)
    if(h[i]==mn || i>r)
    {
        int v=solve(p,i-1,mn);
        f[u][0]=1ll*f[u][0]*f[v][0]%mod,f[u][1]=1ll*f[u][1]*(f[v][0]+f[v][1])%mod;
        p=i+1;++c;
    }
    f[u][1]=(1ll*f[u][0]*(ksm(2,mn-lim)-2)%mod+1ll*f[u][1]*ksm(2,c-1)%mod+mod)%mod;
    f[u][0]=1ll*ksm(2,mn-lim)*f[u][0]%mod;
    return u;
}
int main()
{
    scanf("%d",&n);f[0][0]=1;
    for(int i=1;i<=n;i++) scanf("%d",&h[i]);
    int u=solve(1,n,0);
    printf("%d\n",f[u][1]);
    return 0;
}