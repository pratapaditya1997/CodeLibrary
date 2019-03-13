vi prefix_function(string s){
    int n = (int)s.length();
    vi pi(n);
    for(int i=1;i<n;i++){
        int j = pi[i-1];
        while(j>0 and s[i]!=s[j]) j = pi[j-1];
        if(s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

vi kmp(string pattern,string text){
    string str = pattern + "#" + text;
    int n = pattern.length(), m = str.length();
    vi pi = prefix_function(str);
    vi ret;
    for(int i=n+1;i<m;i++) if(pi[i] == n) ret.pb(i-2*n);
    return ret;
}
