#include<iostream>
#include<cstdio>
#include<cstring>
#define N 600010
#define K 15
#define ll long long
using namespace std;
int _3[16];
ll A[K][N],B[K][N],C[K][N];
void mul(int n)
{
    ll *a=A[n],*b=B[n],*c=C[n];
    if(n==1)
    {
        c[0]=a[1]*b[1]+a[2]*b[2]+a[1]*b[2]+a[2]*b[1];
        c[1]=a[0]*b[2]+a[2]*b[0]+a[0]*b[0];
        c[2]=a[0]*b[1]+a[1]*b[0];
        return;
    }
    int _n=n-1,k=_3[_n];
    ll *c0=c,*c1=c0+k,*c2=c1+k;
    ll *a0=a,*a1=a0+k,*a2=a1+k;
    ll *b0=b,*b1=b0+k,*b2=b1+k;
    ll *f=A[_n],*g=B[_n],*h=C[_n];
    for(int i=0;i<k;i++) f[i]=a2[i],g[i]=b2[i];
    mul(n-1);
    for(int i=0;i<k;i++) c1[i]=-h[i];
    for(int i=0;i<k;i++) f[i]+=a1[i],g[i]+=b1[i];
    mul(n-1);
    for(int i=0;i<k;i++) c0[i]=h[i];
    for(int i=0;i<k;i++) f[i]=a2[i]+a0[i],g[i]=b2[i]+b0[i];
    mul(n-1);
    for(int i=0;i<k;i++) c1[i]+=h[i];
    for(int i=0;i<k;i++) f[i]+=a1[i],g[i]+=b1[i];
    mul(n-1);
    for(int i=0;i<k;i++) c2[i]=h[i]-c1[i]-c0[i];
}
int main()
{
    _3[0]=1;
    for(int i=1;i<=15;i++) _3[i]=_3[i-1]*3;
    int n;
    scanf("%d",&n);
    for(int i=0;i<_3[n];i++) scanf("%lld",&A[n][i]);
    for(int i=0;i<_3[n];i++) scanf("%lld",&B[n][i]);
    mul(n);
    for(int i=0;i<_3[n];i++) printf("%lld ",C[n][i]);
    return 0;
}