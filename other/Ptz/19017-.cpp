#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#define il inline
using namespace std;
typedef vector<int> vec;
const int N=300010,mod=998244353,mod1=1019260817,mod2=1000000007;
int ksm(int a,int b,int mod)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
struct node{
    int x,y;
    node(int X,int Y):x(X),y(Y){}
    node(int X=0):x(X),y(X){}
};
node operator +(const node &a,const node &b){return node((a.x+b.x)%mod1,(a.y+b.y)%mod2);}
node operator -(const node &a,const node &b){return node((a.x-b.x+mod1)%mod1,(a.y-b.y+mod2)%mod2);}
node operator *(const node &a,const node &b){return node(1ll*a.x*b.x%mod1,1ll*a.y*b.y%mod2);}
node operator /(const node &a,const node &b){return node(1ll*a.x*ksm(b.x,mod1-2,mod1)%mod1,1ll*a.y*ksm(b.y,mod2-2,mod2)%mod2);}
bool operator ==(const node &a,const node &b){return a.x==b.x && a.y==b.y;}
node base=2333;
const double alp=0.8;
int fa[N],ff[N],dep[N],son[N],siz[N],iv[N];
vec g[N];
node Ha[N],Hdep[N];
map<node,int>w[N];int f[N];
struct tree_a{
    vec t;
    void ins(int x,int v){for(;x;x-=(x&(-x))) t[x-1]=1ll*t[x-1]*v%mod;}
    void push(vec &u){for(int v:u) t.push_back(1),ins(t.size(),v);}
    int qry(int x){int v=1;for(;x<=t.size();x+=(x&(-x))) v=1ll*v*t[x-1]%mod;return v;}
};
inline node Hash_dep(int u){return Ha[u]*Hdep[dep[u]];}
void dec_fa(int x)
{
    int p=fa[x];
    if(!p) return;
    f[p]=1ll*f[p]*iv[w[p][f[x]]]%mod;
    w[p][f[x]]--;
}
void add(int x)
{
    for(;x;x=fa[ff[x]])
    {
        siz[x]++;
    }
}
void init(int n=N-9)
{
    iv[1]=1;
    for(int i=2;i<=n;i++) iv[i]=1ll*(mod-mod/i)*iv[mod%i]%mod;
}
int main()
{

    int n=1,m;dep[1]=1;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int t,x;scanf("%d%d",&t,&x);
        if(t==0)
        {
            ++n;g[x].push_back(n);
            fa[n]=x;ff[n]=n;f[n]=1;
            dep[n]=dep[x]+1;
        }
    }
    return 0;
}