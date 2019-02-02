/*
seg tree to find max elem and min elem in a range using lazy prop.
modify as required
*/

const int inf = 1e18;

const int N = 1e5+5;
int a[N],lazy[4*N],n,m;

struct Node{
    int mini,maxi;
};
Node tree[4*N];

void build(int node,int start,int end){
    if(start == end){
        tree[node].maxi = a[start];
        tree[node].mini = a[start];
    } else {
        int mid = (start+end)/2;
        build(2*node,start,mid);
        build(2*node+1,mid+1,end);
        tree[node].maxi = max(tree[2*node].maxi,tree[2*node+1].maxi);
        tree[node].mini = min(tree[2*node].mini,tree[2*node+1].mini);
    }
}

void update(int node,int start,int end,int l,int r,int val){
    if(lazy[node]){
        tree[node].maxi += lazy[node];
        tree[node].mini += lazy[node];
        if(start != end){
            lazy[2*node]   += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if(start > end or start > r or end < l) return;

    if(l <= start and r >= end){
        tree[node].maxi += val;
        tree[node].mini += val;
        if(start != end){
            lazy[2*node]   += val;
            lazy[2*node+1] += val;
        }
        return;
    }

    int mid = (start+end)/2;
    update(2*node,start,mid,l,r,val);
    update(2*node+1,mid+1,end,l,r,val);

    tree[node].maxi = max(tree[2*node].maxi,tree[2*node+1].maxi);
    tree[node].mini = min(tree[2*node].mini,tree[2*node+1].mini);
}

Node query(int node,int start,int end,int l,int r){
    Node ret;
    ret.maxi = -inf; ret.mini = inf;

    if(start > end or start > r or end < l) return ret;

    if(lazy[node]){
        tree[node].maxi += lazy[node];
        tree[node].mini += lazy[node];
        if(start != end){
            lazy[2*node]   += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node]=0;
    }

    if(l <= start and r >= end) return tree[node];

    int mid = (start+end)/2;
    Node ret1 = query(2*node,start,mid,l,r);
    Node ret2 = query(2*node+1,mid+1,end,l,r);

    ret.maxi = max(ret1.maxi,ret2.maxi);
    ret.mini = min(ret1.mini,ret2.mini);

    return ret;
}
