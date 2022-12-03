# 平衡树

## Treap

$$
Treap=Tree+Heap
$$



#### 前置知识：

##### 1.BST(Binary Search Tree)二叉搜索树

**BST：** *当前节点的左子树中的任何一个点的权值都是严格小于当前结点的权值，右子树反之*

![image-20210815160654495](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210815160654495.png)

BST的中序遍历一定是一个有序序列

***BST的本质：动态维护一个有序序列***



##### 2.Heap 堆（Treap使用的是大根堆的性质）

Heap，大根堆，即一颗所有根节点的权值大于所有其儿子节点的权值的数据结构.如图便是一个大根堆：

![image-20210816144301585](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816144301585.png)



## 平衡树：

平衡树是一颗基于BST和Heap的数据结构

### Treap解决的问题：

**一颗随机的BST期望高度是logn，这样在进行插入和查询的时候的时间复杂度便是O(logn)级别。但是，如果随意的插入，二叉搜索树有可能退化成链表，其各种操作时间复杂度也就会退化成O(n)：**：

![image-20210816144446029](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816144446029.png)

但是我们期望中的BST应该是：

![image-20210816144525497](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816144525497.png)

因此，就诞生出了平衡树：对于每个点，我们不仅在权值上维护BST的性质，我们还维护一个val值，这个值是由随机生成的(越随机越好)，然后我们通过一些奇奇怪怪的操作来一直维护这一棵二叉搜索树维持第二张图的性质，即之后会提到的左旋和右旋。



##### 平衡树的用途：在只考虑前四种用途的情况下，我们可以借助STL中的set容器来代替平衡树（实际上set就是一颗红黑树）

1.插入：递归找到位置并插入 ___STL set insert()

2.删除：将删除的位置变成叶子节点之后删除 __STL erase

3.找前驱/后继：中序遍历中的前一个位置和后一个位置____STL_ set ++

```python
//找前驱伪代码
if(p->left):
    p=p->left
    while(p->right) p=p->right
    return p;
else:
    while(p->father>p) p=p->father
    return p;
```

4.找最大值和最小值：__STL_set_____/begin()___/end()-1

5.求某一个值得排名

6.求排名是k的数是哪个

7.比某个数小的最大值

8.比某个数大的最小值

##### Treap的存储

```cpp
Node{
	int l,r;
	int key,val; //key是二叉搜索树内用来排序的关键字，val是大根堆内的值，即排序优先级
    int cnt,size; //cnt存储的是当前权值的数的个数，size是以当前节点为根节点的树中数的个数
} tr[N];
int root,idx;  //root存储Treap的根节点，idx是内存分配的编号；
```

##### Treap的维护值的更新

```cpp
void push_up(int &p){ //很类似与线段树，这个操作就是对于额外维护的信息，用子节点来更新父节点
    tr[p].size=tr[tr[p].l].size+tr[tr[p].r].size+tr[p].cnt; //我们额外维护的信息是树的大小，对于p节点的树的大小，等于左儿子为根的子树的大小+右儿子为根的子树的大小+p节点处的相同数值的数的个数
}
```

##### Treap的创建节点

```cpp
int get_node(int key){  //创建一个权值为key的节点
    int u=++idx; //申请到一个内存的编号,便是我们要创建的这一个节点
    tr[u].key=key;
 	tr[u].val=rand(); //此处val越随机越好，因为这样可以保证不退化
    tr[u].cnt=tr[u].size=1; //此时当前节点的大小和节点形成子树的大小都是1
    return u; //最后再返回对应的内存池分配编号
}
```

##### Treap的左旋与右旋

![image-20210816150620531](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816150620531.png)

这张图将会贯穿始终.

右旋操作即将根节点x的左儿子y旋转到根节点，然后y的右儿子“掉”到原来根节点x的左儿子上。我们可以在一系列操作在之后，加入y的val值大于x的val值了，那么为了维护val值满足大根堆的性质，我们可以对整棵树进行右旋操作

```cpp
 void zig(int &p){  //对p节点进行右旋操作
    int q=tr[p].l;  //找到左儿子，即左边这幅图中我们通过x找到y
    tr[p].l=tr[q].r; //将x的左儿子变成z，如图右边右旋之后z滑落到x的左边
    tr[q].r=p;  //右旋之后根节点y的右儿子是x
    p=q;  //右旋之后，q成为新的根节点
    push_up(tr[p].r),push_up(p); //由于x的形态还有y的形态都发生了变化，因此要分别对这两个点进行更新 
}
```

##### 左旋操作：左旋操作即从图中的右边变成左边：

```cpp
void zag(int &p){
    int q=tr[p].r;
    tr[p].r=tr[q].l;
    tr[q].l=p;
    p=q;
    push_up(tr[p].l),push_up(p);
}
```

一开始的建树：此时用了一个小小的trick，为了保证不出现边界问题，我们将原树先用负无穷和正无穷来建好框架，后面再往里面添加和删除即可：

![image-20210816152541426](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816152541426.png)

```cpp
void build(){
    get_node(-INF),get_node(INF);  
    root=1;
    tr[root].r=2;
    push_up(root);

    if(tr[1].val<tr[2].val) zag(root); //be careful!!!!!!!由于是随机生成的数，所以有可能需要左旋
}
```

##### 插入操作

```cpp
//insert a value in position p 
void insert(int &p,int key){  //在p节点的子树中要插入权值为key的节点
    if(!p)  p=get_node(key);  //如果没有这个节点，就申请一块新的节点进行插入
  	else if(tr[p].key==key) tr[p].cnt++; //如果当前节点的值正好相等，就这个值的个数++
    else if(tr[p].key>key){
        insert(tr[p].l,key);  //BST的性质，比当前是数小，就在左子树中插入
        if(tr[tr[p].l].val>tr[p].val) zig(p);  //如果插入之后左子树的val值大，就右旋维护Treap
    }
    else{  //否则在右子树插入，做同样的维护
        insert(tr[p].r,key);
        if(tr[tr[p].r].val>tr[p].val) zag(p);
    }
    push_up(p);  //由于insert操作使得树的形态发生了变化，所以需要通过变化的子节点来更新一下父节点
}
```

##### 删除操作,还是参考这张图

![image-20210816155153366](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816155153366.png)

```cpp
void remove(int &p,int key){
    if(!p) return ; //由于此数不在Treap中，所以无需操作
    if(tr[p].key==key){
        if(tr[p].cnt>1) tr[p].cnt--;  //说明有多个相同的值，值的计数-1即可
        else if(tr[p].l||tr[p].r){  //如果不是叶子节点，就需要通过旋转把根节点旋转到叶子节点上进行删除
            if(!tr[p].r||tr[tr[p].l].val>tr[tr[p].r].val){   
                zig(p);
                remove(tr[p].r,key);
            }
            else{
                zag(p);
                remove(tr[p].l,key);
            }            
        }
        else p=0;   //说明是叶子节点，直接删除即可
    }
    else if(tr[p].key>key) 
        remove(tr[p].l,key); //比根节点小，就在左子树中找到并删除
    else 
        remove(tr[p].r,key); //同理，在右子树中找到并删除
    push_up(p);  //最后再更新一遍父节点
}
```

对于下面的操作，只要明白Node中维护的cnt和size的含义就可以轻松写出来了

##### 给定一个值来查找这个值在BST中序遍历中的排名：

```cpp
//get rank by given value
int get_rank_by_key(int p,int key){
    if(!p) return 0; //the value not exists
    else if(key==tr[p].key) return tr[tr[p].l].size+1;  
    else if(key<tr[p].key) return get_rank_by_key(tr[p].l,key);
    else return tr[tr[p].l].size+tr[p].cnt+get_rank_by_key(tr[p].r,key);
}
```

##### 给定一个中序遍历的排名，来求对应值：

```cpp
//get value by given rank
int get_key_by_rank(int p,int rank){
    if(!p) return INF;
    else if(rank<=tr[tr[p].l].size) return get_key_by_rank(tr[p].l,rank);
    else if(rank<=tr[tr[p].l].size+tr[p].cnt) return tr[p].key;
    else return get_key_by_rank(tr[p].r,rank-tr[tr[p].l].size-tr[p].cnt);
}
```

##### 求在Treap中，比给定数大的最小的数

```cpp
//get the greatest number less than key
int get_pre(int p,int key){
    if(!p) return -INF;
    else if(key<=tr[p].key) return get_pre(tr[p].l,key);
    else return max(tr[p].key,get_pre(tr[p].r,key));
}
```

在Treap中，求比给定数小的最大的数

```cpp
//get the least number greater than key
int get_next(int p,int key){
    if(!p) return INF;
    else if(key<tr[p].key) return min(tr[p].key,get_next(tr[p].l,key));
    else return get_next(tr[p].r,key);
}
```



附上例题的AC代码： （150+行，稍有不注意，眼角两行泪。一杯茶一包烟，百行代码调一天）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

#define MAXN 100010
using namespace std;

const int INF=1e9+7;

struct Node{
    int l,r;  //左右指针指向左右儿子分配的内存编号
    int key,val; //记录权值和维护堆性质的val
    int cnt,size;  //当前数的个数，当前子树中数的个数
} tr[MAXN];
int root,idx=0;
int n;

//子节点更新父节点信息
void push_up(int &u){
    tr[u].size=tr[tr[u].l].size+tr[tr[u].r].size+tr[u].cnt;
}

//右旋
void zig(int &p){
    int q=tr[p].l;
    tr[p].l=tr[q].r;
    tr[q].r=p;
    p=q;
    push_up(tr[p].r),push_up(p);
}

//左旋
void zag(int &p){
    int q=tr[p].r;
    tr[p].r=tr[q].l;
    tr[q].l=p;
    p=q;
    push_up(tr[p].l),push_up(p);
}

//create new point
int get_node(int key){
    int u=++idx;  //get new area
    tr[u].key=key;
    tr[u].val=rand();
    tr[u].size=tr[u].cnt=1;
    return u;
}

//build the prime of the tree
void build(){
    get_node(-INF),get_node(INF);
    root=1;
    tr[root].r=2;
    push_up(root);
    
    if(tr[1].val<tr[2].val) zag(root); //be careful!!!!!!!
}

//insert a value in position p 
void insert(int &p,int key){
    if(!p)  p=get_node(key);
    else if(tr[p].key==key) tr[p].cnt++;
    else if(tr[p].key>key){ //insert into the left
        insert(tr[p].l,key);
        
        if(tr[tr[p].l].val>tr[p].val) zig(p);
    }
    else{
        insert(tr[p].r,key);
        
        if(tr[tr[p].r].val>tr[p].val) zag(p);
    }
    push_up(p);
}

//remove a value
void remove(int &p,int key){
    if(!p) return ;
    else if(tr[p].key==key){
        if(tr[p].cnt>1) tr[p].cnt--;
        else if(tr[p].l||tr[p].r){  //if not the leaf Node
            if(!tr[p].r||tr[tr[p].l].val>tr[tr[p].r].val){   //if the left son s bigger 
                zig(p);
                remove(tr[p].r,key);
            }    
            else{ 
                zag(p);
                remove(tr[p].l,key);
            }
        }
        else p=0;
    }
    else if(tr[p].key>key)
        remove(tr[p].l,key);
    else
        remove(tr[p].r,key);
    push_up(p);
}

//get rank by given value
int get_rank_by_key(int p,int key){
    if(!p) return 0; //the value not exists
    else if(key==tr[p].key) return tr[tr[p].l].size+1;
    else if(key<tr[p].key) return get_rank_by_key(tr[p].l,key);
    else return tr[tr[p].l].size+tr[p].cnt+get_rank_by_key(tr[p].r,key);
}

//get value by given rank
int get_key_by_rank(int p,int rank){
    if(!p) return INF;
    else if(rank<=tr[tr[p].l].size) return get_key_by_rank(tr[p].l,rank);
    else if(rank<=tr[tr[p].l].size+tr[p].cnt) return tr[p].key;
    else return get_key_by_rank(tr[p].r,rank-tr[tr[p].l].size-tr[p].cnt);
}

//get the greatest number less than key
int get_pre(int p,int key){
    if(!p) return -INF;
    else if(key<=tr[p].key) return get_pre(tr[p].l,key);
    else return max(tr[p].key,get_pre(tr[p].r,key));
}

//get the least number greater than key
int get_next(int p,int key){
    if(!p) return INF;
    else if(key<tr[p].key) return min(tr[p].key,get_next(tr[p].l,key));
    else return get_next(tr[p].r,key);
}

int main(){
    build();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(a==1) insert(root,b);
        else if(a==2) remove(root,b);
        else if(a==3) printf("%d\n",get_rank_by_key(root,b)-1);
        else if(a==4) printf("%d\n",get_key_by_rank(root,b+1));
        else if(a==5) printf("%d\n",get_pre(root,b));
        else if(a==6) printf("%d\n",get_next(root,b));
    }
    return 0;
}
```



推荐一个超赞的数据结构可视化网站：https://visualgo.net/zh

封装好的`Treap`:

```cpp
struct Treap{
    const int N = 100010;
    const int INF=1e9;
    int idx=0,root=0;
    
    struct Node{
        int l,r;
        int key,val;
        int cnt,sz; 
    }tr[100010];
    
    void push_up(int &u){
        tr[u].sz=tr[tr[u].l].sz+tr[tr[u].r].sz+tr[u].cnt;
    }
    
    int get_node(int key){
        int u=++idx;
        tr[u].key=key;
        tr[u].val=rand();
        tr[u].cnt=tr[u].sz=1;
        return u;
    }
    
    void zig(int &p){
        int q=tr[p].l;
        tr[p].l=tr[q].r;
        tr[q].r=p;
        p=q;
        push_up(tr[p].r);
        push_up(p);
    }
    
    void zag(int &p){
        int q=tr[p].r;
        tr[p].r=tr[q].l;
        tr[q].l=p;
        p=q;
        push_up(tr[p].l);
        push_up(p);
    }
    
    Treap(){  //初始化函数，初始化两个边界
        get_node(-INF); get_node(INF);
        root=1; tr[root].r=2;
        push_up(root);
        if(tr[1].val < tr[2].val) zag(root);
    }
    
    void insert(int &p,int key){
        if(!p) p=get_node(key);
        else if(tr[p].key==key) tr[p].cnt++;
        else if(tr[p].key>key){
            insert(tr[p].l,key);
            
            if(tr[tr[p].l].val>tr[p].val) zig(p);
        }
        else{
            insert(tr[p].r,key);
            
            if(tr[tr[p].r].val>tr[p].val) zag(p);
        }
        push_up(p);
    }
    
    void remove(int &p,int key){
        if(!p) return ;
        if(tr[p].key==key){
            if(tr[p].cnt>1) tr[p].cnt--;
            else if(tr[p].l||tr[p].r){
                if(!tr[p].r||tr[tr[p].l].val>tr[tr[p].r].val){
                    zig(p);
                    remove(tr[p].r, key);
                }
                else{
                    zag(p);
                    remove(tr[p].l, key);
                }
            }
            else p=0; //直接是叶子节点
        }
        else if(tr[p].key>key) remove(tr[p].l,key);
        else remove(tr[p].r,key);
        push_up(p);
    }
    
    int get_rank_by_key(int p,int key){
        if(!p) return 0;
        if(tr[p].key==key) return tr[tr[p].l].sz+1;
        else if(tr[p].key>key) return get_rank_by_key(tr[p].l,key);
        else return get_rank_by_key(tr[p].r,key)+tr[tr[p].l].sz+tr[p].cnt;
    }
    
    int get_key_by_rank(int p,int rk){
        if(!p) return INF;    
        if(rk<=tr[tr[p].l].sz) return get_key_by_rank(tr[p].l,rk);
        else if(rk<=tr[tr[p].l].sz+tr[p].cnt) return tr[p].key;
        else return get_key_by_rank(tr[p].r,rk-tr[tr[p].l].sz-tr[p].cnt);
    }
    
    int get_pre(int p,int key){
        if(!p) return -INF;
        if(key<=tr[p].key) return get_pre(tr[p].l,key);
        else return max(tr[p].key,get_pre(tr[p].r,key));
    }
    
    int get_nxt(int p,int key){
        if(!p) return INF;
        if(key<tr[p].key) return min(tr[p].key, get_nxt(tr[p].l, key));
        else return get_nxt(tr[p].r,key);
    }
}treap;
```



<hr>


## 替罪羊树

```cpp
/*存储节点信息：
1.左右子树编号
2.当前节点的值
3.以当前节点为根的树的大小和实际大小
4.删除标记*/
struct Node{
    int l,r;  //左右儿子的编号
    int size,cnt; //树的总共大小（包含被删结点），实际大小
    bool exist;  //当前结点是否被删除
}tr[MAXN];
int idx,root;
```

**创建节点**

```cpp
void get_node(int key){
    int u=++idx;
    tr[u].key=key;
    tr[u].size=tr[u].cnt=1;
    tr[u].exist=true;
}
```

**插入操作**

```cpp
void insert(int &p,int key){
    if(!p){
        p=get_node(key);
        check(root,p);
        return ;
    }
    tr[p].size++,tr[p].cnt++;
    if(val>tr[u].key) insert(tr[u].l,key);
    else insert(tr[u].r,key);
}
```

**删除操作**替罪羊树的删除不是真正的删除，而是打上一个惰性标记，删除之后判断是否需要重构

```cpp
void remove(int &p,int key){
    if(tr[p].exist&&tr[p].key==key){
        tr[p].exist=false;
        tr[p].cnt--;
        check(root,p);
        return ;
    }
    tr[p].cnt--;
    if(key<tr[p].key)
       	remove(tr[p].l,key);
   	else remove(tr[p].r,key);
}
```

**当进行完插入和删除操作后要检查树是否需要重构**

从根节点开始往刚刚的操作结点找，如果找到了一个需要重构的结点，那么暴力重构以它为根的子树

需要重构的条件：当前结点的左子树或者右子树的大小大于当前结点的大小乘一个平衡因子alpha，或者以当前结点为根的子树内被删除的结点数量大于树大小的30%

*push_up操作，左右子树的信息来更新当前节点的信息*

```cpp
void push_up(int &p){
    tr[p].size=tr[tr[p].l].size+tr[tr[p].r].size+1;
    tr[p].cnt=tr[tr[p].l].cnt+tr[tr[p].r].cnt+1;
}
```

*定义alpha值*

```cpp
const double alpha=0.75;
```

*判断当前结点是否平衡*

```cpp
bool imbalance(int p){
    //如果当前结点的大小乘平衡因子小于左右子树大小乘积或者以当前结点为根的子树内被删除的结点数量大于树的大小的百30%
    if(max(tr[tr[p].l].size,tr[tr[p],r].size)>tr[p].size*alpha||tr[p].size-tr[p].cnt>tr[p].szie*0.3)
   		return true;
    return false;
}
```

*从根节点开始往操作结点找，看路径上的点是否需要重构*

```cpp
void check(int &p,int end){
    if(p==end) return ;
    if(imblance(p)){
        rebuild(p);
        update(toor,p);
        return ;
    }
    if(tr[end].key<tr[p].key)
        check(tr[p].l,end);
    else check(tr[u].r,end);
}
```

重构方式：先根据中序遍历，分治法进行重构

*中序遍历*

```cpp
vector<int> v;
void lmr(int p){
    if(!now) return ;
    lmr(tr[p].l);
    if(tr[p].exist)
        v.push_back(p);
    lmr(tr[p].r);
}
```

*分治操作*

```cpp
void lift(int l,int r,int &p){
    if(l==r){ //leaf node
        p=v[l];  
        tr[p].l=tr[p].r=0;
        tr[p].size=tr[p].cnt=1;
        return ;
    }
    int mid=l+r>>1;
    while(l<mid&&tr[v[mid]].key==tr[v[m-1]].key) //为了防止出现多个值相同导致相同的值跑至左边，即找到中序遍历的中间节点对应权值最左边的点
        mid--;
    p=v[mid];
    if(l<mid) lift(l,mid-1,tr[p].l);
    else tr[p],l=0;
    list(mid+1,r,tr[p].r);
    push_up(p);
}
```

*重构操作*

```cpp
void rebuild(int &p){
    v.clear();
    lmr(p);
    if(v.empty()){
        p=0;
        return ;
    }
    lift(0,v.size()-1,p);
}
```

**更新操作**

```cpp
void update(int p,int end){
    if(!p) return ;
    if(tr[end].key<tr[p].key)
        update(tr[p].l,end);
    else update(tr[p].r,end);
    push_up(p);
}
```

**获取排名**

```cpp
int get_rank_by_value(int key){
    int now=root,rank=1;
    while(now){
        if(key<tr[now].key)
            now=tr[now].l;
        else{
            rank+=tr[now].exist+tr[tr[now].l].cnt;
           	now=tr[now].r;
        }
    }
    return rank;
}
```

**获取数值**

```cpp
int get_key_by_rank(int rank){
    int now=root;
    while(now){
        if(tr[now].exist&&tr[tr[now].l].cnt+tr[now].exist==rank)
            break;
        else if(tr[tr[now].l].cnt+tr[now].exist>=rank)
            now=tr[now].l;
        else{
            rank-=tr[tr[now].l].cnt+tr[now].exist;
            now=tr[now].r;
        }
    }
    return tr[now].key;
}
```

**找前驱后继**

找比x大1或者小1的排名对应的值



<hr> 

根据给定`key`和`value`求Treap的方法：

- 先按照`key`排序

- ```cpp
  int top = 0;
  rep(i,1,n){
      while(top && tr[s[top]].b < tr[i].b){
          l[tr[i].id] = tr[s[top]].id;
          top --;
      }
      if(top) r[tr[s[top]].id] = tr[i].id;
      s[++top] = i;
  }
  ```

  

