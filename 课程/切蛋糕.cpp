#define int LL
const int N=500010,M=N*2,mod=1e9+7;
int q[N],a[N],hh,tt,n,m;

void solve(){
	int ans=0;
	n=read(); m=read();
	rep(i,1,n) a[i]=a[i-1]+read();
	hh=0,tt=-1;
	q[++tt]=0;
	for(int i=1;i<=n;++i){
		while(hh<=tt&&i-q[hh]>m) hh++;
		while(hh<=tt&&a[q[tt]]>=a[i]) tt--;
		if(hh<=tt) ans=max(ans, a[i]-a[q[hh]]);
		q[++tt]=i;
	}
	print(ans);
}