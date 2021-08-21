#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 100010
#define MP make_pair
#define fi first
#define se second
#define inf 1000000000
using namespace std;
typedef long long ll;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
struct node{
    ll a,b;
    node(ll A=0,ll B=0):a(A),b(B){}
    bool operator <(const node c)const{return a+b<c.a+c.b;}
};
node operator +(node a,node b){return node(min(a.a,b.a-a.b),a.b+b.b);}
node f[N];
ll t[N],g[N],k;
node pre[N],suf[N];
int ch[N];
void dfs(int u,int p)
{
    for(int i=head[u];i;i=nxt[i]) if(to[i]!=p) dfs(to[i],u);
    int m=0;
    for(int i=head[u];i;i=nxt[i]) if(to[i]!=p) ch[++m]=to[i];
    sort(ch+1,ch+m+1,[&](int x,int y){return f[x]<f[y];});
    pre[0]=suf[m+1]=node(inf,0);
    for(int i=1;i<=m;i++) pre[i]=pre[i-1]+f[ch[i]];
    for(int i=m;i>=1;i--) suf[i]=f[ch[i]]+suf[i+1];
    f[u]=node(t[u]-1,1)+pre[m]+node(t[u]+k-2,1);
    if(!m){g[u]=t[u]-1;return;}
    g[u]=-2;
    for(int i=1;i<=m;i++) g[u]=max(g[u],(node(t[u]-1,1)+pre[i-1]+suf[i+1]+node(t[u]+k-2,0)+node(g[ch[i]],0)).a);
}
int main()
{
    int n;
    scanf("%d%lld",&n,&k);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;i++) scanf("%lld",&t[i]);
    dfs(1,0);
    printf("%d\n",g[1]+1);
    return 0;
}