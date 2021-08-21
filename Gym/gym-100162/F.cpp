#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 510
#define M 4010
#define inf 100000000
using namespace std;
char s1[N],s2[N];
vector<int>g1[N],g2[N];
struct answ{
    int w,s,t;
    answ(int W=0,int S=0,int T=0):w(W),s(S),t(T){}
    bool operator <(const answ a)const{return w<a.w;}
}f[N][N];
answ dfs(int s,int t)
{
    if(s1[s]!=s2[t]) return 0;
    if(~f[s][t].w) return answ(f[s][t].w,s,t);
    f[s][t]=answ(inf,s,t);answ res;
    for(int v:g1[s])
        for(int w:g2[t]) res=max(res,dfs(v,w));
    f[s][t]=answ(res.w+1,res.s,res.t);
    return answ(f[s][t].w,s,t);
}
int main()
{
    int n,m,T=0;
    while(cin>>n>>m)
    {
        memset(f,-1,sizeof(f));
        scanf("%s",s1+1);
        for(int i=1;i<=m;i++)
        {
            int u,v;scanf("%d%d",&u,&v);
            g1[u].push_back(v);
        }
        int n0,m0;
        scanf("%d%d%s",&n0,&m0,s2+1);
        for(int i=1;i<=m0;i++)
        {
            int u,v;scanf("%d%d",&u,&v);
            g2[u].push_back(v);
        }
        answ ans;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n0;j++) ans=max(ans,dfs(i,j));
        printf("Case %d: %d\n",++T,ans.w>=inf?-1:ans.w);
        for(int i=1;i<=n;i++) g1[i].clear();
        for(int i=1;i<=n0;i++) g2[i].clear();
        if(ans.w<inf)
        {
            vector<int>a1,a2;
            for(int i=ans.w;i;i--)
            {
                a1.push_back(ans.s),a2.push_back(ans.t);
                ans=f[ans.s][ans.t];
            }
            for(int v:a1) printf("%d ",v);puts("");
            for(int v:a2) printf("%d ",v);puts("");
        }
    }
    return 0;
}