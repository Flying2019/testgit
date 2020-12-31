#include<iostream>
#include<cstdio>
#include<cstring>
#define N 310
using namespace std;
int a[N];
bool f[N][2],rf[N][2];
int g[N][2],rg[N][2];
int k[2];
int n,m;
bool b[N][N];
void make_pre(int l,int r,int u)
{
    for(int i=r;i>=l;i--)
    {
        int p=0;
        for(int j=u+1;j<=n;j+=2)
        if(b[i+1][j]) continue;
        else if(p>=a[i]) break;
        else p++,b[i][j]=true;
        u=g[i][u];
    }
}
void make_suf(int l,int r,int u)
{
    for(int i=l;i<=r;i++)
    {
        int p=0;
        for(int j=u+1;j<=n;j+=2)
        if(b[i-1][j]) continue;
        else if(p>=a[i]) break;
        else p++,b[i][j]=true;
        u=rg[i][u];
    }
}
void solve_pre(int l,int r)
{
    for(int i=l;i<=r;i++)
        for(int j=0;j<=1;j++)
        if(f[i-1][j])
        {
            if(k[!j]>=a[i]) f[i][!j]=true,g[i][!j]=j;
            if(a[i]+a[i-1]<=k[j]) f[i][j]=true,g[i][j]=j;
        }
}
void solve_suf(int l,int r)
{
    for(int i=r;i>=l;i--)
        for(int j=0;j<=1;j++)
        if(rf[i+1][j])
        {
            if(k[!j]>=a[i]) rf[i][!j]=true,rg[i][!j]=j;
            if(a[i]+a[i+1]<=k[j]) rf[i][j]=true,rg[i][j]=j;
        }
}
bool make(int l,int r)
{
    f[l][0]=true;f[l][1]=false;
    rf[r][0]=true;rf[r][1]=false;
    solve_pre(l+1,r-1);
    solve_suf(l+1,r-1);
    if(f[r-1][1])
    {
        make_pre(l+1,r-1,1);
        return true;
    }
    for(int i=l+1;i<r;i++)
    {
        for(int j=0;j<=1;j++)
        if(f[i-1][j] && rf[i+1][!j] && (a[i-1]+a[i+1]<=k[0] || a[i]+a[i-1]+a[i+1]-k[0]<=k[1]))
        {
            make_suf(l+1,i-1,j);make_pre(i+2,r-1,rg[i+1][!j]);
            int w=0;
            for(int p=n-!j;p>=1;p-=2)
            if(b[i+2][p]) continue;
            else if(w==a[i+1]) break;
            else b[i+1][p]=true,w++;
            w=0;
            for(int p=1;p<=n;p++)
            if(b[i-1][p]  || b[i][p-1] || b[i+1][p] || b[i][p+1]) continue;
            else if(w==a[i]) break;
            else w++,b[i][p]=true;
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    if(n%2==0)
    {
        for(int i=1;i<=m;i++)
        {
            int p=0;
            for(int j=1+(i&1);j<=n;j+=2)
            if(b[i-1][j]) continue;
            else if(p>=a[i]) break;
            else p++,b[i][j]=true;
            if(p<a[i]) {puts("No");return 0;}
        }
        puts("Yes");
        for(int i=1;i<=n;i++,puts(""))
            for(int j=1;j<=m;j++)
            putchar('0'+b[j][i]);
        return 0;
    }
    k[0]=n-n/2,k[1]=n/2;
    for(int i=1;i<=m;i++)
    if(a[i]>k[0])
    {
        puts("No");
        return 0;
    }
    int p=0;
    for(int i=1;i<=m;i++)
    if(a[i]==k[0])
    {
        f[i][0]=rf[i][0]=true;
        for(int j=1;j<=n;j+=2) b[i][j]=true;
    }
    f[0][0]=f[0][1]=f[m+1][0]=f[m+1][1]=true;
    rf[0][0]=rf[0][1]=rf[m+1][0]=rf[m+1][1]=true;
    for(int i=1;i<=m;i++)
    if(a[i]==k[0])
    {
        if(!p)
        {
            solve_pre(1,i-1);
            make_pre(1,i-1,1);
        }
        else
        {
            if(!make(p,i)){puts("No");return 0;}
        }
        p=i;
    }
    if(p!=m)
    {
        solve_suf(p+1,m);
        make_suf(p+1,m,1);
    }
    puts("Yes");
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=m;j++)
        putchar('0'+b[j][i]);
    return 0;
}