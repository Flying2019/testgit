#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#define N 100010
#define db long double
using namespace std;
db f[N];
int g[N],n,ql,qr,q[N];
db slp(int x,int y){return (db)(f[x]-f[y])/(x-y);}
void work(db x)
{
    ql=qr=1;
    for(int i=1;i<=n;i++)
    {
        for(;ql<qr && slp(q[ql],q[ql+1])>1.0/i;ql++);
        f[i]=f[q[ql]]-(db)q[ql]/i+1+x;g[i]=g[q[ql]]+1;
        for(;ql<qr && slp(q[qr-1],q[qr])<slp(q[qr],i);qr--);
        q[++qr]=i;
    }
}
int main()
{
    int k;
    scanf("%d%d",&n,&k);
    db l=-1e6,r=1e6,res=0;
    while(r-l>=1e-12)
    {
        db mid=(l+r)/2;
        work(mid);
        if(g[n]<=k) l=mid,res=f[n]-k*mid;
        else r=mid;
    }
    cout<<fixed<<setprecision(9)<<res;
    // printf("%.10f",res);
    return 0;
}