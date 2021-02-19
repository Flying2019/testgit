#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
int a[N],nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int id[N],nid[N],son[N],siz[N],dep[N],fa[N];
int f[N][21],tot,n;
void dfs1(int u,int p)
{
    fa[u]=f[u][0]=p;siz[u]=1;dep[u]=dep[p]+1;
    for(int i=1;f[u][i-1];i++) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
int top[N];
void dfs2(int u,int topp)
{
    top[u]=topp;nid[id[u]=++tot]=u;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i])
    if(to[i]!=son[u] && to[i]!=fa[u]) dfs2(to[i],to[i]);
}
ll val[N<<2],tag[N<<2];
void set_tag(int u,int v,int l,int r){val[u]+=(r-l+1)*v;tag[u]+=v;}
void push_down(int u,int l,int r)
{
    if(!tag[u]) return;
    int mid=(l+r)>>1;
    set_tag(u<<1,tag[u],l,mid),set_tag(u<<1|1,tag[u],mid+1,r);tag[u]=0;
}
void insert(int L,int R,int v,int u=1,int l=1,int r=n)
{
    if(L<=l && r<=R){set_tag(u,v,l,r);return;}
    push_down(u,l,r);
    int mid=(l+r)>>1;
    if(L<=mid) insert(L,R,v,u<<1,l,mid);
    if(R>mid) insert(L,R,v,u<<1|1,mid+1,r);
    val[u]=val[u<<1]+val[u<<1|1];
}
ll answer(int L,int R,int u=1,int l=1,int r=n)
{
    if(L<=l && r<=R) return val[u];
    push_down(u,l,r);
    int mid=(l+r)>>1;ll ans=0;
    if(L<=mid) ans+=answer(L,R,u<<1,l,mid);
    if(R>mid) ans+=answer(L,R,u<<1|1,mid+1,r);
    return ans;
}
int getrk(ll k,int u=1,int l=1,int r=n)
{
    if(l==r) return l;
    push_down(u,l,r);
    int mid=(l+r)>>1;
    if(k<=val[u<<1]) return getrk(k,u<<1,l,mid);
    else return getrk(k-val[u<<1],u<<1|1,mid+1,r);
}
void upd(int x,int y,int v)
{
    for(;top[x]!=top[y];insert(id[top[x]],id[x],v),x=fa[top[x]])
    if(dep[top[x]]<dep[top[y]]) swap(x,y);
    if(dep[x]>dep[y]) swap(x,y);
    insert(id[x],id[y],v);
}
ll qry(int x,int y)
{
    ll ans=0;
    for(;top[x]!=top[y];ans+=answer(id[top[x]],id[x]),x=fa[top[x]])
    if(dep[top[x]]<dep[top[y]]) swap(x,y);
    if(dep[x]>dep[y]) swap(x,y);
    return ans+answer(id[x],id[y]);
}
ll answer()
{
    ll v=val[1];int u=nid[getrk((v+1)>>1)];
    for(int i=19;i>=0;i--)
    if(f[u][i])
    {
        int p=f[u][i];
        if(answer(id[p],id[p]+siz[p]-1)*2<=v) u=p;
    }
    if(answer(id[u],id[u]+siz[u]-1)*2<=v) u=f[u][0];
    return u;
}
int main()
{
    int m;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    scanf("%d",&m);
    while(m --> 0)
    {
        int opt,u,v;
        scanf("%d%d",&opt,&u);
        if(opt==1) insert(id[u],id[u]+siz[u]-1,1);
        else scanf("%d",&v),upd(u,v,1);
        printf("%d\n",answer());
    }
    return 0;
}