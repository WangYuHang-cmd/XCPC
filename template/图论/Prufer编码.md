## `Prufer`编码

**`Prufer编码转树`**  `O(n)`

可以把一棵无根树变成一个序列，也可以将一个序列变成一棵无根树。

- 每次找到无根树编号最小的度数为1的点
- 然后将此点的父节点加入序列

`O(n)`时间求`Prufer`编码

对于一个有`n`个节点的树，其`prufer`编码只有`n-2`个数。

**树转`Prufer编码`**

一个数在`prufer`编码中出现多少次，就说明其有几个儿子

`Step:`

>`void tree2prufer()`的操作是顺序遍历，然后从1开始遍历，当找到出度为0的点时，将其父节点加入`prufer`序列，然后递归其父节点，如果其父节点的出度为0且父节点小于当亲遍历到的j的值，父节点的父节点也加入`prufer`序列。
>
>`void pruffer2tree()`的操作是顺序遍历`prufer`序列的同时遍历1~n，如果1~n遍历的时候有出度为0的点，则其父亲就是当前遍历到的`prufer`序列，然后`prufer`序列当前数的出度--，如果为0且小于当前遍历的树，则其父亲节点为下一个`prufer`序列中的树。

一道板子，如果m=1，给出给定树的prufer编码，否则给出给定prufer编码的树

```cpp
const int N = 1e5+10;
int n,m;
int fa[N],p[N],d[N],idx=0; //d表示出度

void tree2prufer(){
    rep(i,1,n-1) fa[i]=read(),d[fa[i]]++;
    
    for(int i=0,j=1;i<n-2;j++){
        while(d[j]) j++;
        p[i++]=fa[j];
        while(i<n-2&&--d[p[i-1]]==0&&p[i-1]<j) p[i++]=fa[p[i-1]];
    }
    rep(i,0,n-3) printf("%d ",p[i]); puts("");
}

void prufer2tree(){
    rep(i,1,n-2) p[i]=read(),d[p[i]]++;
    p[n-1]=n;
    
    for(int i=1,j=1;i<n;++i,j++){
        while(d[j]) j++;
        fa[j]=p[i];
        while(i<n-1&&--d[p[i]]==0&&p[i]<j) fa[p[i]]=p[i+1],i++;
    }
    rep(i,1,n-1) printf("%d ",fa[i]);
}

void solve(){
    n=read(),m=read();
    if(m==1)
        tree2prufer();
    else prufer2tree();
}
```

#### 应用：

**Cayley定理**

- 对于一个$n$个点的无向完全图，其生成树的个数为$n^{n-2}$  

证明：由`prufer`编码一共n-2位，每一位有n个选择，因此为$n^{n-2}$

