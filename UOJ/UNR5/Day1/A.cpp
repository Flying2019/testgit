#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define mod 998244353
using namespace std;
const int N=5010;
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
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
vector<int>g[N];
int cr,cb,n;
int ton[N],tt;char opt[6];
namespace c1{
    const int N=251;
    int f0[N][N][N],f1[N][N][N],f2[N][N][N],h[N][N][N],w0[N][N][N],w1[N][N][N],dis[N];
    void dfs(int u)
    {
        for(int j=1;j<=cr;j++)
            for(int k=1;k<=cb;k++) f0[u][j][k]=1;
        for(int v:g[u])
        {
            dfs(v);
            for(int j=1;j<=cr;j++)
                for(int k=1;k<=cb;k++)
                {
                    int &uf1=f1[u][j][k],&uf2=f2[u][j][k],&uf0=f0[u][j][k],&uh=h[u][j][k],&uw0=w0[u][j][k],&uw1=w1[u][j][k];
                    int &vf1=f1[v][j][k],&vf2=f2[v][j][k],&vf0=f0[v][j][k],&vh=h[v][j][k],&vw0=w0[v][j][k],&vw1=w1[v][j][k];
                    uw1=(1ll*uw1*vf0%mod+1ll*uf0*vw1%mod+1ll*uf1*vw0%mod+1ll*uw0*vf1%mod+2ll*uh*vf2%mod+2ll*vh*uf2%mod)%mod;
                    uw0=(1ll*uw0*vf0%mod+2ll*uf2*vf2+1ll*uf0*vw0)%mod;
                    uh=(1ll*uh*vf0%mod+1ll*uf0*vh%mod+1ll*uf1*vf2%mod+1ll*uf2*vf1%mod)%mod;
                    uf1=(1ll*uf1*vf0+1ll*uf0*vf1)%mod;
                    uf2=(1ll*uf2*vf0+1ll*uf0*vf2)%mod;
                    uf0=1ll*uf0*vf0%mod;
                }
        }
        if(u==0) return;
        for(int j=cr;j;j--)
            for(int k=cb;k;k--)
            {
                int &tf1=f1[u][j][k],&tf2=f2[u][j][k],&tf0=f0[u][j][k],&th=h[u][j][k],&tw0=w0[u][j][k],&tw1=w1[u][j][k];
                int &uf1=f1[u][j-1][k],&uf2=f2[u][j-1][k],&uf0=f0[u][j-1][k],&uh=h[u][j-1][k],&uw0=w0[u][j-1][k],&uw1=w1[u][j-1][k];
                int &vf1=f1[u][j][k-1],&vf2=f2[u][j][k-1],&vf0=f0[u][j][k-1],&vh=h[u][j][k-1],&vw0=w0[u][j][k-1],&vw1=w1[u][j][k-1];
                tf1=tf2=tf0=th=tw0=tw1=0;
                tf0=(tf0+uf0)%mod;
                tf1=(tf1+uf1+1ll*uf0)%mod;
                tf2=(tf2+uf2)%mod;
                th=(th+uh+1ll*uf2)%mod;
                tw0=(tw0+uw0)%mod;
                tw1=(tw1+uw1+1ll*uw0)%mod;
                tf0=(tf0+vf0)%mod;
                tf1=(tf1+vf1)%mod;
                tf2=(tf2+vf2+1ll*vf0)%mod;
                th=(th+vh+1ll*vf1)%mod;
                tw0=(tw0+vw0+2ll*vf2+vf0)%mod;
                tw1=(tw1+vw1+2ll*vh+vf1)%mod;
            }
        // printf("\n%d\n",u);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",f0[u][j][k]);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",h[u][j][k]);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",w0[u][j][k]);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",w1[u][j][k]);
    }
    void solve()
    {
        ++cr;++cb;
        dfs(0);
        printf("%d\n",w1[0][cr][cb]);
    }
}
namespace c2{
    const int N=2501;
    int f0[N][3][N],f1[N][3][N],f2[N][3][N],h[N][3][N],w0[N][3][N],w1[N][3][N],dis[N];
    void dfs(int u)
    {
        for(int j=1;j<=cr;j++)
            for(int k=1;k<=cb;k++) f0[u][j][k]=1;
        for(int v:g[u])
        {
            dfs(v);
            for(int j=1;j<=cr;j++)
                for(int k=1;k<=cb;k++)
                {
                    int &uf1=f1[u][j][k],&uf2=f2[u][j][k],&uf0=f0[u][j][k],&uh=h[u][j][k],&uw0=w0[u][j][k],&uw1=w1[u][j][k];
                    int &vf1=f1[v][j][k],&vf2=f2[v][j][k],&vf0=f0[v][j][k],&vh=h[v][j][k],&vw0=w0[v][j][k],&vw1=w1[v][j][k];
                    uw1=(1ll*uw1*vf0%mod+1ll*uf0*vw1%mod+1ll*uf1*vw0%mod+1ll*uw0*vf1%mod+2ll*uh*vf2%mod+2ll*vh*uf2%mod)%mod;
                    uw0=(1ll*uw0*vf0%mod+2ll*uf2*vf2+1ll*uf0*vw0)%mod;
                    uh=(1ll*uh*vf0%mod+1ll*uf0*vh%mod+1ll*uf1*vf2%mod+1ll*uf2*vf1%mod)%mod;
                    uf1=(1ll*uf1*vf0+1ll*uf0*vf1)%mod;
                    uf2=(1ll*uf2*vf0+1ll*uf0*vf2)%mod;
                    uf0=1ll*uf0*vf0%mod;
                }
        }
        if(u==0) return;
        for(int j=cr;j;j--)
            for(int k=cb;k;k--)
            {
                int &tf1=f1[u][j][k],&tf2=f2[u][j][k],&tf0=f0[u][j][k],&th=h[u][j][k],&tw0=w0[u][j][k],&tw1=w1[u][j][k];
                int &uf1=f1[u][j-1][k],&uf2=f2[u][j-1][k],&uf0=f0[u][j-1][k],&uh=h[u][j-1][k],&uw0=w0[u][j-1][k],&uw1=w1[u][j-1][k];
                int &vf1=f1[u][j][k-1],&vf2=f2[u][j][k-1],&vf0=f0[u][j][k-1],&vh=h[u][j][k-1],&vw0=w0[u][j][k-1],&vw1=w1[u][j][k-1];
                tf1=tf2=tf0=th=tw0=tw1=0;
                tf0=(tf0+uf0)%mod;
                tf1=(tf1+uf1+1ll*uf0)%mod;
                tf2=(tf2+uf2)%mod;
                th=(th+uh+1ll*uf2)%mod;
                tw0=(tw0+uw0)%mod;
                tw1=(tw1+uw1+1ll*uw0)%mod;
                tf0=(tf0+vf0)%mod;
                tf1=(tf1+vf1)%mod;
                tf2=(tf2+vf2+1ll*vf0)%mod;
                th=(th+vh+1ll*vf1)%mod;
                tw0=(tw0+vw0+2ll*vf2+vf0)%mod;
                tw1=(tw1+vw1+2ll*vh+vf1)%mod;
            }
        // printf("\n%d\n",u);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",f0[u][j][k]);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",h[u][j][k]);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",w0[u][j][k]);
        // for(int j=1;j<=cr;j++,puts(""))
        //     for(int k=1;k<=cb;k++) printf("%d ",w1[u][j][k]);
    }
    void solve()
    {
        ++cr;++cb;
        dfs(0);
        printf("%d\n",w1[0][cr][cb]);
    }
}
int main()
{
    scanf("%d%d%d",&n,&cr,&cb);
    init();
    for(int i=1,t=0;i<=2*n;i++)
    {
        scanf("%s",opt);
        if(opt[1]=='u')
        {
            ++t;
            g[ton[tt]].push_back(t);
            ton[++tt]=t;
        }
        else --tt;
    }
    if(cr<=1){c2::solve();return 0;}
    c1::solve();
    return 0;
}