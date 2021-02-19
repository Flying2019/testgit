#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#define N 100010
#define ll long long
using namespace std;
class ModuloCounters{
public:
    ModuloCounters(){}
    ~ModuloCounters(){}
    ll minFoxes(ll m,vector<ll>c)
    {
        int n=c.size(),u=0;
        ll mx=c[0],mn=1e16;
        for(int i=1;i<n;i++) mx=max(mx,c[i]);
        for(int i=1;i<n;i++)
        if(c[i-1]+c[i]<mn) u=i,mn=c[i-1]+c[i];
        while(mx>mn)
        {
            if(c[u-1]<c[u]) c[u-1]+=m;
            else c[u]+=m;
            mx=max(mx,max(c[u-1],c[u]));
            mn=1e16;u=0;
            for(int i=1;i<n;i++)
            if(c[i-1]+c[i]<mn) u=i,mn=c[i-1]+c[i];
        }
        return mx;
    }
};
// int main()
// {
//     ModuloCounters F;
//     int n;ll m;
//     scanf("%d%lld",&n,&m);
//     vector<ll>v;
//     for(int i=0;i<n;i++)
//     {
//         ll u;
//         scanf("%lld",&u);
//         v.push_back(u);
//     }
//     cout<<F.minFoxes(m,v);
//     return 0;
// }