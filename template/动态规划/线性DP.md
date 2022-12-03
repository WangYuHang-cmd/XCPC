## 线性DP

递推方程有一个线性关系，比如可以转化为一个二维矩阵的形式



## 模型整理：

### 1.LIS最长公共子序列模型

$$
f[i][j]按照以b[j]结尾的最长上升子序列可以划分为：
$$



```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
    	f[i][j]=f[i-1][j];
        if(a[i]==b[j]){
            int maxn=1;
            for(int k=1;k<j;k++){
                if(b[j]>b[k]) maxn=max(maxn,f[i-1][k]+1);
               	f[i][j]=max(maxn,f[i][j]);
            }
        }
    }
```

maxn为前缀最大值，因此考虑优化：

```cpp
for(int i=1;i<=n;i++){
    int maxn=1;
    for(int j=1;j<=n;j++){
    	f[i][j]=f[i-1][j];
        if(a[i]==b[j])f[i][j]=max(f[i][j],maxn);
        if(a[i]>b[j]) maxn=max(maxn,f[i-1][j]+1);
    }
}
```



### 2.最大子矩阵

当这一位什么都不做的时候：$f[i][j][k]=max(f[i-1][j][k],f[i][j-1][k])$

当仅选取第一列的某段区间时：$f[i][j][k]=max(f[l][j][k-1]+sum[i][1]-sum[l-1][1]) 1<=l<i$

当仅选取第二列的某段区间时：$f[i][j][k]=max(f[i][l][k-1]+sum[j][2]-sum[l-1][2]) 1<=l<j$

当i==j时，可以选取两列一起的$f[i][j][k]=max(f[l][l][k]+sum[i][1]+sum[i][2]-sum[l-1][1]-sum[l-1][2])$





## 数论+DP模型

### 1.公约数模型：https://codeforces.com/contest/1614/problem/D1

>对于一个数列，让你经过重新排列之后使得式子$∑_{i=1}^ngcd(a1,a2,…,ai)$的值最大，求最大的结果 。$a_i \le 2e7$

思路： $cnt[i]$表示i的i是其公约数的数的个数，因此有$cnt[i]-cnt[i*k]$表示是i的倍数但不是k的倍数的数的个数，有状态转移方程：

```cpp
for(int i=1;i<=M;++i) for(int j=i*i;j<=M;j+=i) 
    f[i] = max(f[i], cnt[j]*(j-i)+f[i]);  //从后往前转移，即选择从
```

$cnt[]$的处理方法：

```cpp
for(int i=1;i<=M;++i)
	for(int j=i+i;j<=tot;j+=i) 
    	cnt[i] += cnt[j];
```

为了优化，有迪利克雷前缀和优化：

```cpp
rep(j,1,idx)   //迪利克雷前缀和优化
    for(int c=M/prime[j];c>=1;c--) 
        cnt[c] += cnt[c*prime[j]];
for(int i=1;i<=M+1;++i){
		for(int k=1,j=prime[k]*i;j<=tot;j=prime[++k]*i) 
			f[j] = max(f[j],(LL)cnt[j]*(j-i)+f[i]);
```

