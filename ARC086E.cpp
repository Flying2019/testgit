#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200010
#define mod 1000000007
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
struct node{
    int a[3],d;
    int& operator [](int b){return a[b];}
    node(int x=0,int y=0,int z=0,int D=0){a[0]=x;a[1]=y;a[2]=z;d=D;}
};
node operator *(node a,node b)
{
    node c;
    for(int i=0;i<=2;i++)
        for(int j=0;j<=2;j++) c[min(2,i+j)]=(c[min(2,i+j)]+1ll*a[i]*b[j])%mod;
    c.d=a.d+b.d;
    return c;
}
int tot,id[N];
vector<node>f[N];
void merge(int &x,int &y)
{
    if(f[x].size()<f[y].size()) swap(x,y);
    for(int i=(int)f[x].size()-1,j=(int)f[y].size()-1;j>=0;i--,j--)
        f[x][i]=f[x][i]*f[y][j];
}
void dfs(int u)
{
    if(!head[u]) id[u]=++tot;
    int m=0;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        dfs(v);
        merge(id[u],id[v]);
        m=max(m,(int)f[id[v]].size());
        f[id[v]].clear();
    }
    for(int i=(int)f[id[u]].size()-1;i>=(int)f[id[u]].size()-m;i--)
    f[id[u]][i][0]=(f[id[u]][i][0]+f[id[u]][i][2])%mod,f[id[u]][i][2]=0;
    f[id[u]].push_back(node(1,1,0,1));
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=2;i<=n+1;i++)
    {
        int a;
        scanf("%d",&a);++a;
        add(a,i);
    }
    dfs(1);
    int ans=0;
    for(node u:f[id[1]])
        ans=(ans+1ll*u[1]*ksm(2,n+1-u.d))%mod;
    printf("%d\n",ans);
    return 0;
}