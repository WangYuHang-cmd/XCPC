## Trie 字典树

##### 假的字符串

>链接：https://ac.nowcoder.com/acm/problem/15049
>
>给定n个字符串，互不相等，你可以任意指定字符之间的大小关系（即重定义字典序），求有多少个串可能成为字典序最小的串，并输出它们 

**分析**：首先如果某个字符串的前缀也出现，则这个字符串一定不会成为最小的。其次，如果有aa,ac,cc这种串出现，aa和cc都有可能为最小但是ac永远不可能为最小，就是我们对26个小写字母进行拓扑排序如果出现了环则当前字符串不能成为字典序最小。

**思路**：读入每个字符串的时候建`trie`树，因为好处理前缀的情况。然后循环每个字符串的时候检查前缀是否存在的同时对字符串的每一位根据`trie`树建图，然后统计入读，做topsort，如果无环就说明可以称为字典序最小的。

```cpp
const int N = 30050,M=N*10;
string str[N];
int n;string q;
int tr[M][27],dx=0;
string ans[N];int num=0;
int e[M],ne[M],h[N],idx=0;
int cnt[M],din[N],que[N],hh=0,tt=-1;

void init(){
//     memset(h , -1 , sizeof h) ;
//     memset(din , 0 , sizeof din) ;
    rep(i,0,n+26) h[i]=-1,din[i]=0;
    hh = 0 , tt = -1 ;
    idx = 0 ;
}

void add(int a,int b){
    din[b]++;
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void insert(string& q){
    int p=0;
    for(int i=0;i<q.size();++i){
        int u=q[i]-'a';
        if(!tr[p][u]) tr[p][u]=++dx;
        p=tr[p][u];
    }
    cnt[p]++;
}

bool check(string& q){
    int p=0;
    for(int i=0;i<q.size();++i){
        int u=q[i]-'a';
        if(cnt[p]) return false;
        for(int k=0;k<26;++k)
            if(tr[p][k] && k!=u)
                add(u,k);
        p=tr[p][u];
    }
    return true;
}

bool topsort(){
    hh=0,tt=-1;
    for(int i=0;i<26;++i)
        if(!din[i]){
            que[++tt]=i;
        }
    
    while(hh<=tt){
        int u=que[hh++];
        for(int i=h[u];~i;i=ne[i]){
            int j=e[i];
            if(--din[j]==0) que[++tt]=j;
        }
    }
    return tt==25;
}

void solve(){
	cin >> n;
    rep(i,1,n){
        cin >> str[i];
        insert(str[i]);
    }    
    for(int i=1;i<=n;++i){
        init();
        if(check(str[i])&&topsort()){
            ans[++num]=str[i];
        }
    }
    print(num);
    rep(i,1,num) cout << ans[i] << endl;
}
```



