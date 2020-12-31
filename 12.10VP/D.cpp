#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 100010
#define db double
using namespace std;
const db pi=acos(-1);
db sx,sy;
int t[N];
int main()
{
    int n,l;
    scanf("%d%d",&n,&l);
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            db p=pi*(t[i]+t[j])/l;
            sx+=cos(p)*(n-2*(j-i)),sy+=sin(p)*(n-2*(j-i));
        }
    printf("%.10f %.10f",sx*6/n/(n-1)/(n-2),sy*6/n/(n-1)/(n-2));
    return 0;
}