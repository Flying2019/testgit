### [����](http://115.236.49.52:83/contest/1561/problem/1)
���ȿ��Ǳ������������Է��ֶ���ÿ���޸ı�����ֵ���������� $O(nq)$��

����80�����������Է���������ֵֻ������ѡ������ $k\leq 12$�����Ա��ʲ�ͬ�� $n$ �ĸ�����ʵֻ�� $2^k$ ������������Щ�޸ģ��������� $O(2^kn)$���ռ������bitset�Ż��� $O(\frac{2^kn}{\omega})$��

������δ���һ����������Է��֣���������ն�ѯ�ʽڵ�Ĵ� $\geq a$����ô������ $< a$ �����ֱ��0��$\geq a$ �����ֱ��1����Ȼ��1������Խ����Խ������1������ֱ�ӱ���ö�� $a$���ҵ����� $a$ ʹ�����1����ô $a$ ���Ǵ𰸡�

ʱ�临�Ӷ� $O(2^kn+nk)$��
```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#include<cstring>
#define N 100015
#define M 13
using namespace std;
int a[M][N],f[N];
struct node{
    int x,y;
}q[N];
int num[N][110];
bitset<5010>g[N];
int main()
{
    int n,m,p;
    scanf("%d%d%d",&m,&n,&p);
    bool onli=true;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&a[i][j]),f[i]=1<<i,onli=onli && (a[i][j]==1 || a[i][j]==2);
    int t=n;
    if(onli)
    {
        for(int i=0;i<1<<n;i++)
            for(int j=1;j<=n;j++)
            if((i>>(j-1))&1) g[j][i]=1;
        for(int i=1;i<=m;i++) f[i]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            if(a[i][j]==2) f[j]|=1<<(i-1);
        for(int j=1;j<=p;j++)
        {
            int opt,x,y;
            scanf("%d%d%d",&opt,&x,&y);
            if(opt==1) g[++t]=g[x]|g[y];
            else if(opt==2) g[++t]=g[x]&g[y];
            else if(opt==3) printf("%d\n",g[x].test(f[y])+1);
        }
        return 0;
    }
    if(m<=100)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) num[i][j]=a[i][j];
        for(int i=1;i<=p;i++)
        {
            int opt,x,y;
            scanf("%d%d%d",&opt,&x,&y);
            if(opt==1)
            {
                ++t;
                for(int j=1;j<=m;j++) num[t][j]=max(num[x][j],num[y][j]);
            }
            else if(opt==2)
            {
                ++t;
                for(int j=1;j<=m;j++) num[t][j]=min(num[x][j],num[y][j]);
            }
            else if(opt==3) printf("%d\n",num[x][y]);
        }
        return 0;
    }
    for(int i=0;i<1<<n;i++)
        for(int j=1;j<=n;j++)
        if((i>>(j-1))&1) g[j][i]=1;
    for(int i=1;i<=m;i++) f[i]=0;
    for(int j=1;j<=p;j++)
    {
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==1) g[++t]=g[x]|g[y];
        else if(opt==2) g[++t]=g[x]&g[y];
        else if(opt==3)
        {
            int s=0;
            while(1)
            {
                int mx=0,id=0;
                for(int i=1;i<=n;i++)
                if(!((s>>(i-1))&1) && mx<a[i][y]) mx=a[i][y],id=i;
                s|=(1<<(id-1));
                if(g[x][s]){printf("%d\n",mx);break;}
            }
        }
    }
    return 0;
}
```
