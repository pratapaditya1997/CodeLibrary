// with reference to problem ORQUERR on codechef
// change logic according to question

#include "bits/stdc++.h"

using namespace std;

#define int long long int
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define se second
#define fi first

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> matrix;

const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline int add(int x, int y) { x += y; if (x >= mod) x -= mod; return x;}
inline int sub(int x, int y) { x -= y; if (x < 0) x += mod; return x;}
inline int mul(int x, int y) { return ((x % mod) * (y % mod)) % mod;}
inline int power(int a, int b) {
	int x = 1;
	while (b) {
		if (b & 1) x = mul(x, a);
		a = mul(a, a);
		b >>= 1;
	}
	return x;
}
inline int inv(int a) { return power(a, mod - 2);}

const int N = 1e5+5;
const int MOD = 1e8;
int seg[26][N],lazy[26][N],a[N];
int power_2[26];

void build(int j,int node,int st,int en){
	lazy[j][node]=-1;
	if(st==en){
		int bit = (a[st]&(1<<j))?1:0;
		seg[j][node]=bit;
		return;
	}
	int mid = (st+en)/2;
	build(j,2*node,st,mid);
	build(j,2*node+1,mid+1,en);
	seg[j][node] = seg[j][2*node] + seg[j][2*node+1];
}

void update(int j,int node,int st,int en,int l,int r,int val){
	// relaxation
	if(lazy[j][node]!=-1){
		seg[j][node] = lazy[j][node]*(en-st+1);
		if(st!=en){
			lazy[j][2*node] = lazy[j][node];
			lazy[j][2*node+1] = lazy[j][node];
		}
		lazy[j][node]=-1;
	}

	if(en<l or r<st) return;
	if(l<=st and en<=r){
		lazy[j][node]=val;
		seg[j][node] = lazy[j][node]*(en-st+1);
		if(st!=en){
			lazy[j][2*node] = lazy[j][node];
			lazy[j][2*node+1] = lazy[j][node];
		}
		lazy[j][node]=-1;
		return;
	}

	int mid = (st+en)/2;
	update(j,2*node,st,mid,l,r,val);
	update(j,2*node+1,mid+1,en,l,r,val);
	seg[j][node] = seg[j][2*node] + seg[j][2*node+1];
}

int query(int j,int node,int st,int en,int l,int r){
	// relaxation
	if(lazy[j][node]!=-1){
		seg[j][node] = lazy[j][node]*(en-st+1);
		if(st!=en){
			lazy[j][2*node] = lazy[j][node];
			lazy[j][2*node+1] = lazy[j][node];
		}
		lazy[j][node]=-1;
	}

	if(en<l or st>r) return 0;
	if(st>=l and en<=r) return seg[j][node];

	int mid = (st+en)/2;
	int ans = query(j,2*node,st,mid,l,r) + query(j,2*node+1,mid+1,en,l,r);
	return ans;
}

int C(int x,int y){
	if(x<y) return 0;
	if(x==y) return 1;
	if(y==1) return x;
	if(y==2) return (x*(x-1)/2;
	if(y==3) return (x)*(x-1)*(x-2)/6;
}

void pre(){
	power_2[0]=1LL;
	for(int i=1;i<25;i++){
		power_2[i] = (power_2[i-1] * 2);
		power_2[i] %= MOD;
	}
}

#undef int
int main() {
#define int long long int
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	pre();
	int n; cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int j=0;j<25;j++) build(j,1,0,n-1);

	int q; cin>>q;
	while(q--){
		int type; cin>>type;
		if(type==1){
			int l,r,x; cin>>l>>r>>x;
			l--; r--;
			for(int j=0;j<25;j++){
				if(x&(1<<j)) update(j,1,0,n-1,l,r,1);
				else update(j,1,0,n-1,l,r,0);
			}
		} else {
			int l,r; cin>>l>>r;
			l--; r--;
			int ans = 0;
			for(int j=0;j<25;j++){
				int o = query(j,1,0,n-1,l,r);
				int z = (r-l+1) - o;
				int count = C(o,3)*C(z,0) + C(o,2)*C(z,1) + C(o,1)*C(z,2);
				ans = ans + count * power_2[j];
			}
			cout<<ans<<endl;
		}
	}		

	return 0;
}
