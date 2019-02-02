const int N = 1e5+5;

struct DSU{
    int connected,par[N],sz[N];
    DSU(){}
    DSU(int x){
        for(int i=1;i<=x;i++) {
            par[i] = i;
            sz[i] = 1;
        }
        connected = x;
    }
    int root(int x){
        while(x != par[x]){
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    }
    void merge(int u,int v){
        int root_u = root(u), root_v = root(v);
        if(root_u == root_v) return;
        connected -- ;
        if(sz[root_u] > sz[root_v]) swap(root_u,root_v);
        sz[root_v] += sz[root_u];
        sz[root_u] = 0;
        par[root_u] = par[root_v];
    }
};
