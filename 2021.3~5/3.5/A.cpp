#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 110
#define ll long long
using namespace std;
class PenguinSledding
{
    private:
    int deg[N];
    bool mp[N][N];
    public:
    ll countDesigns(int n,vector<int>x,vector<int>y)
    {
        int m=x.size();
        for(int i=0;i<m;i++) deg[x[i]]++,deg[y[i]]++,mp[x[i]][y[i]]=mp[y[i]][x[i]]=true;
        ll ans=0;
        for(int i=1;i<=n;i++) ans=ans+(1ll<<deg[i])-deg[i]-1;
        ans+=m+1;
        for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        for(int k=j+1;k<=n;k++)
        if(mp[i][j] && mp[j][k] && mp[k][i]) ans++;
        return ans;
    }
};
// int main()
// {
//     cout<<a.countDesigns(
// 36,
// {13, 24, 24, 20, 31, 16, 10, 36, 34, 32,
//  28, 5, 20, 29, 23, 2, 14, 4, 9, 5, 19,
//  21, 8, 1, 26, 27, 25, 15, 22, 30, 30,
//  6, 11, 7, 2, 35, 13, 29, 4, 12, 33, 18,
//  13, 14, 17, 35, 3},
// {10, 15, 27, 1, 29, 11, 5, 18, 33, 1, 9,
//  2, 31, 6, 19, 10, 33, 18, 6, 27, 3, 22,
//  4, 12, 31, 30, 34, 16, 7, 24, 3, 28, 15,
//  21, 22, 8, 26, 20, 14, 32, 25, 17, 35,
//  8, 36, 26, 23}
// );
//     return 0;
// }