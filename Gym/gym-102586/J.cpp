#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#define N 300010
#define mod 1000000007
using namespace std;
const int Len(const int x){return 31-__builtin_clz(x);}
int op;
int calc(int x,int p)
{
    int y=x&((1<<p)-1);
    if(op&(1<<((x>>p)&7))) y|=1<<p;
    return y|(x>>(p+3))<<(p+1);
}
map<int,bool>hv;
bool dfs(int x)
{
    int len=Len(x);
    if(len%2==0) return false;
    if(len==1) return x&1;
    if(hv.count(x)) return hv[x];
    for(int i=0;i+2<len;i++) if(dfs(calc(x,i))) return hv[x]=true;
    return hv[x]=false;
}
bool same(int x,int y,int l)
{
    for(int i=0;i<l;i++)
        for(int j=0;j<1<<i;j++)
        if(dfs(x<<i|j)!=dfs(y<<i|j)) return false;
    return true;
}
struct DFA{
    struct node{
        vector<pair<int,int>>to;
        bool las;
    };
    vector<node> g;
}d;
void init(int l=10)
{
    vector<int>V;
    queue<int>q;q.push(1);
    map<int,int>id;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        bool sm=false;
        for(int v:V) if(same(u,v,l)){id[u]=id[v];sm=true;break;}
        if(sm) continue;
        id[u]=V.size();
        V.push_back(u);
        q.push(u<<1),q.push(u<<1|1);
    }
    int n=V.size();
    d.g.resize(n);
    for(int i=0;i<n;i++)
    {
        d.g[i].to.push_back({0,id[V[i]<<1]});
        d.g[i].to.push_back({1,id[V[i]<<1|1]});
        if(dfs(V[i])) d.g[i].las=true;
    }
}
char s[8],t[N];
void solve()
{
    scanf("%s%s",s,t+1);
    int n=strlen(t+1);op=0;
    for(int i=0;i<8;i++) op|=(s[i]-'0')<<i;
    init();
    int m=d.g.size();
    vector<int> f(m);
    f[0]=1;
    for(int _=n;_;_--)
    {
        vector<int>g(m);
        char c=t[_];
        for(int i=0;i<m;i++)
            for(auto v:d.g[i].to)
            if(!((c=='0' && v.first==1) || (c=='1' && v.first==0))) g[v.second]=(g[v.second]+f[i])%mod;
        f=g;
    }
    int ans=0;
    for(int i=0;i<m;i++) if(d.g[i].las) ans=(ans+f[i])%mod;
    printf("%d\n",ans);
}
void clear(){d=DFA();hv.clear();op=0;}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0) solve(),clear();
    return 0;
}