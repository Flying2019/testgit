#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
vector<P >v[N];
P ton[N];
int a[N];
struct ques{
    int l,r,k,id;
    bool operator <(const ques a)const{return k<a.k;}
}q[N];
ll s[N],ans[N];
int l[N],r[N];
int main()
{
    int n,m,t;
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].push_back(MP(i,i));
    for(int i=1;i<=t;i++) scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k),q[i].id=i;
    sort(q+1,q+t+1);
    int u=1;
    for(int x=1;x<=m;x++)
    {
        int tt=0;
        sort(v[x].begin(),v[x].end());
        for(P u:v[x])
        {
            while(tt && ton[tt].se>=u.se) tt--;
            ton[++tt]=u;
        }
        for(int i=1;i<=tt;i++)
        {
            int p=lower_bound(ton+1,ton+tt+1,MP(ton[i].se+1,-1))-ton;
            if(p<=tt) v[x+1].push_back(MP(ton[i].fi,ton[p].se));
            l[i]=ton[i].fi,r[i]=ton[i].se;
        }
        for(int i=2;i<=tt;i++) s[i]=s[i-1]+1ll*(l[i]-l[i-1])*r[i];
        for(;q[u].k==x;u++)
        {
            int pl=lower_bound(l+1,l+tt+1,q[u].l)-l,pr=upper_bound(r+1,r+tt+1,q[u].r)-r-1;
            if(pl>pr) continue;
            ans[q[u].id]=1ll*(l[pr]-l[pl])*(q[u].r+1)+1ll*(l[pl]-q[u].l+1)*(q[u].r-r[pl]+1)-(s[pr]-s[pl]);
        }
    }
    for(int i=1;i<=t;i++) printf("%lld\n",ans[i]);
    return 0;
}