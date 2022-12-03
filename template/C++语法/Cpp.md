首先，感谢各位粉丝在评论区的积极留言。不求三连，多点点赞吧~

很多平台支持的 C++ 版本有高有低，正式比赛有可能就是 C++11，所以，下面的函数基本上是 C++11 所支持的。

本视频只是抛砖引玉，肯定讲不全，希望大家可以多在弹幕、评论区补充，相互学习最重要。



##### 强力推荐大家有空翻一下侯捷老师翻译的鼎鼎大名的《STL源码剖析》



#### upper_bound、lower_bound

一般升序使用



#### sort unique

deque 也可以 sort

sort  不单纯是快排，内部很复杂。

STL的sort算法，数据量大时采用快排算法，分段归并排序。一旦分段后的数据量小于某个门槛，就改用插入排序。如果递归层次过深，还会改用堆排序。详见 《STL源码剖析》 P389

所以，可能某些特殊情况下，手写快排会快，再加入一些奇怪的优化等会更快，例如随机化一下打乱有序列，小范围冒泡。

```cpp
vector<int>a;
sort(a.begin(),a.end());
a.erase(unique(a.begin(),a.end()),a.end());
```



#### partial_sort()

stl_algo.h 4672-4691

```cpp
  template<typename _RandomAccessIterator>
    inline void
    partial_sort(_RandomAccessIterator __first,
		 _RandomAccessIterator __middle,
		 _RandomAccessIterator __last)
    {
      // concept requirements
      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
	    _RandomAccessIterator>)
      __glibcxx_function_requires(_LessThanComparableConcept<
	    typename iterator_traits<_RandomAccessIterator>::value_type>)
      __glibcxx_requires_valid_range(__first, __middle);
      __glibcxx_requires_valid_range(__middle, __last);
      __glibcxx_requires_irreflexive(__first, __last);

      std::__partial_sort(__first, __middle, __last,
			  __gnu_cxx::__ops::__iter_less_iter());
    }

```

实现排序的**平均**时间复杂度为$O(NlogM)$，其中 N 指的是 [first, last) 范围的长度，M 指的是 [first, middle) 范围的长度。

![image-20210903222251792](C:\Users\19172\AppData\Roaming\Typora\typora-user-images\image-20210903222251792.png)

```cpp
vector<int>a;
dec(i,10,1)a.push_back(i);
partial_sort(a.begin(),a.begin()+3,a.end());
for(auto it:a)cout<<it<<" ";
```

```
1 2 3 10 9 8 7 6 5 4
```

可以像 sort 那样带上自定义函数

```cpp
vector<int>a;
rep(i,1,10)a.push_back(i);
partial_sort(a.begin(),a.begin()+3,a.end(),greater<int>());
for(auto it:a)cout<<it<<" ";
```

```
10 9 8 1 2 3 4 5 6 7
```



#### **nth_element**

与上面用法类似，复杂度 $O(n)$，建议记 `partial_sort`

注意，最后 $n$-th 元素在 `a.begin()+n` 的位置，下标从 `0` 开始

```cpp
srand(time(NULL));
vector<int>a;
rep(i,1,10)a.push_back(i);
random_shuffle(a.begin(),a.end());
nth_element(a.begin(),a.begin()+4,a.end(),greater<int>());
cout<<a[4]<<endl;
```



#### rbegin,back

```cpp
vector<int>a;
rep(i,1,10)a.push_back(i);
cout<<a.front()<<endl;
cout<<a.back()<<endl;
cout<<*a.begin()<<endl;
cout<<*a.rbegin()<<endl;

set<int>b;
rep(i,1,10)b.insert(i);
cout<<*b.begin()<<endl;
cout<<*b.rbegin()<<endl;
```



#### min max

```cpp
min(a,min(b,c))
```

```
min({a,b,c})
```

C++11，编译器会将其推导为initializer_list类型，产生一个initializer_list的临时对象。



#### max_element min_element

查找最大值、最小值对应的地址

```cpp
int a[]={1,4,3,2};
int main()
{
    cout<<max_element(a,a+4)-a<<endl;
    return 0;
}
```



#### prev_permutation next_permutation

这个大家应该很熟悉了

值得强调的是时间复杂度，全遍历 $O(n!)$，单次最坏 $O(n)$

```cpp
do
{
  
}while(next_permutation(a+1,a+n+1));
```



#### __int128

128位整数

输入输出要手写快读快写

如果有些题中间数据爆了 `long long`，可以强制转化成 `__int128` 进行处理



#### to_string

C++11，将逐个数字转化为字符串，支持double等，详见 basic_string.h 6413-6473

减少手写的时候，忘记特判 0 的尴尬



#### emplace_back

减少常数的写法

```cpp
struct TSY
{
    int age;
    TSY(int x)
    {
        age=x;
    }
};
int main()
{
    vector<TSY>save;
    save.emplace_back(21);
    save.push_back(TSY{21});
    return 0;
}
```



#### __gcd

看内部实现，如果传`__m, __n` 的时候其中一个为 0，那么会返回另一个非 0 数

```c++
  template<typename _EuclideanRingElement>
    _EuclideanRingElement
    __gcd(_EuclideanRingElement __m, _EuclideanRingElement __n)
    {
      while (__n != 0)
	{
	  _EuclideanRingElement __t = __m % __n;
	  __m = __n;
	  __n = __t;
	}
      return __m;
    }

```



#### __lg

当前数有几位，或者可以说最高位是第几位，如 $12=(1100)_2$, `__lg(12)=3`

stl_algobase.h 997-1021

```cpp
  inline _GLIBCXX_CONSTEXPR int
  __lg(int __n)
  { return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n); }
```

（clz表示Count Leading Zeros，统计前导零个数）

使用注意：`__builtin_clz` 当参数为0，结果未定义，所以 `__lg(0)`也会未定义

这个方法可以认为是O(1)的，而且效率比`log2` 高很多

详细说明：https://www.zhihu.com/question/35361094



#### rotate

```cpp
vector<int>a;
rep(i,1,10)a.push_back(i);
rotate(a.begin(),a.begin()+2,a.end());
for(auto it:a)cout<<it<<" ";
```

效果

```
1 2 3 4 5 6 7 8 9 10
3 4 5 6 7 8 9 10 1 2
```

复杂度 $O(n)$



#### reverse

写字符串常用

```cpp
string s;
cin>>s;
reverse(s.begin(),s.end());
cout<<s<<endl;
```



#### __builtin_popcount

__builtin 内建函数常数小的离谱

统计有多少个位为 1。它使用一张类似基于表的方法来进行位搜索。



#### shuffle

第 45 届国际大学生程序设计竞赛（ICPC）亚洲区域赛（南京）E.Evil Coordinate

https://ac.nowcoder.com/acm/contest/10272/E



一般比较多的写法：

```cpp
srand(time(NULL));
random_shuffle(a+1,a+n+1);
```
复杂度 $O(n)$

也可以，random库里的：

```cpp
unsigned seed=chrono::system_clock::now().time_since_epoch().count();
shuffle(save.begin(),save.end(),default_random_engine(seed));
```



#### memset fill

极其容易犯错~

这个东西估计很多人不知道怎么用，就知道 `memset(a,0,sizeof(a))`，想把数组`a` 中元素全设置成 `1`，写了个`memset(a,1,sizeof(a))`

我们要理解一下，memset是将某一块内存中的内容全部设置为指定的值是以**字节为单位**进行赋值的

![image-20210904100100491](C:\Users\19172\AppData\Roaming\Typora\typora-user-images\image-20210904100100491.png)

int 32位 4字节

填充的时候，每个字节是 0x01，即$[00000001]_2$

所以不建议这么写，建议使用fill

```cpp
int arr[maxn];
int main()
{
    fill(arr,arr+maxn,1);
    return 0;
}
```



#### iota

对 `[arr,arr+n-1]` 的元素赋值连续递增的值，这个 `iota` 在 `GO` 里也有类似含义，但是用法很不同

```cpp
iota(arr,arr+n,0); // 0 1 2 3 4 5...
```



#### next prev

移动迭代器

大部分容器时间复杂度 O(n)

```cpp
set<int>s;

int main()
{
    rep(i,1,3e5)s.insert(i);
    auto it=s.begin();
    auto newit=next(it,3e5-1);
    cout<<*newit<<endl;
    return 0;
}

```



#### isalpha isalnum isdigit

判断字符是否是字母，数字或字母，数字



#### random库

random库提供了均匀分布、伯努利分布、泊松分布、正态分布等多种分布类型，有兴趣可以自己查一下，不展开讲了



#### bit库

有很多处理二进制东西比较方便的函数，不过大多数环境跟不上，不展开讲了

https://www.apiref.com/cpp-zh/cpp/header/bit.html



#### bitset

下下...下期开坑.jpg



#### pb_ds

下下...下期开坑.jpg