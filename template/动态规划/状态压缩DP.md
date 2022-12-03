# 状态压缩DP

<hr>

### 基于连通性的DP（棋盘式）

一般先经过预处理处理出所需要的状态，再进行枚举

### 集合式



### 愤怒的小鸟
这道题对于我这种新手来说不太友好，而且并没有做过重复覆盖问题，所以在y总视频里听的也不是很懂。本题解综合了许多题解和一些我自己的想法。

### 对于这样一道题目有两种做法：
1.状态压缩DP
2.记忆化搜索

#### 状态压缩DP
这道题之所以能状态压缩（1）数据范围允许（2）对于猪的数量我们可以较好的进行压缩

第一步：预处得出理所有两个点所能构成的二次函数，再遍历所有点，并记录此二次函数能经过哪些点.（用状态压缩记录，例如10111表示除了第二个点以外其余点都能经过）
#### 此处path[i,j]表示由第i个 点和第j个点构成的二次函数所能经过的所有点组合成的状态

第二步：状态压缩的动态规划：
f数组是记录能打到当前状态的所有的猪所需要的最少的二次函数数量。例如f[10010]表示能打到第一个和第四个猪所需要的最少的二次函数数量；
状态转移：
###### f[i|path[i,j]]=min(f[i|path[i,j]],f[i]+1);
###### 意为：从i扩展到i|path[i,j]这一个状态有两种决策，我们取之前已经更新过的这一状态或者，从i状态直接添加一条曲线过多出了的一个点，这二者的最小值

#### AC代码：
```
#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define MAXN 20
typedef pair<double,double> pdd;
const double eps=1e-8;

pdd pig[MAXN];
int T,n,m;
int path[MAXN][MAXN];
int f[1<<MAXN];  //类似于动态规划的数组，表示击败每个状态所表示表示的小猪最少需要用到的小鸟数量

int cmp(double a,double b){
    if(fabs(a-b)<eps) return 0; //返回0表示相等
    else if(a>b) return 1; //返回1表示前数大
    return -1;  //返回-1表示前数小
}

int main(){
    cin >> T;
    while(T--){
        cin >> n >> m;  //m没啥用应该...
        for(int i=1;i<=n;i++){
            cin >> pig[i].x >> pig[i].y;
        }
        memset(path,0,sizeof(path));
        //预处理path[i][j]，表示经过i，j猪组成的抛物线能经过的猪的整体状态，如111111
        for(int i=1;i<=n;i++){
            path[i][i]=1<<(i-1);
            for(int j=1;j<=n;j++){
                double x1=pig[i].x,y1=pig[i].y;
                double x2=pig[j].x,y2=pig[j].y;
                
                if(!cmp(x1,x2)) continue;
                
                double a=(y1/x1-y2/x2)/(x1-x2);
                double b=(y1/x1-a*x1);
                
                if(cmp(a,0)>=0) continue;  //表示不是开口向下的二次函数
                int state=0;
                //遍历所有点，找到所有二次函数经过的点
                for(int k=1;k<=n;k++){
                    double x=pig[k].x,y=pig[k].y;
                    if(!cmp(a*x*x+b*x,y))
                        state+=1<<(k-1);
                }
                path[i][j]=state;
            }
        }
        
        memset(f,0x3f,sizeof(f));
        f[0]=0;
        for(int i=0;i<1<<n;i++){  //枚举小猪的数量，其中0表示小猪未被覆盖
            int x=0;
            //找到i中为0的位置，即未被覆盖的猪的位置
            for(int j=0;j<n;j++){
                if(!(i>>j&1)){
                    x=j+1;
                    break;
                }
            }
            for(int j=1;j<=n;j++){ //找到了未被覆盖的小猪x之后，遍历path[x][j]中的所有情况来更新f
                f[i|path[x][j]]=min(f[i|path[x][j]],f[i]+1); //决策：是更新为新的状态还是在原状态基础上增加一条抛物线
            }
        }
        cout << f[(1<<n)-1] << endl;
        //for(int i=0;i<=(1<<(n-1))-1;i++)
        //    cout << f[i] << " ";
        //cout << endl;
    }
    return 0;
}
```

```
/*
void dfs(int state,int cnt) //存储哪些列已经被覆盖
{
    if(state 包括所有列) {
    ans=min(ans,cnt);
    return ;
    }
    任选没有覆盖的一列x；
    枚举所有能够覆盖x的抛物线
    更新一下state->new_state
    dfs(new_state,cnt+1);
}
*/

//预处理f[state]
//任取当前未被覆盖，枚举所有覆盖x的抛物线path[x][j]
//new_state=state|path[x][j]

```
path[i,j]表示穿过i,j这个节点的抛物线能够覆盖的节点