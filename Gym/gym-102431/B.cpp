#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
#define N 4010
#define mod 1000000007
using namespace std;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
vector<int> g[N][10],rg[N];
bool go[N];
void dfs(int u)
{
    if(go[u]) return;go[u]=true;
    for(int v:rg[u]) dfs(v);
}
int iv10=ksm(10);
vector<int>f;
int dis[N*2],res[N*2],tt,n;
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        f.clear();tt=0;
        int m;scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            dis[i]=res[i]=go[i]=0;rg[i].clear();
            for(int j=0;j<10;j++) g[i][j].clear();
        }
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);++u;++v;
            g[u][w].push_back(v);rg[v].push_back(u);
        }
        dfs(2);f.push_back(1);
        while(tt<=n*4)
        {
            auto h=f;f.clear();
            int w=0;
            for(;w<10;w++)
            {
                bool hv=false;
                for(int u:h)
                {
                    for(int v:g[u][w])
                    if(go[v]) f.push_back(v),hv=true;
                }
                if(hv) break;
            }
            ++tt;
            for(int u:h) dis[u]=tt;
            res[tt]=(res[tt-1]*10ll+w)%mod;
            sort(f.begin(),f.end());
            f.erase(unique(f.begin(),f.end()),f.end());
            if(find(f.begin(),f.end(),2)!=f.end()) break;
        }
        printf("Case #%d: ",_);
        if(find(f.begin(),f.end(),2)!=f.end()){printf("%lld\n",1ll*res[tt]*ksm(iv10,tt)%mod);continue;}
        int r=1;
        for(;r<=n;r++)
        {
            bool can=true;
            for(int i=n*3;i<n*4;i++) if((res[i]-1ll*res[i-r]*ksm(10,r)%mod+mod)%mod!=(res[i-r]-1ll*res[i-r*2]*ksm(10,r)%mod+mod)%mod){can=false;break;}
            if(can) break;
        }
        int k=tt-r,w=(res[k]+(res[tt]-1ll*res[k]*ksm(10,r)%mod+mod)%mod*ksm(ksm(10,r)-1))%mod;
        printf("%d\n",1ll*w*ksm(iv10,k)%mod);
    }
    return 0;
}