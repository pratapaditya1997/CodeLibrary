#include "bits/stdc++.h"

using namespace std;

#define int long long int
#define pb push_back
#define se second
#define fi first

typedef pair<int, int> pii;

const int N = 1e5+5;
vector<pii> g[N];
int dp[N],ans;

void dfs(int u,int par){
    for(auto edge: g[u]){
        int v = edge.fi, w=edge.se;
        if(v == par) continue;
        dfs(v,u);
        ans = max(ans,dp[u]+dp[v]+w);
        dp[u] = max(dp[u],dp[v]+w);
    }
}

#undef int
int main() {
#define int long long int
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t; cin>>t;
    for(int tt = 1;tt <= t;tt++){
        for(int i=0;i<N;i++) g[i].clear();
        memset(dp,0,sizeof dp);

        ans=0;
        int n; cin>>n;
        for(int i=1;i<=n-1;i++){
            int u,v,w; cin>>u>>v>>w;
            u++; v++;
            g[u].pb({v,w});
            g[v].pb({u,w});
        }
        dfs(1,0);
        cout << "Case " << tt << ": " << ans << endl;
    }

    return 0;
}
