#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 310
using namespace std;
typedef double db;
struct node{
    int x,y;
    node(int X=0,int Y=0):x(X),y(Y){}
    node operator +(const node a)const{return node(x+a.x,y+a.y);}
    node operator -(const node a)const{return node(x-a.x,y-a.y);}
}p[N];
db dis(node a){return sqrt(1ll*a.x*a.x+1ll*a.y*a.y);}
db f[N][N][2];//i,j,0:i->j 1:j->i
bool mp[N][N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,m;
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%d%d",&p[i].x,&p[i].y);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);mp[x-1][y-1]=mp[y-1][x-1]=true;
        }
        for(int d=2;d<n;d++)
            for(int i=0;i<n;i++)
            {
                int j=(i+d)%n;
                for(int k=(i+1)%n;k!=j;k=(k+1)%n)
                {
                    if(mp[j][k]) f[i][j][0]=max(f[i][j][0],max(f[i][k][0],f[j][k][1])+dis(p[k]-p[j]));
                    if(mp[i][k]) f[j][i][1]=max(f[j][i][1],max(f[i][k][0],f[j][k][1])+dis(p[k]-p[i]));
                }
            }
        db ans=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            if(i!=j && mp[i][j]) ans=max(ans,max(f[i][j][0],f[j][i][1])+dis(p[i]-p[j]));
        printf("%.8f\n",ans);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++) mp[i][j]=f[i][j][0]=f[i][j][1]=0;
    }
    return 0;
}