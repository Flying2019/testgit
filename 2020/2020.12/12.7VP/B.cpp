#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
#define abs(x) ((x)>0?(x):-(x))
char s[N];
int a[N],_2[N],fac[N];
int C2(int a,int b){return (fac[a]-fac[b]-fac[a-b])?0:1;}
int main()
{
    int n;
    scanf("%d%s",&n,s+1);
    for(int i=1;i<=n;i++) _2[i]=(i%2)?0:_2[i/2]+1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]+_2[i];
    for(int i=1;i<n;i++) a[i]=abs(s[i]-s[i+1]);
    --n;
    int res=2;
    for(int i=1;i<=n;i++) if(a[i]==1) res=1;
    if(res==1)
        for(int i=1;i<=n;i++)
        if(a[i]==2) a[i]=0;
    int ans=0;
    for(int i=1;i<=n;i++)
    if(a[i]) ans^=C2(n-1,i-1);
    printf("%d\n",ans*res);
    return 0;
}