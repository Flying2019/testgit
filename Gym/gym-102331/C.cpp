#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define mod 998244353
#define il inline
using namespace std;
const int N=13,M=1<<N,iv2=(mod+1)/2;
int f[M][N][N],g[M][N],h[M][N],n;
//f_{s,i,j}:主链 i -> j，s 集合已经包含(i,j\not\in s)，且 j 是新增的点
//g_{s,i}:以 i 为根，包含 s 的子仙人掌(i\not\in s)
//h_{s,i}:以 i 为根的答案(i\not\in s)
bool mp[N][N];
il int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il void addi(int &x,int y){x=add(x,y);}
int F(int,int,int);int G(int,int);int H(int,int);
int F(int s,int x,int y)
{
    if(~f[s][x][y]) return f[s][x][y];
    int &r=f[s][x][y];r=0;
    for(int i=0;i<n;i++)
    if(mp[y][i])
    {
        if(i==x){addi(r,H(s,y));continue;}
        if(s>>i&1) for(int t=s;t;t=(t-1)&s) if(t>>i&1) addi(r,1ll*H(s^t,y)*F(t^(1<<i),x,i)%mod);
    }
    return r;
}
int G(int s,int x)
{
    if(~g[s][x]) return g[s][x];
    int &r=g[s][x];r=0;
    for(int i=0;i<n;i++) if(mp[x][i] && s>>i&1) addi(r,(F(s^(1<<i),x,i)+H(s^(1<<i),i))%mod);
    return r=1ll*r*iv2%mod;
}
int H(int s,int x)
{
    if(~h[s][x]) return h[s][x];
    int &r=h[s][x],p=s&(-s);r=0;
    for(int t=s;t;t=(t-1)&s) if(t&p) addi(r,1ll*G(t,x)*H(t^s,x)%mod);
    return r;
}
int main()
{
    memset(f,-1,sizeof(f));memset(g,-1,sizeof(g));memset(h,-1,sizeof(h));
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);--u;--v;
        mp[u][v]=mp[v][u]=true;
    }
    int S=(1<<n)-1;
    for(int i=0;i<n;i++) h[0][i]=1;
    printf("%d\n",H(S-1,0));
    return 0;
}