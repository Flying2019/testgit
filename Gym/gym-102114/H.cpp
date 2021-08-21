#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define M 11
using namespace std;
int f[N][M],g[N][M],hi[M],hx[M];
char s[N];int a[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;scanf("%d%s",&n,s+1);
        for(int i=1;i<=n;i++) a[i]=s[i]-'0';
        for(int i=1;i<=n;i++)
        {
            memcpy(f[i],f[i-1],sizeof(f[i]));
            f[i][a[i]]++;
            for(int j=a[i]+1;j<10;j++) f[i][j]=max(f[i][j],f[i][j-1]);
        }
        memset(g[n+1],0,sizeof(g[n+1]));
        for(int i=n;i;i--)
        {
            memcpy(g[i],g[i+1],sizeof(g[i]));
            g[i][a[i]]++;
            for(int j=a[i]-1;j>=0;j--) g[i][j]=max(g[i][j],g[i][j+1]);
        }
        int al=1,ar=1,ans=f[n][9];
        for(int l=0;l<10;l++)
            for(int r=l;r<10;r++)
            {
                memset(hx,-1,sizeof(hx));
                memset(hi,-1,sizeof(hi));
                for(int i=1;i<=n;i++)
                if(a[i]>=l && a[i]<=r)
                {
                    if(hx[a[i]]<=f[i-1][l]) hx[a[i]]=f[i-1][l],hi[a[i]]=i;
                    hx[a[i]]++;
                    for(int k=a[i]-1;k>=l;k--)
                    if(hx[k+1]>hx[k]) hx[k]=hx[k+1],hi[k]=hi[k+1];
                    if(hx[l]+g[i+1][r]>ans)
                        ans=hx[l]+g[i+1][r],al=hi[l],ar=i;
                }
            }
        printf("%d %d %d\n",ans,al,ar);
    }
    return 0;
}