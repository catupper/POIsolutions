#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
#include<string>
using namespace std;
typedef pair<int, int> P;
typedef pair<P, int> T;

vector<T> edges[108000];

string ans[324000];

int n, m, p, k, w, ind;
int u[324000];

int r(int x){
  if(u[x] == x)return x;
  return u[x] = r(u[x]);
}

void unite(int x, int y){
  x = r(x), y = r(y);
  u[x] = y;
}

int main(){
  cin >> n >> m;
  for(int i = 0;i < m;i++){
    cin >> p >> k >> w;
    p--,k--;
    edges[w].push_back(T(P(p, k), i));
  }
  for(int i = 0;i < n;i++)u[i] = i;
  for(int i = 0;i < 108000;i++){
    for(int j = 0;j < edges[i].size();j++){
      p = edges[i][j].first.first;
      k = edges[i][j].first.second;
      ind = edges[i][j].second;
      if(r(p) != r(k))ans[ind] = "TAK";
      else ans[ind] = "NIE";
    }
    for(int j = 0;j < edges[i].size();j++){
      p = edges[i][j].first.first;
      k = edges[i][j].first.second;
      if(r(p) != r(k))unite(p, k);
    }
  }
  for(int i = 0;i < m;i++)cout << ans[i] << endl;
  return 0;
}
