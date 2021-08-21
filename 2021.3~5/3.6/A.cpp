#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
class HamiltonianConstruction
{
    public:
    vector<string> construct(int k)
    {
        int n=20;
        vector<string>res;
        for(int i=0;i<n;i++) res.push_back("NNNNNNNNNNNNNNNNNNNN");
        for(int i=1;i<n-1;i++)
            for(int j=i+1;j<n;j++) res[i][j]='Y';
        for(int i=2;i<n;i++) res[i][i-1]='Y';
        for(int i=n-3;k;i--,k>>=1)
        if(k&1) res[0][i]='Y';
        return res;
    }
};
HamiltonianConstruction F;
int main()
{
    auto s=F.construct(1);
    for(auto u:s) cout<<u<<endl;
    return 0;
}