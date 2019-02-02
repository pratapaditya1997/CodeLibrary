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

const int N = 1e6+6;
int fact[N],ifact[N];

void pre(){
	fact[0]=ifact[0]=1;
	for(int i=1;i<N;i++) fact[i]=mul(i,fact[i-1]);
	ifact[N-1] = inv(fact[N-1]);
	for(int i=N-2;i>=1;i--) ifact[i]=mul(ifact[i+1],i+1);
}
