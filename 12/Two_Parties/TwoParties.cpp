#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool edge[216][216];
int n, x;
bool active[216];
int deg[216];
vector<int> ans;

void solve(){
  int v = -1;
  for(int i = 1;i <= n;i++){
    if(active[i] && deg[i] % 2 == 1){
      v = i;
    }
  }
  if(v == -1)return;
  vector<int> neib;
  for(int i = 1;i <= n;i++){
    if(edge[v][i]){
      neib.push_back(i);
      deg[i] ^= 1;
      deg[v] ^= 1;
      edge[v][i] = edge[i][v] = false;
    }
  }
  for(int i = 0;i < neib.size();i++){
    for(int j = i + 1;j < neib.size();j++){
      int a = neib[i], b = neib[j];
      deg[a] ^= 1;
      deg[b] ^= 1;
      edge[a][b] = edge[b][a] = !edge[a][b];
    }
  }
  active[v] = false;
  solve();
  int cnt = 0;
  for(int i = 0;i < neib.size();i++){
    for(int j = 0;j < ans.size();j++){
      if(neib[i] == ans[j])cnt++;
    }
  }
  if(cnt % 2 == 0)ans.push_back(v);
}

int main(){
  cin >> n;
  for(int i = 1;i <= n;i++){
    active[i] = true;
    cin >> deg[i];
    for(int  j = 0;j < deg[i];j++){
      cin >> x;
      edge[i][x] = edge[x][i] = true;
    }
    deg[i] %= 2;
  }

  solve();

  sort(ans.begin(), ans.end());
  cout << ans.size() << endl;
  for(int i = 0;i < ans.size();i++){
    if(i)cout << " ";
    cout << ans[i];
  }cout << endl;
  return 0;
}
