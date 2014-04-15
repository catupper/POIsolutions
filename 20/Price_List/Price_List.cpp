#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#define INF (1LL << 40)
typedef long long Int;
vector<Int> edge[105000], edgea[105000], edgeb[105000], tmpvec;
Int dista[105000], distb[105000];
bool ban[105000];
int main(){
  Int n, m, k, a, b, x, y;
  scanf("%lld%lld%lld%lld%lld", &n, &m, &k, &a, &b);
  k--;
  for(Int i = 0;i < m;i++){
    scanf("%lld%lld", &x, &y);
    x--,y--;
    edge[x].push_back(y);
    edgea[x].push_back(y);
    edge[y].push_back(x);
    edgea[y].push_back(x);
  }
  fill(dista, dista + n, INF);
  vector<Int> stk;
  stk.push_back(k);
  dista[k] = 0;
  for(Int i = 0;i < n;i++){
    Int from = stk[i];
    for(Int j = 0;j < edge[from].size();j++){
      Int to = edge[from][j];
      if(dista[to] != INF)continue;
      dista[to] = dista[from] + 1;
      stk.push_back(to);
    }
  }

  fill(distb, distb + n, INF);
  distb[k] = 0;
  stk.clear();
  stk.push_back(k);
  for(Int i = 0;i < stk.size();i++){
    Int from = stk[i];
    ban[from] = true;
    for(Int j = 0;j < edge[from].size();j++){
      ban[edge[from][j]] = true;
    }
    for(Int j = 0;j < edge[from].size();j++){
      tmpvec.clear();
      Int to = edge[from][j];
      for(Int k = 0;k < edgea[to].size();k++){
	Int toto = edgea[to][k];
	tmpvec.push_back(toto);
	if(ban[toto])continue;
	tmpvec.pop_back();
	if(distb[toto] != INF)continue;
	distb[toto] = distb[from] + 1;
	stk.push_back(toto);
      }
      edgea[to] = tmpvec;
    }
    for(Int j = 0;j < edge[from].size();j++){
      ban[edge[from][j]] = false;
    }
    ban[from] = false;
  }

  for(Int i = 0;i < n;i++){
    if(a * 2 <= b){
      printf("%lld\n", dista[i] * a);
    }
    else{
      if(dista[i] % 2 == 0){
	printf("%lld\n", b * dista[i] / 2);
      }
      else{
	printf("%lld\n", min(b * (dista[i] / 2) + a, b * distb[i]));
      }
    }
  }
  return 0;
}
