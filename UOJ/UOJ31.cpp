#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
char s[N];
int a[N];
int ax[N],ay[N],tt;
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=1;i<=n;i++) a[i]=a[i-1]+(s[i]=='('?1:-1);
    int s=0;
    for(int l=1;l<=n;l++)
    if(a[l]<0)
    {
        int r=l;
        while(a[r]<0) r++;
        ax[++tt]=l;ay[tt]=r;
        l=r;
    }
    printf("%d\n",tt);
    for(int i=1;i<=tt;i++) printf("%d %d\n",ax[i],ay[i]);
    return 0;
}