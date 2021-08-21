#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
#define inf 100000000
#define MP make_pair
#define fi first
#define se second
#define LB lower_bound
using namespace std;
typedef pair<int,int> P;
int a[N],b[N];
namespace LDIS{
    int f[N],g[N],fn,gn;
    void init(int n){for(int i=1;i<=n+1;i++) f[i]=g[i]=inf;fn=gn=0;}
    void answer(int v,P &r,P &s)
    {
        int w=inf-v;
        r=MP(LB(f+1,f+fn+1,v)-f,LB(g+1,g+gn+1,w)-g);
        s=MP(f[r.fi],g[r.se]);
        if(r.fi>fn) fn++;if(r.se>gn) gn++;
        f[r.fi]=v;g[r.se]=w;
    }
}
namespace SGT{
    P val[N<<2];int tag[N<<2];
    void setg(int x,int v){val[x].fi+=v;tag[x]+=v;}
    void push(int u){if(tag[u]) setg(u<<1,tag[u]),setg(u<<1|1,tag[u]);tag[u]=0;}
    void build(int u,int l,int r,int a[])
    {
        if(l==r){val[u]=MP(a[l],l);return;}
        int mid=(l+r)>>1;
        build(u<<1,l,mid,a);build(u<<1|1,mid+1,r,a);
        val[u]=max(val[u<<1],val[u<<1|1]);
    }
    void insert(int u,int l,int r,int L,int R,int v)
    {
        if(L>R) return;
        if(L<=l && r<=R){setg(u,v);return;}
        push(u);
        int mid=(l+r)>>1;
        if(L<=mid) insert(u<<1,l,mid,L,R,v);
        if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
        val[u]=max(val[u<<1],val[u<<1|1]);
    }
    P answer(int u,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return val[u];
        push(u);
        int mid=(l+r)>>1;
        if(L>mid) return answer(u<<1|1,mid+1,r,L,R);
        if(R<=mid) return answer(u<<1,l,mid,L,R);
        return max(answer(u<<1,l,mid,L,R),answer(u<<1|1,mid+1,r,L,R));
    }
}
P fl[N],fr[N],g[N],ans;
int hl[N],hr[N];
int a1[N],a2[N],n1,n2;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    LDIS::init(n+1);
    for(int i=n;i>=1;i--) LDIS::answer(a[i],fr[i],g[i]);
    for(int i=1,l=1,r=n;i<=n+1;i++)
    {
        while(LDIS::f[l]<i) l++;
        while(LDIS::g[r]>inf-i) --r;
        b[i]=l+r-1;
    }
    LDIS::init(n+1);
    SGT::build(1,1,n+1,b);
    int res=0;
    for(int i=1;i<=n;i++)
    {
        P s,t=g[i];LDIS::answer(a[i],fl[i],s);
        s.se=inf-s.se;t.se=inf-t.se;
        if(s.fi<t.fi) SGT::insert(1,1,n+1,s.fi+1,t.fi,-1);
        else SGT::insert(1,1,n+1,t.fi+1,s.fi,1);
        if(s.se<t.se) SGT::insert(1,1,n+1,s.se+1,t.se,1);
        else SGT::insert(1,1,n+1,t.se+1,s.se,-1);
        if(ans<SGT::val[1]) ans=SGT::val[1],res=i;
    }
    n1=LDIS::fn,n2=LDIS::gn;
    if(ans.fi!=n1+n2){puts("IMPOSSIBLE");return 0;}
    for(int i=1;i<=n;i++) hl[i]=inf,hr[i]=0;
    for(int i=1;i<=res;i++) hl[fl[i].fi]=hr[fl[i].se]=a[i];
    int l=0,r=0;
    for(;hl[l+1]<ans.se;l++);
    for(;hr[r+1]>=ans.se;r++);
    for(int i=res,p=l;i;i--) if(fl[i].fi==p) a1[p--]=i;
    for(int i=res,p=r;i;i--) if(fl[i].se==p) a2[p--]=i;
    reverse(a1+1,a1+n1+1);reverse(a2+1,a2+n2+1);
    for(int i=res+1,p=n1-l;i<=n;i++) if(fr[i].se==p) a1[p--]=i;
    for(int i=res+1,p=n2-r;i<=n;i++) if(fr[i].fi==p) a2[p--]=i;
    reverse(a1+1,a1+n1+1);reverse(a2+1,a2+n2+1);
    printf("%d\n",n1);
    for(int i=1;i<=n1;i++) printf("%d ",a1[i]);
    printf("\n%d\n",n2);
    for(int i=1;i<=n2;i++) printf("%d ",a2[i]);
    return 0;
}