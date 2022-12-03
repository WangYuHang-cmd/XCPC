## `Manacher `算法

只能够解决最长回文串的问题。

时间复杂度：$O(n)$

回文串一共有两类：

1.`abba`

2.`ababa`

![image-20220121172648775](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20220121172648775.png)

![image-20220121172657811](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20220121172657811.png)

```cpp
void init(){
    b[idx++]='$';
    b[idx ++]='#';
    for(int i=0;a[i];++i) b[idx++]=a[i],b[idx++]='#';
    b[idx++]='^';
    n=idx;
}

void manacher(){
    int mr=0,mid;//之前扫过的半径最大的位置+1
    for(int i=0;i<n;++i){
        if(i<mr) p[i]=min(p[2*mid-i], mr-i);
        else p[i]=1;
        while(b[i-p[i]] == b[i+p[i]]) p[i]++;
        if(i+p[i]>mr){
            mr=i+p[i];
            mid=i;
        }
    }
}

void solve(){
	scanf("%s",a);
    n=strlen(a);
    
    init();
    manacher();
    
    rep(i,0,n-1) ans=max(ans, p[i]);
    print(ans-1);
}
```



##### 最长回文

>链接：https://ac.nowcoder.com/acm/problem/14894
>
>  有两个长度均为n的字符串A和B。可以从A中选一个可以为空的子串A[l1..r1]，B中选一个可以为空的子串B[l2..r2]，满足r1=l2，然后把它们拼起来（A[l1..r1]+B[l2..r2]）。求用这样的方法能得到的最长回文串的长度。注意：求的不是本质不同的回文串个数哦！！！

做法：先用manacher预处理出两个字符串对应的字符数组，然后遍历两个字符串的每一个位置；注意题目中的r1=l2,即B的第一个字符会覆盖A的最后一个字符。因此在新的马拉车回文串中我们从2(除去开头符号和`#`)开始，然后B从`i-2`开始，我们需要从B之前一个字符开始匹配

```cpp
void solve(){
    n=read(); len=2*n+1;
    scanf("%s%s",a,b);
    init(a, idxa, pa);
    init(b, idxb, pb);
    len=n*2+1; 
    manacher(pa, idxa, p1);
    manacher(pb, idxb, p2);
    int ans=1;
    for(int i=2;i<=len;++i){
        int tmp=max(p1[i],p2[i-2]);
        while(pa[i-tmp] == pb[i+tmp-2]) tmp++;
        ans=max(ans,tmp);
    }
    print(ans-1);
}
```

### P4555 [国家集训队]最长双回文串

> 求*S*的最长双回文子串T*T*,即可将*T*分为两部分*X*，*Y*，（|X|,|Y|≥1）且*X*和*Y*都是回文串。

manacher在预处理每个点的最长回文半径的同时递推出以每个`#`开始的最长的回文串`ll[i]`和以每个`#`结尾的最长回文串`rr[i]`，由递推式:

`for(int i=1;i<n;i++) ll[i]=max(ll[i], ll[i-2]-2);`

`for(int i=1;i<n;i++) rr[i]=max(rr[i], rr[i+2]-2);`

然后在统计的时候我们就可以通过`ll[i]+ll[i+2*ll[i]]`和`rr[i]+rr[i-2*rr[i]]`统计出所有情况的回文串相加。

```
const int N=200010,M=N*2,mod=1e9+7;
char a[N],b[N];
int idx,n,ans,p[N],ll[N],rr[N]; //ll[i]表示以i位开头的最长回文子串的长度


void init(){
	b[idx++]='$'; 
	b[idx++]='#';
	for(int i=0;a[i];++i) 
		b[idx++]=a[i],b[idx++]='#';
	b[idx++]='^'; 
	n=idx;
}

void manacher(){
	int mr=0,mid=0;
	for(int i=0;i<n;++i){
		if(i<mr) p[i]=min(p[2*mid-i], mr-i);
		else p[i]=1;
		while(b[i-p[i]]==b[i+p[i]]) p[i]++;
		if(i+p[i]>mr){
			mr=i+p[i];
			mid=i;
		}
		ll[i-p[i]+1]=max(ll[i-p[i]+1], p[i]-1);
		rr[i+p[i]-1]=max(rr[i+p[i]-1], p[i]-1);
	}
	for(int i=1;i<n;i++) ll[i]=max(ll[i], ll[i-2]-2);
	for(int i=1;i<n;i++) rr[i]=max(rr[i], rr[i+2]-2);
}
void solve(){
	scanf("%s",a);
	init();
	manacher();
	for(int i=1;i<n;i+=2) 
		if(ll[i+2*ll[i]]) ans=max(ans, ll[i]+ll[i+2*ll[i]]);
	for(int i=1;i<n;i+=2) 
		if(rr[i-2*rr[i]]) ans=max(ans, rr[i]+rr[i-2*rr[i]]);
	print(ans);	
}
```

#### 回文

>链接：https://ac.nowcoder.com/acm/problem/17062
> 删除字符串的第一个字母。
> 删除字符串的最后一个字母。
> 在字符串的头部添加任意一个你想要的字母。
> 在字符串的尾部添加任意一个你想要的字母。
>
> 删除一个第 i 种英文字母需要的花费是 Ai，添加一个第 i 种英文字母的花费是 Bi。
> 请问将字符串 S 变成回文串需要的最小花费是多少？

蛮巧妙地一道题目。首先回文串的话，我们考虑从左边删除有两种情况：

> 1.删除左边所有的串
>
> 2.删除左边部分串，然后在右边添加剩下没删的

假设我们枚举到了第`i`个位置，我们可以考虑对于第i个字符删除的代价是多少，到第i个字符位置的最优策略是什么，这个可以通过递推得到：

```cpp
dell[i]=dell[i-1]+del[s[i]-'a'];
pre[i]=min(dell[i], min(pre[i-1], dell[i-1])+add[s[i]-'a']);
```

右边同理

然后我们使用manacher与处理出每一个位置的最长回文半径，然后扫一遍，从左边右边删各和答案min一下即可
