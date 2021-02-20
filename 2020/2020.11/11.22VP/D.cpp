#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
using namespace std;
int n;
int a[N];
int q[N],ql,qr;
int main()
{
    scanf("%d",&n);
    int mx=0,mn=1e9;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),mx=max(mx,a[i]),mn=min(mn,a[i]);
    if(mn*2>=mx){for(int i=1;i<=n;i++) printf("-1 "); return 0;}
    for(int i=1;i<=n;i++) a[i+2*n]=a[i+n]=a[i];
    q[ql=qr=1]=1;
    int p=1;
    for(int i=1;i<=n;i++)
    {
        if(qr>=ql && q[ql]==i-1) ql++;
        while(p<3*n && (ql>qr || a[p+1]*2>=a[q[ql]]))
        {
            p++;
            while(qr>=ql && a[q[qr]]<=a[p]) qr--;
            q[++qr]=p;
        }
        printf("%d ",p-i+1);
    }
    return 0;
}