## ST 表 & `跳表`

`根号跳表`

先开一个叫做`ST_small[N][sqrt(N)]`的数组，`ST_small[i][j]`意思为`[i,j]`区间内的维护的区间信息

```
for i (1,n):
	for j (1,sqrt(n)):
		ST_small[i][j] = xxx ;
```

定义`ST_big[i][j]`表示`[i,j*sqrt(N)]`的信息

```cpp
ST_big=[i][start]=ST_small[i][start*sqrt(n)];
ST_big[i][j]=ST_big[i][k*sqrt(n)] & ST_small[i+k*sqrt(n)+1][p] 共同维护
```

![image-20220223165517158](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20220223165517158.png)

根号跳表的原理是任何数都能表示为`n=k*sqrt(n)+i`



光速幂：

O(1)求斐波那契数列的第k项，k<=1e9,n<=1e7

sqrt(1e9)=31266=>先预处理出small[]$A^0,A^1, ... ,A^{31622}$

再预处理出big[]$A^{1\cdot 31622}, ... ,A^{31622\cdot 31622}$

每次查询$A^k=A^{big+small}$

