## Dancing Links 详解

## 精确覆盖问题

### 1.初始化部分：建立一行头节点

第0行建立好一排空的头节点，完善好十字链表的各项信息。
![e6f8bd290e7f571e4e3904ebd95fda8.jpg](https://cdn.acwing.com/media/article/image/2022/02/26/92692_c9f1898096-e6f8bd290e7f571e4e3904ebd95fda8.jpg) 
```
void init(){
    for(int i=0;i<=m;++i){
        l[i]=i-1,r[i]=i+1;
        u[i]=d[i]=i;
    }
    l[0]=m,r[m]=0;
    idx=m+1;
}
```

### 2.插入元素
每次在第0行下面插入，虽然直观上行的顺序打乱，实际上是翻转了一下，不影响拓扑结构

```
void add(int &hh,int &tt,int x,int y){
    row[idx]=x,col[idx]=y,s[y]++;
    u[idx]=y,d[idx]=d[y],u[d[y]]=idx,d[y]=idx;
    l[idx]=hh,r[hh]=idx,r[idx]=tt,l[tt]=idx;
    tt=idx++;
}
```

### 3.删除某一列 & 恢复某一列
(1) 在头结点中删除该列 （只删除右指针，左指针复原的时候要用，一般索引都是用右指针，所以删除右指针意味着逻辑上已经删除了，不会再被遍历到）
(2) 删除当前列意味着当前列已经被覆盖，因此凡是有1在这一列的行都不能被选择，可以全部删去。因此删去当前列所有1所在的行
(3) 恢复完全对称写即可，每次遍历使用d[]和r[]两个指针,因此恢复使用另外两个
![5cb80766e6cf450f8abf03cbea9c7ea.jpg](https://cdn.acwing.com/media/article/image/2022/02/26/92692_d2e3769896-5cb80766e6cf450f8abf03cbea9c7ea.jpg) 

```
void remove(int p){ //删除第p列
    r[l[p]]=r[p],l[r[p]]=l[p];
    for(int i=d[p];i!=p;i=d[i])
        for(int j=r[i];j!=i;j=r[j]){
            s[col[j]] --;
            u[d[j]]=u[j],d[u[j]]=d[j];
        }
}

void resume(int p){ //恢复第p列
    for(int i=u[p];i!=p;i=u[i])
        for(int j=l[i];j!=i;j=l[j]){
            s[col[j]] ++;
            u[d[j]]=j,d[u[j]]=j;
        }
    l[r[p]]=p,r[l[p]]=p;
}
```

### 4.深搜DFS+剪枝
剪枝有两种
(1) 每次枚举1最少的列
(2) remove中用到的，当前列能且只能被覆盖1次
借用OIwiki的一张图，这个剪枝效果还是十分明显的
![屏幕截图 2022-02-26 131629.jpg](https://cdn.acwing.com/media/article/image/2022/02/26/92692_6fcad18896-屏幕截图-2022-02-26-131629.jpg) 
![屏幕截图 2022-02-26 131643.jpg](https://cdn.acwing.com/media/article/image/2022/02/26/92692_60503ed396-屏幕截图-2022-02-26-131643.jpg) 
![屏幕截图 2022-02-26 131650.jpg](https://cdn.acwing.com/media/article/image/2022/02/26/92692_722de3fc96-屏幕截图-2022-02-26-131650.jpg) [1]

```
bool dfs(){
    if(!r[0]) return true;
    int p=r[0];
    for(int i=r[0];i;i=r[i])
        if(s[i] < s[p]) p=i;
    remove(p);
    for(int i=d[p];i!=p;i=d[i]){
        ans[++ top]=row[i];
        for(int j=r[i];j!=i;j=r[j]) remove(col[j]);
        if(dfs()) return true;
        for(int j=l[i];j!=i;j=l[j]) resume(col[j]);
        top --;
    }
    resume(p);
    return false;
}
```

[1] 引用自 OI wiki https://oi-wiki.org/search/dlx/#__comments

```cpp
int n,m,l[N],r[N],u[N],d[N],s[N],row[N],col[N],idx=0,ans[N],top=0;

void init(){
    for(int i=0;i<=m;++i){
        l[i]=i-1,r[i]=i+1;
        u[i]=d[i]=i;
    }
    l[0]=m,r[m]=0;
    idx=m+1;
}

void remove(int p){ //删除第p列
    r[l[p]]=r[p],l[r[p]]=l[p];
    for(int i=d[p];i!=p;i=d[i])
        for(int j=r[i];j!=i;j=r[j]){
            s[col[j]] --;
            u[d[j]]=u[j],d[u[j]]=d[j];
        }
}

void resume(int p){ //恢复第p列
    for(int i=u[p];i!=p;i=u[i])
        for(int j=l[i];j!=i;j=l[j]){
            s[col[j]] ++;
            u[d[j]]=j,d[u[j]]=j;
        }
    l[r[p]]=p,r[l[p]]=p;
}

void add(int &hh,int &tt,int x,int y){
    row[idx]=x,col[idx]=y,s[y]++;
    u[idx]=y,d[idx]=d[y],u[d[y]]=idx,d[y]=idx;
    l[idx]=hh,r[hh]=idx,r[idx]=tt,l[tt]=idx;
    tt=idx++;
}

bool dfs(){
    if(!r[0]) return true;
    int p=r[0];
    for(int i=r[0];i;i=r[i])
        if(s[i] < s[p]) p=i;
    remove(p);
    for(int i=d[p];i!=p;i=d[i]){
        ans[++ top]=row[i];
        for(int j=r[i];j!=i;j=r[j]) remove(col[j]);
        if(dfs()) return true;
        for(int j=l[i];j!=i;j=l[j]) resume(col[j]);
        top --;
    }
    resume(p);
    return false;
}

```

##  重复覆盖问题

用最少的边将每一列覆盖

```cpp
#define int LL
const int N=100020,M=N*2,mod=1e9+7;
int n,m,k,l[N],r[N],u[N],d[N],s[N],row[N],col[N],ans[N],top,idx,st[110],depth;

void init(){
    for(int i=0;i<=m;++i){
        l[i]=i-1,r[i]=i+1;
        col[i]=d[i]=u[i]=i;
        s[i]=0;
    }
    l[0]=m,r[m]=0;
    idx=m+1;
}

void add(int &hh,int &tt,int x,int y){
    row[idx]=x,col[idx]=y,s[y]++;
    u[idx]=y,d[idx]=d[y],u[d[y]]=idx,d[y]=idx;
    l[idx]=hh,r[idx]=tt,l[tt]=idx,r[hh]=idx;
    tt=idx++;
}

void remove(int p){
    for(int i=d[p];i!=p;i=d[i]){
        r[l[i]]=r[i],l[r[i]]=l[i];
    }
}

void resume(int p){
    for(int i=u[p];i!=p;i=u[i]){
        r[l[i]]=i,l[r[i]]=i;
    }
}

int h(){
    memset(st,0,sizeof st);
    int ans=0;
    for(int i=r[0];i;i=r[i]){
        if(st[col[i]]) continue;
        ans++;
        st[col[i]]=true;
        for(int j=d[i];j!=i;j=d[j])
        	for(int k=r[j];k!=j;k=r[k])
            	st[col[k]]=true;
    }
    return ans;
}

bool dfs(int k,int depth){
    if(k+h()>depth) return false;
    if(!r[0]) return true;
    int p=r[0];
    for(int i=r[0];i;i=r[i])
        if(s[i]<s[p])
            p=i;
    for(int i=d[p];i!=p;i=d[i]){
        ans[k]=row[i];
        remove(i);
        for(int j=r[i];j!=i;j=r[j]) remove(j);
        if(dfs(k+1,depth)) return true;
        for(int j=l[i];j!=i;j=l[j]) resume(j);
        resume(i);
    }
    return false;
}

void solve(){
	n=read(); m=read();
	init();
	rep(i,1,n) {
	    int hh=idx,tt=idx;
	    rep(j,1,m){
	        int x=read();
	        if(x) add(hh,tt,i,j);
	    }
	}
	depth=0;
	while(!dfs(0,depth)) depth++;
	print(depth);
	for(int i=0;i<depth;++i) printf("%d ",ans[i]);
}
```

