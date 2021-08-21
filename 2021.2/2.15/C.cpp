#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 500010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;head[u]=cnt;
}
namespace LCT{
    int ch[N][2],fa[N],tag[N];
    bool nroot(int u){return ch[fa[u]][0]==u || ch[fa[u]][1]==u;}
    void set_tag(int u){swap(ch[u][0],ch[u][1]);tag[u]^=1;}
    void push_down(int u){if(tag[u]) set_tag(ch[u][0]),set_tag(ch[u][1]);tag[u]=false;}
    void rotate(int u)
    {
        int f=fa[u],ff=fa[f],k=ch[f][1]==u,v=ch[u][!k];
        if(nroot(f)) ch[ff][ch[ff][1]==f]=u;
        ch[f][k]=v;
        ch[u][!k]=f;
        if(v) fa[v]=f;
        fa[f]=u;fa[u]=ff;
    }
    void push(int u){if(nroot(u)) push(fa[u]);push_down(u);}
    void splay(int u)
    {
        push(u);
        for(;nroot(u);rotate(u))
            if(nroot(fa[u])) rotate((ch[fa[u]][1]==u)^(ch[fa[fa[u]]][1]==fa[u])?u:fa[u]);
    }
    void access(int u){for(int v=0;u;v=u,u=fa[u]) splay(u),ch[u][1]=v;}
    int find_root(int u)
    {
        access(u),splay(u);
        for(;ch[u][0];u=ch[u][0]) push_down(u);
        splay(u);
        return u;
    }
    void make_root(int u){access(u);splay(u);set_tag(u);}
    void link(int x, int y){make_root(x);fa[x]=y;}
    void cut(int x, int y){make_root(x);access(y);fa[y]=0;}
}
namespace SGT{
    int val[N<<2],c[N<<2],tag[N<<2];
    void update(int u){val[u]=min(val[u<<1],val[u<<1|1]);c[u]=(val[u<<1]==val[u]?c[u<<1]:0)+(val[u<<1|1]==val[u]?c[u<<1|1]:0);}
    void set_tag(int u,int v){val[u]+=v;tag[u]+=v;}
    void push_down(int u){if(tag[u]) set_tag(u<<1,tag[u]),set_tag(u<<1|1,tag[u]);tag[u]=0;}
    void build(int u,int l,int r)
    {
        if(l==r){val[u]=l+1;c[u]=1;return;}
        int mid=(l+r)>>1;
        build(u<<1,l,mid),build(u<<1|1,mid+1,r);
        update(u);
    }
    void insert(int u,int l,int r,int L,int R,int v)
    {
        if(L<=l && r<=R){set_tag(u,v);return;}
        push_down(u);
        int mid=(l+r)>>1;
        if(L<=mid) insert(u<<1,l,mid,L,R,v);
        if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
        update(u);
    }
    int answer(int u,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return val[u]==1?c[u]:0;
        push_down(u);
        int mid=(l+r)>>1,v=0;
        if(L<=mid) v+=answer(u<<1,l,mid,L,R);
        if(R>mid) v+=answer(u<<1|1,mid+1,r,L,R);
        return v;
    }
}
vector<int>d[N],rd[N];
int deg[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    SGT::build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if(u>v) swap(u,v);
        add(v,u);rd[u+1].push_back(v);
        SGT::insert(1,1,n,v,n,-1);
    }
    ll ans=0;
    for(int l=1,r=1;l<=n;l++)
    {
        for(;r<n;r++)
        {
            bool ca=true;int u=r+1;
            for(int &i=head[u];i;i=nxt[i])
            {
                int v=to[i];
                if(v<l) continue;
                if(deg[u]<2 && deg[v]<2 && LCT::find_root(u)!=LCT::find_root(v))
                {
                    ++deg[u],++deg[v];
                    LCT::link(u,v);
                    d[v].push_back(u);
                }
                else{ca=false;break;}
            }
            if(!ca) break;
        }
        SGT::insert(1,1,n,1,n,-1);
        for(int v:rd[l]) SGT::insert(1,1,n,v,n,1);
        if(l<=r) ans+=SGT::answer(1,1,n,l,r);
        for(int v:d[l]) --deg[l],--deg[v],LCT::cut(l,v);
    }
    printf("%lld\n",ans);
    return 0;
}