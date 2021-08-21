#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 17
#define inf 100000000
using namespace std;
class FoxAndPhotography
{
public:
    FoxAndPhotography(){}
    ~FoxAndPhotography(){}
    int f[1<<N];
    int getMinimumSwaps(vector<int>a,vector<int>b)
    {
        static int h1[N],h2[N];
        int n=a.size(),m=1<<n;
        memset(f,0x3f,sizeof(f));
        f[m-1]=0;
        for(int s=m-2;s>=0;s--)
        {
            int c=0,t=__builtin_popcount(s);
            for(int i=0;i<n;i++)
            if(!((s>>i)&1))
            {
                if(a[i]<b[t] && f[s^(1<<i)]<=inf) f[s]=min(f[s],f[s^(1<<i)]+c);
                ++c;
            }
        }
        return f[0]>=inf?-1:f[0];
    }
};
// int main()
// {
//     FoxAndPhotography F;
//     cout<<F.getMinimumSwaps(

// {170, 170, 170},
// {160, 170, 180}

// );
//     return 0;
// }