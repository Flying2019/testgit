#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define N 110
#define MP make_pair
#define fi first
#define se second
using namespace std;
int a[N],b[N];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
set<pair<int,int> >f;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
    f.insert(MP(0,0));
    for(int i=1;i<=n;i++)
    {
        auto g=f;f.clear();
        for(auto j:g) f.insert(MP(gcd(j.fi,a[i]),gcd(j.se,b[i]))),f.insert(MP(gcd(j.fi,b[i]),gcd(j.se,a[i])));
    }
    long long ans=0;
    for(auto i:f)
        ans=max(ans,1ll*i.fi*i.se/gcd(i.fi,i.se));
    printf("%lld\n",ans);
    return 0;
}