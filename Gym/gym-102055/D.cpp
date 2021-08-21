#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 100010
#define mod 1000000007
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int f[N],g[N],e[N],p[N],q[N],D[N],d[N],w[N];
int inv[N];
void add(int u,int v){D[u]++;nxt[++cnt]=head[u];to[cnt]=v;head[u]=cnt;}
void dfs(int u,int fa)
{
    bool lev=true;
    int S=0,Se=0,P=0;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa) continue;
        lev=false;dfs(v,u);
        S=(S+f[v])%mod;
        Se=(Se+e[v])%mod;
        P=(P+p[v])%mod;
    }
    if(lev){f[u]=g[u]=w[u];return;}
    e[u]=1ll*Se*inv[D[u]]%mod;
    f[u]=1ll*Se*inv[d[u]]%mod;
    g[u]=1ll*S*inv[d[u]]%mod;
    p[u]=1ll*P*inv[D[u]]%mod;
    int dq=1ll*inv[d[u]]*inv[d[u]]%mod,dq2=1ll*inv[d[u]]*inv[d[u]-1]%mod;
    int Dq=1ll*inv[D[u]]*inv[D[u]]%mod,Dq2=1ll*inv[D[u]]*inv[d[u]]%mod;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa) continue;
        f[u]=(f[u]+1ll*(S-f[v]+g[v])*inv[D[v]]%mod*dq%mod+1ll*q[v]*(S-f[v])%mod*dq2%mod+2ll*mod)%mod;
        if(dq2==0) f[u]=(f[u]+1ll*q[v]*w[u])%mod;
        e[u]=(e[u]+1ll*(S-f[v]+g[v])*inv[D[v]]%mod*Dq%mod+1ll*q[v]*(S-f[v])%mod*Dq2%mod+2ll*mod)%mod;
        p[u]=(p[u]+1ll*d[u]*inv[D[v]]%mod*Dq%mod+1ll*q[v]*(d[u]-1)%mod*Dq2%mod)%mod;
    }
    q[u]=(1-(p[u]+inv[D[u]])%mod+mod)%mod;
}
int main()
{
    int t;
    scanf("%d",&t);
    inv[1]=1;
    for(int i=2;i<=N-10;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    for(int _=1;_<=t;_++)
    {
        int n,rt;scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&w[i]);
        for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
        scanf("%d",&rt);
        for(int i=1;i<=n;i++) d[i]=i==rt?D[i]:D[i]-1;
        dfs(rt,0);
        printf("Case %d: ",_);
        printf("%d\n",(f[rt]+mod)%mod);
        for(int i=1;i<=n;i++) f[i]=g[i]=e[i]=p[i]=q[i]=D[i]=d[i]=w[i]=head[i]=0;
        cnt=0;
    }
    return 0;
}