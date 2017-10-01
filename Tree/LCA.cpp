#include "bits/stdc++.h"
#define ll long long int
#define ld long double
#define all(x) x.begin(), x.end()
#define pb push_back
#define se second
#define fi first
using namespace std;
typedef pair<ll,ll> pll;

const ll N=2e5+5;
const ll M=20;
vector<ll> g[N];
ll level[N],P[N][M];

void dfs(ll u,ll par){
	level[u]=1+level[par];
	P[u][0]=par;
	for(ll v:g[u]){
		if(v==par) continue;
		dfs(v,u);
	}
}

ll lca(ll u,ll v){
	if(level[u]<level[v]) swap(u,v);
	ll lg=0;
	for(lg=0;(1<<lg)<=level[u];lg++);
	lg--;
	for(ll i=lg;i>=0;i--){
		if(level[u]-(1<<i)>=level[v]){
			u=P[u][i];
		}
	}
	if(u==v) return u;
	for(ll i=lg;i>=0;i--){
		if(P[u][i]!=-1 and P[u][i]!=P[v][i]){
			u=P[u][i];
			v=P[v][i];
		}
	}
	return P[u][0];
}

ll getAncestor(ll u,ll dis){
	dis=level[u]-dis; // gets level of ancestor
	ll lg=0;
	for(lg=0;(1<<lg)<=level[u];lg++);
	lg--;
	for(ll i=lg;i>=0;i--){
		if(level[u]-(1<<i)>=dis){
			u=P[u][i];
		}
	}
	return u;
}

ll dist(ll u,ll v){
	if(level[u]<level[v]) swap(u,v);
	ll w=lca(u,v);
	return level[u]+level[v]-2*level[w];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    //freopen("input.in","r",stdin); 
    //freopen("output.out","w",stdout);
    ll n; cin>>n;
    for(ll i=0;i<n-1;i++){
    	ll u,v; cin>>u>>v;
    	g[u].pb(v);
    	g[v].pb(u);
    }
    memset(P,-1,sizeof P);
    level[0]=-1;
    dfs(1,0);
    for(ll i=1;i<M;i++){
    	for(ll j=1;j<=n;j++){
    		if(P[j][i-1]!=-1){
    			P[j][i]=P[P[j][i-1]][i-1];
    		}
    	}
    }

    // do anything you want now with this sparse table kind of thing
    
    return 0;
}
