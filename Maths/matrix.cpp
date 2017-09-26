const ll N=205;

struct matrix{
    ll B[N][N],n;
    matrix(){
        n=N; memset(B,0,sizeof B);
    }
    matrix(int _n){
        n=_n; memset(B,0,sizeof B);
    }
    void iden(){
        for(int i=0;i<n;i++) B[i][i]=1;
    }
    void operator += (matrix M){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                B[i][j]+=M.B[i][j];
            }
        }
    }
    void operator -= (matrix M){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                B[i][j]-=M.B[i][j];
            }
        }
    }
    void operator *= (ld b){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                B[i][j]=b*B[i][j];
            }
        }
    }
    matrix operator - (matrix M){
        matrix ret =(*this);
        ret -= M;
        return ret;
    }
    matrix operator + (matrix M){
        matrix ret = (*this);
        ret += M;
        return ret;
    }
    matrix operator * (matrix M){
        matrix ret=matrix(n);
        memset(ret.B,0,sizeof ret.B);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    ret.B[i][j]+=B[i][k]*M.B[k][j];
                }
            }
        }
        return ret;
    }
    matrix operator *= (matrix M){
        *this = ((*this)*M);
    }
    matrix operator * (int b){
        matrix ret=(*this);
        ret *= b;
        return ret;
    }
    matrix power(ll _n){
        matrix I=matrix(n), A=(*this); I.iden();
        for(;_n!=0;A*=A,_n>>=1){
            if(_n & 1) I *= A;
        }
        return I;
    }
    bool operator == (matrix M){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(B[i][j]!=M.B[i][j]){
                    return 0;
                }
            }
        }
        return 1;
    }
};