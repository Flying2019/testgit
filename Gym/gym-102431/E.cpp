#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#include<algorithm>
#define N 100010
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ldb;
struct O{
    int x,y;
    O(int X=0,int Y=0):x(X),y(Y){}
    bool operator <(const O a)const{return x==a.x?y<a.y:x<a.x;}
};
map<O,vector<int> >f;
O a[N];int id[N],S;
db w[N],D;
int cmp(ldb a,ldb b){return abs(a-b)<=1e-8?0:(a<b?-1:1);}
bool check(O a,O b)
{
    if(abs(a.x-b.x)>=S || abs(a.y-b.y)>=S) return true;
    ll dx=abs(a.x-b.x),dy=abs(a.y-b.y),s0=(S-dx)*(S-dy),s1=1ll*S*S;
    if(dx>=S || dy>=S) return true;
    return cmp(1.0L*s0,1.0L*D*(2*s1-s0))<=0;
}
const int X[]={1,0,-1,0,1,1,-1,-1,0},
          Y[]={0,1,0,-1,1,-1,1,-1,0};
int ans[N],tt;
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        f.clear();
        int n;scanf("%d%d%lf",&n,&S,&D);
        for(int i=1;i<=n;i++) scanf("%d%d%lf",&a[i].x,&a[i].y,&w[i]),id[i]=i;
        sort(id+1,id+n+1,[&](int x,int y){return w[x]>w[y];});
        tt=0;
        for(int i=1;i<=n;i++)
        {
            int u=id[i],x=a[u].x/(S+1),y=a[u].y/(S+1);
            bool can=true;
            for(int t=0;t<9;t++)
            if(f.count(O(x+X[t],y+Y[t])))
            {
                auto &s=f[O(x+X[t],y+Y[t])];
                for(int v:s) if(!check(a[u],a[v])){can=false;break;}
                if(!can) break;
            }
            if(!can) continue;
            ans[++tt]=u;
            f[O(x,y)].push_back(u);
        }
        sort(ans+1,ans+tt+1);
        printf("Case #%d: ",_);
        printf("%d\n",tt);
        for(int i=1;i<=tt;i++) printf("%d ",ans[i]);
        puts("");
    }
    return 0;
}