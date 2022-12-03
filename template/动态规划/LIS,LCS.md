### LIS最长上升子序列模型



### 最长公共子序列模型



### 最长公共上升子序列模型

$$
f[i][j]按照以b[j]结尾的最长上升子序列可以划分为：
$$



```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
    	f[i][j]=f[i-1][j];
        if(a[i]==b[j]){
            int maxn=1;
            for(int k=1;k<j;k++){
                if(b[j]>b[k]) maxn=max(maxn,f[i-1][k]+1);
               	f[i][j]=max(maxn,f[i][j]);
            }
        }
    }
```

maxn为前缀最大值，因此考虑优化：

```cpp
for(int i=1;i<=n;i++){
    int maxn=1;
    for(int j=1;j<=n;j++){
    	f[i][j]=f[i-1][j];
        if(a[i]==b[j])f[i][j]=max(f[i][j],maxn);
        if(a[i]>b[j]) maxn=max(maxn,f[i-1][j]+1);
    }
}
```

