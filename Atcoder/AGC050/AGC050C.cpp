#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define S 20
#define mod 998244353
using namespace std;
char s[N];
int f[N][S+2];
int g[N];
bool check(int x,int p){return x<=(1<<p)?g[x]==0:g[x]==g[x-(1<<p)];}
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
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=1;i<=n;i++) g[i]=g[i-1]+(s[i]=='B');
    f[n][0]=1;
    for(int i=n;i;i--)
        for(int j=0;j<=S;j++)
        if(f[i][j])
        {
            if(s[i]!='S' && check(i-1,j)) (f[max(i-(1<<j)-1,0)][j+1]+=f[i][j])%=mod;
            if(s[i]!='B') f[i-1][j]=(f[i-1][j]+f[i][j])%mod;
        }
    int ans=1;
    for(int i=1;i<=n;i++)
    if(s[i]=='?') ans=2ll*ans%mod;
    for(int j=0;j<=S;j++) ans=(ans-f[0][j]+mod)%mod;
    printf("%d\n",ans);
    return 0;
}