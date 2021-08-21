#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 40010
#define M 10
using namespace std;
int a[N][M],F[2][M][1<<M];
vector<int>v[1<<M];
char s[M+2];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
        for(int j=0;j<m;j++)
        {
            scanf("%s",s);
            for(int k=0;k<m;k++) a[i][j]|=(s[k]-'0')<<k;
        }
    for(int i=0;i<m;i++)
        for(int j=0;j<1<<m;j++) if(j>>i&1) v[j].push_back(i);
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        auto &f=F[i%2],&g=F[(i+1)%2];
        memset(f,0,sizeof(f));
        for(int s=0;s<1<<m;s++)
        {
            int t=0;
            for(int j=0;j<m;j++) if(s>>j&1) t|=a[i-1][j];
            for(int j=0;j<m;j++) f[j][t]=max(f[j][t],g[j][s]);
        }
        f[0][(1<<m)-1]=i;
        for(int j=0;j<m-1;j++)
            for(int s=0;s<1<<m;s++)
            {
                f[j+1][s]=max(f[j+1][s],f[j][s]);
                for(int p:v[s]) if(s>>p&1) f[j+1][s^(1<<p)]=max(f[j+1][s^(1<<p)],f[j][s]);
            }
        f[m][0]=i;
        for(int j=1;j<=m;j++) ans+=j*(min(i-1,f[j][0])-min(i-1,f[j-1][0]));
    }
    printf("%lld\n",ans);
    return 0;
}