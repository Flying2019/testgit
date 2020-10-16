### [链接](http://115.236.49.52:83/contest/1523/problem/1)
可以发现，题目的“制表符”后在 $\bmod k$ 意义下一定是从0开始，所以我们只需单独对每个制表符统计其到之前的字符个数。

我们不妨假设一个制表符 $i$ 到其之前的制表符的字符个数为 $a_i$，那么很明显最后的这段字符的长度就是 $a_i+k-(a_i\bmod k)$。

很明显，前两个东西特别好维护，直接前缀和就好了。但是后面那个东西有点问题。

我们考虑：对于某个 $a_i\leq k$，$a_i\bmod k$ 必然是 $a_i$，也就是这段字符的长度就是 $k$。我们不妨将询问离线，按 $k$ 排序。当我们枚举到一个 $k$ 时，删掉所有 $a_i\leq k$ 的值，对于剩下的点统计前缀和，然后对于所有为 $k$ 的询问，二分找到对应的点统计和，对于边界特判一下即可。

我们考虑为什么这样是对的。由于总字符串大小为 $n\leq 5\times 10^6$，所以 $\sum a_i\leq 5\times 10^6$。可以发现，假如我们要让程序跑尽可能多的时间，势必需要所有 $k$ 两两不同。因此对于某一种长度 $a_i$，它只会最多被记录前缀和 $a_i$ 次，总统计次数 $O(\sum a_i)$ 即 $O(n)$。

总时间复杂度 $O(n+m\log n)$。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5000010
#define M 100010
using namespace std;
struct node{
    int l,r;
}p1[N],p2[N];
struct ques{
    int l,r,k,id;
    bool operator <(const ques a)const{return k<a.k;}
}q[N];
char s[N];
int findl(node a[],int n,int x)
{
    int l=1,r=n,ans=n+1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(a[mid].l>=x) r=mid-1,ans=mid;
        else l=mid+1;
    }
    return ans;
}
int findr(node a[],int n,int x)
{
    int l=1,r=n,ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(a[mid].r<=x) l=mid+1,ans=mid;
        else r=mid-1;
    }
    return ans;
}
int num[N];
long long ans[N];
int main()
{
    int n,m,las=1,tot=0;
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++) 
        if(s[i]!='T') s[i]='a';
    for(int i=1;i<=n;i++)
    if (s[i]=='T')
    {
        ++tot;
        p1[tot]=p2[tot]=(node){las,i};
        las=i+1;
    }
    if(s[n]!='T')
    {
        ++tot;
        p1[tot]=p2[tot]=(node){las,n+1};
    }
    n=tot;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k),q[i].id=i;
    sort(q+1,q+m+1);
    las=0;
    for(int i=1;i<=m;i++)
    {
        int k=q[i].k;
        if(k!=las)
        {
            int u=0;
            for(int i=1;i<=n;i++)
            if(p1[i].r-p1[i].l+1>=k)
            {
                p1[++u]=p1[i];
                num[u]=(p1[u].r-p1[u].l)/k+num[u-1];
            }
            n=u,las=k;
        }
        int ql=findl(p1,n,q[i].l),qr=findr(p1,n,q[i].r),res=0;
        if(ql>qr)
        {
            ql=findl(p2,tot,q[i].l),qr=findr(p2,tot,q[i].r);
            if(ql<=qr+1)
            {
                res+=qr-ql+1;
                if(p2[ql].l-q[i].l) res+=(p2[ql].l-q[i].l-1)/k+1;
                ans[q[i].id]=1ll*res*k+q[i].r-p2[qr].r;
            }
            else ans[q[i].id]=q[i].r-q[i].l+1;
            continue;
        }
        int L=findl(p2,tot,q[i].l),R=findr(p2,tot,q[i].r);
        int sl=p2[L].l-q[i].l,sr=q[i].r-p2[R].r;
        res=num[qr]-num[ql-1];
        if(sl) res+=(sl-1)/k+1;
        res+=R-L+1;
        ans[q[i].id]=1ll*res*k+sr;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
```
