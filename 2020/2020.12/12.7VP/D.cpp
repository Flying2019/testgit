#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2010
using namespace std;
int f[N*3][N*6];
int& F(int x,int y){return f[x][y+N*3];}
int main()
{
    int n,mod;
    scanf("%d%d",&n,&mod);n*=3;
    F(0,0)=1;
    for(int i=0;i<n;i++)
        for(int j=-i;j<=i;j++)
        if(F(i,j))
            (F(i+1,j+1)+=F(i,j))%=mod,
            (F(i+2,j-1)+=1ll*F(i,j)*(i+1)%mod)%=mod,
            (F(i+3,j)+=1ll*F(i,j)*(i+1)%mod*(i+2)%mod)%=mod;
    int ans=0;
    for(int i=0;i<=n;i++) ans=(ans+F(n,i))%mod;
    printf("%d\n",ans);
    return 0;
}