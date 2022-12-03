# 可持久化Trie

可持久化数据结构的前提：本身的拓扑结构不变

##### 解决的问题：

可以在存下数据结构的所有历史版本

##### 核心思想：

只记录每个版本与之前不同的节点

### 可持久化字典树（Trie）：

```cpp
const int N = 600010,M=N*25;
int n,m,k,a[N],idx=0,max_id[M];
int tr[M][2],root[N], cnt[M];

void insert(int i,int k,int p,int q){
    if(k<0){
        max_id[q]=i;
        return ;
    }
    int u=a[i]>>k&1;
    if(p) tr[q][u^1]=tr[p][u^1];
    tr[q][u]=++idx;
    insert(i, k-1, tr[p][u], tr[q][u]);
    max_id[q]=max(max_id[tr[q][0]], max_id[tr[q][1]]);
}

int query(int u,int x,int L){
    int p=root[u];
    for(int i=23;i>=0;--i){
        int v=x>>i&1;
        if(max_id[tr[p][v^1]]>=L) p=tr[p][v^1];
        else p=tr[p][v];
    }
    return x^a[max_id[p]];
}
```



![可持久化Tire](C:\Users\Henry\Desktop\OI\板子合辑（自己打的）\数据结构\可持久化Tire.png)
