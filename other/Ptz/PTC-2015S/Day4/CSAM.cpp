#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define N 400010
#define fi first
#define se second
#define ll long long
#define pb push_back
using namespace std;
struct road{int v,w;};
#define mod1 1000000007
#define mod2 1000000009
#define il inline
struct P{
    int x,y;
    P(int X,int Y):x(X),y(Y){}
    P(int X=0):x((X+mod1)%mod1),y((X+mod2)%mod2){}
};
const int base=2607;
il int Add(int x,int y,int m){return x+y>=m?x+y-m:x+y;}
il int Dec(int x,int y,int m){return x-y<0?x-y+m:x-y;}
il P operator +(P a,P b){return P(Add(a.x,b.x,mod1),Add(a.y,b.y,mod2));}
il P operator -(P a,P b){return P(Dec(a.x,b.x,mod1),Dec(a.y,b.y,mod2));}
il P operator -(P a){return P(Dec(0,a.x,mod1),Dec(0,-a.y,mod2));}
il P operator *(P a,P b){return P(1ll*a.x*b.x%mod1,1ll*a.y*b.y%mod2);}
il bool operator ==(P a,P b){return a.x==b.x && a.y==b.y;}
struct astr{
    string s;P hs;
    astr(){}
    astr(string &t)
    {
        s=t;int n=s.size();
        for(int i=0;i<n;i++) hs=hs*base+(s[i]-'a');
    }
};
struct hashton{
    #define MX N*20
    astr w[N];
    int id[MX],tt;
};
struct CSAM{
    string ed[N];
    vector<road> g[N];
    int tot;
    //ed : 最长的字符串，g : 边/边权，tot : 总点数
    int len[N],fa[N],las=1,cnt=1;
    map<char,int>ch[N];
    int insert(char c)
    {
        int p=las,q=las=++cnt;
        len[q]=len[p]+1;
        for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
        if(!p) fa[q]=1;
        else{
            int np=ch[p][c];
            if(len[np]==len[p]+1) fa[q]=np;
            else{
                int nq=++cnt;
                len[nq]=len[p]+1;fa[nq]=fa[np];ch[nq]=ch[np];
                fa[np]=fa[q]=nq;
                for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
            }
        }
        return q;
    }
    int dis[N],mdis[N],id[N];
    vector<int>e[N];int to[N];
    queue<int>q;
    void dfs(int u,int t,string &s){if(u==t) return;for(auto v:ch[u]) s.pb(v.fi),dfs(v.se,t,s);}
    void init(char s[],int n)
    {
        for(int i=1;i<=n;i++) insert(s[i]);
        id[1]=id[las]=1;
        for(int i=1;i<=cnt;i++)
        {
            if(ch[i].size()!=1 || id[i]) id[i]=++tot;
            to[i]=i;
        }
    }
    void comp()
    {
        for(int i=1;i<=cnt;i++)
        if(!id[i]) for(auto u:ch[i])
            if(!id[u.se]) e[u.se].push_back(i);
            else q.push(i),dis[i]=1,to[i]=u.se;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int v:e[u]) if(!id[v]) q.push(v),dis[v]=dis[u]+1,to[v]=to[u];
        }
        for(int i=1;i<=cnt;i++) if(!id[i]) mdis[to[i]]=max(mdis[to[i]],dis[i]);
        for(int i=1;i<=cnt;i++)
        if(id[i])
            for(auto u:ch[i])
            {
                if(mdis[to[u.se]]==dis[u.se] && ed[id[to[u.se]]].empty())
                    dfs(u.se,to[u.se],ed[id[to[u.se]]]=u.fi);
                g[id[i]].push_back((road){id[to[u.se]],dis[u.se]+1});
            }
    }
    void reset()
    {
        for(int i=1;i<=cnt;i++) to[i]=dis[i]=mdis[i]=fa[i]=id[i]=0,ch[i].clear(),e[i].clear();
        for(int i=1;i<=tot;i++) g[i].clear(),ed[i].clear();
        las=cnt=1;tot=0;
    }
}l,r;
char s[N];
int main()
{
    scanf("%s",s+1);
}