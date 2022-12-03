## 珂朵莉树ODT

可以较快地实现：

- 区间加
- 区间赋值
- 求区间第k大值
- 求区间n次方和

>珂朵莉树的思想在于随机数据下的区间赋值操作很可能让大量元素变为同一个数。所以我们以三元组<l,r,v>的形式保存数据（区间 [l,r] 中的元素的值都是v）

存储形式：

```cpp
struct Node{
	int l,r;
    mutable int c;
    node(int l,int r,int v):l(l),r(r),v(v){};
    bool operator<(const Node& W)const{return l<W.l;}
};
set<Node> ds;
```

1.split操作，区间分裂

```cpp
//断开”的操作，把<l,r,v>断成<l,pos-1,v>和<pos,r,v>：
set<Node>::iterator split(int pos){
    auto now=ds.lower_bound(Node(pos,0,0));// 寻找左端点大于等于pos的第一个节点
    if(now!=ds.end()&&now->l == pos)
        return now;
   	now --; //往前数一个节点
    int l=now->l,r=now->r,v=now->v;
    ds.erase(now);
    ds.insert(Node(l, pos-1, v));
    return ds.insert(Node(pos,r,v)).x; //nsert默认返回值是一个pair，第一个成员是以pos开头的那个节点的迭代器
}
```

2.assign操作，区间赋值

```cpp
void assign(LL l,LL r,LL v){ //将[l,r]赋值为v
    auto end=split(r+1),begin=split(l);
	ds.erase(begin, end);
    ds.insert(Node(l,r,v));
}
```



例题：

>从现在到学期结束还有 n 天(从 1 到 n 编号)，他们一开始都是工作日。接下来学校的工作人员会**依次**发出 q 个指令，每个指令可以用三个参数 l,r,k 描述：
>如果 k=1 ，那么从 l 到 r （包含端点）的所有日子都变成**非**工作日。
>如果 k=2 ，那么从 l 到 r （包含端点）的所有日子都变成**工作日**。

将assign()修改一下，暴力统计即可

```cpp
void assign(int l,int r,int v){
	int tot = 0;
	auto end=split(r+1),begin=split(l),now=begin;
	for(;now!=end;now++){
		tot += (now->v)*(now->r-now->l+1);
	}
	ds.erase(begin, end);
    ds.insert(Node(l,r,v));
	sum -= tot;
	sum += (r - l + 1) * v;
}
```

3.add()区间加

直接暴力加法即可

```cpp
void add(int l,int r,int v){
    auto begin=split(l),end=split(r+1);
    for(;begin!=end;begin++)
        begin->v += v;
}
```

4.rank()区间第k小

```cpp
int rank(int l,int r,int k){
    vector<pair<int,int>> tmp;
    auto begin=split(l),end=split(r+1);
    for(;begin!=end;begin++)
        tmp.push_back({begin->v, begin->r-begin->l+1});
	sort(tmp.begin(), tmp.end());
    for(auto u:tmp){
        k -= u.y;
        if(k<=0) return u.x;
    }
    return -1; 
}
```

5.sum_of_pow()区间n次方的和

```cpp
int sum_of_pow(int l,int r,int x,int y){
	int tot=0;
	auto begin=split(l),end=split(r+1);
	for(;begin!=end;begin++){
		tot = (tot + fpower(begin->v, x, y) * (begin->r-begin->l+1) % y)%y;
	}
	return tot;
}
```



ODT经典题：

- 区间加
- 区间赋值
- 求区间第k大值
- 求区间n次方和

```cpp
#define int LL
const int N=200010,M=N*2,mod=1e9+7;
struct Node{
	int l,r;
	mutable int v;
	Node(int _l,int _r,int _v):l(_l),r(_r),v(_v){};
	bool operator<(const Node &W)const{return l<W.l;}
};
set<Node> ds;
int n,m,seed,vmx;
int sum=n;

set<Node>::iterator split(int pos){
	auto now=ds.lower_bound(Node(pos,0,0));
	if(now!=ds.end() && now->l == pos)
		return now;
	now --;
	int l=now->l,r=now->r,v=now->v;;
	ds.erase(now);
	ds.insert(Node(l,pos-1,v));
	return ds.insert(Node(pos, r, v)).x;
}

void assign(int l,int r,int v){
	int tot = 0;
	auto end=split(r+1),begin=split(l);
	ds.erase(begin, end);
    ds.insert(Node(l,r,v));
}

void add(int l,int r,int v){
    auto begin=split(l),end=split(r+1);
    for(;begin!=end;begin++)
        begin->v += v;
}

int kth(int l,int r,int k){
    vector<pair<int,int>> tmp;
    auto begin=split(l),end=split(r+1);
    for(;begin!=end;begin++)
        tmp.push_back({begin->v, begin->r-begin->l+1});
	sort(tmp.begin(), tmp.end());
    for(auto u:tmp){
        k -= u.y;
        if(k<=0) return u.x;
    }
    return -1; 
}

int sum_of_pow(int l,int r,int x,int y){
	int tot=0;
	auto begin=split(l),end=split(r+1);
	for(;begin!=end;begin++){
		tot = (tot + fpower(begin->v, x, y) * (begin->r-begin->l+1) % y)%y;
	}
	return tot;
}
LL rnd()
{
    LL ret = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ret;
}
void solve(){
	n=read(),m=read(),seed=read(),vmx=read();
	rep(i,1,n){
		int r=rnd();
		ds.insert(Node(i, i, r%vmx+1));
	} 
	while(m--){
		//input
		LL ty=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1,x,y;
		if(l>r) swap(l,r);
		if(ty==3) x=rnd()%(r-l+1)+1;
		else x=rnd()%vmx+1;
		if(ty==4) y=rnd()%vmx+1;

		if(ty==1){
			add(l,r,x);
		}
		else if(ty==2){
			assign(l,r,x);
		}
		else if(ty==3){
			print(kth(l, r, x));
		}
		else{
			print(sum_of_pow(l ,r, x, y));
		}
	}
}
```

