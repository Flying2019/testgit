#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 100000
#define M 180010
#define C 5
#define inf 1000000000
using namespace std;
int diff(int x,int y){int c=0;for(int i=0;i<C;i++,x/=10,y/=10) c+=(x%10)!=(y%10);return c;}
int _2[33],c[M][1<<C],f[M],gl[50][M],gr[50][M];
void init()
{
    for(int i=0;i<32;i++) _2[i]=_2[i>>1]+(i&1);
    for(int i=0;i<N;i++)
    {
        static int a[10];int u=i;
        for(int j=0;j<C;j++) a[j]=u%10,u/=10;
        for(int s=0;s<1<<C;s++)
            for(int j=C-1;j>=0;j--) c[i][s]=c[i][s]*11+((s&(1<<j))?10:a[j]);
    }
    for(int i=1;i<=N;i++) gl[0][i]=gl[1][i]=max(i-1,1),gr[0][i]=gr[1][i]=min(i+1,N);
}
vector<int>tu[M],tv[M];
void make(int x)
{
    for(int i=0;i<M;i++) tu[i].clear(),tv[i].clear(),f[i]=-inf;
    for(int i=1;i<N;i++)
        for(int j=0;j<32;j++)
        if(_2[j]<=x-1)
        {
            int u=max(gl[x-_2[j]-1][i]-1,1);
            tu[u].push_back(c[i][j]);tv[u].push_back(gr[x-_2[j]-1][i]);
        }
    for(int i=1;i<N;i++)
    {
        gr[x][i]=gr[x-1][i];int sz=tu[i].size();
        for(int j=0;j<sz;j++) f[tu[i][j]]=max(f[tu[i][j]],tv[i][j]);
        for(int j=0;j<32;j++) gr[x][i]=max(gr[x][i],f[c[i][j]]);
    }
    for(int i=0;i<M;i++) tu[i].clear(),tv[i].clear(),f[i]=inf;
    for(int i=1;i<N;i++)
        for(int j=0;j<32;j++)
        if(_2[j]<=x-1)
        {
            int u=min(gr[x-_2[j]-1][i]+1,N);
            tu[u].push_back(c[i][j]);tv[u].push_back(gl[x-_2[j]-1][i]);
        }
    for(int i=N-1;i;i--)
    {
        gl[x][i]=gl[x-1][i];int sz=tu[i].size();
        for(int j=0;j<sz;j++) f[tu[i][j]]=min(f[tu[i][j]],tv[i][j]);
        for(int j=0;j<32;j++) gl[x][i]=min(gl[x][i],f[c[i][j]]);
    }
}
int main()
{
    init();
    for(int i=2;i<=42;i++) make(i);
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int ans=inf;
        for(int i=l,p=0;i<=r;i++)
        {
            for(p=0;gl[p][i]>l || gr[p][i]<r;p++);
            ans=min(ans,diff(0,i)+p+1);
        }
        printf("%d\n",ans);
    }
    return 0;
}