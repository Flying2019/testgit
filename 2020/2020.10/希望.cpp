#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 1000010
#define ll long long
#define mod 998244353
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
int len[N],son[N],f1[N],n,L,k;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int id[N],idn,val[N];
void dfs(int u,int p)
{
    f1[u]=len[u]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u);
        if(len[v]>len[son[u]]) son[u]=v,len[u]=len[v]+1;
        f1[u]=1ll*f1[u]*f1[v]%mod;
    }
    f1[u]=(f1[u]+1)%mod;
    if(f1[u]) val[id[u]=++idn]=f1[u];
}
struct node{
    int a,d,iv,l,w;
};
node o;
int ar[N<<3],*f[N*2],*g[N*2],par;
inline int* _new(int k){par+=k;return ar+(par-k);}
int inv[N];
#define P pair
#define Pr pair<int,int>
#define MP make_pair
#define fi first
#define se second
int ra[N],rb[N];
#define times(x,v1,v2) x.a=1ll*x.a*v1%mod,x.d=1ll*x.d*v1%mod,x.iv=1ll*x.iv*v2%mod
#define addf(f,p) f[p.l++]=p.w
namespace F{
    node tag[N<<1];
    int ans[N];
    vector<P<node,vector<Pr > > >bk[N];
    inline int get(int u,int k)
    {
        if(k<tag[u].l) return (1ll*f[u][k]*tag[u].a+tag[u].d)%mod;
        return (1ll*tag[u].w*tag[u].a+tag[u].d)%mod;
    }
    inline void put(int u,int k,int v){f[u][k]=1ll*(v-tag[u].d+mod)*tag[u].iv%mod;}

    void merge(int u,int v,int l)
    {
        node tmp=tag[u];
        vector<Pr >s;
        for(int i=1;i<=l;i++)
        {
            s.push_back(MP(i,f[u][i]));
            int t=get(v,i-1);
            if(i==tag[u].l) addf(f[u],tag[u]);
            put(u,i,1ll*get(u,i)*t%mod);
        }
        if(l<L)
        {
            int t=get(v,l);
            if(!t) tag[u].l=l+1,tag[u].w=mod-1ll*tag[u].d*tag[u].iv%mod;
            else
            {
                int iv=inv[id[v]];
                s.push_back(MP(0,f[u][0]));
                for(int i=0;i<=l;i++)
                    put(u,i,1ll*get(u,i)*iv%mod);
                times(tag[u],t,iv);
            }
        }
        if(u<=n) bk[u].push_back(MP(tmp,s));
    }
    void dfs(int u,int p)
    {
        if(son[u])
        {
            f[son[u]]=f[u]+1;
            dfs(son[u],u);
            tag[u]=tag[son[u]];
        }
        else tag[u]=o;
        put(u,0,1);
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(v==p || v==son[u]) continue;
            f[v]=_new(len[v]);
            dfs(v,u);
            merge(u,v,min(len[v]-1,L));
        }
        ra[u]=get(u,min(len[u]-1,L-1));rb[u]=get(u,min(len[u]-1,L));
        ++tag[u].d;
    }
    void popbk(int u){
        tag[u]=bk[u].back().fi;
        for(auto x:bk[u].back().se) f[u][x.fi]=x.se;
        bk[u].pop_back();
    }
}
int ans=0;
namespace G{
    node tag[N];
    inline int get(int u,int k)
    {
        if(k<tag[u].l) return (1ll*g[u][k]*tag[u].a+tag[u].d)%mod;
        return (1ll*tag[u].w*tag[u].a+tag[u].d)%mod;
    }
    inline void put(int u,int k,int v){g[u][k]=1ll*(v-tag[u].d+mod)*tag[u].iv%mod;}
    void dfs(int u,int p)
    {
        if(len[u]>=L+1) put(u,len[u]-L-1,1);
        ans=(ans+ksm(1ll*rb[u]*get(u,len[u]-1)%mod,k))%mod;
        if(p) ans=(ans-ksm(1ll*ra[u]*(get(u,len[u]-1)+mod-1)%mod,k)+mod)%mod;
        if(!son[u]) return;
        vector<int>ch;
        int mx=0;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(v==p || v==son[u]) continue;
            ch.push_back(v);mx=max(mx,min(len[v],L));
        }
        reverse(ch.begin(),ch.end());
        f[u+n]=_new(mx+1);
        F::tag[u+n]=o;
        F::put(u+n,0,1);
        for(int v:ch)
        {
            F::popbk(u);
            g[v]=_new(len[v]);
            for(int i=max(len[v]-L-1,0);i<len[v];i++)
            {
                int p=len[son[u]]-len[v]+i,rp=L-len[v]+i;
                if(len[v]==L+i+1) g[v][i]=get(u,p);
                else g[v][i]=1ll*get(u,p)*F::get(u,min(len[u]-1,rp))%mod*F::get(u+n,min(mx,rp))%mod;
            }
            tag[v]=o;
            F::merge(u+n,v,min(len[v]-1,L));
            dfs(v,u);
        }
        int v=son[u]; g[v]=g[u],tag[v]=tag[u];
        for(int i=max(len[v]-L,0);i<=len[v]+mx-L-1;i++)
        {
            if(i==tag[v].l) addf(g[v],tag[v]);
            put(v,i,1ll*get(v,i)*F::get(u+n,L-len[v]+i)%mod);
        }
        if(mx<L)
        {
            int sv=1,iv=1;
            for(int v:ch)
            {
                sv=1ll*sv*val[id[v]]%mod;
                iv=1ll*iv*inv[id[v]]%mod;
            }
            if(!sv)
            {
                tag[v].l=len[v]+mx-L;
                tag[v].w=mod-1ll*tag[v].d*tag[v].iv%mod;
            }
            else
            {
                for(int i=max(len[v]-L-1,0);i<=len[v]+mx-L-1;i++)
                put(v,i,1ll*get(v,i)*iv%mod);
                times(tag[v],sv,iv);
            }
        }
        ++tag[v].d;
        dfs(v,u);
    }
}
int sum[N];
void for_inv()
{
    sum[0]=1;
    for(int i=1;i<=idn;i++) sum[i]=1ll*sum[i-1]*val[i]%mod;
    int invs=ksm(sum[idn]);
    for(int i=idn;i;invs=1ll*invs*val[i--]%mod) inv[i]=1ll*sum[i-1]*invs%mod;
}
int main()
{
    // freopen("hope4.in","r",stdin);
    scanf("%d%d%d",&n,&L,&k);
    o=(node){1,1,1,n,0};
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs(1,0);
    for_inv();
    f[1]=_new(len[1]);F::dfs(1,0);
    g[1]=_new(len[1]);G::tag[1]=o;
    G::dfs(1,0);
    printf("%d\n",ans);
    return 0;
}