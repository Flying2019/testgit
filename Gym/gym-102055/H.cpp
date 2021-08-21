#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200010
using namespace std;
vector<int>g[N];
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            int x,y;scanf("%d%d",&x,&y);
            g[x].push_back(y);g[y].push_back(x);
        }
    }
    return 0;
}