#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define N 200010
using namespace std;
int cn[N<<2],mx[N<<2],val[N<<2],tag[N<<2],lc[N<<2],rc[N<<2];
void set_tag(int u,int v){cn[u]+=v;tag[u]+=v;}
void push_down(int u){if(tag[u]) set_tag(u<<1,tag[u]),set_tag(u<<1|1,tag[u]);tag[u]=0;}
void update(int u)
{
    cn[u]=min(cn[u<<1],cn[u<<1|1]),mx[u]=max(mx[u<<1],mx[u<<1|1]);
    lc[u]=lc[u<<1],rc[u]=rc[u<<1|1];
    if(cn[u<<1]<cn[u<<1|1]) val[u]=val[u<<1],rc[u]=max(mx[u<<1|1],rc[u<<1]);
    else if(cn[u<<1]>cn[u<<1|1]) val[u]=val[u<<1|1],lc[u]=max(mx[u<<1],lc[u<<1|1]);
    else val[u]=val[u<<1]+val[u<<1|1]+max(lc[u<<1|1],rc[u<<1]);
}
void insert(int u,int l,int r,int L,int R,int v)
{
    if(L>R) return;
    if(L<=l && r<=R){set_tag(u,v);return;}
    int mid=(l+r)>>1;push_down(u);
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    update(u);
}
void change(int u,int l,int r,int p,int v)
{
    if(l==r){lc[u]=mx[u]=v;return;}
    int mid=(l+r)>>1;push_down(u);
    if(p<=mid) change(u<<1,l,mid,p,v);
    else change(u<<1|1,mid+1,r,p,v);
    update(u);
}
int col[N],n;
set<int>s[N];
void del(int c){if(!s[c].empty()) change(1,1,n,*s[c].begin(),0),insert(1,1,n,*s[c].begin(),*s[c].rbegin()-1,-1);}
void add(int c){if(!s[c].empty()) change(1,1,n,*s[c].begin(),s[c].size()),insert(1,1,n,*s[c].begin(),*s[c].rbegin()-1,1);}
void chg(int x,int v)
{
    int c=col[x];
    del(c);s[c].erase(x);add(c);
    col[x]=c=v;
    del(c);s[c].insert(x);add(c);
}
int x[N],y[N];
int main()
{
    int q,m=0;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&col[i]),s[col[i]].insert(i),m=max(m,col[i]);
    for(int i=1;i<=q;i++) scanf("%d%d",&x[i],&y[i]),m=max(m,y[i]);
    for(int i=1;i<=m+1;i++) add(i);
    printf("%d\n",n-val[1]-lc[1]-rc[1]);
    for(int i=1;i<=q;i++) chg(x[i],y[i]),printf("%d\n",n-val[1]-lc[1]-rc[1]);
    return 0;
}