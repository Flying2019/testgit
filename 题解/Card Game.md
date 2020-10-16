### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102661/problem/B)
### ��Ŀ����
��� $p$ ������һ����Ϸ��ÿ����һ��ʼ��һ��ӡ�� $[1,c]$ �����ֵĿ�Ƭ��������Ҳ�� $n$ �������Ŀ�Ƭ��ÿ�������������ϵ�һ�ſ�Ƭ�����Լ����ϵĿ�Ƭ�����ǵ�һ�������ġ�

����Ϸǰ��д��һ������ $h$������������������µĿ�Ƭ�� $h$ ��**Ψһ**��������ô��Ϊ��ɹ���

�������Ǽ��ַ�����ʹ����������Լ����ܳɹ���
### ���
����һ��̰�ģ����������˶�����㣬���Ҷ�֪����д�µ����� $h$����ô���ǿ϶���취����������д�� $h$ �Ŀ�Ƭ��

�������ǿ���ֱ�Ӱѳ�����֮������в��������á�������Ҳ�������ܻ�һ���ƣ�Ҫ��**Ψһ**�������� $h$ ���ļ��ַ�����

ֱ�ӷ������۾����ˡ����и�ֱ�ӵķ�����ֱ��ö�ٻ����ţ�Ȼ�����߶���ͳ�������������ĸ������ɡ�

�ر�ģ��� $n=1$ ʱ���Է���������ֻ��һ��ѡ�񣬶���ֻҪ������� $h$ ���ǳɹ���ֱ�����д���

���Ӷ� $O(n\log c)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define N 400010
using namespace std;
int num[N],ans[N],rtot;
int maxn[N],idn[N],cnt[N];
void update(int u)
{
    maxn[u]=max(maxn[u<<1],maxn[u<<1|1]);
    idn[u]=0;
    if(maxn[u]==maxn[u<<1]) idn[u]+=idn[u<<1];
    if(maxn[u]==maxn[u<<1|1]) idn[u]+=idn[u<<1|1];
}
void build(int u,int l,int r,int a[])
{
    if(l==r){maxn[u]=a[l];idn[u]++;return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid,a);
    build(u<<1|1,mid+1,r,a);
    update(u);
}
void insert(int u,int l,int r,int p,int opt)
{
    if(l==r)
    {
        maxn[u]+=opt;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) insert(u<<1,l,mid,p,opt);
    else insert(u<<1|1,mid+1,r,p,opt);
    update(u);
}
int main()
{
    int n,p,c,h,cs=0;
    scanf("%d%d%d%d",&n,&p,&c,&h);
    for(int i=1;i<=n;i++) scanf("%d",&num[i]),cnt[num[i]]++;
    if(n==1)
    {
        int a=0;
        for(int i=1;i<=p;i++) scanf("%d",&a);
        if(a==h) puts("1\n1");
        else puts("0");
        return 0;
    }
    for(int i=1;i<=p;i++)
    {
        int a;
        scanf("%d",&a);
        if(i==1) cs=a;
        else cnt[h]--,cnt[a]++;
    }
    build(1,1,c,cnt);
    // for(int i=1;i<=n*2;i++) printf("%d ",maxn[i]);puts("");
    for(int i=1;i<=n;i++)
    {
        insert(1,1,c,num[i],-1);
        cnt[num[i]]--;
        insert(1,1,c,cs,1);
        cnt[cs]++;
        // printf("%d %d\n",maxn[1],idn[1]);
        if(maxn[1]==cnt[h] && idn[1]==1) ans[++rtot]=i;
        insert(1,1,c,num[i],1);
        insert(1,1,c,cs,-1);
        cnt[cs]--;
        cnt[num[i]]++;
    }
    printf("%d\n",rtot);
    for(int i=1;i<=rtot;i++) printf("%d ",ans[i]);
    return 0;
}
```
