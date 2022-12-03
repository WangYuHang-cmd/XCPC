## AC自动机

https://www.cnblogs.com/sclbgw7/p/9260756.html

![image-20210817001745044](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210817001745044.png)

构建方法：使用bfs在Trie树上进行构造

![image-20210817001828682](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210817001828682.png)

```cpp
void build(){
    for(int i=0;i<26;i++)
        if(tr[0][i])
            Q.push(tr[0][i]);
    
    while(Q.size()){
        int t=Q.front();  //t is i-1
        Q.pop();
        
        for(int i=0;i<26;i++){
            int c=tr[t][i];
            if(!c) continue;
            
            int j=ne[t]; //j is ne[i-1] ,the previos j,j also means fail point
            while(j&&!tr[j][i]) j=ne[j]; //if tr[j][i] not exists,go back like KMP
            if(tr[j][i]) j=tr[j][i];
            ne[c]=j;
            Q.push(c);
        }
    }
}

int main(){
    scanf("%d",&T);
    while(T--){
        memset(tr,0,sizeof tr);
        memset(cnt,0,sizeof cnt);
        memset(ne,0,sizeof ne);
        idx=0;
        
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            insert();  //insert every word
        }
        
        build(); //build a trie tree
        
        scanf("%s",str);
        
        int res=0;
        for(int i=0,j=0;str[i];i++){
            int t=str[i]-'a';
            
            while(j&&!tr[j][t]) j=ne[j];
            if(tr[j][t]) j=tr[j][t];
            
            int p=j;
            while(p){
                res+=cnt[p];
                cnt[p]=0;
                p=ne[p];
            }
        }
        printf("%d\n",res);
    }
    return 0;
}
```



### AC自动机为何要优化成Trie:

> 匹配时因为每次都要跳fail边，复杂度上界可以达到 O(ml)

对于字符集{a,b,c}上的模式ab,aab,aaab,aaaab,ac和文本串aaaac，它们建出来的AC自动机和匹配过程是这样的（蓝色边是Trie树的边，红色边是fail指针，黄色边是匹配时的状态转移）：

![image-20210816233831378](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816233831378.png)

```cpp
//对应AC自动机中的这一段;
while(j&&!tr[j][t]) j=ne[j];
if(tr[j][t]) j=tr[j][t];
```

我们会想，如果失配时可以一步到位就好了。每次回溯的过程是固定的：一直跳，直到找到拥有儿子c的节点为止。也就是说，无论什么时候在这个节点上失配，只要你找的是字符c，你总会在固定的节点上重新开始匹配。既然这样，不如直接把那个字符为c的节点变成自己的儿子，就可以省去回溯的麻烦：

![image-20210816234135581](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20210816234135581.png)

##### Trie图构造方法：

```cpp
//修改build函数
void build(){
    for(int i=0;i<26;i++)
        if(tr[0][i])
        	Q.push(tr[0][i]);
    
    while(Q.size()){
        int t=Q.front();
        Q.pop();
        
        int p=tr[t][i];
        if(!p) tr[t][i]=tr[ne[t]][i];
        else{
            ne[p]=tr[ne[t]][i];
            Q.push(p);
        }
    }
}
```

由于遍历到t点的时候t的儿子们的ne数组值已经更新过了，因此，必然可以一路递推到对应的子节点上

因为原本是DAG结构的AC自动机出现了环，因此称为Trie图，此时可以做到真正的O(m)

此外，相应的查询操作可以一步直接修改为：

```cpp
for(int i=0,j=0;str[i];i++){
            int t=str[i]-'a';
            
			j=tr[j][t];
            
            int p=j;
            while(p){
                res+=cnt[p];
                cnt[p]=0;
                p=ne[p];
            }
        }
```

参考：https://www.cnblogs.com/sclbgw7/p/9875671.html

