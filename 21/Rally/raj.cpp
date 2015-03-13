#include <cstdio>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cctype>
#define fi first
#define se second
#define rep(i,n) for(int i = 0; i < n; ++i)
#define rrep(i,n) for(int i = 1; i <= n; ++i)
#define drep(i,n) for(int i = n-1; i >= 0; --i)
#define gep(i,g,j) for(int i = g.head[j]; i != -1; i = g.e[i].next)
#define each(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define rng(a) a.begin(),a.end()
#define maxs(x,y) x = max(x,y)
#define mins(x,y) x = min(x,y)
#define pb push_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcount
#define snuke srand((unsigned)clock()+(unsigned)time(NULL));
inline int in() { int x; scanf("%d",&x); return x;}
using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
typedef vector<int> vi;

const int MX = 500005, INF = 1000010000;
const ll LINF = 1000000000000000000ll;
const double eps = 1e-10;
const int di[] = {-1,0,1,0}, dj[] = {0,-1,0,1}; //^<v>

int n, m;
vi to[2][MX];
int d[2][MX];

int dfs(int k, int v) {
  if (d[k][v] != -1) return d[k][v];
  d[k][v] = 0;
  rep(i,sz(to[k][v])) {
    maxs(d[k][v],dfs(k,to[k][v][i])+1);
  }
  return d[k][v];
}

int h;
int ans, len;
inline bool on(int v) { return d[0][v]+d[1][v] >= len;}
bool f(int l) {
  len = l;
  vi a(h+1);
  rep(v,n) {
    if (!on(v)) continue;
    rep(i,sz(to[0][v])) {
      int u = to[0][v][i];
      if (!on(u)) continue;
      if (d[1][v]+d[0][u]+1 < l) continue;
      a[d[1][v]+1]++;
      a[d[1][u]]--;
    }
  }
  rep(i,h) a[i+1] += a[i];
  rep(v,n) {
    if (!on(v)) continue;
    int p = d[1][v];
    if (a[p]) a[p] = INF;
    else a[p] = v+1;
  }
  rep(i,h+1) {
    if (i <= l && i >= h-l && a[i] != INF) {
      ans = a[i];
      return true;
    }
  }
  return false;
}

int main(){
  scanf("%d%d",&n,&m);
  rep(i,m) {
    int a, b;
    scanf("%d%d",&a,&b);
    --a; --b;
    to[0][a].pb(b);
    to[1][b].pb(a);
  }
  rep(k,2)rep(i,n) d[k][i] = -1;
  rep(k,2)rep(i,n) dfs(k,i);
  h = 0;
  rep(i,n) maxs(h,d[0][i]+d[1][i]);
  int l = 0, r = h+1, c;
  while (l+1<r) {
    c = (l+r)>>1;
    if (f(c)) r = c; else l = c;
  }
  f(r);
  if (l == h) ans = 1;
  printf("%d %d\n",ans,l);
  return 0;
}





