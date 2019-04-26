const int N = 3e6+5;
int trie[N][2], cnt[N],sz=0;

void update(int num,int dx) { // num to be inserted and dx is the increment to be made in the count 
    int node = 0;
    for(int i=30;i>=0;i--) {
        int bit = (num >> i) & 1;
        if(!trie[node][bit]){
            trie[node][bit] += ++sz;
        }
        node = trie[node][bit];
        cnt[node] += dx;
    }
}

int max_xor_query(int num) {
    int ret = 0, node = 0;
    for(int i=30;i>=0;i--) {
        int bit = (num >> i) & 1;
        if(cnt[trie[node][bit^1]]) {
            ret |= (1<<i);
            node = trie[node][bit^1];
        } else node = trie[node][bit];
    }
    return ret;
}
