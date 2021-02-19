#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
#define mod 1000000007
using namespace std;
int val[N],n,tot;
void add(int u,int v){for(;u<=tot;u+=(u&(-u))) val[u]=(val[u]+v)%mod;}
int qry(int u,int v=0){for(;u;u-=(u&(-u))) v=(v+val[u])%mod;return v;}
int x[N],y[N],px[N];
struct node{
    int l,r;
    bool operator <(const node a)const{return l==a.l?r>a.r:l<a.l;}
    bool operator ==(const node a)const{return l==a.l && r==a.r;}
}p[N];
int f[N];
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    for(int i=1;i<=m;i++) scanf("%d",&y[i]);
    for(int i=1;i<=n;i++)
    if(x[i]>y[1] && x[i]<y[m])
    {
        int k=lower_bound(y+1,y+m+1,x[i])-y;
        if(y[k]==x[i]) continue;
        ++tot;p[tot].l=x[i]-y[k-1];
        px[tot]=p[tot].r=y[k]-x[i];
    }
    n=tot;
    sort(px+1,px+tot+1);
    tot=unique(px+1,px+tot+1)-px-1;
    for(int i=1;i<=n;i++) p[i].r=lower_bound(px+1,px+tot+1,p[i].r)-px;
    sort(p+1,p+n+1);
    n=unique(p+1,p+n+1)-p-1;
    f[0]=1;
    for(int i=1;i<=n;i++)
        f[i]=(qry(p[i].r-1)+1)%mod,add(p[i].r,f[i]);
    int ans=0;
    for(int i=0;i<=n;++i) ans=(ans+f[i])%mod;
    printf("%d\n",ans);
    return 0;
}