const int mod = 1e8 - 3;
#define N 200010
struct BIT{
	#define lowbit(x) ((x)&(-x))
	int tr[N];
	inline void add(int x,int d){for(;x<=N-10;x+=lowbit(x)) tr[x]+=d;}
	inline int ask(int x){int ans=0;for(;x;x-=lowbit(x)) ans+=tr[x];return ans;}
}T;
int n,m;
pii a[N],b[N];
unordered_map<int,int> mp;

void solve(){
	n=read();
	rep(i,1,n) a[i].x=read(),a[i].y=i;
	rep(i,1,n) b[i].x=read(),b[i].y=i;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;++i){
		mp[i]=a[i].y;
	}
	sort(b+1,b+1+n);
	for(int i=1;i<=n;++i){
		b[i].x=mp[i];
	}
	sort(b+1,b+1+n,[](pii &A,pii &B){
		return A.y < B.y;
	});
	LL ans=0;
	for(int i=1;i<=n;++i){
		T.add(b[i].x,1);
		ans += i-T.ask(b[i].x);
	}
	ans%=mod;
	print(ans);
}