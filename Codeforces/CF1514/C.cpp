#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int a[N];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
    int n;
    int t=1,c=0;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    if(gcd(n,i)==1) t=1ll*t*i%n,a[i]=true,c++;
    int q=1;
    for(int i=1;i<=c-1;i++) q=1ll*q*t%n;
    // printf("%d %d %d\n",t,c,q);
    if(q!=1) a[q]=false,c--;
    printf("%d\n",c);
    for(int i=1;i<n;i++) if(a[i]) printf("%d ",i);
    return 0;
}