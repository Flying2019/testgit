#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<bitset>
#include<cstdlib>
#include<set>
#include<queue>
#define N 51
#define M N*N
using namespace std;
int id[N][N],tt,n,m;
char mp[N][N];
int L[N][N],R[N][N],U[N][N],D[N][N];
vector<bitset<M> >v[N][N];
void dfs(int x,int y,bitset<M> &b)
{
    if(b.count()==tt){puts("YES");exit(0);}
    for(auto p:v[x][y])
    if((p&b)==b) return;
    int sz=0;
    for(int i=0;i<v[x][y].size();i++)
    if((v[x][y][i]|b)!=b) v[x][y][sz++]=v[x][y][i];
    v[x][y].resize(sz);
    v[x][y].push_back(b);
    bitset<M> c=b;
    if(L[x][y]!=y)
    {
        for(int i=L[x][y];i<y;i++)
        if(~id[x][i]) c.set(id[x][i]);
        dfs(x,L[x][y],c);
        c=b;
    }
    if(R[x][y]!=y)
    {
        for(int i=R[x][y];i>y;i--)
        if(~id[x][i]) c.set(id[x][i]);
        dfs(x,R[x][y],c);
        c=b;
    }
    if(U[x][y]!=x)
    {
        for(int i=U[x][y];i<x;i++)
        if(~id[i][y]) c.set(id[i][y]);
        dfs(U[x][y],y,c);
        c=b;
    }
    if(D[x][y]!=x)
    {
        for(int i=D[x][y];i>x;i--)
        if(~id[i][y]) c.set(id[i][y]);
        dfs(D[x][y],y,c);
    }
}
int main()
{
    memset(id,-1,sizeof(id));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        if(mp[i][j]=='*') id[i][j]=tt++;
    int X=0,Y=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        if(mp[i][j]=='O') X=i,Y=j;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        if(mp[i][j]=='#') continue;
        else L[i][j]=!L[i][j-1]?j:L[i][j-1];
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
        if(mp[i][j]=='#') continue;
        else R[i][j]=!R[i][j+1]?j:R[i][j+1];
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++)
        if(mp[i][j]=='#') continue;
        else U[i][j]=!U[i-1][j]?i:U[i-1][j];
    for(int j=1;j<=m;j++)
        for(int i=n;i>=1;i--)
        if(mp[i][j]=='#') continue;
        else D[i][j]=!D[i+1][j]?i:D[i+1][j];
    bitset<M>o;
    dfs(X,Y,o);
    puts("NO");
    return 0;
}