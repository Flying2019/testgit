#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
int suf[N][N];//lcs
int p[N][N],s[N];//p[i][j] : s[i-j:i] 在 s[:i-j] 中尾字母最后一次出现的位置
ll f[N][N];
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        int n;ll x,y,z;scanf("%d%lld%lld%lld",&n,&x,&y,&z);
        for(int i=1;i<=n;i++) scanf("%d",&s[i]);
        for(int i=1;i<=n;i++)
            for(int j=0;j<=n;j++) suf[i][j]=p[i][j]=0,f[i][j]=inf;
        for(int i=1;i<=n;i++)
        {
            suf[i][i]=i;
            for(int j=1;j<i;j++) suf[i][j]=s[i]==s[j]?suf[i-1][j-1]+1:0;
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<i;j++) p[i][min(i-j,suf[i][j])]=j;
            for(int j=i-1;j;j--) p[i][j]=max(p[i][j],p[i][j+1]);
        }
        for(int i=1;i<=n;i++)
        {
            f[i][0]=f[i-1][0]+x;
            for(int j=1;j<=i;j++)
            if(p[i][j]) f[i][j]=min(f[i-j][0]+y+z,f[p[i][j]][j]+(i-(j+p[i][j]))*x+z),f[i][0]=min(f[i][0],f[i][j]);
        }
        printf("Case #%d: ",_);
        printf("%lld\n",f[n][0]);
    }
    return 0;
}