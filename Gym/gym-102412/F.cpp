#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#define ll long long
using namespace std;
set<ll>s;
void solve(ll n)
{
    if(s.count(n)) return;
    ll q=sqrt(n);
    while(q*q<n) q++;
    solve(q);solve(q*q-n);
    printf("%lld %lld\n",q,q*q-n);
    s.insert(n);
    if(s.size()>44) throw;
}
int main()
{
    s.insert(0);s.insert(1);s.insert(2);
    ll n;
    scanf("%lld",&n);
    solve(n);
    return 0;
}