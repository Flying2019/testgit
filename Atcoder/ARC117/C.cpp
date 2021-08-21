#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 400010
using namespace std;
int n;
char s[N];
int fac[3]={1,1,2},inv[3]={1,1,2};
int zu(int a,int b)
{
    if(a==0 || a==b) return 1;
    if(a>b) return 0;
    return fac[b]*inv[a]%3*inv[b-a]%3;
}
int C(int a,int b)
{
    if(a<3 && b<3) return zu(a,b);
    int a1=a/3,a2=a%3,b1=b/3,b2=b%3;
    return C(a1,b1)*zu(a2,b2)%3;
}
int main()
{
    scanf("%d%s",&n,s+1);
    int ans=0;
    for(int i=1;i<=n;i++)
    if(s[i]=='B') ans+=C(i-1,n-1);
    else if(s[i]=='R') ans-=C(i-1,n-1);
    if(n&1) ans=-ans;
    ans=(ans%3+3)%3;
    puts(ans==0?"W":(ans==1?"R":"B"));
    return 0;
}