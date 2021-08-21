#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 100010
#define ll long long
using namespace std;
priority_queue<int>q;
int main()
{
    int n,ans=0;
    ll a,b;
    scanf("%d%lld%lld",&n,&a,&b);
    ll sum=1;
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);--x;
        sum+=x/b;x%=b;
        if(a*sum>x)
        {
            sum-=x/a+1;
            ans++;
            q.push(x/a+2);
        }
        else if(!q.empty() && q.top()-x/a>2)
        {
            sum+=q.top()-x/a-1;
            q.pop();
            q.push(x/a+2);
        }
        else ++sum;
    }
    printf("%d\n", ans);
    return 0;
}
