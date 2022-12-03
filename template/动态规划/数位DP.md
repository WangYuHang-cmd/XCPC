## 数位DP

例子：不要25和4

给定两个数n和m，求出区间[n,m]中的所有数字，满足数字中不含25和4

用 f(pos，st)示第pos位的状态，其中st=0为前面没出现符合要求的（包括只出现2）

st=1表示前一位出现了2的情况 ，st=2表示前面出现了符合情况

因此有状态转移方程：

```cpp
if(i==4||st==2||(st==1&&i==5))
    ans+=dp(pos-1,2,flag||i<x);
else if(i==2)
    ans+=dp(pos-1,2,flag||i<x);
else 
    ans+=dp(pos-1,0,flag||i<x);
```

因此，数位DP一般使用记忆化搜索来做，下面是不要62的模板示例

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 10;

int n,m,a[N];
int f[N][3];

int dp(int pos,int st,int flag){
    if(!pos) return st==2;
    if(flag && f[pos][st]!=-1) return f[pos][st];
    int x=flag?9:a[pos];
    int ans=0;
    for(int i=0;i<=x;i++){
        if(i==4||st==2||(st==1&&i==2))
            ans+=dp(pos-1,2,flag||i<x);
        else if(i==6)
            ans+=dp(pos-1,1,flag||i<x);
        else ans+=dp(pos-1,0,flag||i<x);
    }
    if(flag) f[pos][st]=ans;
    return ans;
}

int clac(int x){
    memset(f,-1,sizeof f);
    f[0][0]=1;
    int pos=0;
    while(x){
        a[++pos]=x%10;
        x/=10;
    }
    return dp(pos,0,0);
}

int main(){
    while(cin >> n >> m,n||m){
        cout << (m-n+1)-(clac(m)-clac(n-1)) << endl;
    }
    return 0;
}
```

