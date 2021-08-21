#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
const int N=500010,C=26;
typedef long long ll;
int n;
char s[N];
int fa[N],len[N],tot;
namespace PAM{
    int ch[N][C],fail[N];
    int get_nxt(int u,int p){for(;s[p-len[u]-1]!=s[p];u=fail[u]); return u;}
    int insert(int las,int p)
    {
        int u=get_nxt(las,p),c=s[p]-'a';
        if(!ch[u][c]) fail[++tot]=ch[get_nxt(fail[u],p)][c],len[tot]=len[u]+2,ch[u][c]=tot;
        return ch[u][c];
    }
    int get_nxtr(int u,int p){for(;s[p+len[u]+1]!=s[p];u=fail[u]); return u;}
    int find_r(int las,int p)
    {
        int u=get_nxtr(las,p),c=s[p]-'a';
        if(!ch[u][c]) throw;
        return ch[u][c];
    }
    void init(){len[1]=-1;fail[0]=1;tot=1;}
    void upd_fa(){for(int i=1;i<=tot;i++) fa[i]=fail[i]==0?1:fail[i];}
}
vector<int>g[N];
int ap[N],bp[N];
int f[N][21],_2[N*2];
void init_f(int n)
{
    for(int i=1;i<=n;i++) f[i][0]=fa[i];
    for(int i=1;1<<i<=n;i++)
        for(int j=1;j<=n;j++) f[j][i]=f[f[j][i-1]][i-1];
}
namespace ST{
    int f[21][N*2],dep[N*2],id[N*2],dfn[N*2],tot;
    void dfs(int u,int p)
    {
        dep[u]=dep[p]+1;
        id[++tot]=u;dfn[u]=tot;
        for(int v:g[u]) dfs(v,u),id[++tot]=u;
    }
    void init()
    {
        dfs(1,0);
        for(int i=1;i<=tot;i++) f[0][i]=id[i];
        for(int i=2;i<=tot;i++) _2[i]=_2[i>>1]+1;
        for(int i=1,p=2;p<=tot;i++,p<<=1)
            for(int j=1;j+p-1<=tot;j++)
            if(dep[f[i-1][j]]<dep[f[i-1][j+p/2]]) f[i][j]=f[i-1][j];
            else f[i][j]=f[i-1][j+p/2];
    }
    int lca(int x,int y)
    {
        if(!x || !y) return 0;
        x=dfn[x],y=dfn[y];
        if(x>y) swap(x,y);
        int p=_2[y-x+1],u=1<<p;
        return dep[f[p][x]]>dep[f[p][y-u+1]]?f[p][y-u+1]:f[p][x];
    }
}
using ST::lca;using ST::dep;
int dfn[N],ind,id[N];
void dfs(int u)
{
    id[dfn[u]=++ind]=u;
    for(int v:g[u]) dfs(v);
}
namespace seg_tree{
    const int M=N*20;
    int ls[M],rs[M],cnt;
    int f[M],fl[M],fr[M];
    void upd(int u)
    {
        f[u]=f[ls[u]]+f[rs[u]]-dep[lca(id[fr[ls[u]]],id[fl[rs[u]]])];
        fl[u]=fl[ls[u]]?fl[ls[u]]:fl[rs[u]];
        fr[u]=fr[rs[u]]?fr[rs[u]]:fr[ls[u]];
    }
    void insert(int &u,int l,int r,int p)
    {
        if(!u) u=++cnt;
        if(l==r){fl[u]=fr[u]=p,f[u]=dep[id[p]];return;}
        int mid=(l+r)>>1;
        if(p<=mid) insert(ls[u],l,mid,p);
        else insert(rs[u],mid+1,r,p);
        upd(u);
    }
    int merge(int x,int y,int l,int r)
    {
        if(!x || !y) return x+y;
        if(l==r) return x;
        int mid=(l+r)>>1;
        ls[x]=merge(ls[x],ls[y],l,mid);rs[x]=merge(rs[x],rs[y],mid+1,r);
        upd(x);return x;
    }
}
using seg_tree::insert;using seg_tree::merge;
vector<int>q[N];
int root[N];
ll ans=0;
void solve(int u)
{
    for(int v:q[u]) insert(root[u],1,tot,dfn[v]);
    for(int v:g[u]) solve(v),root[u]=merge(root[u],root[v],1,tot);
    if(u!=1) ans+=max(seg_tree::f[root[u]]-1,0);
}
namespace runs{
    const int mod=1019260817;
    #define MP make_pair
    #define fi first
    #define se second
    typedef pair<int,int> P;
    P operator +(const P a,const P b){return MP((a.fi+b.fi)%mod,(a.se+b.se)%mod);}
    P operator +(const P a,const int b){return MP((a.fi+b)%mod,(a.se+b)%mod);}
    P operator -(const P a,const P b){return MP((a.fi-b.fi+mod)%mod,(a.se-b.se+mod)%mod);}
    P operator *(const P a,const P b){return MP(1ll*a.fi*b.fi%mod,1ll*a.se*b.se%mod);}
    const P B=MP(233,2333);
    int s[N];
    P h[N],bs[N],bh[N];
    P get(int l,int r){return h[r]-h[l-1]*bs[r-l+1];}
    P getb(int l,int r){return bh[l]-bh[r+1]*bs[r-l+1];}
    bool is_pal(int l,int r){return get(l,r)==getb(l,r);}
    bool qry_pal(int l,int r)
    {
        int p=ap[r];
        for(int i=_2[dep[p]];i>=0;i--)
        if(len[f[p][i]]>r-l+1) p=f[p][i];
        if(len[p]>r-l+1) p=f[p][0];
        if(len[p]==r-l+1) return true;
        return is_pal(l,r-len[p]);
    }
    int lcp(int x,int y)
    {
        int l=1,r=n-max(x,y)+1;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(get(x,x+mid-1)==get(y,y+mid-1)) l=mid+1;
            else r=mid-1;
        }
        return r;
    }
    int lcs(int x,int y)
    {
        int l=1,r=min(x,y);
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(get(x-mid+1,x)==get(y-mid+1,y)) l=mid+1;
            else r=mid-1;
        }
        return r;
    }
    bool cmp(int l1,int l2){int l=lcp(l1,l2); return s[l1+l]<s[l2+l];}
    int nxt[N];
    void lyndon(bool ell){for(int i=n-1;i;i--) for(nxt[i]=i+1;nxt[i] && cmp(nxt[i],i)==ell;nxt[i]=nxt[nxt[i]]);}
    pair<P,int> per[N*20];int pt;
    void make_runs()
    {
        for(int k=n-1;k;k--)
        if(nxt[k])
        {
            int dl=lcs(k,nxt[k]),dr=lcp(k,nxt[k]),p=nxt[k]-k;
            int l=k-dl+1,r=nxt[k]+dr-1;
            if(dl+dr<=p) continue;
            for(int i=l;i<l+p && i+2*p-1<=r;i++)
            if(qry_pal(i,i+2*p-1))
            per[++pt]=MP(get(i,i+2*p-1),(r-i+1)/p-is_pal(i,i+2*p-1));
        }
    }
    void solve()
    {
        for(int i=1;i<=n;i++) s[i]=::s[i]-'a'+1;
        bs[0]=MP(1,1);
        for(int i=1;i<=n;i++) h[i]=h[i-1]*B+s[i],bs[i]=bs[i-1]*B;
        for(int i=n;i;i--) bh[i]=bh[i+1]*B+s[i];
        lyndon(0);make_runs();
        lyndon(1);make_runs();
        sort(per+1,per+pt+1);reverse(per+1,per+pt+1);
        ll res=0;
        for(int i=1;i<=pt;i++)
        if(i==1 || per[i].fi!=per[i-1].fi) res+=1ll*per[i].se*(per[i].se-1)/2;
        ans-=res;
    }
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    PAM::init();
    for(int i=1;i<=n;i++) g[fa[i]].push_back(i);
    for(int i=1;i<=n;i++) ap[i]=PAM::insert(ap[i-1],i);
    for(int i=n;i;i--) bp[i]=PAM::find_r(bp[i+1],i);
    PAM::upd_fa();
    fa[1]=0;len[1]=0;
    for(int i=2;i<=tot;i++) g[fa[i]].push_back(i);
    for(int i=1;i<=n;i++) ap[i]=max(ap[i],1),bp[i]=max(bp[i],1);
    init_f(tot);ST::init();
    for(int i=2;i<=n;i++) q[bp[i]].push_back(ap[i-1]);
    dfs(1),solve(1);
    runs::solve();
    printf("%lld\n",ans);
    return 0;
}