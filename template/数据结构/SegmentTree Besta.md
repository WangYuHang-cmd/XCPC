## SegmentTree Besta

板子题[CF1290E]

>对于序列有三种操作:
>
>`1 l r x`对于$i \in [l,r] ,a_i = a_i + x$
>
>`2 l r x 对于`$i\in [l,r],a_i=min(a_i, x)$
>
>`3 l r` 求解$\sum_{l}^{r}a_i$

解法：

用线段树维护区间最大值mx，区间次大值tmx，区间和sum，区间最大值出现次数cnt，加法标记tag 。

对于第二种操作，如果一个区间mx≤x那么无事发生，可以跳过其所有子区间。如果se<x<mx，那么sum=sum−(mx−x)×cnt,mx=x

注意这里子区间的mx,sum并没有更改，相当于 mx同时作为一个修改标记，当前区间比子区间的mx小时，要进行sum=sum−(mx−mx[fa])×cnt的pushdown操作，打完标记之后就可以跳过了。对于其它情况，暴力对其子区间求解。

对于操作二：

```cpp
void get_mn(int u,int l,int r,int d){
		if(tr[u].l>=l&&tr[u].r<=r){
			if(tr[u].mx<=d) return ;
			if(tr[u].tmx<d){
				tr[u].sum -= (LL)(tr[u].mx-d)*(tr[u].r-tr[u].l+1);
				tr[u].mx = d;
				return ;
			}
			push_down(u);
			get_mn(u<<1,l,r,d); get_mn(u<<1|1,l,r,d);
			push_up(u);
			return ;
		}
		push_down(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) modify(u<<1, l, r, d);
		if(r>mid) modify(u<<1|1, l, r, d);
		push_up(u);
	}
```

因此`push_down()`函数需要特殊进行改动

```cpp
void push_down(int u){
		if(tr[u].tag){
			if(tr[u<<1].mx) tr[u<<1].mx += tr[u].tag;
			if(tr[u<<1].tmx) tr[u<<1].tmx += tr[u].tag;
			if(tr[u<<1|1].mx) tr[u<<1|1].mx += tr[u].tag;
			if(tr[u<<1|1].tmx) tr[u<<1|1].tmx += tr[u].tag;
			tr[u<<1].sum += tr[u].tag*(tr[u].r-tr[u].l+1);
			tr[u<<1|1].sum += tr[u].tag*(tr[u].r-tr[u].l+1);
			tr[u<<1].tag += tr[u].tag;
			tr[u<<1|1].tag += tr[u].tag;
			tr[u].tag = 0;
		}
		if(tr[u<<1].mx > tr[u].mx){
			tr[u<<1].sum -= (tr[u<<1].mx-tr[u].mx)*(tr[u<<1].r-tr[u<<1].l+1);
			tr[u<<1].mx = tr[u].mx;
		}
		if(tr[u<<1|1].mx > tr[u].mx){
			tr[u<<1|1].sum -= (tr[u<<1].mx-tr[u].mx)*(tr[u<<1|1].r-tr[u<<1|1].l+1);
			tr[u<<1|1].mx = tr[u].mx;
		}
	}
```



```cpp
struct Segment_Tree{
	struct Node{
		int l,r;
		LL mx,tmx,tag,sum;
	}tr[N<<2];
	void push_up(int u){
		tr[u].mx=tr[u<<1].mx,tr[u].tmx=tr[u<<1].tmx;
		if(tr[u<<1|1].mx>tr[u].mx){
			tr[u].tmx=tr[u].mx,tr[u].mx=tr[u<<1|1].mx;
		}
		else if(tr[u<<1|1].mx>tr[u].tmx) tr[u].tmx=tr[u<<1|1].mx;
		if(tr[u<<1|1].tmx>tr[u].tmx) tr[u].tmx=tr[u<<1|1].tmx;
		tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
	}
	void push_down(int u){
		if(tr[u].tag){
			if(tr[u<<1].mx) tr[u<<1].mx += tr[u].tag;
			if(tr[u<<1].tmx) tr[u<<1].tmx += tr[u].tag;
			if(tr[u<<1|1].mx) tr[u<<1|1].mx += tr[u].tag;
			if(tr[u<<1|1].tmx) tr[u<<1|1].tmx += tr[u].tag;
			tr[u<<1].sum += tr[u].tag*(tr[u].r-tr[u].l+1);
			tr[u<<1|1].sum += tr[u].tag*(tr[u].r-tr[u].l+1);
			tr[u<<1].tag += tr[u].tag;
			tr[u<<1|1].tag += tr[u].tag;
			tr[u].tag = 0;
		}
		if(tr[u<<1].mx > tr[u].mx){
			tr[u<<1].sum -= (tr[u<<1].mx-tr[u].mx)*(tr[u<<1].r-tr[u<<1].l+1);
			tr[u<<1].mx = tr[u].mx;
		}
		if(tr[u<<1|1].mx > tr[u].mx){
			tr[u<<1|1].sum -= (tr[u<<1].mx-tr[u].mx)*(tr[u<<1|1].r-tr[u<<1|1].l+1);
			tr[u<<1|1].mx = tr[u].mx;
		}
	}
	void build(int u,int l,int r){
		tr[u]={l,r};
		if(l==r){
			tr[u]={l,r,0,0,0,0};
			return ;
		}
		int mid=(l+r)>>1;
		build(u<<1,l,mid); build(u<<1|1,mid+1,r);
		push_up(u);
	}
	void insert(int u,int pos,int d){
		if(tr[u].l==tr[u].r){
			tr[u].mx = tr[u].sum = d;
			return ;
		}
		push_down(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(pos<=mid) insert(u<<1,pos,d);
		else insert(u<<1|1,pos,d);
		push_up(u);
	}
	void get_mn(int u,int l,int r,int d){
		if(tr[u].l>=l&&tr[u].r<=r){
			if(tr[u].mx<=d) return ;
			if(tr[u].tmx<d){
				tr[u].sum -= (LL)(tr[u].mx-d)*(tr[u].r-tr[u].l+1);
				tr[u].mx = d;
				return ;
			}
			push_down(u);
			get_mn(u<<1,l,r,d); get_mn(u<<1|1,l,r,d);
			push_up(u);
			return ;
		}
		push_down(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) modify(u<<1, l, r, d);
		if(r>mid) modify(u<<1|1, l, r, d);
		push_up(u);
	}
	void modify(int u,int l,int r,int d){
		if(tr[u].l>=l&&tr[u].r<=r){
			if(tr[u].mx) tr[u].mx += d;
			if(tr[u].tmx) tr[u].tmx += d;
			tr[u].sum += ((LL)tr[u].r-tr[u].l+1)*d;
			tr[u].tag += d;
			return ;
		}
		push_down(u);
		int mid=(tr[u].l+tr[u].r)>>1;
		if(l<=mid) modify(u<<1,l,r,d);
		if(r>mid) modify(u<<1|1,l,r,d);
		push_up(u);
	}
	LL query(int u,int l,int r){
		if(tr[u].l>=l&&tr[u].r<=r){
			return tr[u].sum;
		}
		push_down(u);
		int mid=(tr[u].l+tr[u].r)>>1;
		LL ans=0;
		if(l<=mid) ans += query(u<<1,l,r);
		if(r>mid) ans += query(u<<1|1,l,r);
		return ans;
	}
}T;
```

