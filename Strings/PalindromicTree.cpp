/*
SPOJ - NUMOFPAL
modify as needed
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
typedef vector<vector<int>> matrix;

const int inf = 1e18;
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

string s;
int nodes=0,suff,n;

struct node{
    int next[26],len,sufflink,height;
}tree[N];

void initTree(){
    nodes=2; suff=2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len =  0; tree[2].sufflink = 1;
}

bool addLetter(int pos){
    int cur = suff, curlen=0;
    int letter = s[pos]-'a';

    while(true){
        curlen = tree[cur].len;
        if((pos-1-curlen)>=0 and s[pos-1-curlen]==s[pos]) break;
        cur = tree[cur].sufflink;
    }
    if(tree[cur].next[letter]){
        suff = tree[cur].next[letter];
        return false;
    }

    nodes++;
    suff = nodes;
    tree[nodes].len = tree[cur].len + 2;
    tree[cur].next[letter] = nodes;

    if(tree[nodes].len == 1){
        tree[nodes].sufflink = 2;
        tree[nodes].height = 1;
        return true;
    }

    while(true){
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if((pos-1-curlen)>=0 and s[pos-1-curlen]==s[pos]){
            tree[nodes].sufflink = tree[cur].next[letter];
            break;
        }
    }
    tree[nodes].height = tree[tree[nodes].sufflink].height + 1;
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    clock_t start = clock();

    cin >> s;
    n = s.length();

    initTree();
    int ans=0;
    for(int i=0;i<n;i++){
        addLetter(i);
        ans += tree[suff].height;
    }
    cout << ans << endl;

    clock_t end = clock();
    cerr << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}
