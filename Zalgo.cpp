#include "bits/stdc++.h"
#define ll long long int
#define all(x) x.begin(), x.end()
#define pb push_back
#define se second
#define fi first
using namespace std;
typedef pair<ll,ll> pll;

const int N = 1e5+5;
int Z[N];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin>>s;
    int n = s.length();
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(i>r){
            l=r=i;
            while(r<n and s[r-l] == s[r]){
                r ++;
            }
            Z[i] = r-l;
            r--;
        }
        else{
            int k = i-l;
            if(Z[k] < r-i+1){
                Z[i] = Z[k];
            }
            else{
                l=i;
                while(r<n and s[r-l] == s[r]){
                    r++;
                }
                Z[i] = r-l;
                r--;
            }
        }
    }
    for(int i=1;i<n;i++) cout<<Z[i]<<" ";
    return 0;
}
