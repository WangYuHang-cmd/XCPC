ST算法，处理RMQ区间最大值问题


ST预处理函数

```cpp
void ST_prework(){
	for(int i=1;i<=n;i++) ST[i][0]=arr[i];
	int t=log(n)/log(2)+1;
	for(int j=1;j<t;j++){
    	for(int i=1;i<=n-(1<<j)+1;i++){
        	//由公式ST[i,j]=max(ST[i,j-1],ST[i+2^(j-1),j-1]
        	ST[i][j]=max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
    	}
	}
}
```


查询操作
    
```cpp
int ST_query(int l,int r){
	int k=log(r-l+1)/log(2);
	return max(ST[l][k],ST[r-(1<<k)+1][k]);
}
```