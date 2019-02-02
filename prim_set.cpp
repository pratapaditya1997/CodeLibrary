/*
constructs MST of given graph 'g' -> 'tree' using set implementation of prims algo
*/

int n;
int dist[N],parent[N],vis[N];
vector<pii> g[N],tree[N];

int prim(int source){
    for(int i=1;i<=n;i++) dist[i]=inf;
    set<pii> s;
    s.insert({0,source});
    int cost=0; dist[source]=0;
    while(!s.empty()){
        auto x = *(s.begin());
        s.erase(x);
        vis[x.se]=1;
        cost += x.fi;
        int v=x.se, u=parent[x.se], w=x.fi;
        tree[u].pb({v,w});
        tree[v].pb({u,w});
        for(auto it: g[x.se]){
            if(vis[it.fi]) continue;
            if(dist[it.fi] > it.se){
                s.erase({dist[it.fi],it.fi});
                dist[it.fi] = it.se;
                s.insert({dist[it.fi],it.fi});
                parent[it.fi] = x.se;
            }
        }
    }
    return cost;
}
