const int inf = 1e9;

int LIS(vector<int> v,int n){
    vector<int> d(n+1,inf);
    for(int i=0;i<n;i++){
        *lower_bound(d.begin(),d.end(),v[i])=v[i];
    }
    for(int i=0;i<=n;i++){
        if(d[i]==inf) return i;
    }
}
