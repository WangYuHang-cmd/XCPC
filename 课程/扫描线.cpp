#include<unordered_set>
#include<unordered_map>
#include<functional>
#include<algorithm>
#include<string.h>
#include<iostream>
#include<iterator>
#include<cstring>
#include<numeric> 
#include<cstdio>
#include<vector>
#include<bitset>
#include<queue>
#include<stack>
#include<cmath>
#include<set>
#include<map>
#define x first
#define y second
using namespace std;
//================================
#define FASTIO cin.tie(nullptr) -> sync_with_stdio(false)
#define debug(a) cout << #a": " << a << endl;
#define rep(i, ll, rr) for(int i = ll; i <= rr; ++ i)
#define per(i, rr, ll) for(int i = rr; i >= ll; -- i)
typedef pair<int,int> pii;
typedef long long LL; typedef unsigned long long ULL; typedef long double LD;
inline LL read(){LL s=0,w=1;char ch=getchar();for(;!isdigit(ch); ch = getchar())if(ch == '-') w = -1; for (; isdigit(ch);ch = getchar())s=(s<<1)+(s<<3)+(ch^48);return s*w;}
inline void print(LL x,int op=10){if(!x){putchar('0');if(op)putchar(op);return;}char F[40];LL tmp=x>0?x:-x;if(x<0)putchar('-');int cnt=0;while(tmp>0){F[cnt++]=tmp%10+'0';tmp/=10;}while(cnt>0)putchar(F[--cnt]);if(op)putchar(op);}
inline void print128(__int128_t x){if(x < 0) {putchar('-');x = -x;}if(x/10) print128(x/10);putchar(x%10+'0');}
template <typename T>void read(T &x){x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}x*=f;return;}
template <typename T>void write(T x){if(x<0){putchar('-');x=-x;}if(x>9)write(x/10);putchar(x%10+'0');return;}      
LL fpower(LL a,LL b,LL mod) {LL ans = 1; while(b){ if(b & 1) ans = ans * (a % mod) % mod; a = a % mod * (a % mod) % mod; b >>= 1;} return ans; } 
LL Mod(LL a,LL mod){return (a%mod+mod)%mod;}
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
int mov[8][2]={1,0,0,1,-1,0,0,-1,1,1,-1,-1,1,-1,-1,1};
//================================= 
#define N 200010
int n,m,k;
vector<int> alls;
int get(int x){
	return lower_bound(alls.begin(), alls.end(), x)-alls.begin();
}
struct Segment_Tree{
	struct Node{
		int l,r,cnt;
		LL len;
	}tr[N<<2];
	void push_up(int u){
		if(tr[u].cnt) tr[u].len=1ll*alls[tr[u].r+1]-alls[tr[u].l];
		else if(tr[u].l!=tr[u].r) tr[u].len=1ll*tr[u<<1].len+tr[u<<1|1].len;
		else tr[u].len=0;
	}
	void build(int u,int l,int r){
		tr[u]={l,r,0,0};
		if(l==r) return ;
		int mid=l+r>>1;
		build(u<<1,l,mid); 
		build(u<<1|1,mid+1,r);
	}
	void modify(int u,int l,int r,int d){
		if(tr[u].l>=l&&tr[u].r<=r){
			tr[u].cnt += d;
			push_up(u);
			return ;
		}
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) modify(u<<1,l,r,d);
		if(r>mid) modify(u<<1|1,l,r,d);
		push_up(u);
	}
}T;
struct Pos{
	int x,y1,y2,z;
	bool operator<(Pos &W)const{
		return x<W.x;		
	}
};
vector<Pos> v;

void solve(){
	n=read();
	rep(i,1,n){
		int x1=read(),y1=read(),x2=read(),y2=read();
		v.push_back({x1,y1,y2,1});
		v.push_back({x2,y1,y2,-1});
		alls.push_back(y1); alls.push_back(y2);
	}
	sort(alls.begin(), alls.end());
	alls.erase(unique(alls.begin(), alls.end()), alls.end());
	
	sort(v.begin(), v.end());
	T.build(1,0,alls.size());
	LL ans=0,last=0;
	for(int i=0;i<v.size();++i){
		auto u=v[i];
		int x=u.x,y1=u.y1,y2=u.y2,z=u.z;
		y1=get(y1),y2=get(y2);
		if(i) ans += 1ll*T.tr[1].len*(x-last);
		T.modify(1,y1,y2-1,z);
		last=x;
	}
	print(ans);
}
//=================================
signed main(){
	int _=1; 
	// _=read();
	while(_--)	solve();
	return 0;
}



