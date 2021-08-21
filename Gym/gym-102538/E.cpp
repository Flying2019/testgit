#include<iostream>
#include<cstdio>
#include<cstring>
#define S(l,r) (a[(r)]^a[(l)])
using namespace std;
const int N=1000010,M=20;
int a[N],f[N][M],_k[M],_2[M];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++) scanf("%d",&x),a[x]^=1;
    for(int i=n;~i;i--) a[i]^=a[i+1];
    _k[0]=(1<<M)-1;_2[0]=1;
    for(int i=1;i<M;i++) _k[i]=_k[i-1]^_2[i-1],_2[i]=_2[i-1]<<1;
    for(int i=n;~i;i--)
        for(int j=0;_2[j]<=n;j++) f[i][j]=f[i+_2[j+1]][j]^S(i+_2[j],i+_2[j+1]);
    for(int i=1;i<=n;i++)
    {
        bool z=true;
        for(int j=0;_2[j]<=i;j++)
        {
            int s=0;
            for(int l=0;l<=n;l+=(i+1))
            {
                int m=min(l+i,n);int r=l+((m-l+1)&_k[j+1])+_2[j+1];
                s^=f[l][j]^f[r][j]^S(max(m+1,r-_2[j]),r);
            }
            if(s){z=false;break;}
        }
        printf("%s ",z?"Bob":"Alice");
    }
    return 0;
}