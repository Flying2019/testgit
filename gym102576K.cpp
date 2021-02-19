#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310
#define S (1<<12)
#define mod 1000000007
using namespace std;
int fac[N],inv[N],_2[N];
int f[2][S][N];
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-10)
{
    fac[0]=_2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod,_2[i]=_2[i-1]*2%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
char s[N];
bool mp[N][N];
void clear(){memset(f,0,sizeof(f));}
void work()
{
    int n,m,k,tt=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<n;i++)
    {
        scanf("%s",s);
        for(int j=0;j<m;j++) mp[i][j]=s[j]=='.',tt+=mp[i][j];
    }
    if(n<m)
    {
        for(int i=0;i<m;i++)
            for(int j=0;j<i;j++) swap(mp[i][j],mp[j][i]);
        swap(n,m);
    }
    int u=1,p=0;
    f[p][0][0]=1;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++,p=!p,u=!u,memset(f[u],0,sizeof(f[u])))
            for(int s=0;s<1<<m;s++)
                for(int d=0;d<=k;d++)
                {
                    int &r=f[u][s][d];
                    r=(r+f[p][s&~(1<<j)][d])%mod;
                    if(!d || !mp[i][j]) continue;
                    if(j && mp[i][j-1] && !((s>>(j-1))&3)) r=(r+f[p][s|(1<<(j-1))][d-1])%mod;
                    if(i && mp[i-1][j] && !((s>>j)&1)) r=(r+f[p][s|(1<<j)][d-1])%mod;
                }
    int ans=0;
    for(int d=0;d<=k;d++)
    {
        int res=1ll*_2[d]*f[p][0][d]%mod*fac[k]%mod*inv[k-d]%mod;
        ans=(ans+(d&1?-1ll:1ll)*res*fac[tt-2*d]%mod*inv[tt-2*k]%mod+mod)%mod;
    }
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    init();
    while(t --> 0) work(),clear();
    return 0;
}