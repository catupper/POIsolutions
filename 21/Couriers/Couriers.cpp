#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define catupper upper_bound
#define catlower lower_bound

vector<int> appear[540000];
vector<int> res;
int n, m, a, b;
int mode[1 << 20], p[540000], tcnt[540000];
int cnt(int x, int l, int r){
  return catupper(appear[x].begin(), appear[x].end(), r) - catlower(appear[x].begin(), appear[x].end(), l);
}
void solve(int l, int r, int bottom = 0 ,int top = (1 << 19), int pos = 1){
  if(r <= bottom || top <= l)return;
  if(l <= bottom && top <= r){
    res.push_back(mode[pos]);
    return;
  }
  int mid = (bottom + top) / 2;
  solve(l, r, bottom, mid, pos * 2);
  solve(l, r, mid, top, pos * 2 + 1);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i = 0;i < n;i++){
    scanf("%d", &p[i]);
    mode[i + (1 << 19)] = p[i];
    appear[p[i]].push_back(i);
  }
  int range = 1;
  for(int i = 1 << 18;i > 0;i >>= 1){
    range <<= 1;
    for(int j = 0;j < (1 << 19);j += range){
      for(int k = j;k < j + range;k++){
	if(k >= n)break;
	tcnt[p[k]]++;
	if(tcnt[mode[i + j / range]] < tcnt[p[k]])mode[i + j / range] = p[k];
      }
      for(int k = j;k < j + range;k++){
	if(k >= n)break;
	tcnt[p[k]]--;
      }
    }
  }

  for(int i = 0;i < m;i++){
    res.clear();
    scanf("%d%d", &a, &b);
    a--,b--;
    solve(a, b + 1);
    int lim = (b - a + 1) / 2;
    int m = 0, c = 0;
    for(int i = 0;i < res.size();i++){
      int t = catlower(appear[res[i]].begin(), appear[res[i]].end(), a) - appear[res[i]].begin();
      if(t + lim >= appear[res[i]].size() || appear[res[i]][t + lim] > b)continue;
      m = res[i];break;
    }  
    printf("%d\n", m);
  }
  return 0;
}
