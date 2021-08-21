#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
using namespace std;
const int mod1=1019260817,mod2=1000000007;
int ksm(int a,int b,int mod)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
const int B=2333;
struct node{
    int x,y;
    node(int X,int Y):x(X),y(Y){}
    node(int X=0):x(X),y(X){}
};
node iB=node(ksm(B,mod1-2,mod1),ksm(B,mod2-2,mod2));
bool operator ==(node a,node b){return a.x==b.x && a.y==b.y;}
node operator +(node a,node b){return node((a.x+b.x)%mod1,(a.y+b.y)%mod2);}
node operator -(node a,node b){return node((a.x-b.x+mod1)%mod1,(a.y-b.y+mod2)%mod2);}
node operator *(node a,node b){return node(1ll*a.x*b.x%mod1,1ll*a.y*b.y%mod2);}
int b[N*2],a[N];
bool ban[N];
node bs[N*2],ib[N*2],h[N*2];
void pushr(int p){h[p+1]=h[p]+bs[p]*b[p];}
void pushl(int p){h[p]=h[p+1]-bs[p]*b[p];}
node get(int l,int r){return (h[r]-h[l])*ib[l];}
void init(int n=N*2-1){bs[0]=ib[0]=1;for(int i=1;i<=n;i++) bs[i]=bs[i-1]*B,ib[i]=ib[i-1]*iB;}
int main()
{
    init();
    int t;scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1,x;i<=m;i++) scanf("%d",&x),ban[x]=true;
        int l1=N,r1=N,l2=N,r2=N;
        b[l2]=a[1];
        pushr(r1);
        for(int i=2;i<=n;i++)
        {
            b[++r2]=b[--l1]=a[i];
            // for(int i=l1;i<=r1;i++) printf("%d ",b[i]);puts("");
            // for(int i=l2;i<=r2;i++) printf("%d ",b[i]);puts("");
            pushr(r2);pushl(l1);
            // printf("%d %d %d %d\n",l1,r1,l2,r2);
            if(ban[i]) continue;
            int l=1,r=r1-l1+1,x=r1-l1+1;
            // printf("%d %d %d %d\n",get(l1,l1).x,get(l1,l1).y,get(l2,l2).x,get(l2,l2).y);
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(get(l1,l1+mid)==get(l2,l2+mid)) l=mid+1;
                else r=mid-1,x=mid;
            }
            // printf("lcp:%d\n",x-1);
            if(x==r1-l1+1 || b[l1+x-1]<b[l2+x-1]) l2=l1,r2=r1;
            else l1=l2,r1=r2;
        }
        int res=0;
        // for(int i=l2;i<=r2;i++) printf("%d ",b[i]);puts("");
        for(int i=r2;i>=l2;i--) res=(37ll*res+b[i])%20181125;
        printf("Case %d: %d\n",_,res);
        for(int i=N-n;i<=N+n;i++) h[i]=b[i]=0;
        for(int i=1;i<=n;i++) ban[i]=0;
    }
    return 0;
}