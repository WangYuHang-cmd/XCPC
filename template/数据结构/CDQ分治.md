## CDQ分治

模板：（使用归并排序的分治解法）

![image-20220321205515700](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20220321205515700.png)

```cpp
const int N=200010,M=N*2,mod=1e9+7,tot=200000;
struct BIT{
    #define N 200010
    #define lowbit(x) ((x)&(-x))
    const int tot=200000;
    int tr[N];
    void add(int x,int d){for(;x<=tot;x+=lowbit(x))tr[x]+=d;}
    int ask(int x){
        int ans=0;
        for(;x;x-=lowbit(x)) ans+=tr[x];
        return ans;
    }
}B;
int n,m,k,ans[N];
struct Poi{
    int a,b,c,s,res;
    bool operator<(const Poi &W)const{
        if(a!=W.a) return a<W.a;
        if(b!=W.b) return b<W.b;
        return c<W.c;
    }
    bool operator == (const Poi& W)const{
        return a==W.a && b==W.b&& c==W.c;
    }
}p[N];

Poi tmp[N];
void merge(int l,int r){
    if(l>=r) return ;
    int mid=l+r>>1;
    merge(l,mid); merge(mid+1,r);
    int i=l,j=mid+1,cnt=0;
    while(i<=mid&&j<=r){
        if(p[i].b<=p[j].b) B.add(p[i].c, p[i].s), tmp[++cnt]=p[i++];
        else p[j].res+=B.ask(p[j].c), tmp[++cnt]=p[j++];
    }
    while(i<=mid) B.add(p[i].c, p[i].s), tmp[++cnt]=p[i++];
    while(j<=r) p[j].res+=B.ask(p[j].c), tmp[++cnt]=p[j++];
    for(int i=l;i<=mid;++i) B.add(p[i].c, -p[i].s);
    for(int i=l,j=1;i<=r;++i,++j) p[i]=tmp[j];
}

void solve(){
    n=read(),m=read();
    rep(i,1,n){
        p[i].a=read(),p[i].b=read(),p[i].c=read();
        p[i].s=1;
    }
    sort(p+1,p+1+n);  //先按照三关键字排序
    int k=1;
    for(int i=2;i<=n;++i){
        if(p[i]==p[k]) p[k].s++;
        else p[++k]=p[i];
    }
    merge(1, k);
    for(int i=1;i<=k;++i){
        ans[p[i].res+p[i].s-1]+=p[i].s;
    }
    for(int i=0;i<n;++i) print(ans[i]);
}
```

CDQ分治的应用：

1.二维数点问题

对于要求统计的二维平面的数点问题分拆成三个维度：`x,y,z`其中z表示是否是查询的的点

```cpp
    rep(i,1,n){
        int x=read(),y=read(),P=read();
        p[++idx]={x,y,0,P};
    }
    rep(i,1,m){
        int x1=read(),y1=read(),x2=read(),y2=read();
        p[++idx]={x1-1, y1-1, 1, 0, 1, i};
        p[++idx]={x1-1, y2, 1, 0, -1, i};
        p[++idx]={x2, y1-1, 1, 0, -1, i};
        p[++idx]={x2, y2, 1, 0, 1, i};
    }
    sort(p+1,p+1+idx);
```

然后在归并的过程中算出结果即可。

```cpp
void merge(int l,int r){
    if(l>=r) return ;
    int mid=l+r>>1;
    merge(l,mid), merge(mid+1,r);
    int i=l,j=mid+1,cnt=0;
    LL sum=0;
    while(i<=mid&&j<=r){
        if(p[i].y<=p[j].y) sum +=(!p[i].z)*p[i].p, tmp[++cnt]=p[i++];
        else p[j].sum+=sum,tmp[++cnt]=p[j++];
    }
    while(i<=mid) sum += (!p[i].z)*p[i].p, tmp[++cnt]=p[i++];
    while(j<=r) p[j].sum+=sum,tmp[++cnt]=p[j++];
    for(int i=l,j=1;i<=r;) p[i++]=tmp[j++];
}
```



2.统计LIS的数量：

```cpp
void CDQ(int l,int r){
    if(l>=r) return ;
    int mid=l+r>>1;
    CDQ(l,mid);
    int idx=0;
    rep(k,l,r) tmp[++idx]=k;
    sort(tmp+1, tmp+1+idx,[](int &x,int &y){
       	return a[x]==a[y]?x>y:a[x]<a[y];
    });
    int mx=0; LL num=0;
    for(int i=1;i<=idx;++i){
        int x=tmp[i];
        if(x>mid){
            if(mx+1>f[x])
                f[x]=mx+1,cnt[x]=num;
            else if(mx+1==f[x])
                cnt[x]=Mod(cnt[x]+num,mod);
        }
        else{
            if(f[x]>mx)
                mx=f[x], num=cnt[x];
            else if(f[x]==mx)
                num=Mod(num+cnt[x],mod);
        }
    }
    CDQ(mid+1, r);
}
```

