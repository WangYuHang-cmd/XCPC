# Splay 

伸展树 文艺平衡树

### 引入

区间翻转

### 核心

每一次操作一个节点，均将该节点旋转至树根，这样可以保证树的高度，并且当一个点被用到之后，此点之后再被用到的话则会降低时间复杂度



## 板子拆解：

##### 存储

```cpp
struct Node{
    int s[2]; //存储两个儿子
    int fa,v,size;  //父亲节点，额外信息
    bool rev;  //反转区间特有的信息
}tr[N];
int root,idx=0; //根节点  内存分配器
```

##### push_up函数

子节点更新父节点

```cpp
void push_up(int u){
    tr[u].size=tr[tr[u].s[0]].size+tr[tr[u].s[1]].size+1;
}
```

##### push_down函数

下传懒标记,即将区间交换后并下传

```cpp
void push_down(int u){
    if(tr[u].rev){
        swap(tr[u].s[0],tr[u].s[1]);
        tr[tr[u].s[0]].rev^=1;
        tr[tr[u].s[1]].rev^=1;
        tr[u].rev=0;
    }
}
```

##### rot旋转函数

![image-20210922092111917](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210922092111917.png)

> [1]先将x z相连
>
> [2]将B y相连
>
> [3]将x y相连

```cpp
void rot(int x){
    int y=tr[x].fa,z=tr[y].fa;
    int k=tr[y].s[1]==x; //k=0表示x是y的左儿子，1表示右儿子
    tr[z].s[tr[z].s[1]==y]=x,tr[x].fa=z;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].fa=y;
    tr[x].s[k^1]=y,tr[y].fa=x;
    push_up(y),push_up(x);
}
```

##### splay函数

> splay函数的旋转分为一字型的旋转和之字形的旋转,splay(x,k)指将x节点转到k节点的下面，splay(x,0)指将x转到根节点

![image-20210922093836545](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210922093836545.png)

```cpp
void splay(int x,int k){
    while(tr[x].fa!=k){
        int y=tr[x].fa,z=tr[y].fa;
        if(z!=k)
            (tr[y].s[1]==x)^(tr[z].s[1]==y)?rot(x):rot(y);  //一字形转y否则转x
        rot(x);
    }
    if(!k) root=x;
}
```

##### insert函数

```cpp
void insert(int v){
    int u=root,p=0;
    while(u) p=u,u=tr[u].s[v>tr[v].v]; //像在二叉搜索树里插入那样找到位置
    u=++idx;
    if(p) tr[p].s[v>tr[p].v]=u;
    tr[u].init(v,p);
    splay(u,0);
}
```

##### find_kth函数

注意，这里的find_kth的返回值根据题目而定

```cpp
int find_kth(int v){
    int u=root;
    while(true){
        push_down(u);
        if(tr[tr[u].s[0]].size>=k) u=tr[u].s[0];
        else if(tr[tr[u].s[0]].size+1==k) return u;
        else k-=tr[tr[u].s[0]].size+1,u=tr[u].s[1];
    }
    return -1; //找不到返回-1
}
```

##### find找后继函数

```cpp
int find(int v){
    int u=root,res;
    while(u){
        if(tr[u].v>=v) res=u,u=tr[u].s[0];
        else u=tr[u].s[1];
    }
    return res;
}
```



#### 板子

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100010

int n,m;
struct Node{
    int s[2];
    int size,fa,v;
    bool rev;
    
    void init(int _v,int _fa){
        v=_v,fa=_fa;
        size=1;
    }
}tr[N];
int root,idx=0;

void push_up(int x){
    tr[x].size=tr[tr[x].s[0]].size+tr[tr[x].s[1]].size+1;
}

void push_down(int x){
    if(tr[x].rev){
        swap(tr[x].s[0],tr[x].s[1]);
        tr[tr[x].s[0]].rev^=1;
        tr[tr[x].s[1]].rev^=1;
        tr[x].rev=0;
    }
}

void rot(int x){
    int y=tr[x].fa,z=tr[y].fa;
    int k=tr[y].s[1]==x; //k=0 -> x is y's leftson else y's rightson
    tr[z].s[tr[z].s[1]==y]=x,tr[x].fa=z; //x be z's son replace y
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].fa=y; //x's son transfer to y
    tr[x].s[k^1]=y,tr[y].fa=x;
    push_up(y),push_up(x);
}

void splay(int x,int k){
    while(tr[x].fa!=k){
        int y=tr[x].fa,z=tr[y].fa;
        if(z!=k)
            (tr[y].s[1]==x)^(tr[z].s[1]==y)?rot(x):rot(y);
        rot(x);
    }
    if(!k) root=x;
}

void insert(int v){ //
    int u=root,p=0;
    while(u) p=u,u=tr[u].s[v>tr[u].v];  //find u's place first
    u=++idx;
    if(p) tr[p].s[v>tr[p].v]=u;
    tr[u].init(v,p);
    splay(u,0);
}

int find_kth(int k){
    int u=root;
    while(true){
        push_down(u);
        if(tr[tr[u].s[0]].size>=k) u=tr[u].s[0];
        else if(tr[tr[u].s[0]].size+1==k) return u;
        else k-=tr[tr[u].s[0]].size+1,u=tr[u].s[1];
    }
    return -1; //if not found
}

void dfs(int u){
    push_down(u);
    if(tr[u].s[0]) dfs(tr[u].s[0]);
    if(tr[u].v>=1&&tr[u].v<=n) printf("%d ",tr[u].v);
    if(tr[u].s[1]) dfs(tr[u].s[1]);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n+1;i++) insert(i);
    while(m--){
        int l,r;
        scanf("%d%d",&l,&r);
        l=find_kth(l),r=find_kth(r+2);
        splay(l,0),splay(r,l);
        tr[tr[r].s[0]].rev^=1;
    }
    dfs(root);
    return 0;
}
```

板子：

```cpp
struct Splay{
    int root,idx;
    
    struct Node{
       int s[2];
       int sz,p,v;
       bool flag;
       
       void init(int _v=0,int _p=0){
           p=_p,v=_v;
           sz=1;
       }
    }tr[100010];

    Splay(){
      root=idx=0;
    }
   
    void push_up(int u){
       tr[u].sz=tr[tr[u].s[0]].sz+tr[tr[u].s[1]].sz+1;
    }
   
    void push_down(int u){
        if(tr[u].flag){
           swap(tr[u].s[0],tr[u].s[1]);
           tr[tr[u].s[0]].flag^=1;
           tr[tr[u].s[1]].flag^=1;
           tr[u].flag=false;
        }
    }
   
   void rotate(int x){
        int y=tr[x].p,z=tr[y].p;
        int k=tr[y].s[1]==x;
        tr[z].s[tr[z].s[1]==y]=x, tr[x].p=z;
        tr[y].s[k]=tr[x].s[k^1], tr[tr[x].s[k^1]].p=y;
        tr[x].s[k^1]=y, tr[y].p=x;
        push_up(y); push_up(x);
   }
   
    void splay(int x,int k){
       while(tr[x].p!=k){
            int y=tr[x].p,z=tr[y].p;
            if(z!=k)
                (tr[y].s[1]==x)^(tr[z].s[1]==y)?rotate(x):rotate(y);
            rotate(x);
       }
       if(!k) root=x;
    }
    
    void insert(int v){
        int u=root,p=0;
        while(u) p=u,u=tr[u].s[v>tr[u].v];
        u=++idx;
        if(p) tr[p].s[v>tr[p].v]=u;
        tr[u].init(v,p);
        splay(u,0);
    }
    
    int find(int v){
	    int u=root,res;
	    while(u){
	        if(tr[u].v>=v) res=u,u=tr[u].s[0];
	        else u=tr[u].s[1];
	    }
	    return res;
	}
    
    int find_kth(int x){
        int u=root;
        while(true){
            push_down(u);
            if(tr[tr[u].s[0]].sz>=x) u=tr[u].s[0];
            else if(tr[tr[u].s[0]].sz+1==x) return u;
            else x-=tr[tr[u].s[0]].sz+1,u=tr[u].s[1];
        }
        return -1;
    }
}tree;
```

![image-20220209222706067](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20220209222706067.png)

- 区间拼接
- 区间翻转
- 区间大段插入 

splay的区间翻转可以用于换根DP
