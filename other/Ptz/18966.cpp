#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int s[N],nxt[N];
int main()
{
    int n,seed;
    scanf("%d%d",&n,&seed);
	for(int i=1;i<=n;i++) seed=(1ll*seed*13331+23333)%1000000007,a[i]=seed&1;
    for(int i=1;i<=n;i++)
    return 0;
}