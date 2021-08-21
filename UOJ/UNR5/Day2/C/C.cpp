#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstring>
#include "airline.h"
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
#define N 2010
ll tf[N],f[N],g[N][N];
ll solve(int n, int x, int y, int q, vector<int> P, int L)
{
    P.push_back(x);P.push_back(y);
    for(int i=0;i<q+2;i++)
        for(int j=i+1;j<q+2;j++) g[i][j]=g[j][i]=distance(P[i],P[j]);
    f[q]=g[q+1][0],f[q+1]=g[q][0];
    for(int i=1;i<q;i++)
    {
        for(int j=0;j<q+2;j++) tf[j]=f[j],f[j]=0;
        for(int j=0;j<q+2;j++) f[i-1]=max(f[i-1],tf[j]+g[j][i]),f[j]=max(f[j],tf[j]+g[i-1][i]);
    }
    ll ans=0;
    for(int j=0;j<q+2;j++) ans=max(ans,f[j]);
    return ans;
}