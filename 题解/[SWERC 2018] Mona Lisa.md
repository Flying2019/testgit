### [����](https://codeforces.com/gym/102465/problem/J)
������Ȼ��һ�����������������Ǵ��� $2^{25}$ �� $A$ �������Ȼ����� $B,C,D$���鿴�Ƿ��� $A=B\text{ ^ }C\text{ ^ }D$������ʱ�临�Ӷ� $O(2^{\frac n 2})$��

��������Ż�����Ȼ���ǲ�û�����úá�4��������������ʡ��������ǲ����� $A,B$ ��Ϊ1�飬$C,D$ ��Ϊ1�顣

���ǲ���������� $A\text{^}B$ �к� $p$ λΪ0�Ľ����ͬ�� $C,D$��Ȼ���ٺϲ������Է��֣�����������ʱ�临�Ӷ� $O(2^p+2^{\frac {n-p} 2})$��

��Ȼ���� $p=\frac n 3$ ʱ������ʱ�临�Ӷ� $O(n^{\frac n 3})$������ͨ����
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<unordered_map>
#include<vector>
#define B 18
#define N (1<<B)
#define ll long long
using namespace std;
typedef unsigned long long uint64;
typedef unsigned long long ull;
struct node{
    uint64 s[2],seed;
    void init(){s[0]=seed;s[1]=seed ^ 0x7263d9bd8409f526;}
    uint64 nxt() {
        uint64 s0 = s[0];
        uint64 s1 = s[1];
        uint64 result = s0 + s1;
        s1 ^= s0;
        s[0] = ((s0 << 55) | (s0 >> 9)) ^ s1 ^ (s1 << 14);
        s[1] = (s1 << 36) | (s1 >> 28);
        return result;
    }
}a[4];
struct pnode{
    ull v;
    int id;
};
unordered_map<ull,vector<pnode> >s[2];
struct qnode{
    ull v;
    int i1,i2;
};
unordered_map<ull,vector<qnode> >t;
int main()
{
    int n;
    scanf("%d",&n);
    cin>>a[0].seed>>a[1].seed>>a[2].seed>>a[3].seed;
    ull o=N-1,p=(1ull<<n)-1;
    for(int _=0;_<4;_++) a[_].init();
    // ull p0=0,p1=0,p2=0,p3=0;
    // for(int i=1;i<=287;i++) p0=a[0].nxt();
    // for(int i=1;i<=17609;i++) p1=a[1].nxt();
    // for(int i=1;i<=122886;i++) p2=a[2].nxt();
    // for(int i=1;i<=59914;i++) p3=a[3].nxt();
    // cout<<((p0^p1^p2^p3)&p)<<endl;
    for(int i=1;i<=N;i++)
    {
        ull u=a[0].nxt();
        s[0][u&o].push_back((pnode){u,i});
    }
    for(int i=1;i<=N;i++)
    {
        ull u=a[1].nxt();
        if(s[0].count(u&o))
        {
            for(auto h:s[0][u&o])
            t[(h.v^u)&p].push_back((qnode){h.v^u,h.id,i});
        }
    }
    for(int i=1;i<=N;i++)
    {
        ull u=a[2].nxt();
        s[1][u&o].push_back((pnode){u,i});
    }
    for(int i=1;i<=N;i++)
    {
        ull u=a[3].nxt();
        if(s[1].count(u&o))
        {
            for(auto h:s[1][u&o])
            {
                ull v=h.v^u;
                if(!t.count(v&p)) continue;
                for(auto c:t[v&p])
                if(((c.v^v)&p)==0){printf("%d %d %d %d",c.i1,c.i2,h.id,i);return 0;}
            }
        }
    }
    return 0;
}
```
