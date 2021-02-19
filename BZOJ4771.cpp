#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define N 100010
#define M N*100
using namespace std;
int root[N],ls[M],rs[M],val[M],tot;
void insert(int &u,int pre,int l,int r,int p,int v)
{
    u=++tot;ls[u]=ls[pre];rs[u]=rs[pre];val[u]=val[pre]+v;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(p<=mid) insert(ls[u],ls[pre],l,mid,p,v);
    else insert(rs[u],rs[pre],mid+1,r,p,v);
}
int answer(int u,int l,int r,int L,int R)
{
    if(L>r || l>R || !u) return 0;
    if(L<=l && r<=R) return val[u];
    int mid=(l+r)>>1;
    if(R<=mid) return answer(ls[u],l,mid,L,R);
    if(L>mid) return answer(rs[u],mid+1,r,L,R);
    return answer(ls[u],l,mid,L,R)+answer(rs[u],mid+1,r,L,R);
}
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int fa[N],dep[N],siz[N],son[N];
void dfs1(int u)
{
    dep[u]=dep[fa[u]]+1;siz[u]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        dfs1(v);
        if(siz[v]>siz[son[u]]) son[u]=v;
        siz[u]+=siz[v];
    }
}
int nid[N],id[N],top[N],tt;
void dfs2(int u,int topp)
{
    top[u]=topp;nid[id[u]=++tt]=u;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i]) if(to[i]!=son[u]) dfs2(to[i],to[i]);
}
int lca(int u,int v)
{
    for(;top[u]!=top[v];u=fa[top[u]]) if(dep[top[u]]<dep[top[v]]) swap(u,v);
    return dep[u]<dep[v]?u:v;
}
int p[N],c[N];
set<int>s[N];
bool cmp(int x,int y){return dep[x]<dep[y];}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&c[i]);
        for(int i=2;i<=n;i++) scanf("%d",&fa[i]),add(fa[i],i);
        dfs1(1);dfs2(1,1);
        for(int i=1;i<=n;i++) p[i]=i;
        sort(p+1,p+n+1,cmp);
        for(int i=1,j=1;i<=dep[p[n]];++i,root[i]=root[i-1])
            for(;j<=n && dep[p[j]]==i;j++)
            {
                int u=p[j];
                insert(root[i],root[i],1,n,id[u],1);
                auto t=s[c[u]].lower_bound(id[u]);
                int pre=0,nxt=0;
                if(t!=s[c[u]].end()) nxt=nid[*t];
                if(t!=s[c[u]].begin()) pre=nid[*--t];
                if(pre) insert(root[i],root[i],1,n,id[lca(pre,u)],-1);
                if(nxt) insert(root[i],root[i],1,n,id[lca(u,nxt)],-1);
                if(pre && nxt) insert(root[i],root[i],1,n,id[lca(pre,nxt)],1);
                s[c[u]].insert(id[u]);
            }
        int ans=0;
        while(m --> 0)
        {
            int x,d;
            scanf("%d%d",&x,&d);
            x^=ans,d^=ans;
            printf("%d\n",ans=answer(root[min(dep[x]+d,dep[p[n]])],1,n,id[x],id[x]+siz[x]-1));
        }
        for(int i=1;i<=n;i++) s[i].clear(),root[i]=head[i]=id[i]=son[i]=0;
        tot=cnt=tt=0;root[1]=0;
    }
    return 0;
}