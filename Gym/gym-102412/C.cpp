#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 100010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;head[u]=cnt;
}
int fa[N],siz[N],dep[N],son[N];
int top[N],id[N],nid[N],tot,n,m;
void dfs1(int u)
{
    siz[u]=1;
    dep[u]=dep[fa[u]]+1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa[u]) continue;
        fa[v]=u;
        dfs1(v);
        if(siz[son[u]]<siz[v]) son[u]=v;
        siz[u]+=siz[v];
    }
}
void dfs2(int u,int topp)
{
    top[u]=topp;
    id[u]=++tot;nid[tot]= u;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v!=fa[u] && v!=son[u])dfs2(v,v);
    }
}
int sz[N<<2],tag[N<<2];
ll sum[N<<2],val[N<<2];
void build(int u,int l,int r)
{
    if(l==r){val[u]=1;return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    val[u]=val[u<<1]+val[u<<1|1];
}
void set_tag(int u,int v){sz[u]+=v;tag[u]+=v;sum[u]+=1ll*v*val[u];}
void push_down(int u)
{
    if(!tag[u]) return;
    set_tag(u<<1,tag[u]),set_tag(u<<1|1,tag[u]);
    tag[u]=0;
}
void update(int u)
{
    sz[u]=max(sz[u<<1],sz[u<<1|1]);
    sum[u]=sum[u<<1]+sum[u<<1|1];
}
void insert(int u,int l,int r,int L,int R,ll v)
{
    if(L<=l && r<=R){set_tag(u,v);return;}
    int mid=(l+r)>>1;
    push_down(u);
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    update(u);
}
ll answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return sum[u];
    push_down(u);
    int mid=(l+r)>>1;
    ll v=0;
    if(L<=mid) v+=answer(u<<1,l,mid,L,R);
    if(R>mid) v+=answer(u<<1|1,mid+1,r,L,R);
    return v;
}
int get_weight(void)
{
    int u=1,l=1,r=n;
    while(l<r)
    {
        push_down(u);
        int mid=(l+r)>>1;
        if(sz[u<<1|1]*2>=sz[1]) l=mid+1,u=u<<1|1;
        else r=mid,u=u<<1;
    }
    return nid[l];
}
void ins(int x,int v)
{
    for(;top[x]!=1;x=fa[top[x]]) insert(1,1,n,id[top[x]],id[x],v);
    insert(1,1,n,1,id[x],v);
}
ll answer(int x)
{
    ll res=0;
    for(;top[x]!=1;x=fa[top[x]]) res+=answer(1,1,n,id[top[x]],id[x]);
    return res+answer(1,1,n,1,id[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    scanf("%d",&m);
    dfs1(1),dfs2(1,1);
    build(1,1,n);
    ll s1=0,s2=0;
    while(m --> 0)
    {
        char op[3];
        int x,v;
        scanf("%s%d",op,&x);
        if(op[0]=='+') v=1;
        else v=-1;
        s1+=v;
        s2+=1ll*dep[x]*v;
        ins(x,v);
        int p=get_weight();
        printf("%lld\n",s2+s1*dep[p]-2*answer(p));
    }
    return 0;
}