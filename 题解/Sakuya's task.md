### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102652/problem/D)
### ��Ŀ����
��
$$\sum_{i=1}^{n}\sum_{j=1}^{n}\varphi{(\gcd(i,j))}$$
��֤ $n\leq 10^{10}$
### ���
һ������ͣ����� $n$ ����ô�󣬾��ǶŽ�ɸ�����ˡ�

���ǻ���ʽ�ӣ����Է���
$$\text{ԭʽ}=\sum_{p=1}^{n}\varphi(p)(2\sum_{i=1}^{\lfloor\frac n p\rfloor}-1)$$

��Ȼ�����Ǹ�ʽ�ӿ���ֱ�ӶŽ�ɸ�ϣ����԰Ѻ����Ǹ�ʽ��Ҳ���� $g(\lfloor\frac n p\rfloor)$����
$$\text{ԭʽ}=\sum_{p=1}^{n}\varphi(p)g(\lfloor\frac n p\rfloor)$$
��Ҳ��һ���������ʽ��ֱ�����۷ֿ鼴�ɡ�

���Ӷ� $O(�ܹ�)$��

