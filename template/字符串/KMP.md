## KMP

### border

对于字符串满足$Prefix[i]==Suffix[i]$,即前缀和后缀完全相同，则称为一个border

### 周期和循环节

###### 循环周期

对于字符串S和正整数p，如果有`S[i]=S[i-p]`,对于`p<i<=|S|`成立，则称p为字符串S的一个周期，特殊的`p=|S|`一定是S的周期

###### 循环节

若S的周期满足$p \mid \abs{S}$,周期整除总长度，则为循环节.

##### 重要性质

>1.p是S的周期 等价于 |S| -p是S的一个`Border`，但是border不具有二分性
>
>2.S的Border的Border也是S的Border
>
>3.p,q为S的周期，则gcd(p,q)也为S的周期
>
>4.一个串的Border数量为O(n)个，但是组成了O(logn)个等差数列



#### Next数组的求解(下标从1开始)

`next[1]=0`

前缀i的border一定是前缀i-1的border，因此可以通过next数组的border链



### 前缀函数定义

给定一个长度为$n$的字符串$s$，其 **前缀函数**$\pi[i]$被定义为一个长度为$n$的数组 。 其中$\pi[i]$的定义是：

1. 如果子串$s[0...i]$有一对相等的真前缀与真后缀：$s[0...k-1]$和$s[i-(k-1)...i]$,namo有 ，$\pi[i]$就是这个相等的真前缀（或者真后缀，因为它们相等：)）的长度，也就是$\pi[i]=k$；
2. 如果不止有一对相等的，那么$\pi[i]$就是其中最长的那一对的长度；
3. 如果没有相等的，那么$\pi[i]=0$。

简单来说$\pi[i]$就是，子串$s[0...i]$最长的相等的真前缀与真后缀的长度。

用数学语言描述如下：

$\pi[i]=max_{k=0...i}\{k:s[0...k-1]\}=s[i-(k-1)...i]$

特别地，规定$\pi[0]=0$。

Next数组求解：

![20181005223221225.gif](https://cdn.acwing.com/media/article/image/2021/08/19/92692_1d98988500-20181005223221225.gif)

改进后的KMP算法：

![KMP.gif](https://cdn.acwing.com/media/article/image/2021/08/19/92692_19abc73e00-KMP.gif)

模板1：

```cpp
//求ne数组，考察前面那个，如果后一个可以匹配就+1，否则退到ne[j]
for(int i=2,j=0;i<=n;i++){
    while(j&&p[i]!=p[j+1])j=ne[j];
    if(p[i]==p[j+1]) j++;
    ne[i]=j;
}

//KMP匹配
for(int i=1,j=0;i<=m;i++){
    while(j&&s[i]!=p[j+1]) j=ne[j];  //j不停回溯直到j为第一位而且第二位还不与i匹配
    if(s[i]==p[j+1]) j++;  //如果可以匹配，则j往前走一位
    if(j==n){
        //匹配成功
        printf("%d ",i-j);
    }
}
```

模板2：

```cpp
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
```

##### 下标从`0`开始的KMP

```cpp
void kmp_nxt(string &s){
    nxt[0]=0;
    for(int i=1,j=0;i<s.size();++i){
        while(j&&s[i]==s[j]) j=nxt[j-1];
        if(s[i]==s[j]) j++;
        nxt[i]=j;
    }
}

LL kmp(string &s,string &p){
    LL ans=0;
    for(int i=0,j=0;i<s.size();++i){
        while(j&&s[i]!=p[j]) j=nxt[j-1];
        if(s[i]==p[j] && ++j==p.size()) {
            ++ans;
            j=nxt[j-1];
        }
    }
    return ans;
}
```



### KMP的优化

2.1.3 KMP算法中$next[]$数组的优化

​    我们观察我们在匹配的过程中，假如在$j$位置失配了，模式串必然会跳到其对应$j=next[j]$处，但是 由于在构$next[]$造的时候若有此时则$p[j]=p[next[j]]$需要再次递归，即令$next[j]=next[next[j]]$，因此在$next[]$构造的时候若有模式串$p[j]=p[next[j]]$则令$next[j]=next[next[j]]$即可

```cpp
void next_fast(){
    int i, j, k;                                   
    for(i = 2, j = 0 ; i <= m ; i++){
		if(word[i] == word[j])
			ne[i] = ne[j];
         else
			ne[i] = j;
       	while(j > 0 && word[i] != word[j])
            j = ne[j-1];
		if(word[i] == word[j])
			j ++;
	}
}
```



朴素字符串匹配方法：

![朴素.gif](https://cdn.acwing.com/media/article/image/2021/08/19/92692_0b57b52800-%E6%9C%B4%E7%B4%A0.gif)

### 

### KMP的拓展

- 扩展KMP
- KMP自动机，Border树
- AC自动机
- Trie图
