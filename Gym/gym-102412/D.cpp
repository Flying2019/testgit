#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 1000000000
#define N 200010
using namespace std;
int a[N],siz[N],ls[N],rs[N],mx[N],mn[N],mvx[N],mvn[N],rnd[N],tt;
int ans[N];
//mx/mn:The max.min number
//mvx:The maxinum x (x->y)
//mvn:The mininum y (x->y)
int new_node(int v)
{
    int u=++tt;
    siz[u]=1;mx[u]=mn[u]=u;mvx[u]=mvn[u]=0;
    rnd[u]=rand();
    return u;
}
bool chk(int x,int y){return x && y && a[x]<a[y];}
inline int vmax(int x,int y)
{
    if(!x || !y) return x+y;
    return a[x]>a[y]?x:y;
}
inline int vmin(int x,int y)
{
    if(!x || !y) return x+y;
    return a[x]<a[y]?x:y;
}
int find_last(int u,int v)//The mininum number that larger than v
{
    if(!u || a[mx[u]]<v) return 0;
    if(a[mn[u]]>=v) return mn[u];
    int t=find_last(rs[u],v);
    if(t) return t;
    else if(a[u]>=v) return u;
    else return find_last(ls[u],v);
}
int find_first(int u,int v)//The maxinum number that less than v
{
    if(!u || a[mn[u]]>v) return 0;
    if(a[mx[u]]<=v) return mx[u];
    int t=find_first(ls[u],v);
    if(t) return t;
    else if(a[u]<=v) return u;
    else return find_first(rs[u],v);
}
void update(int u)
{
    const int sl=ls[u],sr=rs[u];
    siz[u]=siz[sl]+siz[sr]+1;
    if(ans[sl] || ans[sr] || chk(vmin(mn[sl],u),mvx[sr]) || chk(mvn[sl],vmax(mx[sr],u)) || (chk(mn[sl],u) && chk(u,mx[sr]))){ans[u]=true;return;}
    ans[u]=false;
    mx[u]=vmax(u,vmax(mx[sl],mx[sr]));
    mn[u]=vmin(u,vmin(mn[sl],mn[sr]));
    mvx[u]=vmax(find_first(ls[u],a[vmax(mx[sr],u)]),vmax(mvx[sl],mvx[sr]));
    mvn[u]=vmin(find_last(rs[u],a[vmin(mn[sl],u)]),vmin(mvn[sl],mvn[sr]));
    if(chk(u,mx[sr])) mvx[u]=vmax(mvx[u],u);
    if(chk(mn[sl],u)) mvn[u]=vmin(mvn[u],u);
}
int merge(int x,int y)
{
    if(!x || !y) return x+y;
    if(rnd[x]<rnd[y]){rs[x]=merge(rs[x],y);update(x);return x;}
    else{ls[y]=merge(x,ls[y]);update(y);return y;}
}
void split(int u,int k,int &l,int &r)
{
    if(!u){l=r=0;return;}
    if(siz[ls[u]]<k){l=u;split(rs[u],k-siz[ls[u]]-1,rs[u],r);}
    else{r=u;split(ls[u],k,l,ls[u]);}
    update(u);
}
int main()
{
    srand(233);
    int n,q;
    scanf("%d",&n);
    int root=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),root=merge(root,new_node(a[i]));
    scanf("%d",&q);
    while(q --> 0)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        int s=r-l+1,tl=0,tr=0,rr=0;
        split(root,l-1,root,tl);
        split(tl,s,tl,rr),split(tl,s-k,tl,tr);
        root=merge(root,merge(merge(tr,tl),rr));
        puts(ans[root]?"YES":"NO");
    }
    return 0;
}