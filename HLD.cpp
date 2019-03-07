/*
for SPOJ question QTREE
this will give TLE. optimize IO operations for AC
*/

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

const int inf = 1e18;
const int mod = 1e9+7;

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

const int N = 1e4+4;
const int M = 15;

vi g[N],edges[N],idx[N];

int lca[M][N],tree[4*N],subSize[N],depth[N];
int pos,chainNo,chainHead[N],chainIndex[N],arr[N],basePos[N],endNode[N];

void reset(int n){
    for(int i=0;i<=n;i++){
        g[i].clear();
        edges[i].clear();
        idx[i].clear();
        chainHead[i] = -1;
        for(int j=0;j<M;j++) lca[j][i] = -1;
    }
}

void init(int n){
    for(int j=1;j<M;j++){
        for(int i=1;i<=n;i++){
            lca[j][i] = lca[j-1][lca[j-1][i]];
        }
    }
}

int LCA(int x,int y){
    if(depth[x] < depth[y]) swap(x,y);
    for(int i=M-1;i>=0;i--){
        if((depth[x]-(1 << i)) >= depth[y]) x = lca[i][x];
    }
    if(x == y) return x;
    for(int i=M-1;i>=0;i--){
        if(lca[i][x] != lca[i][y]){
            x = lca[i][x];
            y = lca[i][y];
        }
    }
    return lca[0][x];
}

void dfs(int u,int par,int level){
    depth[u] = level;
    lca[0][u] = par;
    subSize[u] = 1;
    int x = (int)g[u].size();
    while(x--){
        int v = g[u][x];
        if(v == par)continue;
        endNode[idx[u][x]] = v;
        dfs(v,u,level+1);
        subSize[u] += subSize[v];
    }
}

void HLD(int u,int cost,int parent){
    if(chainHead[chainNo] == -1) chainHead[chainNo] = u;
    pos ++;
    chainIndex[u] = chainNo;
    basePos[u] = pos;
    arr[pos] = cost;
    int specialChild = -1, edgeCost=0;
    int x = (int)g[u].size();
    while(x--){
        int v = g[u][x];
        if(v != parent){
            if(specialChild == -1 or subSize[v] > subSize[specialChild]){
                specialChild = v;
                edgeCost = edges[u][x];
            }
        }
    }
    if(specialChild != -1) HLD(specialChild,edgeCost,u);

    x = (int)g[u].size();
    while(x--){
        int v = g[u][x];
        if(v != parent and v != specialChild){
            chainNo ++;
            HLD(v,edges[u][x],u);
        }
    }
}

void build(int node,int start,int end){
    if(start == end){
        tree[node] = arr[start];
    } else {
        int mid = (start+end)/2;
        build(2*node,start,mid);
        build(2*node+1,mid+1,end);
        tree[node] = max(tree[2*node],tree[2*node+1]);
    }
}

void update_tree(int node,int start,int end,int l,int r,int val){
    if(start > end or start > r or end < l) return;
    if(l <= start and r >= end){
        tree[node] = val;
        return;
    }
    int mid = (start+end)/2;
    update_tree(2*node,start,mid,l,r,val);
    update_tree(2*node+1,mid+1,end,l,r,val);
    tree[node] = max(tree[2*node],tree[2*node+1]);
}

int query_tree(int node,int start,int end,int l,int r){
    if(start > end or start > r or end < l) return -inf;
    if(l <= start and r >= end) return tree[node];
    int mid = (start + end)/2;
    int ret1 = query_tree(2*node,start,mid,l,r);
    int ret2 = query_tree(2*node+1,mid+1,end,l,r);
    return max(ret1,ret2);
}

int queryUp(int u,int v){
    if(u == v) return 0;
    int lchain,rchain = chainIndex[v], ans=-1;
    while(1){
        lchain = chainIndex[u];
        if(lchain == rchain){
            if(u == v) break;
            int cur = query_tree(1,0,pos,basePos[v]+1,basePos[u]);
            ans = max(ans,cur);
            break;
        }
        int cur = query_tree(1,0,pos,basePos[chainHead[lchain]],basePos[u]);
        ans = max(ans,cur);
        u = chainHead[lchain];
        u = lca[0][u];
    }
    return ans;
}

int queryPath(int u,int v){
    int w = LCA(u,v);
    int val1 = queryUp(u,w);
    int val2 = queryUp(v,w);
    return max(val1,val2);
}

void update(int idx,int val){
    int u = endNode[idx];
    update_tree(1,0,pos,basePos[u],basePos[u],val);
}

class QueryOnATree {
public:
	void solve(std::istream& cin, std::ostream& cout) {
	    int t; cin >> t;
	    while(t--){
	        int n; cin >> n;
	        reset(n);
	        for(int i=1;i<n;i++){
	            int u,v,w; cin >> u >> v >> w;
	            g[u].pb(v);     g[v].pb(u);
	            edges[u].pb(w); edges[v].pb(w);
	            idx[u].pb(i);   idx[v].pb(i);
	        }
	        dfs(1,0,0);
	        init(n);
	        pos = -1; chainNo=1;
	        HLD(1,0,0);

	        //for(int i=0;i<=pos;i++) cout << arr[i]  << endl;
	        build(1,0,pos);
	        string str; cin >> str;
	        while(str[0] != 'D'){
	            int u,v; cin >> u >> v;
	            if(str[0] == 'Q') {
	                cout << queryPath(u,v) << endl;
	            } else update(u,v);
	            cin >> str;
	        }
	    }
	}
};
