#include<bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(int i=l;i<=r;++i)
typedef long long LL; 

inline LL read() { 
	LL s = 0, w = 1; char ch = getchar();
	 for (; !isdigit(ch); ch = getchar()) 
	 if (ch == '-') w = -1; 
	 for (; isdigit(ch); ch = getchar())    
	 s = (s << 1) + (s << 3) + (ch ^ 48); 
	 return s * w; 
}
inline void print(LL x, int op = 10) { 
	if (!x) { putchar('0'); if (op)  putchar(op); return; } 
	char F[40]; LL tmp = x > 0 ? x : -x; 
	if (x < 0)putchar('-');
	int cnt = 0;    
	while (tmp > 0) { F[cnt++] = tmp % 10 + '0';tmp /= 10; }   
    while (cnt > 0)putchar(F[--cnt]);  
    if (op) putchar(op); 
}

//================================= 
#define int LL
const int N = 200010;
int n,m,k,w[N];
struct Node{
    int l,r;
    int sum,mx,mn;
    int lazy,set;
}tr[N<<4];

void push_up(int u){
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
    tr[u].mx=max(tr[u<<1].mx,tr[u<<1|1].mx);
    tr[u].mn=min(tr[u<<1].mn,tr[u<<1|1].mn);
    tr[u].set=tr[u].lazy=0;
}

void val(Node& u,int lazy,int set){
    if(lazy){
        u.sum+=lazy*(u.r-u.l+1);
        u.mx+=lazy;
        u.mn+=lazy;
        if(u.set) u.set+=lazy;
        else u.lazy+=lazy;
    }
    if(set){
        u.sum = set*(u.r-u.l+1);
        u.mx=u.mn=set;
        u.set=set;
        u.lazy=0;
    }
}

void push_down(int u){
    val(tr[u<<1], tr[u].lazy, tr[u].set);
    val(tr[u<<1|1], tr[u].lazy, tr[u].set);
    tr[u].lazy=tr[u].set=0;
}

void build(int u,int l,int r){
    tr[u]={l,r};
    if(l==r){
        tr[u].lazy=tr[u].set=0;
        tr[u].mx=tr[u].mn=tr[u].sum=w[l];
        return ;
    }
    int mid=l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}

void tsqrt(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r){
        if(tr[u].mx==tr[u].mn){
            val(tr[u],0,(int)(sqrt(tr[u].mx)));
            return ;
        }
        push_down(u);
        int mid=tr[u].l+tr[u].r>>1;
        if(l<=mid) tsqrt(u<<1, l, r);
        if(r>mid) tsqrt(u<<1|1, l, r);
        push_up(u);
        return ;
    }
    push_down(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid) tsqrt(u<<1,l,r);
    if(r>mid) tsqrt(u<<1|1,l,r);
    push_up(u);
}

void modify(int u,int l,int r,int d){
    if(tr[u].l>=l&&tr[u].r<=r){
        val(tr[u],d,0);
        return ;
    }
    push_down(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(l<=mid) modify(u<<1,l,r,d);
    if(r>mid) modify(u<<1|1,l,r,d);
    push_up(u);
}

int query(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r){
        return tr[u].sum;
    }
    push_down(u);
    int mid=tr[u].l+tr[u].r>>1;
    int ans=0;
    if(l<=mid) ans+=query(u<<1,l,r);
    if(r>mid) ans+=query(u<<1|1,l,r);
    return ans;
}

void solve(){
	n=read(); m=read();
    rep(i,1,n) w[i]=read();
    build(1,1,n);
    while(m--){
        int op=read(),l,r,x;
        if(op==1){
            l=read(),r=read();
            tsqrt(1,l,r);
        }
        else if(op==2){
            l=read(),r=read(),x=read();
            modify(1,l,r,x);
        }
        else{
            l=read(),r=read();
            print(query(1,l,r));
        }
    }
}
//=================================
signed main(){
	int _=1; 
	// int _=read();
	while(_--)	solve();
	return 0;
}



