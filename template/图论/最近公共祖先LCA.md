### 最近公共祖先LCA

对于一棵树：
$$
每个点与其根节点被称为这个点的祖先
$$
**绿色的点都是⭐的祖先**![image-20210805114952904](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210805114952904.png)

当一个点同时是另外两个点的祖先时，成为这两点的公共祖先

**紫色点是绿色与红色点的公共祖先**

![image-20210805115215096](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210805115215096.png)



#### 求法：

##### **1.向上标记法**

从某一个点向上遍历并标记。再从另外一个点开始标记，标记到的第一个已经被标记到的点便是最近公共祖先

##### **2.树上倍增LCA**

倍增f[i,j]表示从i开始，向上走2^j所能走到的所有节点
$$
j=0 \ \ \ \ \ \ \ f(i,j)=i's \ father
$$

$$
j\ge 0 \ \ \ \ \ \ \ f(i,j)=f(f(i,j-1),j-1)
$$

$$
function:\ \ \ \ \    fa[i][j]=fa[fa[i][j-1]][j-1]
$$

###### 预处理,一般使用BFS

fa[i,j]表示从i开始，向上走2^j步所能走到的节点。0<=j<=logn

depth[i]表示深度

哨兵：如果从i开始跳2^j步会跳过根节点，那么fa[i,j]=0.depth[0]=0

###### 在线step:

[1]先将两个点跳到同一层

[2]判断a与b之间的关系

[3]让两个点同时往上跳，一直跳到他们最近公共祖先的下一层。

跳法：从最大的二的整次幂开始跳

预处理O(nlogn)

查询O(logn)

**板子**：

```cpp
void bfs(int root){
    depth[0]=0,depth[root]=1;  //depth[0]初始化深度为0表示不合法的深度
    queue<int> Q;Q.push(root);
    
    while(Q.size()){
        int t=Q.front();
        Q.pop();
        
        for(int i=h[t];~i;i=ne[i]){
            int j=e[i];
            if(depth[j]>depth[t]+1){
                depth[j]=depth[t]+1;
                
                Q.push(j);
                fa[j][0]=t;
                for(int k=1;k<=15;k++)
                    fa[j][k]=fa[fa[j][k-1]][k-1];
            }
        }
    }
}

inline int lca(int a,int b){
    if(depth[a]<depth[b]) swap(a,b);
    //从后向前遍历
    for(int i=15;i>=0;i--){
        if(depth[fa[a][i]]>=depth[b]) 
            a=fa[a][i];
    }
    
    if(a==b) return a;
    
    for(int i=15;i>=0;i--)
        if(fa[a][i]!=fa[b][i]){
            a=fa[a][i],b=fa[b][i];
        }
    return fa[a][0];
}
```



##### 3.Tarjan缩点———离线求LCA  O(n+m)

*对向上标记法的优化，基于DFS*

DFS的过程中将点分成三类：

![image-20210805150806951](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210805150806951.png)

其中，**绿色部分为已经被遍历且回溯的2类点**，**红色为正在遍历的1类点**。对于每一个1号点与2号点的组合，他们的最近公共祖先一定在1号点的父辈节点上，因此可以考虑使用并查集将2类点压缩到1类点的路径上。

如果求2区域内的点与x的最近公共祖先，可以将绿颜色部分（已经遍历且回溯过的点）合并到1区域的根节点上（使用并查集维护）

```cpp
tarjan缩点step:
	[1]预处理步骤，存储所有询问，保存数组中时应该保存并双向，dfs出所有的点距
tarjan:
	[2]类似于深度搜索，标记当前点为第1类点（如上图红）
    遍历所有以当前点为根节点的点，如果未被标记则搜索，然后并查集合并
	[3]对于与当前点有关的询问，如果另外一个点被标记为图上绿（已遍历且回溯）
    则计算出距离并记录答案。
    [4]当前点已经被遍历且回溯，应当标记为第二类点
```

附上板子：

```cpp
void dfs(int u,int father){ //算出每个点到根节点的距离
    for(int i=h[u];~i;i=ne[i]){
        int j=e[i];
        if(j==father) continue;
        dist[j]=dist[u]+w[i];
        dfs(j,u);
    }
}

void tarjan(int u){
    st[u]=1;
    for(int i=h[u];~i;i=ne[i]){
        int j=e[i];
        if(!st[j]){
            tarjan(j);
            fa[j]=u;
        }    
    }
    
    for(int i=0;i<query[u].size();i++){
        int ver=query[u][i].x,id=query[u][i].y;
        if(st[ver]==2){ //如果已经被划分到了左边被遍历过的子树中
            int root=find(ver);
            res[id]=dist[u]+dist[ver]-2*dist[root];
        }
    }
    st[u]=2;
}
```



##### 4.RMQ+欧拉序列

![image-20210805171657805](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210805171657805.png)

`图上的欧拉序为：1 2 4 6 4 7 4 2 5 2 1 3 1`

```cpp
[1]深度优先搜索出这一颗树的欧拉序（根节点出现多次）
[2]求节点x和节点y之间的最近公共祖先，
   即在dfs序中任意x,y之间找深度的最小值的点
[3]找区间最小值可以使用RMQ算法
```

`e.g.` 

`ST`：用一个数组`f[i][j]`维护`[i,i+2^j-1]`中的最小值。



##### 5.建笛卡尔树跑正负RMQ



#### 树上差分：

最近公共祖先减少2，两个节点各增加1

```cpp
cnt[root]-=2;
cnt[a]++;
cnt[b]++;
```

- 对于统计树上节点类型，最大值等信息的情况可以每个点开一棵动态开点的线段树来进行维护。

  