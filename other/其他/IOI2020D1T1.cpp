#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 1010
using namespace std;
void build(vector<vector<int> >b);
int f[N],g[N],id[N];
int h[N];
int find(int x){return f[x]==x?x:(f[x]=find(f[x]));}
int findg(int x){return g[x]==x?x:(g[x]=findg(g[x]));}
vector<int>t[N];
int construct(vector<vector<int> >p)
{
    vector<vector<int> >r;
    int n=p.size();
    r.resize(n);
    for(int i=0;i<n;i++) r[i].resize(n);
    for(int i=0;i<n;i++) f[i]=i;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        if(p[i][j]==1)
        {
            if(find(i)==find(j)) continue;
            f[find(i)]=find(j);r[i][j]=true;
        }
        else if(p[i][j]==3) return 0;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        if(p[i][j]!=1 && find(i)==find(j)) return 0;
    for(int i=0;i<n;i++) id[i]=find(i);
    int m=0;
    for(int i=0;i<n;i++)
    if(id[i]==i) h[m++]=i;
    for(int i=0;i<m;i++) g[i]=i;
    for(int i=0;i<m;i++)
        for(int j=i+1;j<m;j++)
        if(p[h[i]][h[j]]==1) return 0;
        else if(p[h[i]][h[j]]==2) g[findg(i)]=findg(j);
    for(int i=0;i<m;i++)
        for(int j=i+1;j<m;j++)
        if(p[h[i]][h[j]]==0 && findg(i)==findg(j)) return 0;
    for(int i=0;i<m;i++) t[findg(i)].push_back(i);
    for(int i=0;i<m;i++)
    if(t[i].size()>=2)
    {
        if(t[i].size()==2) return 0;
        int q=t[i].size()-1;
        for(int j=0;j<q;j++) r[h[t[i][j]]][h[t[i][j+1]]]=1;
        r[h[t[i][q]]][h[t[i][0]]]=1;
    }
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++) r[i][j]=r[j][i]=r[i][j]|r[j][i];
    build(r);
    return 1;
}
// void build(vector<vector<int> >b)
// {
//     int n=b.size();
//     for(int i=0;i<n;i++,puts(""))
//         for(int j=0;j<n;j++) printf("%d ",b[i][j]);
// }
// vector<vector<int> >p;
// int main()
// {
//     int n;
//     scanf("%d",&n);p.resize(n);
//     for(int i=0;i<n;i++) p[i].resize(n);
//     for(int i=0;i<n;i++)
//         for(int j=0;j<n;j++) scanf("%d",&p[i][j]);
//     printf("%d\n",construct(p));
//     return 0;
// }