### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102652/problem/D)
### 题目大意
求
$$\sum_{i=1}^{n}\sum_{j=1}^{n}\varphi{(\gcd(i,j))}$$
保证 $n\leq 10^{10}$
### 题解
一看有求和，而且 $n$ 还这么大，就是杜教筛无疑了。

考虑化简式子，可以发现
$$\text{原式}=\sum_{p=1}^{n}\varphi(p)(2\sum_{i=1}^{\lfloor\frac n p\rfloor}-1)$$

显然后面那个式子可以直接杜教筛上，可以把后面那个式子也看成 $g(\lfloor\frac n p\rfloor)$，有
$$\text{原式}=\sum_{p=1}^{n}\varphi(p)g(\lfloor\frac n p\rfloor)$$
这也是一个卷积的形式。直接数论分块即可。

复杂度 $O(能过)$。

