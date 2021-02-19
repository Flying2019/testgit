#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define ll long long
using namespace std;
bitset<10000>b;
int main()
{
    ll n;
    scanf("%lld",&n);
    n-=n/500;
    ll res=0;
    for(int a=0;a<5;a++)
        for(int b=0;b<2;b++)
            for(int c=0;c<5;c++)
                for(int d=0;d<2;d++)
                    for(int e=0;e<5;e++)
                    if(a+b+c+d+e<=n) res++;
    printf("%lld\n",res);
    return 0;
}