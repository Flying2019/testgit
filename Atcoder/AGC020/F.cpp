#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=7,M=51;
int l[M],c[M];
long long f[N*M][1<<N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&l[i]),c[i]=i;
    sort(l+1,l+n+1);
    int S=1<<(n-1);
    long double ans=0;
    do{
        memset(f,0,sizeof(f));
        f[n*l[n]][0]=1;
        for(int i=1;i<n*m;i++)
            for(int j=i;j<=n*m;j++)
                for(int s=0;s<S;s++)
                if(i%n && !(s>>(c[i%n]-1)&1))
                f[min(n*m,max(j,i+l[c[i%n]]*n))][s|1<<(c[i%n]-1)]+=f[j][s];
        ans+=f[n*m][S-1];
    }while(next_permutation(c+1,c+n+1));
    for(int i=1;i<n;i++) ans/=i;
    ans/=pow(m,n-1);
    printf("%.12Lf\n",ans);
    return 0;
}