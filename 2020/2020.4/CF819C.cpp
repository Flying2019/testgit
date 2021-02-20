#include<iostream>
#include<cstdio>
#include<cstring>
#define N 80
using namespace std;
int p[N],tot;
bool vis[1000010];
void work(int num[],int x)
{
    for(int i=1;i*i<=x;i++)
    if(x%i==0)
    {
        while(x%i==0) x/=i;
        if(!vis[i])
    }
}
int main()
{
    int n;
    scanf("%d",&n);
}