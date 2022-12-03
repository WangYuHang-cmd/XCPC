## 动态树__Link Cut Tree

**解决的问题：**

动态的维护一个森林，可以添加一条边或者删除一条边。并维护树上路径的一些信息。

维护一棵树，支持如下操作：

- 修改两点间路径权值。
- 查询两点间路径权值和。
- 修改某点子树权值。
- 查询某点子树权值和。

##### 组成

所有边可以分成虚边和实边,每个节点最多只有一条实边，也可能没有实边。通过维护实边之间的关系来维护一棵树。

##### 方法：

- 用splay维护所有实边路径：splay的中序遍历就是路径
  - 用splay的后继和前驱来维护原树的父子关系
  - 虚边用splay的根节点来维护

每一条实边路径可看作一棵树，每一棵树都是用splay来维护，每一个虚边通过对应的两个splay的节点来维护，即某个splay的某个点指向另外一个splay的根节点

![image-20220215215554626](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20220215215554626.png)

虚边：子节点知道父节点，父节点不知道子节点，即父节点未指向自己。

实边：父节点指向自己。

越在上面的点位于序列的前面，即splay的左子树

**操作**

1.`access(x)`：建立一条从根节点到x的实边路径

![image-20220215215613375](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20220215215613375.png)

- `splay(x,0)`将x转到根节点
- `splay(y,0)`将y转到根节点
- 将以x为根的树接到y的右子树
- 把y直接插入z的右子树（修改后继）

2.`make_root(int x)`将x变成根节点

- 先建立从根节点到x的实边路径
- 将x转到根节点，然后翻转整条路经(借助于懒标记`swap`)

3.`find_root(int x)`找到x所在原树的根节点，再将原树的根节点转到splay的根节点

- 建立从根到x的路径
- 将x旋转到根节点
- 一直向左走到尽头便是根节点

>副作用：调用access(x)会自动调用将x转到根节点

4.`split(int x,int y)`将从x到y的路径建成一棵splay(变成实边路径)

- `make_root(x)`
- `access(y)`

> 此时splay的根节点为

5.`link(x,y)`如果x,y不连通，则假如<x,y>

- `make_root(x)`
- `find_root(y)`

6.`cut(x,y)`如果x和y之间有边，则删除该边

7.`isroot(x)`判断x是不是所在splay的根节点

等价于x是其父节点的左儿子或者右儿子

```cpp
const int N = 300010,M=N*2,mod=1e9+7;
struct Node{
    int s[2],p,v;
    int sum,rev;
}tr[N<<2];
int n,m,stk[N];

void rev(int u){
    swap(tr[u].s[0], tr[u].s[1]);
    tr[u].rev^=1;
}

void push_up(int u){
    tr[u].sum=tr[tr[u].s[0]].sum^tr[u].v^tr[tr[u].s[1]].sum;
}

void push_down(int u){
    if(tr[u].rev){
        rev(tr[u].s[0]); rev(tr[u].s[1]);
        tr[u].rev=0;
    }
}

bool isroot(int x) {
    return ((tr[tr[x].p].s[0]!=x) && (tr[tr[x].p].s[1]!=x));
}

void rotate(int x){
    int y=tr[x].p, z=tr[y].p;
    int k=tr[y].s[1]==x;
    if(!isroot(y)) tr[z].s[tr[z].s[1]==y] = x;
    tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1], tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y,tr[y].p=x;
    push_up(y); push_up(x);
}

void splay(int x){
    int top=0,r=x;
    stk[++top]=r;
    while(!isroot(r)) r=tr[r].p, stk[++top]=r;
    while(top) push_down(stk[top--]);
    
    while(!isroot(x)){
        int y=tr[x].p, z=tr[y].p;
        if(!isroot(y))
            ((tr[z].s[1]==y)^(tr[y].s[1]==x))?rotate(x):rotate(y);
        rotate(x);
    }
}

void access(int x){ //建立一条从原树根节点到x的路径，同时将x变成所在辅助树的根节点
    int z=x;
    for(int y=0; x; y=x,x=tr[x].p){
        splay(x);
        tr[x].s[1]=y,push_up(x);
    }
    splay(z);
}

void makeroot(int x){ //将x变成原树的根
    access(x);
    rev(x);
}

int findroot(int x){ //找到x所在原树的根节点,再将原树的根节点转到所在辅助树的根节点
    access(x);
    while(tr[x].s[0]) push_down(x), x=tr[x].s[0];
    splay(x);
    return x;
}

void split(int x,int y){
    makeroot(x);
    access(y);
}

void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x) tr[x].p=y;
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1]=tr[y].p=0;
        push_up(x);
    }
}

void solve(){
	n=read(); m=read();
	rep(i,1,n) tr[i].v=read();
	while(m--){
	    int op=read(),x=read(),y=read(); 
	    if(op==0){
	        split(x,y);
	        print(tr[y].sum);
	    }
	    else if(op==1){
	        link(x,y);
	    }
	    else if(op==2){
	        cut(x,y);
	    }
	    else{
	        splay(x);
	        tr[x].v=y;
	        push_up(x);
	    }
	}
}
```



压一点：

```cpp
struct Node{
    int s[2],p,v;
    int sum,rev;
}tr[N<<2];
int n,m,stk[N];
#define rev(u) swap(tr[u].s[0], tr[u].s[1]),tr[u].rev^=1
#define push_up(u) tr[u].sum=tr[tr[u].s[0]].sum^tr[u].v^tr[tr[u].s[1]].sum
#define isroot(x) ((tr[tr[x].p].s[0]!=x)&&(tr[tr[x].p].s[1]!=x))
#define split(x,y) makeroot(x),access(y)
#define makeroot(x) access(x),rev(x)
void push_down(int u){
    if(tr[u].rev){
        rev(tr[u].s[0]); rev(tr[u].s[1]);
        tr[u].rev=0;
    }
}
void rotate(int x){
    int y=tr[x].p, z=tr[y].p;
    int k=tr[y].s[1]==x;
    if(!isroot(y)) tr[z].s[tr[z].s[1]==y] = x;
    tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1], tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y,tr[y].p=x;
    push_up(y); push_up(x);
}
void splay(int x){
    int top=0,r=x;
    stk[++top]=r;
    while(!isroot(r)) r=tr[r].p, stk[++top]=r;
    while(top) push_down(stk[top--]);
    while(!isroot(x)){
        int y=tr[x].p, z=tr[y].p;
        if(!isroot(y))
            ((tr[z].s[1]==y)^(tr[y].s[1]==x))?rotate(x):rotate(y);
        rotate(x);
    }
}
void access(int x){ //建立一条从原树根节点到x的路径，同时将x变成所在辅助树的根节点
    int z=x;
    for(int y=0; x; y=x,x=tr[x].p){
        splay(x);
        tr[x].s[1]=y,push_up(x);
    }
    splay(z);
}
int findroot(int x){ //找到x所在原树的根节点,再将原树的根节点转到所在辅助树的根节点
    access(x);
    while(tr[x].s[0]) push_down(x), x=tr[x].s[0];
    splay(x);
    return x;
}
void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x) tr[x].p=y;
}
void cut(int x,int y){
    makeroot(x);
    if(findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1]=tr[y].p=0;
        push_up(x);
    }
}
```

