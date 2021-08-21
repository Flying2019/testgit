#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<vector>
#define N 100010
using namespace std;
int x[N],y[N];
map<int,int>mx,my;
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        mx.clear();my.clear();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]),mx[x[i]]++,my[y[i]]++;
        int nx=0,ny=0;
        for(auto v:mx) nx=max(nx,v.second);
        for(auto v:my) ny=max(ny,v.second);
        int cx=0,cy=0;
        for(auto v:mx) if(v.second==nx) cx++;
        for(auto v:my) if(v.second==ny) cy++;
        long long c1=1ll*cx*cy;
        for(int i=1;i<=n;i++) if(mx[x[i]]==nx && my[y[i]]==ny) --c1;
        if(c1) printf("%d %lld\n",nx+ny,c1);
        else
        {
            int dx=0,dy=0;
            for(auto v:mx) if(v.second+1==nx) dx++;
            for(auto v:my) if(v.second+1==ny) dy++;
            c1=1ll*cx*cy+1ll*dx*cy+1ll*dy*cx;
            for(int i=1;i<=n;i++) if(mx[x[i]]==nx && my[y[i]]+1==ny) --c1;
            for(int i=1;i<=n;i++) if(mx[x[i]]+1==nx && my[y[i]]==ny) --c1;
            printf("%d %lld\n",nx+ny-1,c1);
        }
    }
    return 0;
}