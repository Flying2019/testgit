#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;
class TheBrickTowerMediumDivOne
{
    private:
    bool chs[N];
    vector<int>ans;
    struct node{
        int w,u;
        bool operator <(const node a)const{return w==a.w?u<a.u:w<a.w;}
    }pn[N];
    public:
    vector<int> find(vector<int> h)
    {
        int n=h.size();
        int m=h[0];
        for(int i=1;i<n;i++) m=min(m,h[i]);
        int pre=100;
        for(int i=0;i<n;i++)
        {
            if(h[i]>pre) continue;
            ans.push_back(i);pre=h[i];
            chs[i]=true;
        }
        int t=0;
        for(int i=0;i<n;i++)
        if(!chs[i]) pn[++t]=(node){h[i],i};
        sort(pn+1,pn+t+1);
        for(int i=1;i<=t;i++) ans.push_back(pn[i].u);
        return ans;
    }
};
// TheBrickTowerMediumDivOne F;
// int main()
// {
//     auto x=F.find(
// {13, 32, 38, 25, 43, 47, 6}
// );
//     for(int u:x) printf("%d ",u);
//     return 0;
// }