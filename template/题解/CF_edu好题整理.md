[Educational Codeforces Round 27](https://codeforces.com/contest/845) 

G. Shortest Path Problem? [2300]

非常经典的一道题。n个点m条边的无向图，求1到n的路径异或最小值.

> 相同类型的题目有：https://www.luogu.com.cn/problem/P4151，只不过求的是路径异或最大值，处理方法完全一样。

首先，dfs出图中的所有环（任意形态的所有环，因为环之间相互异或能够变成其他环）。

然后随便选择一条1~n的路径的异或和，在所有环中选择任意个值使得答案最大/最小。下面就是线性基的板子了。

Code:https://codeforces.com/contest/845/submission/170961140



[Educational Codeforces Round 100 (Rated for Div. 2)](https://codeforces.com/contest/1463) 

D. Pairs  [1900]

大意是1~2n你可以随意两两一对组成pair，然后对所有n对pair，你选择其中x对的最小值和剩下n-x对的最大值组成集合b。问对于给定的n和集合b，有多少种可能的x的取值。

首先我们看第二个样例

> a:	1	4	5	9	10
>
> b:	2	3	6	7 	8

我们从小到大观察随着x取值不同需要满足哪些条件。（x=0和x=n特判）对于a数组取前x个为取最小pair，显然有一个贪心策略是对应和这x个组成pair的是b数组中最大的x个，然后再检查b数组剩下的最小的n-x个能不能和a数组中最大的n-x个按次序组成对满足对于任意i都有a[i]>b[i]。这个显然是可以分别预处理出来的。

首先我用一个mx[i]和mn[i]分别表示在b数组中第一个大于&小于a[i]的位置。然后分别预处理出x等于哪些值时满足a前x个按次序小于b数组后x个和x取哪些值时a后x个按次序大于b前x个。然后再扫一遍预处理的数组即可得到答案。

Code:https://codeforces.com/contest/1463/submission/171013162



