#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 8010
#define ull unsigned long long
using namespace std;
int a[N],b[N];
short f[N][N],mn[N][N];
ull s[N],rd[N];
ull rand0(){return (ull)rand()<<47^((ull)rand()<<32)^((ull)rand()<<16)^rand();}
int main()
{
    srand(19260817);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
    sort(b+1,b+n+1);
    int m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+m+1,a[i])-b;
    auto pmin=[&](int x,int y){return a[x]<a[y]?x:y;};
    for(int i=1;i<=n;i++)
    {
        mn[i][i]=i;
        for(int j=i+1;j<=n;j++) mn[i][j]=pmin(mn[i][j-1],j);
    }
    for(int i=n;i;i--)
    {
        f[i][i]=2;
        int pn=i;
        for(int j=i+1;j<=n;j++)
        {
            if(f[i][j-1]==2 && a[j]<=a[j-1]){f[i][j]=2;continue;}
            if(a[j]>a[i]) pn=j;
            int p=mn[i][pn];
            if(pn==i) f[i][j]=f[i+1][j];
            else if(p==i) f[i][j]=f[pn][j]==2;
            else f[i][j]=f[p][j];
        }
    }
    for(int i=1;i<=n;i++) rd[i]=rand0();
    int ans=0;
    for(int l=n;l;l--)
    {
        for(int r=l+1;r<=n;r++) if(a[l]<a[r]) s[r]^=rd[l]^rd[r];
        ull x=0;
        for(int r=l;r<=n;r++)
        {
            x^=s[r];
            if(f[l][r]!=0 && !x) ++ans;
        }
    }
    printf("%d\n",ans);
    return 0;
}