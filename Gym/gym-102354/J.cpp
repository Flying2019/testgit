#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
#define pb push_back
#define S(x) ((int)x.size())
#define MP make_pair
#define fi first
#define se second
using namespace std;
int n;
vector<int>g[N];
namespace Root{
    int siz[N],mx,rt;
    void dfs(int u,int p)
    {
        siz[u]=1;
        int mr=0;
        for(int v:g[u]) if(v!=p) dfs(v,u),siz[u]+=siz[v],mr=max(mr,siz[v]);
        mr=max(mr,n-siz[u]);
        if(!rt || mx>mr) rt=u,mx=mr;
    }
    int find(){dfs(1,0);return rt;}
}
typedef vector<int> vec;
typedef vector<vec> vvec;
typedef pair<string,vec> pvec;
vvec ans;
void add(const vec &a,const vec &b)
{
    vec c(n);
    for(int i=0;i<n;i++) c[i]=i+1;
    for(int i=0;i<S(a);i++) swap(c[a[i]-1],c[b[i]-1]);
    ans.pb(c);
}
void operator +=(vec &a,const vec &b){for(int d:b) a.pb(d);}
pvec dfs(int u,int p)
{
    vector<pvec> son;
    for(int v:g[u]) if(v!=p) son.push_back(dfs(v,u));
    sort(son.begin(),son.end());
    for(int i=0;i<S(son);i++)
        for(int j=i+1;j<S(son) && son[i].fi==son[j].fi;i++,j++) add(son[i].se,son[j].se);
    pvec a;
    a.se.pb(u);
    for(auto v:son) a.fi+="0"+v.fi+"1",a.se+=v.se;
    return a;
}
int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].pb(v),g[v].pb(u);
    int u=Root::find();Root::dfs(u,0);
    bool only=true;
    for(int v:g[u])
    if(Root::siz[v]*2==n)
    {
        auto f=dfs(u,v),g=dfs(v,u);
        if(f.fi==g.fi) add(f.se,g.se);
        only=false;break;
    }
    if(only) dfs(u,0);
    if(ans.empty()) add(vec(),vec());
    printf("%d\n",S(ans));
    for(auto p:ans)
    {
        for(auto x:p) printf("%d ",x);
        puts("");
    }
    return 0;
}