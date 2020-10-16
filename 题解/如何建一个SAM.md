### ���ָı���[OI WIKI](https://oi-wiki.org/string/sam/)
�ȴ�һ���򵥵��������֣�

����һ����������һ��ͼ��ʹ���ܹ���ʾ���������Ӵ���

��Ȼһ���Ӵ�����һ����׺��ǰ׺������һ������Ȼ�ķ�ʽ���ǰ����к�׺�ӽ�trie�

���統ǰ����aaba��

![](https://images.cnblogs.com/cnblogs_com/Flying2018/1821917/o_200806000430graph.png)

�������Ƿ��֣������ǲ����е��˷ѣ�����"ba"����ַ���������������������顣

![](https://images.cnblogs.com/cnblogs_com/Flying2018/1821917/o_200806001228graph.png)

��Ȼ���ͽṹ�Ѿ����ܸ����ˣ���ô���ǲ�������辶�������ܲ����ҵ�һ���㷨����һ��DAG�������trie�������罫����������ɫԲȦ�ϲ������Ա�ɣ�

![](https://images.cnblogs.com/cnblogs_com/Flying2018/1821917/o_200806001628graph%20(1).png)

���ǿ϶��ġ�����㷨����SAM��

��������չʾһЩ�򵥵��ַ����ĺ�׺�Զ�����

��������ɫ��ʾ��ʼ״̬������ɫ��ʾ��ֹ״̬��

�����ַ���  $s=\varnothing$ ��

![](https://oi-wiki.org/string/images/SAM/SA.svg)

�����ַ���  $s=\texttt{a}$��

![](https://oi-wiki.org/string/images/SAM/SAa.svg)

�����ַ���  $s=\texttt{aa}$��

![](https://oi-wiki.org/string/images/SAM/SAaa.svg)

�����ַ���  $s=\texttt{ab}$��

![](https://oi-wiki.org/string/images/SAM/SAab.svg)

�����ַ���  $s=\texttt{abb}$��

![](https://oi-wiki.org/string/images/SAM/SAabb.svg)

�����ַ���  $s=\texttt{abbb}$��

![](https://oi-wiki.org/string/images/SAM/SAabbb.svg)

---

�������е㸴�ӣ���ô���Ǹ���ν�����һ����׺�Զ����أ�

�����ȸ������ۣ����ǿ����� $O(n)$ ʱ���ڽ��������ĺ�׺�Զ���~~���Ҵ��뼫��~~��

�ڽ���׺�Զ���֮ǰ��������Ҫ���˽�һ��һЩ���ʣ�

���Ƕ��� $\operatorname{endpos}(t)$ Ϊĸ�ַ��� $s$ �ķǿ��Ӵ� $t$ ���ַ��� $s$ �е����н���λ�õļ��ϡ�

���� s="$\texttt{aabab}$"��t="$\texttt{ab}$"����ô $\operatorname{endpos}(t)=\{2,4\}$��

����endpos���ϵ����� [OI WIKI](https://oi-wiki.org/string/sam/#endpos) ���ĺ���ϸ�������е㷱������������ҵ���⣺

����endpos�������ǿ���һ�����ι�ϵ�����и����Ϊ $\varnothing$��ÿ���ڵ��endpos���϶���ȫ��������ӵ�endpos���ϡ��Ҷ�������û�����ȹ�ϵ�ĵ㣬endpos��Ϊ $\varnothing$��

��ʵ��������ι�ϵ����parent�������ں�����õ���

����֤����� [OI WIKI](https://oi-wiki.org/string/sam/#endpos)��

���Է��֣�����SAM��ĳ���ڵ� $u$�����ʾ���ַ����� $s$ ����Ϊ $len_u$ ��ǰ׺�г��ȴ���ĳһ���ȵĺ�׺���� $len_u$ ��ȻҲ�� $u$ ��ʾ���Ӵ�������Ǹ���

����֤����$len_u$ ����������ʱ���ַ����ĳ��ȡ�

���ǿ��Ǽ� $\operatorname{link}(u)=v$ Ϊ��� $len_v$ ʹ $\operatorname{endpos}(u)\subseteq\operatorname{endpos}(v)$��

��ô $u$ ��ʾ���ַ����� $s$ ����Ϊ $len_u$ ��ǰ׺�г��ȴ��� $len_{\operatorname{link}(u)}$ �ĺ�׺��

֤����� [OI WIKI](https://oi-wiki.org/string/sam/#link)��

���統s="$\texttt{abcbc}$"ʱ��SAM��parent��������ʾ��

![](https://oi-wiki.org/string/images/SAM/SA_suffix_links.svg)

---

���������ǿ��Կ�ʼ��SAM�ˡ�

�ȷ�һ�����ӣ�
```cpp
void insert(int c)
{
    int p=las,q=las=++cnt;
    len[q]=len[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
    if(!p) fa[q]=1;
    else
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) fa[q]=np;
        else
        {
            int nq=++cnt;
            memcpy(ch[nq],ch[np],sizeof(ch[nq]));
            fa[nq]=fa[np];
            fa[np]=fa[q]=nq;
            len[nq]=len[p]+1;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
}
```
������Ҫע��һ�㣬����� $\text{fa}$ ��������ʵ�� $\text{link}$������������` fa[ch[u][c]]=u `֮��Ĺ�ϵ��

����һ����������γ����ڸ�ʲô��
```cpp
    int p=las,q=las=++cnt;
    len[q]=len[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
```
$las$ ��������һ�β���Ľڵ㣬�� $q$ ������Ҫ����Ľڵ㡣

������Ǽ� $s_u$ ��ʾ�ڵ� $u$ �ܱ�ʾ������Ӵ�����ô $s_q=s_{p}+c$��

������Ȼ�� `len[q]=len[p]+1`������������Ҫ�� $q$ �� $fa$��

���������˸о��ر���KMP��������֪�� $s_{fa[p]}$ һ���� $s_p$ ��һ����׺������ϣ���ҵ�һ���Ѿ����ڵ�״̬��������һ�� $c$ �ߵ���չ��

��������ڵ�ǰ $p$ ������ $c$ �ߵ���չ����ô��Ȼ $q$ �������һ���µ���չ��ֱ�Ӹ�ֵ `ch[p][c]=q`��Ȼ����������ҡ�
```cpp
    if(!p) fa[q]=1;
    else
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) fa[q]=np;
```
����ҵ����˻���û���ҵ� $c$ �ߵ���չ��˵����ǰ��������ǰ������ô����ֱ���� `fa[q]=1`��

���������ҵ���һ�� $c$ �ߵ���չ����Ȼ���Ǵ��� $c$ �ߵ���չ������Ӵ����������ж������չ�ǲ���ֱ�ӵģ����� $s_{np}=s_p+c$ ���� $s_{np}=s_p+c\dots$��

�����ǰ�ߣ���ô��Ȼ $np$ ���� $q$ ��ǰ������ $\operatorname{endpos}(q)\subseteq\operatorname{endpos}(np)$��ֱ�Ӹ�ֵ���ɡ�

����Ƚ��鷳���� $np$ ��ʾ��ĳ������ $q$ ��ǰ����
```cpp
        else
        {
            int nq=++cnt;
            memcpy(ch[nq],ch[np],sizeof(ch[nq]));
            fa[nq]=fa[np];
            fa[np]=fa[q]=nq;
            len[nq]=len[p]+1;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
```
�������������������Ҫ���ѳ�һ���� $nq$��������� $s_{nq}=s_p+c$ ��

���Է������� $nq$ �� $np$ ��һ���Ӽ���$np$ ������ת�Ʊ� $nq$ Ҳ���С�

��ô `fa[nq]=fa[np]` �� `fa[np]=fa[q]=nq` Ҳ�ͺ���Ȼ�ˡ�

��������$nq$ ������ $np$ ��Ϊ�� $len$ ���̵ĵ㣬��ô��Ȼ���������� $np$ �ı߶������� $nq$��

�������Ǿͽ�����һ��SAM��

��Ȼ�����ռ临�Ӷ� $O(n)$����Ϊ���ǲ���һ���ַ���������2���㡣����ʱ�临�Ӷȵ�֤�����[OI WIKI](https://oi-wiki.org/string/sam/#_7)��

---
���������ǿ�һЩ������·��
### 1.���ʲ�ͬ�Ӵ�����
���ȶ��ַ��� $S$ �����׺�Զ�����

ÿ�� $S$ ���Ӵ����൱���Զ����дӸ���ʼ��·������˲�ͬ�Ӵ��ĸ��������Զ�������1Ϊ���Ĳ�ͬ·����������

���ǵ�SAM��һ��DAG����ͬ·������������ͨ����̬�滮���㡣��Ȼ���Ҫȥ���մ���

ʱ�临�Ӷ� $O(|S|)$ ��

��Ȼ���ַ����кܴ�����ԣ���Ϊÿһ�ζ���Ҫdfsһ�顣���Դ����ʱ����õĶ�������������

����֪��һ���ַ���Ψһ��Ӧһ���ڵ㣬��һ���ڵ��ʾ���ǳ���Ϊ $len_u$ ��ǰ׺�г����� $(len_{fa},len_u]$ �ĺ�׺��

������Ȼ�� $\text{��}=\sum{(len_{fa_u}-len_u)}$��
### 2.�ֵ���� $k$ ���Ӵ�
���Է���һ��SAM��һ��DAG���������ǿ���dp�����һ����������Ӵ�������

��ô�����ԣ����Ǵ� 'a'->'z' ���β鿴���ҵ���һ�������Ӵ�����ǰ׺�� $\geq k$ ��ת�Ʊߣ�ת�Ƽ��ɡ�

ʱ�临�Ӷ� $O(|S|)$��
### 3.��̬����ִ���
�����ı��� $S$ ������ѯ�ʴ� $T_i$����̬ѯ�� $T_i$ �� $S$ �г��ִ����� 

����֪����SAM�������ǽ�һ��trieѹ����õ��Ľ�����������ǿ���ֱ����ת�Ʊߵõ���

���õ��Ľ����״̬�����Ǵ𰸡�״̬������dfsԤ���������

ʱ�临�Ӷ� $O(|S|+|T|)$��

### 4. ������ǰ׺��LCS
�Ȿ���ǹ�SA�ܵ�һ�������⣬��ƫƫ��Щ��������Ҫ��̬���ַ���

���Է��֣�parent��������һ��ѹ����trie�����������еĹؼ��ڵ㡣

�������trie������Ȼ���ǿ���ֱ����trie�ϵ�LCA����parent�������ľ���һ��������������ȻҲ����������

$\color{black}{\text{O}}\color{red}{\text{IerWanHong}}$ $\texttt{orz}$��
