#include<cstdio>
#include<algorithm>
using namespace std;
int T,k,n,a,b,c,d;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&a,&b,&c,&d);n=a+b;
        int l=0,r=n+1,mid,A,B;k=(max(a,b)-1)/(min(a,b)+1)+1;;
        while(l<r){
            mid=(l+r)>>1;
            A=a-mid/(k+1)*k-mid%(k+1);B=b-mid/(k+1);
            if(B<=1ll*A*k)l=mid+1;else r=mid;
        }
        A=a-l/(k+1)*k-l%(k+1);B=b-l/(k+1);r=l+B-A*k+1;
        for(int i=c;i<=min(d,l);i++)putchar(i%(k+1)?'A':'B');
        for(int i=max(c,l+1);i<=d;i++)putchar((i-r)%(k+1)?'B':'A');
        puts("");
    }
    return 0;
}