#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 400010
#define db double
#define inf 1e11
using namespace std;
namespace SGT{
    db val[N<<2],tag[N<<2];
    void set_tag(int u,db v){val[u]+=v;tag[u]+=v;}
    void push_down(int u){if(tag[u]) set_tag(u<<1,tag[u]),set_tag(u<<1|1,tag[u]);tag[u]=0;}
    void insert(int u,int l,int r,int L,int R,db v)
    {
        if(L<=l && r<=R){set_tag(u,v);return;}
        int mid=(l+r)>>1;push_down(u);
        if(L<=mid) insert(u<<1,l,mid,L,R,v);
        if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
        val[u]=min(val[u<<1],val[u<<1|1]);
    }
    db answer(int u,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return val[u];
        int mid=(l+r)>>1;push_down(u);db v=inf;
        if(L<=mid) v=min(v,answer(u<<1,l,mid,L,R));
        if(R>mid) v=min(v,answer(u<<1|1,mid+1,r,L,R));
        return v;
    }
}
struct road{
    int len,u;db v;
    bool operator <(const road a)const{return v<a.v;}
}d[N];int tt;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int pre=0;db ans=0;
    for(int i=1;i<=n;i++)
    {
        int l,r;db v;scanf("%d%d%lf",&l,&r,&v);
        ++tt,d[tt]=(road){l-pre,tt,0};
        ++tt,d[tt]=(road){r-l,tt,v};
        pre=r;
    }
    ++tt,d[tt]=(road){m-pre,tt,0};
    sort(d+1,d+tt+1);
    for(int i=1;i<=tt;i++) if(d[i].v) SGT::insert(1,1,tt,d[i].u,tt,d[i].len/d[i].v);
    for(int i=1;i<=tt;i++)
    {
        db t=d[i].v?d[i].len/d[i].v:0;
        db v=min(t+d[i].len/(d[i].v+2),SGT::answer(1,1,tt,d[i].u,tt));
        SGT::insert(1,1,tt,d[i].u,tt,-v);
        ans+=(t+d[i].len-v)/(d[i].v+1);
    }
    printf("%.8lf",ans);
    return 0;
}