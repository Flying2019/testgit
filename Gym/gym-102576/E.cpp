#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 1000010
using namespace std;
struct node{
    int x,l,r;
    bool operator <(const node a)const{return x<a.x;}
}p[N];
bool ans[N];
int ly[N],ry[N],X[N];
vector<int>q[N<<2];
void insert(int u,int l,int r,int L,int R,int v)
{
    if(L<=l && r<=R){q[u].push_back(v);return;}
    int mid=(l+r)>>1;
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
}
void push(int u,int l,int r)
{
    if(!q[u].empty())
    {
        struct node{
            int x,y,z;
            node(int X=0,int Y=0,int Z=0):x(X),y(Y),z(Z){}
            bool operator <(const node a)const{return x==a.x?z<a.z:x<a.x;}
        };
        vector<node>v;
        for(int i=l;i<=r;i++) v.push_back(node(p[i].l,p[i].r,0));
        for(int i:q[u]) v.push_back(node(ly[i],ry[i],i));
        sort(v.begin(),v.end());
        int mx=-2e9;
        for(auto w:v)
        if(!w.z) mx=max(mx,w.y);
        else if(mx>=w.y) ans[w.z]=true;
        v.clear();
    }
    if(l==r) return;
    int mid=(l+r)>>1;
    push(u<<1,l,mid);
    push(u<<1|1,mid+1,r);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int y,r;
        scanf("%d%d%d",&p[i].x,&y,&r);
        p[i].l=y-r,p[i].r=y+r;
    }
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) X[i]=p[i].x;
    for(int i=1;i<=m;i++)
    {
        int px,qx;
        scanf("%d%*d%d%*d%d%d",&px,&qx,&ly[i],&ry[i]);
        if(px>qx) swap(px,qx);
        px=lower_bound(X+1,X+n+1,px)-X;
        qx=upper_bound(X+1,X+n+1,qx)-X-1;
        if(px<=qx) insert(1,1,n,px,qx,i);
    }
    push(1,1,n);
    for(int i=1;i<=m;i++) puts(ans[i]?"NO":"YES");
    return 0;
}