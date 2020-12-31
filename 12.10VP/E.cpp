#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 50
using namespace std;
ll f[N][N][N],g[N][N][N],ans;
char s[N][N];
int main()
{
    int n;
    scanf("%d",&n);n*=2;
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++)
    {
        f[i][i][i]=1;
        for(int j=1;j<=n;j++) g[i][i][j]=s[i][j]-'0';
    }
    for(int c=3;c<n;c+=2)
        for(int i=1;i<=n-c;i++)
        {
            int p=c+i-1;
            for(int l=i;l<=p;l+=2)
                for(int r=p;r>l;r-=2)
                {
                    ll s=0;
                    for(int j=r;j<=p;j++) s+=g[i][l][j]*f[r][p][j];
                    for(int j=l+1;j<r;j++) f[i][p][j]+=f[l+1][r-1][j]*s;
                }
            for(int l=i+1;l<p;l++)
                for(int r=p+1;r<=n;r++)
                if(s[l][r]=='1') g[i][p][r]+=f[i][p][l];
        }
    for(int i=1;i<n;i++)
    if(s[i][n]=='1') ans+=f[1][n-1][i];
    printf("%lld\n",ans);
    return 0;
}