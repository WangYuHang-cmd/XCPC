## 基环树DP

![image-20211014131927381](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20211014131927381.png)

- 形如图上的数据结构称为基环树，基环树有n个结点和n条边，对于每一棵树根据方向又可分为外向树和内向树

>每个点恰好有一条出边/每个点恰好有一条入边表示这是一棵基环树。

基环树DP常见套路：

### 基环树+前缀和+单调队列

`IOI2008 Island`

https://www.luogu.com.cn/problem/P4381

- 思路：

> 首先`dfs`找出所有的环并记录在`cir[]`数组中，端点记录在`ed[]`数组中(很巧妙)，然后对于基环数森林中的每一棵基环树拉直开两倍数组存下来，使用单调队列优化长度为n的一段中的`d[j]-sum[j]`的最值，状态转移方程：
> $$
> ans = max(ans,d[j]+sum[j]+d[i]-sum[i])
> $$
> 由于是顺时针枚举，因此能够保证所有的状态都能枚举的到，单调队列优化区间最值使得算法复杂度可以降到`O(n)`

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
/*
由于本题是一颗基环树森林，因此需要找出每一棵基环数的最大值并累加到答案
*/
typedef long long LL;
const int N = 1e6+10;

LL n,ans,res=0;
int h[N],ne[N*2],e[N*2],w[N*2],idx=0;
int fu[N],fw[N],q[N];  //fu[]存储父节点，fw[]存储对应长度，q[]存储 单调队列
int cir[N],ed[N],cnt; //cir存储圆，ed存储终点，cnt分配对应下标
LL s[N],sum[N*2],d[N*2]; //s[]记录环上的前缀和，sum[]记录破环成链后的前缀和，d[]记录答案
bool st[N],ins[N];

void add(int a,int b,int v){
    e[idx]=b,w[idx] =v,ne[idx]=h[a],h[a]=idx++;
}

void dfs_s(int u,int from){ //找环
    st[u] = ins[u] = true;
    for(int i = h[u]; ~i ;i = ne[i]){
        if(i == (from^1)) continue;  //这里要用边判断是因为会出现
        int j = e[i];
        fu[j] = u,fw[j] = w[i];
        
        if(!st[j]) dfs_s(j,i);
        else if(ins[j]){  //找到环了
            cnt ++;
            ed[cnt] = ed[cnt-1];
            LL sum = w[i];
            for(int k = u;k != j;k = fu[k]){
                s[k] = sum;
                sum += fw[k];
                cir[++ed[cnt]] = k;
            }
            s[j] = sum ,cir[++ed[cnt]] = j;
        }
    }
    
    ins[u] = false;
}

LL dfs_d(int u){  //找最长链
    st[u] = true;
    LL d1 = 0, d2 = 0;
    for(int i=h[u];~i;i=ne[i]){
        int j=e[i];
        if(st[j]) continue;
        LL length = dfs_d(j)+w[i];
        if(length >= d1) d2=d1,d1=length;
        else if(length >d2) d2=length;
    }
    ans=max(ans,d1+d2);
    return d1;
}

int main(){
    memset(h,-1,sizeof h);
    scanf("%lld",&n);
    
    for(int i=1;i<=n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,i,b),add(i,a,b);
    }
    for(int i=1;i<=n;i++)
        if(!st[i])
            dfs_s(i,-1); //找到所有环
            
    memset(st,0,sizeof st);
    for(int i=1;i<=ed[cnt];i++) st[cir[i]]=true; //环上的点不需要进行搜索
    
    for(int i=1;i<=cnt;i++){ //遍历每一棵基环树,找树上最长链和往下的最深深度
        ans = 0;
        int sz = 0;
        for(int j=ed[i-1]+1;j<=ed[i];j++){
            int k =cir[j];
            d[sz]=dfs_d(k);
            sum[sz]=s[k];
            sz ++ ;
        }
        for(int j=0;j<sz;j++)  
            d[sz+j] = d[j] , sum[sz+j] = sum[j] + sum[sz-1];
        
        int hh=0,tt=-1;//单调队列优化
        for(int j=0;j<2*sz;j++)
        {
            if(hh<=tt&&j-q[hh]>=sz) hh++;
            if(hh<=tt) ans=max(ans,d[j]+sum[j]+d[q[hh]]-sum[q[hh]]);
            while(hh<=tt&&d[q[tt]]-sum[q[tt]] <= d[j]-sum[j]) tt--;
            q[++tt] = j;
        }
        res += ans;
    } 
    printf("%lld\n",res);
    return 0;
}

```



### 基环树+断开环后的树上DP

`ZJOI 骑士`

https://www.luogu.com.cn/problem/P2607

### 做法1：
1.通过并查集维护连通性找出所有基环树的环的起点终点

2.对于每一个起点终点dfs不选这个点（和没有上司的舞会一摸一样的dfs），取max累加答案

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;
//================================
#define debug(a) cout << #a": " << a << endl;
#define rep(i, ll,rr) for(int i = ll; i <= rr; ++i)
const int N =2e6+10,INF = 1e9;
//================================
typedef pair<int,int> pii;
#define x first
#define y second
typedef long long LL; typedef unsigned long long ULL; typedef long double LD;
inline LL read() { LL s = 0, w = 1; char ch = getchar(); for (; !isdigit(ch); ch = getchar()) if (ch == '-') w = -1; for (; isdigit(ch); ch = getchar())    s = (s << 1) + (s << 3) + (ch ^ 48); return s * w; }
inline void print(LL x, int op = 10) { if (!x) { putchar('0'); if (op)  putchar(op); return; }  char F[40]; LL tmp = x > 0 ? x : -x; if (x < 0)putchar('-');  int cnt = 0;    while (tmp > 0) { F[cnt++] = tmp % 10 + '0';     tmp /= 10; }    while (cnt > 0)putchar(F[--cnt]);    if (op) putchar(op); }
//================================= 
int n,m,e[N],ne[2*N],h[N],node[N],idx=0,x,y,ans=0;
LL fa[N],f[N][2];
bool st[N],ins[N];
vector<pii> root;
/*
先使用并查集维护出所有基环树的断开的两个结点
对每一棵基环树各跑一遍两棵子树都不选
*/
void add(int a,int b){
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

int find(int x){
    return x==fa[x]?fa[x]:find(fa[x]);
}

LL dfs(int u,int p){
    f[u][0] = 0,f[u][1] = node[u];
    for(int i=h[u];~i;i=ne[i]){
        int j = e[i];
        if(j==p) continue;
        dfs(j,u);
        f[u][0] += max(f[j][0],f[j][1]);
        f[u][1] += f[j][0];
    }
    return f[u][0];
}

signed main(){
    memset(h,-1,sizeof h);
    n = read();
    rep(i,1,n) fa[i] = i; //初始化并查集
    rep(i,1,n){
        node[i]=read(),x=read();
        int pa=find(i),pb=find(x);
        if(pa!=pb){
            fa[pa]=pb;
            add(x,i),add(i,x);
        }
        else
            root.push_back({i,x});
    }
    LL sum = 0;
    for(auto u:root)
        sum += max(dfs(u.x,-1),dfs(u.y,-1));
    printf("%lld\n",sum);
    return 0;
}

```

### 做法2：

对于基环树森林

1.找出所有环

2.对于每一个环做dfs分别得到选起点和不选起点的答案取max
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
//================================
#define debug(a) cout << #a": " << a << endl;
#define rep(i, ll,rr) for(int i = ll; i <= rr; ++i)
const int N =1e6+10,INF = 1e9;
//================================
typedef pair<int,int> pii;
#define x first
#define y second
typedef long long LL; typedef unsigned long long ULL; typedef long double LD;
inline LL read() { LL s = 0, w = 1; char ch = getchar(); for (; !isdigit(ch); ch = getchar()) if (ch == '-') w = -1; for (; isdigit(ch); ch = getchar())    s = (s << 1) + (s << 3) + (ch ^ 48); return s * w; }
inline void print(LL x, int op = 10) { if (!x) { putchar('0'); if (op)  putchar(op); return; }  char F[40]; LL tmp = x > 0 ? x : -x; if (x < 0)putchar('-');  int cnt = 0;    while (tmp > 0) { F[cnt++] = tmp % 10 + '0';     tmp /= 10; }    while (cnt > 0)putchar(F[--cnt]);    if (op) putchar(op); }
//================================= 
int n,e[N],node[N],h[N],rm[N],ne[N],idx=0;
LL f1[N][2],f2[N][2],ans=0;
bool st[N],ins[N];

inline void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

void dfs_f(int u,int avo,LL f[][2]){
    //f[u][0] = 0;
    for(int i = h[u];~i; i = ne[i]){
        if(rm[i]) continue; //被斩断之边
        int j = e[i];
        dfs_f(j,avo,f);
        f[u][0] += max(f[j][0],f[j][1]);
    }
    f[u][1]=-INF;
    if(u!=avo){
        f[u][1] = node[u];
        for(int i=h[u];~i;i=ne[i]){
            if(rm[i]) continue;
            int j = e[i];
            f[u][1] += f[j][0];
        }
    }
}

void dfs_s(int u){
    st[u] = ins[u] = true;
    for(int i=h[u];~i;i=ne[i]){
        int j=e[i];
        if(!st[j]) dfs_s(j);
        else if(ins[j]){
            rm[i] = 1;
            dfs_f(j,-1,f1);
            dfs_f(j,u,f2);
            ans+=max(f1[j][0],f2[j][1]);
        }
    }
    ins[u]=false;
}

signed main(){
    memset(h,-1,sizeof h);
    n = read();
    rep(i,1,n){
        int a= read(),b=read();
        add(b,i);
        node[i] = a;
    }
    rep(i,1,n)
        if(!st[i])
            dfs_s(i);
    
    print(ans);
    return 0;
}
```



`bzoj`创世纪

```cpp
```



### 算法：基环树DP

这道题是我学完基环树后自己做出来的第一道题目hh，虽然调了很久
和这道题目有些类似的题目有IOI2008 Island 这题

https://www.luogu.com.cn/problem/P4381

下面来说这一题的思路：

n点n边，任意两点之间都有一条双向边，因此这是一颗基环树，对于基环树DP的题目，我们首先做的应该是找到环并断开
-	1.找环
```
void dfs_s(int u,int fa){
    st[u] = ins[u] = true;
    for(int i=h[u];~i;i=ne[i]){
        //if(i == (from^1)) continue; //用边判重会导致有三个点RE
        int j = e[i];
        if(j==fa) continue;
        fu[j] = u,fw[j] = w[i];
        
        if(!st[j]) dfs_s(j,u);
        else if(ins[j]){
           //debug(u);debug(j);
	       brk = w[i];
	       LL sum = 0;
	       for(int k = u;k!=j;k=fu[k]){
	           s[k] = sum;
	           sum += fw[k];
	           cir[++ed] = k;
	           
	       }
	       s[j] = sum, cir[++ed] = j;
        }
    }
    ins[u] = false;
}
```
找环有一个技巧在dfs的时候存储每个结点的访问状态，然后当遇到一个结点已经被访问过了，说明找到了环。然后同时根据记录的反向边而新开的数组fu[]就可以找出完整的环了

*！注意在判断是否重复走一个点的时候不能用边判重，需要用是否为父节点来判重,不然可能只有70pts*

这个时候我们断环成链，需要依次计算出在链上每一条边断开的形成的最长直径，在所有的直径中取最小的。之所以要取最小的是因为我们依次断开的那条边也是可以走的，但是在我们断开他之后不一定会被算到；

因此需要预处理四个数组来协助我们在O(n)的复杂度内完成最长直径的寻找

-	处理数组找直径
```
//处理出后缀和和A[]数组,起点出发到i点子树或者左边子树的最大值
    for(int j=1;j<=sz-1;j++){
        sub[j] = sum[sz] - sum[j];
        if(j==1) A[j] = d[j];
        else A[j] = max(A[j-1] , d[j] + sum[j]);
    	//debug(j);debug(A[j]);
    }
    //处理B[]数组
    for(int j=sz-1;j>=1;j--){
        if(j==sz-1) B[j] = d[j+1];
        else B[j] = max(B[j+1],d[j+1] + sub[j+1]);
        //debug(sub[j]);
    }
    mn=-0x3f3f3f3f;
    //处理C[]数组
    for(int j=1;j<=sz-1;j++){
        if(j==1) C[j] = max(d[j],tr[j]);
        else C[j] = max({C[j-1],tr[j],d[j]+sum[j]+mn});
        mn = max(mn,d[j]-sum[j]);
    }
    mn=-0x3f3f3f3f;
    //处理D[]数组
    for(int j=sz-1;j>=1;j--){
        if(j==sz-1) D[j] = max(tr[j+1],d[j+1]);
        else D[j] = max({D[j+1],tr[j+1],d[j+1]+sub[j+1]+mn});
        mn = max(mn,d[j+1]-sub[j+1]);
    }
    //debug(brk);
    for(int i=1;i<=sz-1;i++){
  		 //debug(A[i]);debug(B[i]);debug(C[i]);debug(D[i]);debug(A[i]+B[i]+brk);debug(ans);
        ans=min(ans,max({A[i],B[i],C[i],D[i],A[i]+B[i]+brk}));
    }
```

**下面是完整的代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
//================================
#define debug(a) cout << #a": " << a << endl;
#define rep(i, ll,rr) for(int i = ll; i <= rr; ++i)
const int N =1e5+10,INF = 1e9;
//================================
typedef pair<int,int> pii;
#define x first
#define y second
typedef long long LL; typedef unsigned long long ULL; typedef long double LD;
inline LL read() { LL s = 0, w = 1; char ch = getchar(); for (; !isdigit(ch); ch = getchar()) if (ch == '-') w = -1; for (; isdigit(ch); ch = getchar())    s = (s << 1) + (s << 3) + (ch ^ 48); return s * w; }
inline void print(LL x, int op = 10) { if (!x) { putchar('0'); if (op)  putchar(op); return; }  char F[40]; LL tmp = x > 0 ? x : -x; if (x < 0)putchar('-');  int cnt = 0;    while (tmp > 0) { F[cnt++] = tmp % 10 + '0';     tmp /= 10; }    while (cnt > 0)putchar(F[--cnt]);    if (op) putchar(op); }
//================================= 
int n,m,a,b;
LL e[N*2],ne[N*2],h[N],idx=0,fu[N*2],tr[N*2],brk;  //tr[]维护当前树上的直径
LL w[N*2],fw[N],d[N*2],s[N*2],sum[N*2],c;
LL A[N],B[N],C[N],D[N],sub[N],mn=-0x3f3f3f3f;//mn维护d[x]-s[x]的最大值
int cir[N],ed=0,q[N*2];
bool st[N*2],ins[N*2];
LL res,ans=1e18;
/*
sum为前缀和
1.A[]:环上第一个点出发到i点的子树或者左边子树的最大距离 d[i] + sum[i]
2.B[]:环上最后一个点出发到i或者右边子树的最大距离 d[i] + sub[i]
3.C[]:i之前的直径 d[x] + d[y] - sum[x] + sum[y]
4.D[]:i之后的直径 d[x] + d[y] + sum[x] - sum[y]
*/
void add(int a,int b,LL c){
    e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

void dfs_s(int u,int fa){
    st[u] = ins[u] = true;
    for(int i=h[u];~i;i=ne[i]){
        //if(i == (from^1)) continue; //用边判重会导致有三个点RE
        int j = e[i];
        if(j==fa) continue;
        fu[j] = u,fw[j] = w[i];
        
        if(!st[j]) dfs_s(j,u);
        else if(ins[j]){
           //debug(u);debug(j);
	       brk = w[i];
	       LL sum = 0;
	       for(int k = u;k!=j;k=fu[k]){
	           s[k] = sum;
	           sum += fw[k];
	           cir[++ed] = k;
	           
	       }
	       s[j] = sum, cir[++ed] = j;
        }
    }
    ins[u] = false;
}

LL dfs_d(int u,int id){
    st[u] = true;
    LL d1 = 0 , d2 = 0 ;
    for(int i=h[u];~i;i=ne[i]){
        int j = e[i];
        if(st[j]) continue;
        LL length = dfs_d(j,id)+w[i];
        if(length > d1) d2 = d1,d1 = length;
        else if(length > d2) d2 = length;
    }
    tr[id] = d1 + d2;
    return d1;
}

signed main(){
    memset(h,-1,sizeof h);
    n=read();
    rep(i,1,n){
        a=read(),b=read(),c=read();
        add(a,b,c),add(b,a,c);
    }
    for(int i=1;i<=n;i++)
        if(!st[i])
            dfs_s(i,-1);
    
    memset(st,0,sizeof st);
    for(int i=1;i<=ed;i++) st[cir[i]] = true;  //将圆上的点全部标记一下，防止被找过
    
//     ans = 0.0;
    int sz = 1;
    for(int j = 1;j <= ed; j++){
        int k = cir[j];
        d[sz] = dfs_d(k,sz);
        sum[sz] = s[k];
        sz ++ ;
    }sz--;
    //debug(sz);debug(sum[sz]);
    //处理出后缀和和A[]数组,起点出发到i点子树或者左边子树的最大值
    for(int j=1;j<=sz-1;j++){
        sub[j] = sum[sz] - sum[j];
        if(j==1) A[j] = d[j];
        else A[j] = max(A[j-1] , d[j] + sum[j]);
    	//debug(j);debug(A[j]);
    }
    //处理B[]数组
    for(int j=sz-1;j>=1;j--){
        if(j==sz-1) B[j] = d[j+1];
        else B[j] = max(B[j+1],d[j+1] + sub[j+1]);
        //debug(sub[j]);
    }
    mn=-0x3f3f3f3f;
    //处理C[]数组
    for(int j=1;j<=sz-1;j++){
        if(j==1) C[j] = max(d[j],tr[j]);
        else C[j] = max({C[j-1],tr[j],d[j]+sum[j]+mn});
        mn = max(mn,d[j]-sum[j]);
    }
    mn=-0x3f3f3f3f;
    //处理D[]数组
    for(int j=sz-1;j>=1;j--){
        if(j==sz-1) D[j] = max(tr[j+1],d[j+1]);
        else D[j] = max({D[j+1],tr[j+1],d[j+1]+sub[j+1]+mn});
        mn = max(mn,d[j+1]-sub[j+1]);
    }
    //debug(brk);
    for(int i=1;i<=sz-1;i++){
  		 //debug(A[i]);debug(B[i]);debug(C[i]);debug(D[i]);debug(A[i]+B[i]+brk);debug(ans);
        ans=min(ans,max({A[i],B[i],C[i],D[i],A[i]+B[i]+brk}));
    }
    
    ans & 1 ? printf("%lld.5",ans/2) : printf("%lld.0",ans/2);
    
    return 0;
}
```
