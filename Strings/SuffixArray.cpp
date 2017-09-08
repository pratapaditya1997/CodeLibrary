#include "bits/stdc++.h"
#define ll long long int
#define all(x) x.begin(), x.end()
#define pb push_back
#define se second
#define fi first
using namespace std;
typedef pair<ll,ll> pll;

const ll N = 1e5+5;
const ll M = 18;

pair<pll,ll> L[N];
ll P[M][N],n,stp,cnt,sa[N];

void suffix_array(string s){
    for(ll i=0;i<n;i++) P[0][i]=s[i]-'a';
    sa[0]=0;
    for(stp=1,cnt=1;cnt<n;stp++,cnt<<=1){
        for(ll i=0;i<n;i++){
            L[i]={{P[stp-1][i],(i+cnt)<n?P[stp-1][i+cnt]:-1},i};
        }
        sort(L,L+n);
        for(ll i=0;i<n;i++){
            P[stp][L[i].se]=(i and L[i].fi==L[i-1].fi)?P[stp][L[i-1].se]:i;
        }
    }
    for(ll i=0;i<n;i++) sa[i]=L[i].se;
}

int lcp(int x,int y){
    int k,ret=0;
    if(x==y) return (n-x);
    for(k=stp-1;k>=0 and x<n and y<n;k--){
        if(P[k][x]==P[k][y]){
            x += (1<<k); y+= (1<<k);
            ret += (1<<k);
        }
    }
    return ret;
}

int main(){
    string s; cin>>s;
    n = s.length();
    suffix_array(s);
    return 0;
}
