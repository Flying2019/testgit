#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
#define M 1000010
#define K 7
#define D 21
#define B 41
#define ls(u) t[u].l
#define rs(u) t[u].r
using namespace std;
#define ui unsigned int
#define ll long long
#define ull unsigned long long
ui bs[M],hs[N],hh[M],iv[M];
int dep[N];
struct node{
    int l,r,siz,rnd,u;
}t[N*D<<1];
ui ksm(ui a,ui b=(1u<<31)-1)
{
    ui r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=r*a;
        a=a*a;
    }
    return r;
}
ui qs(int l,int r){return (hs[r]-hs[l])*iv[dep[l]];}
ui qh(int l,int r){return hh[l]-hh[r]*bs[r-l];}
int tid;
int fa[N][D],sv[N],pre[N];
ull rnk[N];
int s[K][N];
int _2[N];
void upd(int u){t[u].siz=t[ls(u)].siz+t[rs(u)].siz+1;}
int new_node(int x=0)
{
    int u=++tid;
    t[u].l=0,t[u].r=0,t[u].siz=1,t[u].rnd=rand(),t[u].u=x;
    return u;
}
int merge(int x,int y)
{
    if(!x || !y) return x+y;
    int u=new_node();
    if(t[x].rnd<t[y].rnd) t[u]=t[x],t[u].r=merge(t[u].r,y);
    else t[u]=t[y],t[u].l=merge(x,t[u].l);
    upd(u);
    return u;
}
bool cmp(int x,int y)
{
    if(sv[x]!=sv[y]) return sv[x]<sv[y];
    if(rnk[pre[x]]!=rnk[pre[y]]) return rnk[pre[x]]<rnk[pre[y]];
    for(int i=_2[min(dep[x],dep[y])];i;i--)
    {
        if(qs(fa[x][i],x)==qs(fa[y][i],y)) x=fa[x][i],y=fa[y][i];
        if(sv[x]<sv[y]) return true;
    }
    return false;
}
void split(int p,int k,int &l,int &r)
{
    if(!p){l=r=0;return;}
    if(cmp(t[p].u,k))
    {
        l=new_node();
        t[l]=t[p];
        split(rs(l),k,rs(l),r),upd(l);
    }
    else
    {
        r=new_node();
        t[r]=t[p];
        split(ls(r),k,l,ls(r)),upd(r);
    }
}
int root[N];
int rts[K][N];
void insert(int u)
{
    ull L(0),R(-1);
    rnk[0]=0;
    int l=0,r=0;
    split(root[u],u,l,r);
    int v=l;
    while(v && rs(v)) v=rs(v);
    if(v) L=rnk[t[v].u];
    v=r;
    while(v && ls(v)) v=ls(v);
    if(v) R=rnk[t[v].u];
    rnk[u]=(L>>1)+(R>>1)+(L&R&1);
    root[u]=merge(l,merge(new_node(u),r));
}
void ins(int p,int v,int k)
{
    int pr=rts[p][k];
    int u=++tid;
    pre[u]=pr;sv[u]=v;root[u]=root[pr];
    dep[u]=dep[pr]+1;
    fa[u][0]=pr;
    for(int i=1;(1<<i)<=dep[u];i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    hs[u]=hs[pr]+bs[dep[pr]]*(v+1);
    rts[p][k]=u;
    insert(u);
}
int ts[M];
int answer0(int rt,int k,int len)
{
    int res=0;
    for(int p=root[rt],v;p;)
    {
        int u=t[p].u;v=u;
        int re=0;
        for(int i=_2[min(len,dep[u])];i>=0;i--)
            if(qs(fa[v][i],u)==qh(len-(1<<i)-re,len)) re+=1<<i,v=fa[v][i];
        int l=re+1,r=re;
        bool can=false;
        if(r==len) can=(r==dep[u] || sv[v]<k);
        else if(r==dep[u]) can=true;
        else can=sv[v]<ts[len-l];
        if(can) res+=t[ls(p)].siz+1,p=rs(p);
        else p=ls(p);
    }
    return res;
}
int answer1(int rt,int k,int v)
{
    int res=0;
    for(int p=root[rt];p;)
    {
        int u=t[p].u;
        int x=k,y=u;
        for(int i=_2[min(dep[k],dep[u])];i>=0;i--)
        if(qs(fa[x][i],k)==qs(fa[y][i],u)) x=fa[x][i],y=fa[y][i];
        bool can=true;
        if(!x) can=(!y) || sv[y]<v;
        else if(!y) can=true;
        else can=sv[x]>sv[y];
        if(can) res+=t[ls(p)].siz+1,p=rs(p);
        else p=ls(p);
    }
    return res;
}
int len[K];
int main()
{
    for(int i=2;i<=N-10;i++) _2[i]=_2[i>>1]+1;
    int n,m,ty;
    scanf("%d%d%d",&n,&m,&ty);
    bs[0]=1;
    for(int i=1;i<=N-10;i++) bs[i]=bs[i-1]*B;
    iv[N-10]=ksm(bs[N-10]);
    for(int i=N-11;i>=0;i--) iv[i]=iv[i+1]*B;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&len[i]);
        for(int j=0;j<len[i];j++) scanf("%d",&s[i][j]),ins(i,s[i][j],0);
    }
    sv[0]=-1;
    int q;
    scanf("%d",&q);
    int las=0;
    for(int i=1;i<=q;i++)
    {
        for(int j=0;j<n;j++) rts[j][i]=rts[j][i-1];
        int op,x,y,k,l,r;
        scanf("%d%d%d",&op,&x,&y);op^=ty*las;x^=ty*las;y^=ty*las;
        if(op==0)
        {
            --x;
            ins(x,y,i);
        }
        else if(op==1)
        {
            scanf("%d%d%d",&k,&l,&r);
            k^=ty*las;l^=ty*las;r^=ty*las;
            --x;--y;
            printf("%d\n",las=answer1(rts[x][i],rts[y][k],r+1)-answer1(rts[x][i],rts[y][k],l));
        }
        else if(op==2)
        {
            --x;--y;
            rts[x][i]=rts[y][i];
        }
        else
        {
            scanf("%d",&k);
            k^=ty*las;
            for(int j=0;j<k;j++) scanf("%d",&ts[j]),ts[j]^=las;
            hh[k]=0;
            for(int j=k-1;j>=0;j--) hh[j]=hh[j+1]*B+ts[j]+1;
            for(int j=0;j<n;j++) printf("%d ",las=answer0(rts[j][i],y+1,k)-answer0(rts[j][i],x,k));
            puts("");
        }
    }
    return 0;
}