/*
for question : https://codeforces.com/contest/1117/problem/D
solving linear recurrence blog: http://fusharblog.com/solving-linear-recurrence-for-programming-contest/
*/

#include "bits/stdc++.h"

using namespace std;

#define int long long int

typedef vector<int> vi;
typedef vector<vector<int>> matrix;

int n,m;

vi mul_vec(vi f,matrix mat){
    vi res(m,0);
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            res[i] = add(res[i],mul(mat[i][j],f[j]));
        }
    }
    return res;
}

matrix mul_mat(matrix a, matrix b){
    matrix c(m,vi (m,0));
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<m;k++){
                c[i][j] = add(c[i][j],mul(a[i][k],b[k][j]));
            }
        }
    }
    return c;
}

matrix power_mat(matrix mat,int expo){
    if(expo == 1) return mat;
    if(expo&1) return mul_mat(mat,power_mat(mat,expo-1));
    matrix x = power_mat(mat,expo/2);
    return mul_mat(x,x);
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin>>n>>m;

    if(m>n){
        cout << 1 << endl;
        return 0;
    }
    
    // construct initial value 'f' vector
    vi f(m,1);
    f[m-1]++;
    
    // constructing transformation matrix T[m][m] , F_i+1 = T^i * f
    matrix T(m,vi (m,0));
    for(int i=0;i<m-1;i++){
        T[i][i+1]=1;
    }
    T[m-1][0]=T[m-1][m-1]=1;

    f = mul_vec(f,power_mat(T,n-1));

    cout << f[0] << endl;

    return 0;
}
