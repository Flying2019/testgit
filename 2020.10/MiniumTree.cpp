#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 200010
using namespace std;
struct node{
    int u,w,h,tg;
    node(int U=0,int W=0,int H=0,int T=0):u(U),w(W),h(H),tg(T){}
    void operator +=(int v){w+=v;tg+=v;}
}tr[N];
int ls[N],rs[N];
void push_down(int u){if(tr[u].tg)tr[ls[u]]+=tr[u].tg,tr[rs[u]]+=tr[u].tg,tr[u].tg=0;}
int merge(int x,int y)
{
    if(!x || !y) return x+y;
    push_down(x),push_down(y);
    if(tr[x].w>tr[y].w) swap(x,y);
    rs[x]=merge(rs[x],y);
    if(tr[ls[x]].h<tr[rs[x]].h) swap(ls[x],rs[x]);
    tr[x].h=tr[rs[x]].h+1;
    return x;
}
void pop(int &x)
{
    tr[x].tg-=tr[x].w;tr[x].w=0;
    push_down(x);
    x=merge(ls[x],rs[x]);
}
int find(int f[],int x){return x==f[x]?f[x]:(f[x]=find(f,f[x]));}
struct nd{
    int u,v;
    nd(int U=0,int V=0):u(U),v(V){};
    bool operator <(const nd a)const{return v>a.v;}
};
priority_queue<nd>q;
int root[N];
int f[N],g[N],fa[N];
#define RT(x) tr[root[x]].u
#define RTW(x) tr[root[x]].w
int main()
{
    int n,m,rt;
    scanf("%d%d%d",&n,&m,&rt);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        if(v==rt) continue;
        tr[i]=node(u,w,1);
        root[v]=merge(root[v],i);
    }
    for(int i=1;i<=n;i++) f[i]=g[i]=i;
    for(int i=1;i<=n;i++)
    if(i!=rt)
    {
        if(!root[i]){puts("-1");return 0;}
        q.push(nd(i,RTW(i)));
    }
    int ans=0;
    for(int t=0;t<n-1;t++)
    {
        while(!q.empty())
        {
            nd a=q.top();
            if(find(f,a.u)!=a.u || RTW(a.u)!=a.v) q.pop();
            else break;
        }
        if(q.empty()){puts("-1");return 0;}
        int u=q.top().u;ans+=q.top().v;q.pop();
        f[u]=find(f,fa[u]=RT(u));
        pop(root[u]);u=f[u];
        if(!root[u]) continue;
        int s=0;
        while(find(f,RT(u))==u)
        {
            int v=find(g,RT(u));
            s+=RTW(u);
            pop(root[u]);
            for(;v!=u;g[v]=u,v=find(g,fa[v])) root[u]=merge(root[u],root[v]);
        }
        if(!root[u]) continue;
        tr[root[u]]+=s;
        q.push(nd(u,RTW(u)));
    }
    printf("%d\n",ans);
    return 0;
}