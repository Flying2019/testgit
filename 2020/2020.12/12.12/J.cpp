#include<iostream>
#include<cstdio>
#include<cstring>
#define N 510
#define mod 998244353
using namespace std;
int n,k;
int l,f[N][10];
int a[17];
int work(int s)
{
    for(int i=0;i<l;i++) a[i]=(s>>i)&1;
    for(int i=0;i<=l-k;i++)
    {
        int w=0;
        for(int j=0;j<k;j++) w=w*2+a[i+j];
        if(!a[w]) return 0;
    }
    s=0;
    for(int i=l-k+1;i<l;i++) s=s*2+a[i];
    int m=(1<<(k-1))-1;
    memset(f,0,sizeof(f));
    f[l][s]=1;
    // if((s>>(l-k+1))>m) throw;
    for(int i=l+1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        if(f[i-1][j])
            for(int p=0;p<=1;p++)
            {
                int t=j<<1|p;
                if(!a[t]) continue;
                f[i][t&m]=(f[i][t&m]+f[i-1][j])%mod;
            }
    }
    int ans=0;
    for(int i=0;i<=m;i++) ans=(ans+f[n][i])%mod;
    return ans;
}
int main()
{
    scanf("%d%d",&n,&k);l=1<<k;
    int ans=0;
    for(int s=0;s<1<<l;s++)
    // if(work(s)) printf("%d\n",s);
    ans=(ans+work(s))%mod;
    printf("%d\n",ans);
    return 0;
}