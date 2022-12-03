链接：https://ac.nowcoder.com/acm/contest/21763/1017
来源：牛客网



## 题目描述

After successive failures in the battles against the Union, the Empire retreated to its last stronghold. Depending on its powerful defense system, the Empire repelled the six waves of Union's attack. After several sleepless nights of thinking, Arthur, General of the Union, noticed that the only weakness of the defense system was its energy supply. The system was charged by *N* nuclear power stations and breaking down any of them would disable the system.

The general soon started a raid to the stations by *N* special agents who were paradroped into the stronghold. Unfortunately they failed to land at the expected positions due to the attack by the Empire Air Force. As an experienced general, Arthur soon realized that he needed to rearrange the plan. The first thing he wants to know now is that which agent is the nearest to any power station. Could you, the chief officer, help the general to calculate the minimum distance between an agent and a station? 

## 输入描述:

The first line is a integer *T* representing the number of test cases.
Each test case begins with an integer *N* (1 ≤ *N* ≤ 100000).
The next *N* lines describe the positions of the stations. Each line consists of two integers *X* (0 ≤ *X* ≤ 1000000000) and *Y* (0 ≤ *Y* ≤ 1000000000) indicating the positions of the station.
The next following *N* lines describe the positions of the agents. Each line consists of two integers *X* (0 ≤ *X* ≤ 1000000000) and *Y* (0 ≤ *Y* ≤ 1000000000) indicating the positions of the agent. 　

## 输出描述:

For each test case output the minimum distance with precision of three decimal placed in a separate line.

示例1

## 输入

[复制](javascript:void(0);)

```
2
4
0 0
0 1
1 0
1 1
2 2
2 3
3 2
3 3
4
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
```

## 输出

[复制](javascript:void(0);)

```shell
1.414
0.000
```

AC:

```cpp
//分治
#include<bits/stdc++.h>
using namespace std;
//================================
#define debug(a) cout << #a": " << a << endl;
#define rep(i, ll,rr) for(int i = ll; i <= rr; ++i)
#define N 200010
//================================
typedef pair<int,int> pii;
#define x first
#define y second
typedef long long LL; typedef unsigned long long ULL; typedef long double LD;
inline LL read() { LL s = 0, w = 1; char ch = getchar(); for (; !isdigit(ch); ch = getchar()) if (ch == '-') w = -1; for (; isdigit(ch); ch = getchar())    s = (s << 1) + (s << 3) + (ch ^ 48); return s * w; }
inline void print(LL x, int op = 10) { if (!x) { putchar('0'); if (op)  putchar(op); return; }  char F[40]; LL tmp = x > 0 ? x : -x; if (x < 0)putchar('-');  int cnt = 0;    while (tmp > 0) { F[cnt++] = tmp % 10 + '0';     tmp /= 10; }    while (cnt > 0)putchar(F[--cnt]);    if (op) putchar(op); }
//================================= 
double eps = 1e-12;
const double INF = 1000000000000.0;
int n;
struct Pos{
    double x,y;
    int type;
}p[N];
int a[N];

double dist(int i,int j){
    if(p[i].type==p[j].type) return INF;
    return sqrt((1.0*p[i].x-p[j].x)*(1.0*p[i].x-p[j].x)+(1.0*p[i].y-p[j].y)*(1.0*p[i].y-p[j].y));
}

bool cmp(int i,int j){
    return p[i].y >= p[j].y;
}

bool cmp1(Pos A,Pos B){
	return A.x < B.x;
}

double merge_dist(int l,int r){
    if(r == l+1) return dist(l,r);
    if(r == l+2) return min(min(dist(l,l+1),dist(l+1,r)),dist(l,r));
    int mid = l + r >> 1;
    double ans = min(merge_dist(l,mid),merge_dist(mid+1,r));
    int cnt = 0;
    rep(i,l,r){
        if(p[i].x>=p[mid].x - ans && p[i].x <= p[mid].x + ans)
            a[++cnt] = i;
    }
    sort(a+1,a+1+cnt,cmp);
    rep(i,1,cnt)
    rep(j,i+1,cnt)
    {
        if(p[a[i]].y - p[a[j]].y >= ans) break;
        ans = min(ans,dist(a[i],a[j]));
    }
    return ans;
}

//=================================
int main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n ;
        rep(i,1,n)
            cin >> p[i].x >> p[i].y,p[i].type = 1;
        rep(i,n+1,2*n)
            cin >> p[i].x >> p[i].y, p[i].type = 2;
        sort(p+1,p+1+2*n,cmp1);
        printf("%.3lf\n",merge_dist(1,2*n)) ;
    }
	return 0;
}
```

![image-20211028183815897](C:\Users\Henry\AppData\Roaming\Typora\typora-user-images\image-20211028183815897.png)

可以转化为平面点对来做

