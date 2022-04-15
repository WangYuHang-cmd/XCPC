## 2-SAT

#### 一般SAT问题 (NP问题)

> 给定n个命题$x_1,x_2...x_n$
>
> 给出n个形式的条件，形如$x_1 \or \neg x_2 .... \or x_n $ 表示如图形式中至少有一个为真
>
> 求给出$x_1,x_2...x_n$的一组取值使得所有上述条件都为真。

做法：

首先将每个数$x_i$看作两个点$x_1$为真和$\neg x_i$ 为真，即拆成要么正变量成立要么取反后成立

然后根据数理逻辑的原理，有推论

$a \or b $等价于$\neg b \to a$和$\neg a \to b$ (a或者b成立等价于a不成立时b必然成立且b不成立时a必然成立)。因此我们从$\neg a$向$b$连边`add(2*a,2*b+1)`,从$\neg b$向$a$连边`add(2*b+1,2*a)`，这表征$\neg b$与$a$在同一逻辑域(同时成立)。按照此形式建立出来的图中，如果$a$和$\neg a$在同一个连通分量中，说明存在矛盾。否则，其中一可行解为：先对原图进行`tarjan`缩点，之后对于变量$a$和$\neg a$谁的拓扑序在更后面，我们就选取那一个变量对应的值。

> 但是，由于我们之前使用了`tarjan`缩点，根据结论`tarjan`缩点后每个点的便后就是每个点的拓扑序的逆序，因此又对于每个点
>
> ```cpp
> if(id[i*2]<id[i*2+1]) cout << 0 << " ";
> else cout << 1 << " ";
> ```
>
> 

板子没什么特别的，就是建图+tarjan,关键还是第一步

```cpp
void tarjan(int u){
    dfn[u]=low[u]=++timestamp;
    ins[u]=true; stk[++top]=u;
    
    for(int i=h[u];~i;i=ne[i]){
        int j=e[i];
        if(!dfn[j]){
            tarjan(j);
            low[u]=min(low[u],low[j]);
        }
        else if(ins[j]) low[u]=min(low[u],dfn[j]);
    }
    if(low[u]==dfn[u]){
        int y;
        scc_cnt ++;
        do{
            y=stk[top --];
            ins[y]=false;
            id[y]=scc_cnt;
        }while(y!=u);
    }
}

void solve(){
    n=read(),m=read();
    rep(i,1,m){
        int x,a,y,b;
        x=read(),a=read(),y=read(),b=read();
        x--,y--;
        add(2*x+!a,2*y+b); add(2*y+!b,2*x+a);
    }
    
    rep(i,0,2*n-1) if(!dfn[i]) tarjan(i);
    
    bool ok=true;
    rep(i,0,n-1){
        if(id[i*2]==id[2*i+1]) {
            // debug(i);
            ok=false;
            break;
        }
    }
    if(!ok) puts("IMPOSSIBLE");
    else{
        puts("POSSIBLE");
        rep(i,0,n-1){
            if(id[2*i]<id[2*i+1]) printf("0 ");
            else printf("1 ");
        }
    }
}
```







