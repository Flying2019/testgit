#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
#define ll long long
using namespace std;
int n;
void reset(int);
struct SQ{
    int a[N],p[N];
    int l,r,D;
    void init(int x[])
    {
        l=1,r=n,D=0;
        for(int i=1;i<=n;i++) a[x[i]]=i,p[i]=x[i];
    }
    void moveL(int k)
    {
        D-=k;
        while(l<r && D<1-l) reset(a[++l]);
        if(D<1-l) D=1-l;
    }
    void moveR(int k)
    {
        D+=k;
        while(l<r && D>n-r) reset(a[--r]);
        if(D>n-r) D=n-r;
    }
    int operator [](int x){return min(max(p[x],l),r)+D;}
}X,Y;
int c[4];
bool on[N];
void reset(int a)
{
    if((X.p[a]>X.l && X.p[a]<X.r) || (Y.p[a]>Y.l && Y.p[a]<Y.r) || on[a]) return;
    on[a]=true;
    int p=(X.p[a]<=X.l?0:1)^(Y.p[a]<=Y.l?0:2);
    c[p]++;
}
int x[N],y[N];
ll C[N];
ll qry()
{
    if(X.l==X.r && Y.l==Y.r) return C[c[0]+c[1]+c[2]+c[3]];
    if(X.l==X.r) return C[c[0]+c[1]]+C[c[2]+c[3]];
    if(Y.l==Y.r) return C[c[0]+c[2]]+C[c[1]+c[3]];
    return C[c[0]]+C[c[1]]+C[c[2]]+C[c[3]];
}
int main()
{
    for(int i=0;i<N-1;i++) C[i]=1ll*i*(i-1)/2;
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int q;
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
        X.init(x);Y.init(y);
        for(int i=1;i<=n;i++) reset(i);
        while(q --> 0)
        {
            char op[3];int k;
            scanf("%s",op);
            if(op[0]=='!'){printf("%lld\n",qry());continue;}
            else
            {
                scanf("%d",&k);
                if(op[0]=='U') X.moveL(k);
                if(op[0]=='D') X.moveR(k);
                if(op[0]=='L') Y.moveL(k);
                if(op[0]=='R') Y.moveR(k);
                if(op[0]=='?') printf("%d %d\n",X[k],Y[k]);
            }
        }
        for(int i=1;i<=n;i++) on[i]=false;memset(c,0,sizeof(c));
    }
    return 0;
}