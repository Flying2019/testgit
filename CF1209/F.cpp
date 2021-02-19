#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 1100010
#define mod 1000000007
using namespace std;
vector<int>g[N][10];
int val[N],pre[N],idn;
bool vis[N];
void add(int u,int v,int c)
{
    while(c>=10) g[++idn][c%10].push_back(v),v=idn,c/=10;
    g[u][c%10].push_back(v);
}
queue<vector<int> >q;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);idn=n;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y,i);add(y,x,i);
    }
    q.push({1});val[1]=0;vis[1]=true;
    while(!q.empty())
    {
        auto x=q.front();q.pop();
        for(int i=0;i<10;i++)
        {
            vector<int>sw;sw.clear();
            for(int u:x)
                for(int v:g[u][i])
                if(!vis[v]) vis[v]=true,val[v]=(10ll*val[u]+i)%mod,sw.push_back(v);
            if(!sw.empty()) q.push(sw);
        }
    }
    for(int i=2;i<=n;i++) printf("%d\n",val[i]);
    return 0;
}