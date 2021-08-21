#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_map>
#include<cassert>
using namespace std;
const int N=12,M=1501,mod=998244353;
const double alp=0.7;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
double rand0(){return 1.0*rand()/RAND_MAX;}
struct matrix{
    int a[N+2][N+2],v,b[N+2][N+2];
    void add(int u,int v){b[u][v]--;b[v][u]--;b[u][u]++;b[v][v]++;a[u][v]=a[v][u]=true;}
    int gauss(int n)
    {
        int fl=1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) b[i][j]=(b[i][j]+mod)%mod;
        for(int i=1;i<n;i++)
        {
            int p=i;
            for(;p<n && !b[p][i];p++);
            if(p!=i){swap(b[p],b[i]);fl=mod-fl;}
            int r=ksm(b[i][i]);
            for(int j=i+1;j<n;j++)
            {
                int v=1ll*b[j][i]*r%mod;
                for(int k=i;k<n;k++) b[j][k]=(b[j][k]-1ll*b[i][k]*v%mod+mod)%mod;
            }
        }
        for(int i=1;i<n;i++) fl=1ll*fl*b[i][i]%mod;
        return fl;
    }
    void rand_graph(int n=N)
    {
        for(int i=2;i<=n;i++)
            add(rand()%(i-1)+1,i);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++) if(!a[i][j] && rand0()>alp) add(i,j);
        v=gauss(n);
    }
}t[M];
struct node{
    int x,y;
    node(int X=0,int Y=0):x(X),y(Y){}
};
unordered_map<int,node>s;
void init(int n=M-1)
{
    for(int i=1;i<=n;i++) t[i].rand_graph(),assert(t[i].v);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
        s[1ll*t[i].v*t[j].v%mod]=node(i,j);
}
int rx[M],ry[M],rt;
void print(matrix &a,int v,int n=N){for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(a.a[i][j]) ++rt,rx[rt]=i+v,ry[rt]=j+v;}
int main()
{
    srand(1019260817);
    int T;
    scanf("%d",&T);
    init();
    while(T --> 0)
    {
        int k;scanf("%d",&k);
        if(k==0){puts("2 0");continue;}
        if(k==1){puts("1 0");continue;}
        rt=0;
        bool can=true;
        for(int i=1;i<M && can;i++)
            for(int j=i+1;j<M && can;j++)
            {
                int v=ksm(1ll*t[i].v*t[j].v%mod);
                if(!s.count(1ll*v*k%mod)) continue;
                node w=s[1ll*v*k%mod];
                print(t[i],0);print(t[j],N);
                print(t[w.x],2*N);print(t[w.y],3*N);
                // printf("%d %d %d %d\n",i,j,w.x,w.y);
                // printf("%d %d %d %d\n",t[i].v,t[j].v,t[w.x].v,t[w.y].v);
                ++rt,rx[rt]=1,ry[rt]=N+1;
                ++rt,rx[rt]=1,ry[rt]=2*N+1;
                ++rt,rx[rt]=1,ry[rt]=3*N+1;
                printf("%d %d\n",4*N,rt);
                for(int i=1;i<=rt;i++) printf("%d %d\n",rx[i],ry[i]);
                can=false;
            }
    }
    return 0;
}