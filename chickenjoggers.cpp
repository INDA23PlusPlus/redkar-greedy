#include "bits/stdc++.h" 
#include <ext/pb_ds/assoc_container.hpp>
         
using namespace std;
using namespace __gnu_pbds;
 
/* typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set; */
         
#define el "\n"
#define faster ios_base::sync_with_stdio(0); cin.tie(0);
#define sq(x) (x)*(x)
#define pb push_back
#define mp make_pair
#define F first
#define S second
         
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;
         
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define per(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define trav(a, x) for (auto &a : x)
         
struct chash { // large odd number for C
      const uint64_t C = ll(4e18 * acos(0)) | 71;
      ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
 
template<typename T> using fast_set = __gnu_pbds::gp_hash_table<T, null_type, chash>;
template<typename T, typename H> using fast_set_h = __gnu_pbds::gp_hash_table<T, null_type, H>;
template<typename T, typename U> using fast_map = __gnu_pbds::gp_hash_table<T, U, chash>;
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x);
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

vpii dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
vpii dirs2 = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

const int inf = 2e9;
const ll infLL = 1e18;

int n, s;
vector<vpii> graph;
vvi newGraph;
vi dp;
vector<bool> on;

void relevantize(int node, int par, int d) {
	if (d * 2 >= s) return;
	trav(child, graph[node]) {
		if (child.F != par) {
			newGraph[node].pb(child.F);
			relevantize(child.F, node, d+child.S);
		}
	}
}

int vertex_cover(int node) {
	if (dp[node] != -1) return dp[node];
	int sum = 0;
	if (on[node]) {
		trav(child, newGraph[node]) {
			sum += vertex_cover(child);
		}
	}
	else {
		int inCover = 1, notInCover = 0;
		trav(child, newGraph[node]) {
			if (!on[child]) notInCover++;
		}
		trav(child, newGraph[node]) {
			inCover += vertex_cover(child);
			trav(gchild, newGraph[child]) {
				notInCover += vertex_cover(gchild);	
			}
		}
		sum = min(inCover, notInCover);
	}
	dp[node] = sum;
	return sum;
}

void solve() {
	cin >> n >> s;
	graph.resize(n);
	newGraph.resize(n);
	on.resize(n);
	dp.assign(n, -1);
	rep(i, 0, n-1) {
		int u, v, d;
		cin >> u >> v >> d; u--, v--;
		graph[u].pb(mp(v, d));
		graph[v].pb(mp(u, d));
	}
	relevantize(0, 0, 0);
	int L; cin >> L;
	rep(i, 0, L) {
		int node; cin >> node;
		node--;
		on[node] = 1;
	}
	cout << vertex_cover(0);
}

int main() {
   	faster
    	int test = 1; // cin >> test;
    	REP(tc, 1, test) {
        	solve();
    	}
}


