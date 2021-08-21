#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#define N 400010
#define fi first
#define se second
#define ll long long
using namespace std;
struct road{int v,w;};
namespace SAM{
    int fa[N],ch[N][26],len[N],las=1,cnt=1;
    int insert(int c)
    {
        int p=las,q=las=++cnt;
        len[q]=len[p]+1;
        for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
        if(!p) fa[q]=1;
        else
        {
            int np=ch[p][c];
            if(len[np]==len[p]+1) fa[q]=np;
            else
            {
                int nq=++cnt;
                len[nq]=len[p]+1;
                fa[nq]=fa[np];
                memcpy(ch[nq],ch[np],sizeof(ch[np]));
                fa[np]=fa[q]=nq;
                for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
            }
        }
        return len[q]-len[fa[q]];
    }
    void reset(){for(int i=1;i<=cnt;i++) memset(ch[i],0,sizeof(ch[i])),fa[i]=0;cnt=las=1;}
}
namespace bidsam{
    map<char,int>ch[N];
    int len[N],fa[N],las=1,cnt=1;
    int insert(char c)
    {
        int p=las,q=las=++cnt;
        len[q]=len[p]+1;
        for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
        if(!p) fa[q]=1;
        else
        {
            int np=ch[p][c];
            if(len[np]==len[p]+1) fa[q]=np;
            else
            {
                int nq=++cnt;
                len[nq]=len[p]+1;
                fa[nq]=fa[np];ch[nq]=ch[np];
                fa[np]=fa[q]=nq;
                for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
            }
        }
        return q;
    }
    int dis[N],mdis[N];bool rem[N];
    vector<int>e[N];int to[N];
    queue<int>q;
    string ed[N];
    vector<road> g[N];
    void dfs(int u,int t,string &s)
    {
        if(u==t) return;
        for(auto v:ch[u]) s.push_back(v.fi),dfs(v.se,t,s);
    }
    void init(char s[],int n)
    {
        for(int i=1;i<=n;i++) insert(s[i]);
        for(int i=1;i<=cnt;i++) rem[i]=ch[i].size()!=1,to[i]=i;
        rem[1]=rem[las]=true;
        for(int i=1;i<=cnt;i++)
        if(!rem[i]) for(auto u:ch[i])
            if(!rem[u.se]) e[u.se].push_back(i);
            else q.push(i),dis[i]=1,to[i]=u.se;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int v:e[u])
            if(!rem[v]) q.push(v),dis[v]=dis[u]+1,to[v]=to[u];
        }
        for(int i=1;i<=cnt;i++) if(!rem[i]) mdis[to[i]]=max(mdis[to[i]],dis[i]);
        for(int i=1;i<=cnt;i++)
        if(rem[i])
            for(auto u:ch[i])
            {
                if(mdis[to[u.se]]==dis[u.se] && ed[to[u.se]].empty())
                    dfs(u.se,to[u.se],ed[to[u.se]]=u.fi);
                g[i].push_back((road){to[u.se],dis[u.se]+1});
            }
        // printf("%d\n",cnt);
        // for(int i=1;i<=cnt;i++) printf("%d ",rem[i]);
        // puts("");
        // for(int i=1;i<=cnt;i++)
        // if(rem[i]) cout<<ed[i]<<endl;
        // for(int i=1;i<=cnt;i++)
        // {
        //     printf("%d -> ",i);
        //     for(auto j:ch[i]) printf("%d ",j.se);
        //     puts("");
        // }
        // for(int i=1;i<=cnt;i++)
        // if(rem[i])
        // {
        //     printf("%d -> ",i);
        //     for(auto j:g[i]) printf("%d,%d ",j.v,j.w);
        //     puts("");
        // }
    }
    void reset()
    {
        for(int i=1;i<=cnt;i++)
            to[i]=dis[i]=mdis[i]=fa[i]=rem[i]=0,ch[i].clear(),e[i].clear(),ed[i].clear(),g[i].clear();
        las=cnt=1;
    }
}
using bidsam::ed;
using bidsam::g;
using bidsam::cnt;
using bidsam::rem;
queue<int>q;
int way[N],tt[N];//路径数
vector<road>rg[N];
void initway()
{
    for(int u=1;u<=cnt;u++)
    if(rem[u]) for(auto v:g[u]) rg[v.v].push_back((road){u,v.w});
    for(int u=1;u<=cnt;u++) tt[u]=rg[u].size();
    q.push(1);way[1]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(auto v:g[u])
        {
            way[v.v]+=way[u];
            if(!(--tt[v.v])) q.push(v.v);
        }
    }
}
void clear()
{
    for(int i=1;i<=cnt;i++) rg[i].clear(),way[i]=tt[i]=0;
    bidsam::reset();
}
void work()
{
    ll ans=0;
    initway();
    for(int i=1;i<=cnt;i++) if(rem[i])
    {
        SAM::reset();
        int m=ed[i].size();ll res=0;
        sort(rg[i].begin(),rg[i].end(),[&](road a,road b)->bool{return a.w<b.w;});
        // printf("%d : ",i);cout<<ed[i]<<endl;
        auto u=rg[i].begin();
        for(int j=m-1;j>=0;j--)
        {
            res+=SAM::insert(ed[i][j]-'a');
            for(;u!=rg[i].end() && u->w==m-j;u++) ans+=way[u->v]*res;
            // printf("%d ",res);
        }
        // puts("");
    }
    printf("%lld\n",ans);
}
char s[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        scanf("%s",s+1);
        int n=strlen(s+1);
        bidsam::init(s,n);
        work();
        clear();
    }
    return 0;
}