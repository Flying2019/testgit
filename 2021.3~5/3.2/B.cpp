#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2010
using namespace std;
int mp[N][N],tt[N],n,k;
void push(int x,int v){if(tt[x]>k) throw;mp[x][++tt[x]]=v;}
int Id(int x,int y,int p=k-1){return (x-1)*p+y;}
int main()
{
    // scanf("%d",&k);
    k=8;n=k*(k-1)+1;
    for(int i=1;i<=k;i++) push(n,i);
    for(int i=1;i<n;i++) push(i,(i-1)/(k-1)+1);
    for(int i=1;i<k;i++)
        for(int j=1;j<k;j++)
        {
            int c=k+Id(i,j);
            push(i,c);
            for(int p=1,v=j-1;p<k;p++,v=(v+i-1)%(k-1)) push(k+Id(p,v),c);
        }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            int tt=0;
            for(int l=1;l<=k;l++)
                for(int r=1;r<=k;r++)
                if(mp[i][l]==mp[j][r]) ++tt;
            if(tt!=1){printf("Wrong on %d , %d : %d",i,j,tt);throw;}
        }
    // puts("Right");return 0;
    printf("%d %d\n",n,k);
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=tt[i];j++) printf("%d ",mp[i][j]);
    return 0;
}