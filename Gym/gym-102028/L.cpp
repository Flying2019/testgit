#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 200010
#define mod 1000000007
#define S(a) ((int)a.size())
using namespace std;
vector<int>g[N],gr[N];
bool cmp(int x,int y){return S(g[x])==S(g[y])?x<y:S(g[x])<S(g[y]);}
int ton[N];
int calc4(int n)//四元环
{
    for(int i=0;i<=n;i++) ton[i]=0;
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int u:g[i])
            for(int v:gr[u]) if(cmp(i,v)) ans+=ton[v],++ton[v];
        for(int u:g[i])
            for(int v:gr[u]) if(cmp(i,v)) ton[v]=0;
    }
    return ans%mod;
}
int extra(int x,int y,int z){return S(g[x])-2+S(g[y])-2+S(g[z])-1;}
/*
o---o===o
|       |   <-  This is acceptable
+-------+
*/
int calc3(int n)//三元环
{
    for(int i=0;i<=n;i++) ton[i]=0;
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int u:gr[i]) ton[u]=true;
        for(int u:gr[i])
            for(int v:gr[u]) if(ton[v]) ans+=extra(i,u,v);
        for(int u:gr[i]) ton[u]=false;
    }
    return ans%mod;
}
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
int C(int a,int b){return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);g[v].push_back(u);
        }
        for(int i=1;i<=n;i++)
            for(int v:g[i]) if(cmp(i,v)) gr[i].push_back(v);
        int w3=calc3(n),w4=calc4(n);
        int ans=0;
        for(int i=1;i<=n;i++) ans=(ans+C(S(g[i]),4))%mod;//菊花
        for(int i=1;i<=n;i++)
            for(int u:g[i]) ans=(ans+1ll*C(S(g[i])-1,2)*(S(g[u])-1))%mod;
        for(int i=1;i<=n;i++)
        {
            int s=0;
            for(int u:g[i]) ans=(ans+1ll*s*(S(g[u])-1))%mod,s+=S(g[u])-1;
        }
        ans=(ans-3ll*(w3+w4)%mod+mod)%mod;
        printf("%d\n",ans);
        for(int i=1;i<=n;i++) g[i].clear(),gr[i].clear();
    }
    return 0;
}