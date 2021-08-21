#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2010
using namespace std;
int f[N],g[N];
int main()
{
    int n;
    scanf("%d",&n);
    if(n==1){puts("1\n1");return 0;}
    if(n==2){puts("-1");return 0;}
    int m=1,k=1;
    while(m<n) m<<=1,k++;
    printf("%d\n",k);
    if(n%2==0 && n%4)
    {
        for(int i=0;i<n-2;i+=4) f[i+1]=i+2,f[i+2]=i+4,f[i+3]=i+1,f[i+4]=i+3;
        f[n-1]=n-1;f[n]=n;
        for(int i=1;i<=n;i++) printf("%d ",f[i]);puts("");
        f[1]=1;f[2]=2;
        for(int i=2;i<n;i+=4) f[i+1]=i+2,f[i+2]=i+4,f[i+3]=i+1,f[i+4]=i+3;
        for(int i=1;i<=n;i++) printf("%d ",f[i]);puts("");
        for(int p=2;p<n;p<<=1,puts(""))
            for(int i=1;i<=n;i++) printf("%d ",(i+p-1)%n+1);
        return 0;
    }
    for(int p=1;p<n;p<<=1,puts(""))
        for(int i=1;i<=n;i++) printf("%d ",(i+p-1)%n+1);
    if(n%2){for(int i=1;i<=n;i++) printf("%d ",i%n+1);puts("");return 0;}
    for(int i=0;i<n;i+=4) f[i+1]=i+2,f[i+2]=i+4,f[i+3]=i+1,f[i+4]=i+3;
    for(int i=1;i<=n;i++) printf("%d ",f[i]);
    return 0;
}