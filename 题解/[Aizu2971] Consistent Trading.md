### [����](https://vjudge.net/problem/Aizu-2971/origin)
### ��Ŀ����
����һЩ�����ת��������ϵ���� $a_1=2\times a_2,\ a_2=2\times a_3$�����Ƿ����ì�ܡ�
### ���
���ȣ����ڲ�ͬ����ͨ����ȻҪ�������ۡ�

������������ִ�С����Ȼ���ǿ�����ȷ��һ������λ1������������Ϊ1�Žڵ㡣Ȼ�����нڵ��ʾ��1�Žڵ�ı�����ʽ��

��Ȼ�����һ����ϵ�����ӵ��������Ѿ����ڱ�����ϵ�����뵱ǰ��ϵ��������Ȼ����ì�ܡ�����ֱ��dfsһ�飬Ȼ��������б��ж��Ƿ����ì�ܼ��ɡ�

��ô����������һ�����⣺���ﱶ��ʱָ������ģ��߾�����Ȼ�� $\text{TLE}$����ֱ��ȡ $\log$ ��Ȼ���ھ��Ȳ�������⡣

�������ǲ�����Ҫ֪��ĳ���������1�Žڵ�ļ���������ֻ��Ҫ֪��һ�����ֺ���һ�������Ƿ���ȼ��ɡ�����ֱ�� $\text{Hash}$ һ�¼��ɡ�

ע�����ﵥ $\text{Hash}$ ���ܱ�����д˫ $\text{Hash}$ ���ɡ�

���Ӷ� $O(n+m)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#define ll long long
#define ld long double
#define N 400010
#define eps 1e-12
using namespace std;
int nxt[N],to[N],head[N],cnt;
ll mods[4]={998244353,19260817,1000000007,1000000009},w[N];
bool vis[N];
ll ksm(ll a,ll b,ll mod)
{
    ll r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=r*a%mod;
        a=a*a%mod;
    }
    return r;
}
struct hs_4{
    ll a[4];
    hs_4(){a[0]=a[1]=a[2]=a[3]=1;}
    ll& operator [](int c){return a[c];}
    bool operator ==(hs_4 b){return a[0]==b[0] && a[1]==b[1] && a[2]==b[2] && a[3]==b[3];}
    bool operator !=(hs_4 b){return a[0]!=b[0] || a[1]!=b[1] || a[2]!=b[2] || a[3]!=b[3];}
    void operator *=(ll c){for(int i=0;i<4;i++) a[i]=a[i]*c%mods[i];}
    void operator /=(ll c)
    {
        for(int i=0;i<4;i++) a[i]=a[i]*ksm(c,mods[i]-2,mods[i])%mods[i];
    }
}dis[N];
void add(int u,int v,ll w1)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=w1;
    head[u]=cnt;
}
void dfs(int u)
{
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        hs_4 d=dis[u];
        if(w[i]>0) d*=w[i];
        else d/=-w[i];
        if(vis[v]){if(d!=dis[v]){puts("No");exit(0);} continue;}
        dis[v]=d;
        dfs(v);
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        ll w;
        scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w);
        add(v,u,-w);
    }
    for(int i=1;i<=n;i++)
    if(!vis[i])dfs(i);
    puts("Yes");
    return 0;
}
```
