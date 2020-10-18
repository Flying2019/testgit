#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long
#define N 200010
#define B 233
using namespace std;
int x[N],y[N];
vector<int>vx[N],vy[N];
int bl[N];
int qlx[N],qrx[N],qly[N],qry[N];
struct node{
    int l,r,v,id;
    bool operator <(const node a)const
    {
        if(bl[l]!=bl[a.l]) return bl[l]<bl[a.l];
        if(bl[r]!=bl[a.r]) return bl[r]<bl[a.r];
        return v<a.v;
    }
}qt[N*2];
int cnt[N*2],ans;
int fl,fr,fv;
void add1(vector<int>&a)
{
    for(auto v:a)
    if(v<=fv){if(!cnt[v]) ans++;cnt[v]++;}
}
void del1(vector<int>&a)
{
    for(auto v:a)
    if(v<=fv){if(cnt[v]==1) ans--;cnt[v]--;}
}
void add2(vector<int>&a)
{
    for(auto v:a)
    if(fl<=v && v<=fr){if(!cnt[fv]) ans++;cnt[fv]++;}
}
void del2(vector<int>&a)
{
    for(auto v:a)
    if(fl<=v && v<=fr){if(cnt[fv]==1) ans--;cnt[fv]--;}
}
int rx[N],ry[N];
int main()
{
    int n,m,k,q;
    scanf("%d%d%d%d",&n,&m,&k,&q);
    for(int i=1;i<=k;i++) scanf("%d%d",&x[i],&y[i]),vx[x[i]].push_back(y[i]),vy[y[i]].push_back(x[i]);
    for(int i=1;i<=q;i++) scanf("%d%d%d%d",&qlx[i],&qly[i],&qrx[i],&qry[i]);
    for(int i=1;i<=q;i++) bl[i]=i/B;
    int t=0;
    for(int i=1;i<=q;i++) qt[++t]=(node){qlx[i],qrx[i],qly[i]-1,-i},qt[++t]=(node){qlx[i],qrx[i],qry[i],i};
    sort(qt+1,qt+t+1);
    fl=1,fr=0,fv=0;
    for(int i=1;i<=t;i++)
    {
        while(fl<qt[i].l) del1(vx[fl]),fl++;
        while(fl>qt[i].l) --fl,add1(vx[fl]);
        while(fr<qt[i].r) ++fr,add1(vx[fr]);
        while(fr>qt[i].r) del1(vx[fr]),fr--;
        while(fv<qt[i].v) ++fv,add2(vy[fv]);
        while(fv>qt[i].v) del2(vy[fv]),fv--;
        if(qt[i].id<0) ry[-qt[i].id]-=ans;
        else ry[qt[i].id]+=ans;
    }
    t=0;
    memset(cnt,0,sizeof(cnt));ans=0;
    for(int i=1;i<=q;i++) qt[++t]=(node){qly[i],qry[i],qlx[i]-1,-i},qt[++t]=(node){qly[i],qry[i],qrx[i],i};
    sort(qt+1,qt+t+1);
    fl=1,fr=0,fv=0;
    for(int i=1;i<=t;i++)
    {
        while(fl<qt[i].l) del1(vy[fl]),fl++;
        while(fl>qt[i].l) --fl,add1(vy[fl]);
        while(fr<qt[i].r) ++fr,add1(vy[fr]);
        while(fr>qt[i].r) del1(vy[fr]),fr--;
        while(fv<qt[i].v) ++fv,add2(vx[fv]);
        while(fv>qt[i].v) del2(vx[fv]),fv--;
        if(qt[i].id<0) rx[-qt[i].id]-=ans;
        else rx[qt[i].id]+=ans;
    }
    for(int i=1;i<=q;i++)
    {
        ll res=1ll*(qrx[i]-qlx[i]+1)*(qry[i]-qly[i]+1);
        res-=1ll*(qrx[i]-qlx[i]+1-rx[i])*(qry[i]-qly[i]+1-ry[i]);
        printf("%lld\n",res);
    }
    return 0;
}