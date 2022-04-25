#include<iostream>
#include<algorithm>
#include<cstring>
#include<string.h>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#define N 100010
using namespace std; 
typedef long long LL;
//read(x)
template <typename T>void read(T &x){x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}x*=f;return;}
//write(x)
template <typename T>void write(T x){if(x<0){putchar('-');x=-x;}if(x>9)write(x/10);putchar(x%10+'0');return;}      

int n,m;
int w[N];
struct Segment_Tree{
	struct Node{
		int l,r;
		int add;
		LL sum;
	}tr[N*4];
	
	void val(Node &root,int add){
		root.sum=(LL)(root.sum+(LL)add*(root.r-root.l+1));
		root.add+=add;
	}
	
	void push_up(int u){
		tr[u].sum=(LL)tr[u<<1].sum+tr[u<<1|1].sum;
		tr[u].add=0;
	}
	
	void push_down(int u){
		if(tr[u].add){
			val(tr[u<<1], tr[u].add);
			val(tr[u<<1|1], tr[u].add);
			tr[u].add=0;	
		}
	}
	
	void build(int u,int l,int r){
		tr[u]={l,r};
		if(l==r){
			tr[u].sum=w[r];
			return ;
		}
		int mid=l+r>>1;
		if(l<=mid) build(u<<1,l,mid);
		if(r>mid) build(u<<1|1,mid+1,r);
		push_up(u);
	}
	
	void modify(int u,int l,int r,int d){
		if(tr[u].l>=l&&tr[u].r<=r){
			tr[u].sum+=(LL)d*(tr[u].r-tr[u].l+1);
			tr[u].add+=d;
			return ;
		}
		push_down(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) modify(u<<1,l,r,d);
		if(r>mid) modify(u<<1|1,l,r,d);
		push_up(u);
	}
	
	LL query(int u,int l,int r){
		if(tr[u].l>=l&&tr[u].r<=r) return tr[u].sum;
		push_down(u);
		int mid=tr[u].l+tr[u].r>>1;
		LL ans=0;
		if(l<=mid) ans+=query(u<<1,l,r);
		if(r>mid) ans+=query(u<<1|1,l,r);
		return ans;
	}
}T;

int main(){
	read(n),read(m);
	for(int i=1;i<=n;i++)
		read(w[i]);
	T.build(1,1,n);
	
	for(int i=1;i<=m;i++){
		int op,l,r,k;
		read(op),read(l),read(r);
		if(op==1){
			read(k);
			T.modify(1,l,r,k);
		}
		else{
			printf("%lld\n",T.query(1,l,r));
		}
	}	
	return 0;
}

