## OI中的时空复杂度分析

一般来说运行次数再1kw-1ww次以内都是能在一秒内运行完毕的

一般ACM或者笔试题的时间限制是1秒或2秒。
在这种情况下，C++代码中的操作次数控制在 107∼108107∼108 为最佳。

下面给出在不同数据范围下，代码的时间复杂度和算法该如何选择：

1.n≤30n≤30, 指数级别, dfs+剪枝，状态压缩dp

2.n≤100n≤100 => O(n3)O(n3)，floyd，dp，高斯消元

3.n≤1000n≤1000 => O(n2)O(n2)，O(n2logn)O(n2logn)，dp，二分，朴素版Dijkstra、朴素版Prim、Bellman-Ford

4.n≤10000n≤10000 => O(n∗n√)O(n∗n)，块状链表、分块、莫队

5.n≤100000n≤100000 => O(nlogn)O(nlogn) => 各种sort，线段树、树状数组、set/map、heap、拓扑排序、dijkstra+heap、prim+heap、spfa、求凸包、求半平面交、二分、CDQ分治、整体二分

6.n≤1000000n≤1000000 => O(n)O(n), 以及常数较小的 O(nlogn)O(nlogn) 算法 => 单调队列、 hash、双指针扫描、并查集，kmp、AC自动机，常数比较小的 O(nlogn)O(nlogn) 的做法：sort、树状数组、heap、dijkstra、spfa

7.n≤10000000n≤10000000 => O(n)O(n)，双指针扫描、kmp、AC自动机、线性筛素数

8.n≤109n≤109 => O(n√)O(n)，判断质数

9.n≤1018n≤1018 => O(logn)O(logn)，最大公约数，快速幂

10.n≤101000n≤101000 => O((logn)2)O((logn)2)，高精度加减乘除

11.n≤10100000n≤10100000 => O(logk×loglogk)，k表示位数

12.O(logk×loglogk)，k表示位数，高精度加减、FFT/NTT

作者：yxc
链接：https://www.acwing.com/blog/content/32/
来源：AcWing

![image-20210716203019092](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210716203019092.png)