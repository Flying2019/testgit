#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300010
#define ll long long
using namespace std;
int x[N],y[N],w[N],id[N],f[N],g[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
ll merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return 0;
    if(g[x]<g[y]) swap(x,y);
    ll res=1ll*g[x]*g[y];
    f[y]=x;g[x]+=g[y];g[y]=0;
    return res;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) f[i]=i,g[i]=1;
    for(int i=1;i<=m;i++) scanf("%d%d%d",&x[i],&y[i],&w[i]),id[i]=i;
    sort(id+1,id+m+1,[&](int x,int y){return w[x]>w[y];});
    bool can=true;
    ll res=0;
    for(int l=1,r=1;l<=m;l=r)
    {
        while(r<=m && w[id[l]]==w[id[r]]) r++;
        for(int i=l;i<r;i++) if(find(x[id[i]])==find(y[id[i]])){can=false;break;}
        if(!can) break;
        for(int i=l;i<r;i++) res+=w[id[i]]*merge(x[id[i]],y[id[i]]);
    }
    for(int i=1;i<=n;i++) if(find(i)!=find(1)) res+=merge(1,i);
    if(!can) puts("-1");
    else printf("%lld\n",res);
    return 0;
}