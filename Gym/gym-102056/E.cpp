#include<iostream>
#include<cstdio>
#include<cstring>
#define N 10010
#define mod 998244353
using namespace std;
int h[2][N];
void solve(char s[],int f[][N],int n)
{
    f[0][n]=1;
    for(int i=1;i<=n;i++)
    {
        char c=s[n-i+1];
        memcpy(h,f,sizeof(h));memset(f,0,sizeof(h));
        for(int j=0;j<=2*n;j++)
        {
            if(c!='P') f[0][j+1]=(f[0][j+1]+h[0][j])%mod,f[1][j+1]=(f[1][j+1]+h[1][j])%mod;
            if(j && c!='V')
            {
                f[1][min(n,j-1)]=(f[1][min(n,j-1)]+h[1][j])%mod;
                if(j<=n) f[0][j-1]=(f[0][j-1]+h[0][j])%mod;
                else f[1][n]=(f[1][n]+h[0][j])%mod;
            }
        }
    }
}
int f[2][N],g[2][N];
char s1[N],s2[N];
int main()
{
    int n,m;
    scanf("%s%s",s1+1,s2+1);
    n=strlen(s1+1),m=strlen(s2+1);
    solve(s1,f,n);solve(s2,g,m);
    int ans=0;
    for(int i=0;i<=2*n;i++)
        for(int j=0;j<=2*m;j++)
        if(i-n+j-m>0) ans=(ans+1ll*(f[0][i]+f[1][i])*(g[0][j]+g[1][j]))%mod;
        else if(i-n+j-m==0) ans=(ans+1ll*f[0][i]*g[0][j])%mod;
    printf("%d\n",ans);
    return 0;
}