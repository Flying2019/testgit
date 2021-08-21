#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200010
#define MP make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int M=30;
int x[N],y[N],f[N],n;
vector<int>r[M+2];
vector<P>e,tmp;
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
bool merge(int x,int y)
{
    x=find(x),y=find(y);
    if(x>n) swap(x,y);
    if(x==y) return false;
    f[x]=y;if(x>n && y>n) e.push_back(MP(x-n,y-n));
    return true;
}
ll ans[N],g[N];
int main()
{
    int k,m;
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=m;i++)
    {
        int w;
        scanf("%d%d%d",&x[i],&y[i],&w);
        for(int j=w;j<=M;j++) r[j].push_back(i);
    }
    for(int t=0;t<=M;t++)
    {
        for(int i=1;i<=2*n;i++) f[i]=i;
        for(int i=0;i<=m;i++) g[i]=0;
        for(int d:r[t]) g[1]+=merge(x[d],y[d]+n);
        for(int i=2;i<=k;i++)
        {
            g[i]=g[i-1];tmp=e,e.clear();
            for(P v:tmp) g[i]-=!merge(v.fi,v.se);
        }
        for(int i=1;i<=k;i++) g[i]+=g[i-1],ans[i]+=1ll*n*(i+1)-1-g[i];
    }
    for(int i=1;i<=k;i++) printf("%lld\n",ans[i]);
    return 0;
}