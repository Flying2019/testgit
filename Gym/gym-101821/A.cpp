#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
const ll m=1000000;
using namespace std;
int a[m],b,c,r,d;ll res=0;
bool get_next()
{
    if(b<0 || c<0 || d<0) return false;
    if(r%m>c) b-=r/m+1,c+=m-r%m,d-=m-r%m;
    else b-=r/m,c-=r%m,d+=r%m;
    if(b<0 || c<0 || d<0) return false;
    res++;
    return true;
}
int main()
{
    scanf("%d%d%d%d",&b,&c,&r,&d);
    res=(b*m+c)/r;
    if(c+d>=m){printf("%lld\n",res);return 0;}
    res=0;
    while(1)
    {
        if(a[c])
        {
            ll w=1ll*m*(a[c]-b)/r;
            res+=w*(b/(a[c]-b));
            b%=(a[c]-b);
            break;
        }
        a[c]=b;
        if(!get_next()) break;
    }
    while(get_next());
    printf("%lld\n",res);
    return 0;
}