#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 100010
using namespace std;
typedef vector<int> vec;
vec a[N],b[N];
int p[N],mu[N],cnt;bool pr[N];
void init(int n=N-10)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]){mu[i]=-1;p[++cnt]=i;}
        for(int j=1;j<=cnt && i*p[j]<=n;j++)
        {
            pr[i*p[j]]=true;
            if(i%p[j]==0) break;
            mu[i*p[j]]=-mu[i];
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    init();
    a[1].resize(n+1);b[1].resize(n+1);
    for(int i=1;i<=n;i++) scanf("%d",&a[1][i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[1][i]);
    for(int i=2;i<=n;i++)
    {
        a[i].resize(n/i+1);b[i].resize(n/i+1);
        for(int j=1;i*j<=n;j++) a[i][j]=a[1][i*j],b[i][j]=b[1][i*j];
    }
    for(int i=1;i<=n;i++) sort(a[i].begin()+1,a[i].end()),sort(b[i].begin()+1,b[i].end());
    for(int t=1;t<=n;t++)
    {
        auto check=[&](int k,vec a[],vec b[]){
            long long res=0;
            for(int d=1;t*d<=n;d++)
            {
                int c=0;
                for(int i=1,j=1;i*d*t<=n;i++)
                {
                    while(j*d*t<=n && b[t*d][j]<=a[t*d][i]-k) j++;
                    c+=j-1;
                }
                res+=mu[d]*c;
            }
            return !!res;
        };
        int l=0,r=1e9,res=0;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(check(mid,a,b) || check(mid,b,a)) l=mid+1,res=mid;
            else r=mid-1;
        }
        printf("%d ",res);
    }
    return 0;
}