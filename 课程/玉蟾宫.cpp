const int N=200010,M=N*2,mod=1e9+7;
int n,m,k,a[N];
int g[1010][1010],w[1010];
int stk[N],top=0,col[1010][1010],lf[N],rt[N];

void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			char op[2];
			scanf("%s",op);
			g[i][j]=(*op=='F');
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			col[i][j]=g[i][j]?col[i-1][j]+g[i][j]:0;
		}
	}
	
	// for(int i=1;i<=n;++i) {
		// for(int j=1;j<=m;++j) printf("%d ",col[i][j]);
		// puts("");
	// }
	
	for(int i=1;i<=n;++i){
		top=-1;
		stk[++top]=0;
		for(int j=1;j<=m;++j){
			while(top&&col[i][stk[top]]>=col[i][j]) top--;
			lf[j]=j-stk[top];
			stk[++top]=j;
		}
		top=-1;
		stk[++top]=m+1;
		for(int j=m;j>=1;--j){
			while(top&&col[i][stk[top]]>=col[i][j]) top--;
			rt[j]=stk[top]-j;
			stk[++top]=j;
		}
		
		for(int j=1;j<=m;++j){
			ans=max(ans, (rt[j]+lf[j]-1)*col[i][j]);
		}	
	}
	print(ans*3);
}