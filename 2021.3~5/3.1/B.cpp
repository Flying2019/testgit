#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define N 600010
#define inf 100000000
using namespace std;
int f[N],c[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
void merge(int x,int y){x=find(x),y=find(y);if(x!=y) f[x]=y,c[y]+=c[x];}
int x[N],y[N],t;
struct node{
    int u,t;
    node(int U=0,int T=0):u(U),t(T){};
    bool operator <(const node a)const{return u==a.u?t<a.t:u<a.u;}
}p[N];
bool cmp(node a,node b){return y[a.u]==y[b.u]?a.t>b.t:y[a.u]>y[b.u];}
set<node>s;
int ans[N],to[N];
int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) ++t,scanf("%d%d",&x[i],&y[i]),p[t].u=i,p[t].t=0;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) ++t,scanf("%d%d",&x[t],&y[t]),p[t].u=t,p[t].t=1;
    sort(p+1,p+t+1,cmp);
    for(int i=1;i<=t;i++)
    {
        int u=p[i].u,v=x[p[i].u];
        if(!p[i].t)
        {
            auto q=s.lower_bound(node(v,-inf));
            if(q!=s.end()) c[q->t]++;
            continue;
        }
        u-=n;
        auto q=s.insert(node(v,u)).first;
        if((++q)!=s.end()) to[u]=q->t;--q;
        auto qr=q;
        while(q!=s.begin())
        {
            --q;
            if(q->t<u){++q;break;}
        }
        s.erase(q,qr);
    }
    for(int i=1;i<=m;i++) f[i]=i;
    for(int i=m;i;i--)
    {
        ans[i]=c[find(i)];
        if(to[i]) merge(i,to[i]);
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}