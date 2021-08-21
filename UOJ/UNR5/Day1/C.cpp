#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
#define N 100010
using namespace std;
int fa[N],n;
vector<int>g[N];
vector<int>t,a,tt;
bool vdfs()
{
    set<vector<int> >s;
    queue<vector<int> >q;
    tt.resize(n);
    for(int i=0;i<n;i++) tt[t[i]]=i;
    q.push(t);
    s.clear();
    while(!q.empty())
    {
        auto u=q.front();q.pop();
        if(t==a) return true;
        for(int i=1;i<n;i++)
        {
            swap(u[i],u[fa[i]]);
            if(!s.count(u)) s.insert(u),q.push(u);
        }
    }
    return false;
}
void dfs(int u)
{
    t.push_back(u);
    if(t.size()==n)
    {
        if(vdfs()){for(int i=0;i<n;i++) printf("%d\n",tt[i]);exit(0);}
        return;
    }
    int id[8];
    for(int i=0;i<g[u].size();i++) id[i]=i;
    do
    {
        for(int i=0;i<g[u].size();i++)
            dfs(g[u][id[i]]);
    } while(next_permutation(id,id+g[u].size()));
    t.pop_back();
}
int main()
{
    int typ;
    scanf("%d%d",&typ,&n);
    a.resize(n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    fa[0]=-1;
    for(int i=1;i<n;i++) scanf("%d",&fa[i]),--fa[i],g[fa[i]].push_back(i);
    dfs(0);
    puts("-1");
    return 0;
}