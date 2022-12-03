## 有后效性的DP问题

### 动态规划倒推+高斯消元

#### 坏掉的机器人

![image-20211216004139344](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20211216004139344.png)

```
10 10
10 4

0.0000000000

10 14
5 14

18.0038068653
```

1.概率DP的老套路：从后向前推导，我们令`f[i][j]`表示在`(i,j)`处到终点的期望步数，初始状态为`f[n][i] = 0`

2.写出状态转移方程：

- `j=1时`有$f[i][j] = \frac{1}{3} (f[i][j]+f[i][j+1]+f[i+1][j])$
- `j=m`时有$f[i][j] = \frac{1}{3}(f[i][j-1]+f[i][j]+f[i+1][j])$
- 其他情况$f[i][j]=\frac{1}{4}(f[i][j-1]+f[i][j]+f[i][j+1]+f[i+1][j])$

我们将状态的转移看成一层一层的，因此转移只在层间进行

我们可以写出转移的式子：
$$
\begin{gathered}
\quad
\begin{bmatrix} f(i,1) \\ f(i,2) \\ 
				f(i,3) \\ f(i,4) \\ 
				f(i,5) \end{bmatrix}
				=

\quad
\begin{bmatrix} \frac{2}{3} & -\frac{1}{3} & 0 & 0 & 0 \\
				-\frac{1}{4} & \frac{3}{4} & -\frac{1}{4} & 0 & 0 \\
                0 & -\frac{1}{4} & \frac{3}{4} & -\frac{1}{4} & 0 \\
                0 & 0 & 0 & \frac{2}{3} & -\frac{1}{3}
                \end{bmatrix}
\quad
\begin{bmatrix} \frac{1}{3}f(i+1,1) + 1 \\ \frac{1}{3}f(i+1,2) + 1 \\ 
				\frac{1}{3}f(i+1,3) + 1 \\ \frac{1}{3}f(i+1,4) + 1 \\ 
				\frac{1}{3}f(i+1,5) + 1 \end{bmatrix}
\end{gathered}
$$
从而使用高斯消元法进行转移，最后求解式子

```cpp
void gauss(){
    double t;

    for(int i=1;i<=m;++i){
        t = mat[i][i];
        mat[i][i] /= t, mat[i][i+1] /= t;
        if(i<m) mat[i][m+1] /= t;  //当最后一行时，已经除过，因此无需再除
        t = mat[i+1][i];
        mat[i+1][i] -= t * mat[i][i], mat[i+1][i+1] -= t * mat[i][i+1];
        mat[i+1][m+1] -= t*mat[i][m+1];
    }

    for(int i=m;i;--i){
        mat[i-1][m+1] -= mat[i-1][i] * mat[i][m+1];
        mat[i-1][i] -= mat[i-1][i] * mat[i][i]; 
    }
}

void solve(){
    cin >> n >> m >> x >> y;

    if(m==1){ printf("%.4lf",2.0*(n-x)); return ;}

    for(int i=n-1;i>=x;--i){
        mat[1][1] = mat[m][m] = 2.0/3;
        mat[1][2] = mat[m][m-1] = -1.0/3;
        mat[1][m+1] = 1.0+f[i+1][1]/3.0;
        mat[m][m+1] = 1.0+f[i+1][m]/3.0;

        for(int j=2;j<m;++j){
            mat[j][j-1] = -1.0/4, mat[j][j] = 3.0/4, mat[j][j+1] = -1.0/4;
            mat[j][m+1] = 1.0+f[i+1][j]/4;
        }

        gauss();

        rep(j,1,m) f[i][j] = mat[j][m+1]; //重新赋值 
    }

    printf("%.4lf",f[x][y]);
}
```

