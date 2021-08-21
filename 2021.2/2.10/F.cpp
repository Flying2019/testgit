#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<set>
#define N 1000010
#define mod 998244353
#define ll long long
#define P pair<ll,int>
#define MP make_pair
#define fi first
#define se second
#define si set<P >::iterator
using namespace std;
int n;
namespace Tree{
    int f[N],s[N];
    int find(int x){return f[x]==x?f[x]:(f[x]=find(f[x]));}
    struct road{
        int x,y;ll w;
        bool operator <(const road a)const{return w>a.w;}
    }r[N];
    int tt=0;
    void add(int u,int v,ll w){r[++tt]=(road){u,v,w};}
    ll merge(int x,int y)
    {
        int hx=find(x),hy=find(y);
        if(hx==hy) return 0;
        ll res=1ll*s[hx]*s[hy]%mod;
        s[hy]+=s[hx];f[hx]=hy;
        return res;
    }
    void solve()
    {
        for(int i=1;i<=n;i++) f[i]=i,s[i]=1;
        sort(r+1,r+tt+1);
        ll ans=0;
        for(int i=1;i<=tt;i++) ans=(ans+merge(r[i].x,r[i].y)*r[i].w%mod)%mod;
        printf("%lld\n",ans%mod);
    }
}
vector<int>r[N];
int x[N],y[N],tt=1;
ll w[N];
void add(int u,int v,int w1)
{
    x[++tt]=u;y[tt]=v;w[tt]=w1;r[u].push_back(tt);
    x[++tt]=v;y[tt]=u;w[tt]=w1;r[v].push_back(tt);
}
int nxt[N];
set<P >s;
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    for(int u=1;u<=n;u++)
    {
        sort(r[u].begin(),r[u].end(),[&](int a,int b){return (y[a]-u+n)%n<(y[b]-u+n)%n;});
        int d=r[u].size();
        for(int i=0;i<d;i++) nxt[r[u][i]^1]=r[u][(i+1)%d];
        for(int i=0;i<d;i++)
        {
            int v=r[u][i];
            if((y[v]-u+n)%n==1) s.insert(MP(w[v],v));
        }
    }
    while(!s.empty())
    {
        int u=s.begin()->se^1;
        s.erase(s.begin());
        for(int v=nxt[u];v!=u;v=nxt[v])
        {
            si p=s.find(MP(w[v],v^1));
            w[v]+=w[u],w[v^1]+=w[u];
            if(p==s.end()) s.insert(MP(w[v],v));
            else s.erase(p),Tree::add(x[v],y[v],w[v]);
        }
    }
    Tree::solve();
    return 0;
}