#include<iostream>
#include<cstdio>
#include<cstring>
#define N 8
using namespace std;
int g[N][N],a[1<<N],ans;
int uban[N],ulnk[N],vban[N],vlnk[N];
void dfs(int x,int y,int n)
{
    if(x==y) y++;if(y==n) y=0,x++;
    if(x>=n){ans++;return;}
    if(!(ulnk[x]&vlnk[y]))
    {
        uban[x]^=1<<y;vban[y]^=1<<x;
        dfs(x,y+1,n);
        uban[x]^=1<<y;vban[y]^=1<<x;
    }
    if(g[x][y] && !(uban[x]&ulnk[y]) && !(vban[y]&vlnk[x]))
    {
        ulnk[x]^=1<<y;vlnk[y]^=1<<x;
        dfs(x,y+1,n);
        ulnk[x]^=1<<y;vlnk[y]^=1<<x;
    }
}
int n,tn[N];
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    for(int t=0;t<1<<n;t++)
        for(int s=0;s<=t;s++)
        if((s|t)==t)
        {
            bool can=true;
            for(int i=1;i<=m;i++) if((a[i]&s)!=s || (a[i]|t)!=t){can=false;break;}
            if(!can) continue;
            int k=0;
            for(int i=0;i<n;i++) if((s^t)>>i&1) tn[k++]=i;
            for(int i=0;i<k;i++)
                for(int j=0;j<k;j++)
                {
                    g[i][j]=true;
                    for(int p=1;p<=m;p++) if(a[p]>>tn[i]&1 && !(a[p]>>tn[j]&1)) g[i][j]=false;
                }
            dfs(0,0,k);
        }
    printf("%d\n",ans);
    return 0;
}