#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define ll long long
#define mod 998244353
#define _18 (1000000000000000000ll%mod)
using namespace std;
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
#define N 100010
struct graph{
    int nxt[N<<1],to[N<<1],head[N],cnt;
    set<int>s;
    void add(int u,int v)
    {
        nxt[++cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt;
    }
    int g[N],c[N],gt;
    void work(int n)
    {
        int m;
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            if(u>v) swap(u,v);
            add(u,v);
        }
        for(int u=n;u>=1;u--)
        {
            s.clear();
            for(int i=head[u];i;i=nxt[i])
            {
                int v=to[i];
                s.insert(g[v]);
            }
            while(s.count(g[u])) g[u]++;
        }
        for(int i=1;i<=n;i++) gt=max(gt,g[i]),c[g[i]]=(c[g[i]]+ksm(_18,i))%mod;
    }
}f[3];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<=2;i++) f[i].work(n);
    int ans=0;
    for(int i=0;i<=f[0].gt;i++)
    if(f[0].c[i])
        for(int j=0;j<=f[1].gt;j++)
        if(f[1].c[j]) ans=(ans+1ll*f[0].c[i]*f[1].c[j]%mod*f[2].c[i^j]%mod)%mod;
    printf("%d",ans);
    return 0;
}