/*
learning source - https://www.youtube.com/watch?v=1CxyVdA_654
to calculate median of stream of integers using two heaps 
O(n*log(n))
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

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t=1;
    while(t--){
        int n; cin>>n;
        int a[n];
        for(int i=0;i<n;i++) cin >> a[i];

        priority_queue<int> lower_half;
        priority_queue<int,vi,greater<int>> upper_half;

        if(n <= 2){
            if(n==1) cout << a[0] << endl;
            else cout << a[0] << " " << a[0] << endl;
        }
        else {
            cout << a[0] << " " << a[0] << " ";

            if(a[0]<a[1]){
                lower_half.push(a[0]);
                upper_half.push(a[1]);
            } else {
                lower_half.push(a[1]);
                upper_half.push(a[0]);
            }

            for(int i=2;i<n;i++){
                // inserting
                if(a[i] <= lower_half.top()){
                    lower_half.push(a[i]);
                } else upper_half.push(a[i]);

                // re-balancing
                if(abs((int)lower_half.size() - (int)upper_half.size()) >= 2){
                    if(lower_half.size() > upper_half.size()){
                        upper_half.push(lower_half.top());
                        lower_half.pop();
                    } else{
                        lower_half.push(upper_half.top());
                        upper_half.pop();
                    }
                }

                // extracting median
                if(lower_half.size() < upper_half.size()) cout << upper_half.top() << " ";
                else cout <<  lower_half.top() << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
