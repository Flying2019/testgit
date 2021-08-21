#include<iostream>
#include<cstdio>
#include<cstring>
#define N 45
#define mod 998244353
using namespace std;
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
struct MatT{
    struct node{
        int x,y;
        node(int A=0,int B=0):x(A),y(B){}
        node operator +(node a){return node((x+a.x)%mod,(y+a.y)%mod);}
        node operator -(node a){return node((x-a.x+mod)%mod,(y-a.y+mod)%mod);}
        node operator *(node a){return node(1ll*x*a.x%mod,(1ll*x*a.y+1ll*y*a.x)%mod);}
    }a[N][N];
    node inv(node a){return node(a.x,mod-a.y)*ksm(a.x,mod-3);}
    void add(int u,int v,int w)
    {
        a[u][v]=a[u][v]-node(1,w);a[v][u]=a[v][u]-node(1,w);
        a[u][u]=a[u][u]+node(1,w);a[v][v]=a[v][v]+node(1,w);
    }
    int gauss(int n)
    {
        int fl=1;
        for(int i=1;i<n;i++)
        {
            int u=i;
            for(int j=i;j<n;j++)
            if(a[j][i].x){u=j;break;}
            if(u!=i) swap(a[i],a[u]),fl*=-1;
            node iv=inv(a[i][i]);
            for(int j=i+1;j<n;j++)
            {
                node v=a[j][i]*iv;
                for(int k=i;k<n;k++) a[j][k]=a[j][k]-a[i][k]*v;
            }
        }
        node u=1;
        for(int i=1;i<n;i++) u=u*a[i][i];
        return fl==1?u.y:(mod-u.y)%mod;
    }
    void clear(){memset(a,0,sizeof(a));}
}g;
int f[N],n,m;
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int x[N*N],y[N*N],w[N*N];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int solve(int d)
{
    for(int i=1;i<=n;i++) f[i]=i;
    int p=0;
    for(int i=1;i<=m;i++)
    if(w[i]%d==0) f[find(x[i])]=find(y[i]),p=gcd(p,w[i]);
    if(p!=d) return -1;
    for(int i=2;i<=n;i++)
    if(find(i)!=find(i-1)) return -1;
    g.clear();
    for(int i=1;i<=m;i++)
    if(w[i]%d==0) g.add(x[i],y[i],w[i]);
    return g.gauss(n);
}
#define M 200010
bool pr[M];
int p[M],pt,mu[M];
int h[M];
void init(int n=M-10)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]) p[++pt]=i,mu[i]=-1;
        for(int j=1;j<=pt && i*p[j]<=n;j++)
        {
            pr[i*p[j]]=true;
            if(i%p[j]==0){mu[i*pr[j]]=0;break;}
            mu[i*p[j]]=mod-mu[i];
        }
    }
}
int main()
{
    init();
    scanf("%d%d",&n,&m);
    int mx=0;
    for(int i=1;i<=m;i++) scanf("%d%d%d",&x[i],&y[i],&w[i]),mx=max(mx,w[i]);
    int ans=0;
    for(int i=mx;i;i--)
    {
        h[i]=solve(i);
        if(h[i]==-1){h[i]=0;continue;}
        for(int j=2*i;j<=mx;j+=i) h[i]=(h[i]-h[j]+mod)%mod;
        ans=(ans+1ll*i*h[i])%mod;
    }
    printf("%d\n",ans);
    return 0;
}