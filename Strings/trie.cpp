#include "bits/stdc++.h"
#define ll long long int
#define all(x) x.begin(), x.end()
#define pb push_back
#define se second
#define fi first
using namespace std;
typedef pair<ll,ll> pll;

const int N = 1e5+5;
ll trie[60*N][2],sz=0;

void insert(ll val){
    ll curr=0;
    for(ll i=45;i>=0;i--){
        ll dir=0;
        if((val>>i)&1) dir=1;
        if(trie[curr][dir]==-1) trie[curr][dir]=++sz;
        curr=trie[curr][dir];
    }
}

ll max_xor_query(ll val){
    ll ans=0,curr=0;
    for(ll i=45;i>=0;i--){
        ll dir=0;
        if((val>>i)&1) dir=1;
        if(dir==0){
            if(trie[curr][1]!=-1){
                ans += (1LL<<i);
                curr=trie[curr][1];
            }
            else{
                assert(trie[curr][0]!=-1);
                curr=trie[curr][0];
            }
        }
        if(dir==1){
            if(trie[curr][0]!=-1){
                ans += (1LL<<i);
                curr=trie[curr][0];
            }
            else{
                assert(trie[curr][1]!=-1);
                curr=trie[curr][1];
            }
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    memset(trie,-1,sizeof trie);
    insert(5); insert(10);
    cout<<max_xor_query(6)<<endl;
    return 0;
}
