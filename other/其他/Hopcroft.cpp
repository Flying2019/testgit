#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#define N 1010
#define M 1010
using namespace std;
struct DFA{
    vector<vector<int> >link;int q0;
    vector<int>ed;
    DFA(int n=1,int m=0,int q=0){q0=q;link.resize(n);for(int i=0;i<n;i++) link[i].resize(m,-1);}
};
namespace Hopcroft{
    int id[N],cut[N];set<int>s[N];
    bool vis[N];
    DFA minimize(DFA &a)
    {
        int n=a.link.size(),m=a.link[0].size();
        for(int i=0;i<n;i++) id[i]=0;
        for(int u:a.ed) id[u]=1;
        for(int i=0;i<n;i++) s[id[i]].insert(i);
        int tt=2;
        set<int>w({1});
        while(!w.empty())
        {
            int u=*w.begin();w.erase(u);
            if(tt>n) throw;
            for(int c=0;c<m;c++)
            {
                for(int i=0;i<n;i++) vis[i]=(~a.link[i][c] && id[a.link[i][c]]==u);
                for(int i=0;i<tt;i++) cut[i]=0;
                for(int i=0;i<n;i++) if(vis[i]) cut[id[i]]++;
                for(int i=0;i<tt;i++)
                if(cut[i] && cut[i]!=s[i].size())
                {
                    if(w.count(i)) w.insert(tt);
                    else w.insert(i);
                    if(cut[i]*2>=s[i].size())
                    {
                        vector<int>p;p.reserve(cut[i]);
                        for(int u:s[i]) if(vis[u]) s[id[u]=tt].insert(u),p.push_back(u);
                        for(int i:p) s[i].erase(u);
                    }
                    else
                    {
                        vector<int>p;p.reserve(s[i].size()-cut[i]);
                        for(int u:s[i]) if(!vis[u]) s[id[u]=tt].insert(u),p.push_back(u);
                        for(int u:p) s[i].erase(u);
                    }
                    ++tt;
                }
            }
        }
        DFA ans(tt,m,id[a.q0]);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            if(~a.link[i][j]) ans.link[id[i]][j]=id[a.link[i][j]];
        for(int i=0;i<tt;i++) vis[i]=false;
        for(int u:a.ed) vis[id[u]]=true;
        for(int i=0;i<tt;i++) if(vis[i]) ans.ed.push_back(i);
        return ans;
    }
}
bool run(DFA &q,vector<int>v)
{
    int u=q.q0;
    for(int c:v)
    if(~q.link[u][c]) return false;
    else u=q.link[u][c];
    for(int d:q.ed) if(u==d) return true;
    return false;
}
using Hopcroft::minimize;
int main()
{
    int n,m,c,q,w;
    scanf("%d%d%d%d",&n,&m,&c,&w);
    scanf("%d",&q);q--;
    DFA o(n,c,q);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        --u;--v,--w;o.link[u][w]=v;
    }
    o.ed.resize(w);
    for(int i=0,a;i<w;i++) scanf("%d",&a),o.ed[i]=a-1;
    o=minimize(o);
    n=o.link.size();
    printf("%d %d\n",n,o.q0+1);
    for(int i=0;i<n;i++)
        for(int j=0;j<c;j++)
        if(~o.link[i][j]) printf("%d %d %d\n",i+1,o.link[i][j]+1,j+1);
    for(int u:o.ed) printf("%d ",u);
    return 0;
}