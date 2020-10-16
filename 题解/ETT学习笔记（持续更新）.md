## -1.什么是ETT / 为什么要学ETT
#### ~~ETT是一种化学物质，分子式是[$C_3H_6N_4S$](https://baike.baidu.com/item/ETT/4683984?fr=aladdin)~~
ETT全名Eular Tour Tree（欧拉游览树），是一种~~玄学的~~维护动态树的数据结构。

学ETT的理由：
1. 特别好写，特别好调
2. 可以支持动态树的大部分操作
3. 一只log跑得快（
4. ~~不想学LCT~~
## 0.前置知识
### 0.1 欧拉序
既然有Eular，自然离不开欧拉序。这个东西在ST表 $O(1)$ 求LCA中用到过，若不会请自行学习。

但是这里我们并不是用求LCA的那个欧拉序，而是稍微变形一下。这个在后面会讲到。
### 0.2 平衡树
这个不会的话，左转洛谷[模板区](https://www.luogu.com.cn/problem/P3369)包你学会。

正常情况下，常用的平衡树任选一种均可。
## 1.ETT的基础操作
首先我们先介绍ETT的基础操作：支持子树加，改父亲，求某个点到根的路径。
### 1.1 如何用括号序序维护子树信息。
为了维护第1,3个操作，我们需要使用一种特殊的序列——括号序，即：每个点访问时记录，退出时再记录。
```cpp
void dfs(int u)
{
    //push u
    for(int v:rd[u]) dfs(v);
    //push u
}
```
可以发现，这种括号序中每个点出现且仅出现2次。
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723001345graph%20(1).png)
比如上图，括号序就是12334556421（结果不唯一）。

我们考虑这样一种括号序有什么特殊性质：

1. 一个节点的子树的节点都是连续的。
2. 一个点 $v$ 在 $u$ 到根路径上当且仅当 $v$ 在欧拉序中 $u$ 第一次出现的位置前出现且仅出现一次。

第一个性质和dfs序类似，显然成立。考虑如何证明第二个性质：

如果我们将一个点第一次记录视为插入栈，第二次记录视为从栈中删除，显然可以发现访问到一个点时，栈中的元素都是它到根的路径。
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723225036p2.png)
如上图，绿线表示第一次记录，红线表示第二次记录。蓝色表示记录一次，棕色表示记录两次。显然访问5时1,2,4,5被记录一次。

可以发现 $u$ 到根路径上的点就是栈中只被记录一次的点，所以显然有第二个性质成立。

考虑如何利用这个性质：子树加显然就是区间修改，那么询问一个点到根的路径上点权和怎么办。

由于我们只需要被记录一次的点的点权和，考虑在第二次记录的时候把第一次记录的结果撤销。具体来说，一个结点第一次被记录时在序列中插入他的点权，第二次被记录时插入他的点权的相反数。
```cpp
void dfs(int u)
{
    //push w[u]
    for(int v:rd[u]) dfs(v);
    //push -w[u]
}
```

可以发现，我们只需要对该点第一次出现位置求一次前缀和，就可以知道它到根的路径的点权和。这样我们就完成了除了改父亲之外的所有操作。
### 1.2  如何用ETT维护动态树
在此之前，我们已经能够处理 $66.7\%$ 的操作了。但是好像至今为止所有的操作都可以用树剖来完成。。。

所以接下来就是维护动态树最重要的部分：改父亲。

我们考虑改父亲对括号序有什么要求：

其实可以发现，子树内部的括号序是不会变的，只是括号序整体的位置有所变化。

举个例子：
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723230138graph2.png)
考虑上图，$u$ , $v$ 是两颗子树，不妨用 $\text{{u}}$，$\text{{v}}$ 表示子树部分的欧拉序。按照1.1，我们可以写出它的一种括号序：
```
12334{u}{v}425667751
```
考虑我们将4的父亲改成5：
![](https://images.cnblogs.com/cnblogs_com/Flying2018/1812057/o_200723230531graph3.png)
我们可以再写出它的一种括号序：
```
1233254{u}{v}4667751
```
可以发现，4的子树部分的欧拉序并没有改变。变化的实质是 $\text{4{u}{v}4}$ 这段括号序向后移动了2个单位。

可以发现什么？假如我们用 $\text{{u}}$ 表示 $u$ 的子树的欧拉序，那么将 $u$ 的父亲改为 $v$ 本质就是把 $\text{{u}}$ 移动到 $v$ 在欧拉序中第一次出现的位置。

那么我们怎么维护呢？这本质是区间移动的过程，其实大部分平衡树都支持这种操作。不妨用平衡树维护序列的位置（注意不是数值），即改平衡树中序遍历的结果就是整个序列

特别的，由于我们需要查找某个节点第一次出现的位置。我们不妨记录下第一次出现的位置所代表的节点。那么它在平衡树上的位置就是序列中第一次出现的位置。

这个就比较好求了。每次不断跳在平衡树上的父亲记录经过的节点数。特别的，如果当前节点是其父亲的右儿子，那么还要加上左儿子 $\text{size}$。

我这里采用的是fhq-treap，因为这个平衡树自带split和merge操作，不用特别处理平衡树移动这种操作。

关键代码：
```cpp
split(root,kth(l[x])-1,lt,mt);//kth(u)是求u在平衡树中的位置
split(mt,kth(r[x]),mt,rt);//提取出l[u]~r[u]
st=merge(lt,rt);//将非l[u]~r[u]部分合并
split(st,kth(l[y]),lt,rt);//提取出l[y]，即要插入的节点
rt=merge(merge(lt,mt),rt);
```
这样，我们就完成了用ETT维护动态树的操作。
### 1.3 一些基础题目
#### 例：[[bzoj3786] 星系探索](https://darkbzoj.tk/problem/3786)
#### 题目大意
给定一颗有根树，支持子树加，修改父亲，询问某个点到父亲的点权和。
#### 题解
这就是一道ETT模板题，所有操作都是ETT的基础操作，直接维护即可。

时间复杂度 $O(n\log n)$。
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
## 2.ETT的一些奇怪技巧
### 2.1
