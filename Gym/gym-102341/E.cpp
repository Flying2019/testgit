#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 100010
#define mod 1000000007
#define M 310
using namespace std;
int fac[N],inv[N];
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
void init()
{
    const int n=N-10;
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int a[M][M],p[M][M],f[M];
vector<int>nxt[M];
int s[M][M],vl[M][M],id[M],k,n;
int calc(int r,int x,int y)
{
    vl[x][y]=vl[x][y]+p[y][r]-p[x][r]-1;
    s[x][y]=1ll*s[x][y]*C(vl[x][y],p[y][r]-p[x][r]-1)%mod;
    return s[x][y];
}
void init(int l)
{
    for(int x=0;x<=n;x++) nxt[x].clear();
    for(int i=1;i<=n;i++) id[i]=i;
    sort(id+1,id+n+1,[&](int x,int y){return p[x][l]>p[y][l];});
    for(int i=0;i<=n;i++)
        for(int j=1;j<=n+1;j++) s[i][j]=1,vl[i][j]=0;
    for(int x=0;x<=n;x++)
        for(int y=1;y<=n;y++)
        if(p[x][l]<p[y][l]) nxt[x].push_back(y),calc(l,x,y);
    for(int x=0;x<=n;x++) calc(l,x,n+1);
}
int main()
{
    int ans=0;
    scanf("%d%d",&k,&n);
    init();
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=n;j++) scanf("%d",&a[i][j]),p[a[i][j]][i]=j;
        p[a[i][n+1]=n+1][i]=n+1;
    }
    for(int l=1;l<k;l++)
    {
        init(l);
        for(int r=l+1;r<=k;r++)
        {
            for(int i=1;i<=n+1;i++)
            {
                int u=id[i];
                f[u]=calc(r,u,n+1);
                vector<int>tmp;
                for(int v:nxt[u])
                if(p[u][r]<p[v][r]) f[u]=(f[u]-1ll*calc(r,u,v)*f[v]%mod*fac[r-l+1]%mod+mod)%mod,tmp.push_back(v);
                nxt[u]=tmp;
            }
            ans=(ans+f[0])%mod;
        }
    }
    printf("%d\n",ans);
    return 0;
}