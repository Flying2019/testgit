#include<iostream>
#include<cstdio>
#include<cstring>
#define N 6010
using namespace std;
char s[N];
string f[N];
int r[N],a[N],b[N],id[N];
int main()
{
    int n;
    scanf("%d%s",&n,s+1);n*=2;
    int m=0;
    for(int i=1;i<=n;i++) if(s[i]=='a') a[++m]=i,id[i]=m;
    m=0;for(int i=1;i<=n;i++) if(s[i]=='b') b[++m]=i,id[i]=m;
    for(int i=1;i<=m;i++) r[a[i]]=b[i],r[b[i]]=a[i];
    r[n+1]=n+1;
    f[m]=a[m]<b[m]?"ab":"ba";
    // cout<<f[m]<<endl;
    for(int i=m-1;i>=1;i--)
    {
        f[i]=f[i+1];
        if(a[i]<b[i])
        {
            for(int j=b[i]+1;j<=n+1;j++)
            if(r[j]>b[i]){f[i]=max(f[i],"ab"+f[id[j]]);break;}
        }
        else
        {
            int mx=a[i];
            for(int j=b[i]+1;j<=mx;j++) if(s[j]=='b') mx=max(mx,r[j]);
            string t;
            for(int j=b[i];j<=mx;j++) if(r[j]>=b[i]) t+=s[j];
            for(int j=mx+1;j<=n+1;j++)
            if(r[j]>mx){f[i]=max(f[i],t+f[id[j]]);break;}
        }
    }
    cout<<f[1]<<endl;
    return 0;
}