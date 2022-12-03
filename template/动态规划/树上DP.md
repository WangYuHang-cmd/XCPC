# 树形DP

#### 找无边权树的直径的方法：

1.任取一点作为起点，找到距离此点最远的点u

2.找到距离u最远的点a

3.a与u便是树的一条直径



### 树形DP的三个状态机模型

##### 最大独立集

子节点和父节点不能同时选

```cpp
f[i][1] //表示选当前点的最小方案
f[i][0] //表示不选当前点的最小方案
    
f[i][1]+=f[son][1];
f[i][0]+=min(f[son][0],f[son][1]);
```

##### 最小点覆盖

对于每一条边都需要至少选取一个点来“覆盖”此边。

```cpp
f[i][1] //表示选当前点的最小方案
f[i][0] //表示不选当前点的最小方案
    
f[i][0]+=f[son][1];
f[i][1]+=min(f[son][0],f[son][1]);
```



##### 最小支配集

```cpp
f[i][0] //表示选i
f[i][1] //表示选i的儿子
f[i][2] //表示选i的父亲
//状态转移方程
f[i][0]=1+min(f[i][])
```



### 树上背包

`f[u][i]`表示以u为根，背包容量为i的情况下所能装的最大价值

```cpp
f[u][j]=max(f[u][k]+f[v][j-k-1]+w)
```

![image-20210916180509279](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210916180509279.png)



#### 树的直径：

跑两遍dfs，第一遍取任意一点找到边权值和最大的链，取 链中离选取点最远的点再跑一遍dfs即可

标程https://blog.csdn.net/m0_51780913/article/details/120340026?spm=1001.2014.3001.5501



### 换根法：

287. 积蓄程度

> 有一个树形的水系，由 N−1N−1 条河道和 NN 个交叉点组成。每条河道都有一个容量，连接 x 与 y 的河道的容量记为 c(x,y)。在流量不超过河道容量的前提下，求哪个点作为源点时，整个水系的流量最大，输出这个最大值。

轻易写出状态方程：`f[u]` :以u为根的子树的最大流量

```python
void dfs_f(int u, int pre){
    if(deg[u] == 1){
        f[u] = INF;
        return ;
    }
    for(int i=h[u];~i;i=ne[i]){
        int j = e[i];
        if(j == pre) continue;
        dfs_f(j, u);
        f[u] += min(w[i], f[j]);
    }
}
```

再进行换根

```cpp
void dfs_s(int u, int pre){
    for(int i=h[u];~i;i=ne[i]){
        int j = e[i];
        if(j == pre) continue;
        if(deg[j] == 1) { f[j] = min(w[i], f[u] - w[i]); continue ;}
        f[j] = f[j] + min(w[i], f[u] - w[i]);
        dfs_s(j, u);
    }
}
```

## BUT ! 千万记住 ！ 一开始一定要从非叶子结点开始寻找！！！

```cpp
while(root<=n&&deg[root]==1) root++;
if(root > n) {print(w[0]); continue;}
dfs_f(root, -1);
dfs_s(root, -1);
```

