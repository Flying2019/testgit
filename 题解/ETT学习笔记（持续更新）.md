## -1.ʲô��ETT / ΪʲôҪѧETT
#### ~~ETT��һ�ֻ�ѧ���ʣ�����ʽ��[$C_3H_6N_4S$](https://baike.baidu.com/item/ETT/4683984?fr=aladdin)~~
ETTȫ��Eular Tour Tree��ŷ��������������һ��~~��ѧ��~~ά����̬�������ݽṹ��

ѧETT�����ɣ�
1. �ر��д���ر�õ�
2. ����֧�ֶ�̬���Ĵ󲿷ֲ���
3. һֻlog�ܵÿ죨
4. ~~����ѧLCT~~
## 0.ǰ��֪ʶ
### 0.1 ŷ����
��Ȼ��Eular����Ȼ�벻��ŷ�������������ST�� $O(1)$ ��LCA���õ�����������������ѧϰ��

�����������ǲ���������LCA���Ǹ�ŷ���򣬶�����΢����һ�¡�����ں���ὲ����
### 0.2 ƽ����
�������Ļ�����ת���[ģ����](https://www.luogu.com.cn/problem/P3369)����ѧ�ᡣ

��������£����õ�ƽ������ѡһ�־��ɡ�
## 1.ETT�Ļ�������
���������Ƚ���ETT�Ļ���������֧�������ӣ��ĸ��ף���ĳ���㵽����·����
### 1.1 �������������ά��������Ϣ��
Ϊ��ά����1,3��������������Ҫʹ��һ����������С��������򣬼���ÿ�������ʱ��¼���˳�ʱ�ټ�¼��
```cpp
void dfs(int u)
{
    //push u
    for(int v:rd[u]) dfs(v);
    //push u
}
```
���Է��֣�������������ÿ��������ҽ�����2�Ρ�
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723001345graph%20(1).png)
������ͼ�����������12334556421�������Ψһ����

���ǿ�������һ����������ʲô�������ʣ�

1. һ���ڵ�������Ľڵ㶼�������ġ�
2. һ���� $v$ �� $u$ ����·���ϵ��ҽ��� $v$ ��ŷ������ $u$ ��һ�γ��ֵ�λ��ǰ�����ҽ�����һ�Ρ�

��һ�����ʺ�dfs�����ƣ���Ȼ�������������֤���ڶ������ʣ�

������ǽ�һ�����һ�μ�¼��Ϊ����ջ���ڶ��μ�¼��Ϊ��ջ��ɾ������Ȼ���Է��ַ��ʵ�һ����ʱ��ջ�е�Ԫ�ض�����������·����
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723225036p2.png)
����ͼ�����߱�ʾ��һ�μ�¼�����߱�ʾ�ڶ��μ�¼����ɫ��ʾ��¼һ�Σ���ɫ��ʾ��¼���Ρ���Ȼ����5ʱ1,2,4,5����¼һ�Ρ�

���Է��� $u$ ����·���ϵĵ����ջ��ֻ����¼һ�εĵ㣬������Ȼ�еڶ������ʳ�����

�����������������ʣ���������Ȼ���������޸ģ���ôѯ��һ���㵽����·���ϵ�Ȩ����ô�졣

��������ֻ��Ҫ����¼һ�εĵ�ĵ�Ȩ�ͣ������ڵڶ��μ�¼��ʱ��ѵ�һ�μ�¼�Ľ��������������˵��һ������һ�α���¼ʱ�������в������ĵ�Ȩ���ڶ��α���¼ʱ�������ĵ�Ȩ���෴����
```cpp
void dfs(int u)
{
    //push w[u]
    for(int v:rd[u]) dfs(v);
    //push -w[u]
}
```

���Է��֣�����ֻ��Ҫ�Ըõ��һ�γ���λ����һ��ǰ׺�ͣ��Ϳ���֪����������·���ĵ�Ȩ�͡��������Ǿ�����˳��˸ĸ���֮������в�����
### 1.2  �����ETTά����̬��
�ڴ�֮ǰ�������Ѿ��ܹ����� $66.7\%$ �Ĳ����ˡ����Ǻ�������Ϊֹ���еĲ�������������������ɡ�����

���Խ���������ά����̬������Ҫ�Ĳ��֣��ĸ��ס�

���ǿ��Ǹĸ��׶���������ʲôҪ��

��ʵ���Է��֣������ڲ����������ǲ����ģ�ֻ�������������λ�������仯��

�ٸ����ӣ�
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723230138graph2.png)
������ͼ��$u$ , $v$ ������������������ $\text{{u}}$��$\text{{v}}$ ��ʾ�������ֵ�ŷ���򡣰���1.1�����ǿ���д������һ��������
```
12334{u}{v}425667751
```
�������ǽ�4�ĸ��׸ĳ�5��
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723230531graph3.png)
���ǿ�����д������һ��������
```
1233254{u}{v}4667751
```
���Է��֣�4���������ֵ�ŷ����û�иı䡣�仯��ʵ���� $\text{4{u}{v}4}$ �������������ƶ���2����λ��

���Է���ʲô������������ $\text{{u}}$ ��ʾ $u$ ��������ŷ������ô�� $u$ �ĸ��׸�Ϊ $v$ ���ʾ��ǰ� $\text{{u}}$ �ƶ��� $v$ ��ŷ�����е�һ�γ��ֵ�λ�á�

��ô������ôά���أ��Ȿ���������ƶ��Ĺ��̣���ʵ�󲿷�ƽ������֧�����ֲ�����������ƽ����ά�����е�λ�ã�ע�ⲻ����ֵ��������ƽ������������Ľ��������������

�ر�ģ�����������Ҫ����ĳ���ڵ��һ�γ��ֵ�λ�á����ǲ�����¼�µ�һ�γ��ֵ�λ��������Ľڵ㡣��ô����ƽ�����ϵ�λ�þ��������е�һ�γ��ֵ�λ�á�

����ͱȽϺ����ˡ�ÿ�β�������ƽ�����ϵĸ��׼�¼�����Ľڵ������ر�ģ������ǰ�ڵ����丸�׵��Ҷ��ӣ���ô��Ҫ��������� $\text{size}$��

��������õ���fhq-treap����Ϊ���ƽ�����Դ�split��merge�����������ر���ƽ�����ƶ����ֲ�����

�ؼ����룺
```cpp
split(root,kth(l[x])-1,lt,mt);//kth(u)����u��ƽ�����е�λ��
split(mt,kth(r[x]),mt,rt);//��ȡ��l[u]~r[u]
st=merge(lt,rt);//����l[u]~r[u]���ֺϲ�
split(st,kth(l[y]),lt,rt);//��ȡ��l[y]����Ҫ����Ľڵ�
rt=merge(merge(lt,mt),rt);
```
���������Ǿ��������ETTά����̬���Ĳ�����
### 1.3 һЩ������Ŀ
#### ����[[bzoj3786] ��ϵ̽��](https://darkbzoj.tk/problem/3786)
#### ��Ŀ����
����һ���и�����֧�������ӣ��޸ĸ��ף�ѯ��ĳ���㵽���׵ĵ�Ȩ�͡�
#### ���
�����һ��ETTģ���⣬���в�������ETT�Ļ���������ֱ��ά�����ɡ�

ʱ�临�Ӷ� $O(n\log n)$��
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cstdlib>
#define N 200010
#define ll long long
using namespace std;
int cnt,id[N],siz[N],ch[N][2],fa[N],typ[N],rnd[N];
ll val[N],sum[N],tag[N];
int newnode(int v,int type)
{
    siz[++cnt]=1;sum[cnt]=val[cnt]=v*type;
    typ[cnt]=id[cnt]=type;
    rnd[cnt]=rand();
    return cnt;
}
void update(int x)
{
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
    id[x]=id[ch[x][0]]+id[ch[x][1]]+typ[x];
    sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+val[x];
}
void set_tag(int u,ll v){val[u]+=typ[u]*v; sum[u]+=id[u]*v; tag[u]+=v;}
void push_down(int u)
{
    if(!tag[u]) return;
    if(ch[u][0]) set_tag(ch[u][0],tag[u]);
    if(ch[u][1]) set_tag(ch[u][1],tag[u]);
    tag[u]=0;
}
inline void chgf(int u,int f){if(u) fa[u]=f;}
int merge(int x,int y)
{
    if(!x || !y) return x+y;
    push_down(x);push_down(y);
    if(rnd[x]<rnd[y]){ch[x][1]=merge(ch[x][1],y);chgf(ch[x][1],x);update(x);return x;}
    else {ch[y][0]=merge(x,ch[y][0]);chgf(ch[y][0],y);update(y);return y;}
}
void split(int x,int k,int &l,int &r)
{
    if(!x){l=r=0;return;}
    push_down(x);
    if(k<=siz[ch[x][0]]){r=x;fa[ch[x][0]]=0;split(ch[x][0],k,l,ch[x][0]);chgf(ch[x][0],x);update(x);return;}
    else{l=x;fa[ch[x][1]]=0;split(ch[x][1],k-siz[ch[x][0]]-1,ch[x][1],r);chgf(ch[x][1],x);update(x);return;}
}
int root,lt,mt,rt,st;
void add(int l,int r,ll v)
{
    split(root,l-1,lt,mt);
    split(mt,r-l+1,mt,rt);
    set_tag(mt,v);
    root=merge(merge(lt,mt),rt);    
}
int ptot=0;
int kth(int x)
{
    int son=1,ans=0;
    while(x)
    {
        if(son) ans+=siz[ch[x][0]]+1;
        son=ch[fa[x]][1]==x;
        x=fa[x];
        // printf("%d ",x);
        // ++ptot;
        // if(ptot>1000) throw;
    }
    return ans;
}
int w[N];
vector<int>rd[N];
int l[N],r[N];
void dfs(int u)
{
    l[u]=newnode(w[u],1);
    root=merge(root,l[u]);
    for(int v:rd[u]) dfs(v);
    r[u]=newnode(w[u],-1);
    root=merge(root,r[u]);
}
char opt[4];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
    {
        int fa;
        scanf("%d",&fa);
        rd[fa].push_back(i);
    }
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    dfs(1);
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int x,y;
        scanf("%s%d",opt,&x);
        if(opt[0]=='Q')
        {
            split(root,kth(l[x]),lt,rt);
            printf("%lld\n",sum[lt]);
            root=merge(lt,rt);
        }
        else if(opt[0]=='C')
        {
            scanf("%d",&y);
            split(root,kth(l[x])-1,lt,mt);
            split(mt,kth(r[x]),mt,rt);
            st=merge(lt,rt);
            split(st,kth(l[y]),lt,rt);
            rt=merge(merge(lt,mt),rt);
        }
        else if(opt[0]=='F')
        {
            scanf("%d",&y);
            add(kth(l[x]),kth(r[x]),y);
        }
    }
    return 0;
}
```
## 2.ETT��һЩ��ּ���
### 2.1
