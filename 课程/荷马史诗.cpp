#define int LL
typedef pair<int,int> pii;
const int N=200010,M=N*2,mod=1e9+7;
int n,m,k,a[N],w[N];
struct Pos{
    int x,y;
    bool operator<(const Pos &W)const{
        if(x!=W.x) return x>W.x;
        return y>W.y;
    }
};
priority_queue<Pos> heap;

void solve(){
	n=read(),k=read();
	rep(i,1,n) w[i]=read();
	for(int i=1;i<=n;++i) heap.push({w[i],0});
 	while((n-1)%(k-1)!=0) heap.push({0,0}),n++;
	int ans=0;
	while(heap.size()>1){
	    Pos c; c.x=0,c.y=0;
	    for(int i=1;i<=k&&heap.size();++i){
	        auto u=heap.top(); heap.pop();
	       // cout<<u.x<<" "<<u.y<<"\n";
	        c.y=max(c.y, u.y);
	        c.x+=u.x;
	        ans+=u.x;
	    } //puts("");
	    c.y++;
	    heap.push(c);
	}
	print(ans);print(heap.top().y);
}
