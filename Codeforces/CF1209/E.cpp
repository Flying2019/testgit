#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 12
#define M 2010
using namespace std;
int f[1<<N],g[1<<N],h[1<<N];
vector<int>a[M];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int j=1;j<=m;j++) a[j].resize(n);
        for(int i=0;i<n;i++)
            for(int j=1;j<=m;j++) scanf("%d",&a[j][i]);
        sort(a+1,a+m+1,[](vector<int>&f,vector<int>&g){return *max_element(f.begin(),f.end())>*max_element(g.begin(),g.end());});
        memset(f,0,sizeof(f));memset(g,0,sizeof(g));
        int S=1<<n;
        for(int i=1;i<=min(n,m);i++)
        {
            for(int j=0;j<n;j++) g[1<<j]=a[i][j];
            for(int s=1;s<S;s++) g[s]=g[s&(-s)]+g[s-(s&(-s))];
            for(int s=1;s<S;s++) h[s]=g[s];
            for(int s=1;s<S;s++)
                for(int t=(s>>1)|((s&1)<<(n-1));t!=s;t=(t>>1)|((t&1)<<(n-1))) h[s]=max(h[s],g[t]);
            for(int s=S-1;~s;s--)
                for(int t=s;t;t=(t-1)&s) f[s]=max(f[s],h[t]+f[s^t]);
        }
        printf("%d\n",f[S-1]);
        for(int j=1;j<=m;j++) a[j].clear();
    }
    return 0;
}