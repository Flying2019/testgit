#include<iostream>
#include<cstdio>
#include<cstring>
#define N 110
#define M 2010
using namespace std;
bool f[N*M];
int a[N];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
    int n;
    scanf("%d",&n);
    int s=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),s+=a[i];
    if(s%2==1){puts("0");return 0;}
    f[0]=1;int m=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=0;j--) if(f[j]) f[j+a[i]]=true;
        m+=a[i];
    }
    if(!f[s/2]){puts("0");return 0;}
    puts("1");
    int g=0;
    for(int i=1;i<=n;i++) g=gcd(g,a[i]);
    for(int i=1;i<=n;i++) a[i]/=g;
    for(int i=1;i<=n;i++) if(a[i]&1){printf("%d\n",i);return 0;}
    return 0;
}