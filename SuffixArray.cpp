/*
suffix array construction - O(n*log(n)*log(n)) ; use radix sort for O(n*log(n)) complexity
LCP construction - O(n) using kasai algorithm
*/

const int N = 1e5+5;
const int M = 24;

int P[M][N],sa[N],lcp[N],sufinv[N],n;

struct entry{
    int rank[2],pos;
} L[N];

bool comp(entry a,entry b){
    if(a.rank[0] == b.rank[0]){
        return (a.rank[1] < b.rank[1]);
    } else return (a.rank[0] < b.rank[0]);
}

void suffix_array(string s){
    memset(P,0,sizeof P);
    for(int i=0;i<n;i++) P[0][i]=s[i]-'!';
    for(int step=1, cnt=1; cnt<n; step++, cnt <<= 1){
        for(int i=0;i<n;i++){
            L[i].rank[0] = P[step-1][i];
            L[i].rank[1] = ((i+cnt)<n) ? P[step-1][i+cnt] : -1;
            L[i].pos = i;
        }
        sort(L,L+n,comp);
        for(int i=0;i<n;i++){
            if(i and L[i].rank[0] == L[i-1].rank[0] and L[i].rank[1] == L[i-1].rank[1]){
                P[step][L[i].pos] = P[step][L[i-1].pos];
            } else P[step][L[i].pos] = i;
        }
    }
    for(int i=0;i<n;i++) sa[i] = L[i].pos;
}

void kasai(string s){
    int k=0;
    for(int i=0;i<n;i++) sufinv[sa[i]]=i;
    for(int i=0;i<n;i++){
        if(sufinv[i] == n-1) {
            k=0; continue;
        }
        int j = sa[sufinv[i]+1];
        while(i+k<n and j+k<n and s[i+k]==s[j+k]) k++;
        lcp[sufinv[i]] = k;
        if(k) k--;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    string s; cin >> s;
    n = s.length();

    memset(sa,0,sizeof sa);
    memset(lcp,0,sizeof lcp);
    suffix_array(s);
    kasai(s);

//    for(int i=0;i<n;i++) cout << sa[i] << " ";
//    cout << endl;
//    for(int i=0;i<n;i++) cout << lcp[i] << " ";
//    cout << endl;

    return 0;
}
