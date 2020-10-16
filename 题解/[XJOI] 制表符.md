### [����](http://115.236.49.52:83/contest/1523/problem/1)
���Է��֣���Ŀ�ġ��Ʊ�������� $\bmod k$ ������һ���Ǵ�0��ʼ����������ֻ�赥����ÿ���Ʊ��ͳ���䵽֮ǰ���ַ�������

���ǲ�������һ���Ʊ�� $i$ ����֮ǰ���Ʊ�����ַ�����Ϊ $a_i$����ô��������������ַ��ĳ��Ⱦ��� $a_i+k-(a_i\bmod k)$��

�����ԣ�ǰ���������ر��ά����ֱ��ǰ׺�;ͺ��ˡ����Ǻ����Ǹ������е����⡣

���ǿ��ǣ�����ĳ�� $a_i\leq k$��$a_i\bmod k$ ��Ȼ�� $a_i$��Ҳ��������ַ��ĳ��Ⱦ��� $k$�����ǲ�����ѯ�����ߣ��� $k$ ���򡣵�����ö�ٵ�һ�� $k$ ʱ��ɾ������ $a_i\leq k$ ��ֵ������ʣ�µĵ�ͳ��ǰ׺�ͣ�Ȼ���������Ϊ $k$ ��ѯ�ʣ������ҵ���Ӧ�ĵ�ͳ�ƺͣ����ڱ߽�����һ�¼��ɡ�

���ǿ���Ϊʲô�����ǶԵġ��������ַ�����СΪ $n\leq 5\times 10^6$������ $\sum a_i\leq 5\times 10^6$�����Է��֣���������Ҫ�ó����ܾ����ܶ��ʱ�䣬�Ʊ���Ҫ���� $k$ ������ͬ����˶���ĳһ�ֳ��� $a_i$����ֻ����౻��¼ǰ׺�� $a_i$ �Σ���ͳ�ƴ��� $O(\sum a_i)$ �� $O(n)$��

��ʱ�临�Ӷ� $O(n+m\log n)$��
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
