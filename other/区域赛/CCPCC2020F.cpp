#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 5010
#define M 10
#define mod 1000000007
using namespace std;
const int MS=(1<<M)-1;
int _2[M+2],f[N][1<<M];
bool ban[N];
void upd(int d,int d0,int s,int x)
{
    if(d>10)
    {
        int t=d0?s&_2[d0-1]:s;
        f[x][t&MS]=(f[x][t&MS]+f[x-1][s>>1])%mod;
        return;
    }
    upd(d+2,d0,s,x);
    if(x>=d && ((s>>(d-1))&1) && !ban[x-d] && !ban[x]) upd(d+2,d,s,x);
}
vector<int>cr[N];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    _2[0]=(1<<(M+2))-1;
    for(int i=1;i<=M;i++) _2[i]=_2[i-1]^(1<<(i-1));
    for(int i=1;i<=k;i++)
    {
        int c,r;
        scanf("%d%d",&c,&r);
        cr[c+r].push_back(r*2);
    }
    f[0][0]=1;
    for(int x=1;x<=n;x++)
    {
        int L=max(0,x-M-1),R=min(n,x+M+1);
        for(int i=L;i<=R;i++) ban[i]=false;
        for(int i=L;i<=R;i++)
            for(int j=0;j<(int)cr[i].size();j++)
            {
                int r=cr[i][j],l=i-r;
                if(x<=l) continue;
                if(x==i) ban[l]=true;
                else if(l<x && x<i) for(int k=L;k<l;k++) ban[k]=true;
                else for(int k=l+1;k<i;k++) ban[k]=true;
            }
        for(int s=0;s<=MS;s++)
        if(f[x-1][s]) upd(2,0,s<<1|1,x);
    }
    int ans=0;
    for(int s=0;s<=MS;s++) ans=(ans+f[n][s])%mod;
    printf("%d\n",ans);
    return 0;
}