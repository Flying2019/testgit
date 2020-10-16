### [链接](http://115.236.49.52:83/contest/1530/problem/3)
考虑所有操作离线，令 $f_u$ 表示 $u$ 的答案，用 $g_{t,u}$ 表示$t$ 时间 $u$ 子树内的黑点的 $v$ 之和，$h_{t,u}$ 表示 $t$ 时间 $u$ 子树内部有无询问。

考虑枚举每个点作为 $lca$ 的价值，显然有 $\displaystyle f_u=\sum_t{(\sum_{v\in son}{g_{t,v}\times (h_{t,u}-h_{t,v})}+h_{t,u}\times[u\text{在t时间是黑点}])}$。

显然，里面的东西可以直接树形dp搞定，但是 $t$ 难以处理。可以发现，对于一个 $v$，$g_{t,v}$ 只有 $0/v$，而且其中 $v$ 值只有几段区间。

我们不妨对于每段区间单独计算贡献，即 $\displaystyle f_u=\left(\sum_{v\in son\ and\ \text{v is black in}[l,r]}v\times  \sum_{t\in[l,r]}{\left(h_{t,u}-h_{t,v}\right)}\right)+h_{t,u}\times[u\text{在t时间是黑点}]$。

可以发现，我们对于每个 $u$ 将所有区间加入一个树状数组，直接维护，然后每次查所有子树的询问 $q$。但是这样是 $O(n^2\log n)$ 的。

发现这个可以直接套上树上启发式合并，每个点继承儿子信息，可以做到 $O(n\log^2 n)$，可以通过此题。
