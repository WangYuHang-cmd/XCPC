## Mo's Algorithm

 莫队算法是一种离线算法，能够高效的完成序列的暴力查询和暴力修改。目前的理解是通过对所有查询离线排序后，通过分块来提高效率。

#### 普通莫队

##### 排序方式

通过对区间`[l,r]`以`l`所在块为第一关键字，`r`为第二关键字进行从小到大的排序

##### 算法操作

排序后按照顺序应对每个查询，由于每次左右指针只在一个块内移动，因此最大修改次数为$2\sqrt{n}$，因此莫队的时间复杂度为$n\sqrt{n}$

```cpp
for(int k=1,i=0,j=1,res=0;k<=m;++k){
    while(i<r) add(a[++i], res);
    while(i>r) del(a[i--], res);
    while(j<l) del(a[j++], res);
    while(j>l) add(a[--j], res);
    ans[id]=res;
}
```



#### 带修莫队

由于带修改操作，因此每个询问需要多记录一条时间轴，表征第几次询问。

##### 排序方式

对于区间`[l,r]`和修改次数`t`进行以`l`所在块为第一关键字，`r`所在块为第二关键字，`t`为第三关键字进行排序。

##### 算法操作

排序后对于每个查询，与原来一样，只是多加一个维度，最后处理不同修改的影响。有一个小`trick`，对于每次修改，可以将修改的数与修改数组记录的进行交换，无需新开数组记录。

```cpp
for(int k=1,i=0,j=1,t=0,res=0;k<=q1;++k){
    int id=q[k].id,l=q[k].l,r=q[k].r,tn=q[k].t;
    while(i<r) add(w[++i], res);
    while(i>r) del(w[i--], res);
    while(j<l) del(w[j++], res);
    while(j>l) add(w[--j], res);
    while(t < tn){
        t ++;
        if(mo[t].pos>=j&&mo[t].pos<=i){
            del(w[mo[t].pos], res);
            add(mo[t].c, res);
        }
        swap(w[mo[t].pos], mo[t].c);
    }
    while(t > tn){
        if(mo[t].pos>=j&&mo[t].pos<=i){
            del(w[mo[t].pos], res);
            add(mo[t].c, res);
        }
        swap(w[mo[t].pos], mo[t].c);
        t--;
    }
    ans[id]=res;
}
```



#### 回滚莫队

回滚莫队主要解决单个操作无法实现的问题，例如增加或者删除不好直接实现，例如求最大值等操作

##### 排序方式

此处正常按照区间`[l,r]`的`l`所在块为第一关键字，`r`的大小为第二关键字进行排序

##### 算法实现

按照排序顺序处理

- 初始化莫队区间为`l=询问左端点所在块的最右结点+1`,`r=询问左端点所在块的最右`
  - 如果询问的左右端点在一个块内，直接暴力求解，时间复杂度最多$\sqrt{n}$
  - 对于所有左端点在一个块内的，莫队区间右指针向右移动并更新答案。备份答案后左指针向左移动并记录答案。然后左指针回溯到原来初始化的位置，当前答案值回溯至备份答案。  $2\sqrt{n}$

###### 第一种实现方式

```cpp
for(int nw=1;nw<=m;){
    int af=nw; 
    //对于所有左端点在一个块内的
    int right = len*get(q[nw].l)+len-1;
    //暴力处理块内
    while(af<=m&&get(q[af].l) == get(q[nw].l)) af++;
    while(nw<af&&q[nw].r<=right){
        LL res=0;
        int id=q[nw].id,l=q[nw].l,r=q[nw].r;
        for(int i=l;i<=r;++i) add(a[i], res);
        ans[id]=res;
        for(int i=l;i<=r;++i) cnt[a[i]]--;
        nw++;
    }

    //莫队处理跨区间的
    LL res=0;
    int j=right+1,i=right;
    while(nw<af){
        int id=q[nw].id,l=q[nw].l,r=q[nw].r;
        while(i<r) add(a[++i], res);
        LL res_backup = res; //存储回溯点
        while(j>l) add(a[--j], res);
        ans[id]=res;
        while(j<right+1) cnt[a[j++]]--;
        res = res_backup;
        nw++;
    }
    // rep(i,lmx,rmx) cnt[i]=0;
    memset(cnt,0,sizeof cnt);
}
```

###### 第二种实现方式

```cpp
int left=1,right=0,last_block=-1,__l; //左指针，右指针，上一个块
LL res=0,backup=0;  //答案和备份
for(int i=1;i<=m;++i){  
    int l=q[i].l,r=q[i].r,id=q[i].id;
    //如果在一块内，在单独开的数组内直接暴力
    if(get(l) == get(r)){
        rep(j,l,r) __cnt[a[j]] ++;
        rep(j,l,r) ans[id]=max(ans[id], 1ll*__cnt[a[j]]*alls[a[j]]);
        rep(j,l,r) __cnt[a[j]] --;
        continue;
    }

    //访问到新的块则初始化莫队区间
    //初始化莫队左结点为当前询问区间的左边所属块的右节点+1
    if(get(l)!=last_block){
        while(right>get_right(l)) --cnt[a[right--]];
        while(left<get_right(l)+1) --cnt[a[left++]];
        last_block=get(l);
        res = 0;
    }
    //扩展右端点
    while(right<r) add(a[++right], res);
    backup = res; 
    __l=left;
    //暴力扩展左端点，统计答案后回滚
    while(__l>l) --__l,add(a[__l], res);
    ans[id] = res;
    res=backup; 

    while(__l<left) --cnt[a[__l]],__l++; //回滚
}
```



