#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<cstdio>
using namespace std;
typedef pair<int, int> P;

int n, m;
long long res;
int p[108000];
int a[108000];
int cnt[108000];
int deg[108000];
vector<int> edge[108000];
vector<P> edges;
bool cmp(const int &a, const int &b){
  if(deg[a] == deg[b])return a < b;
  return deg[a] < deg[b];
}

int main(){
  cin >> n >> m;
  for(int i = 0;i < n;i++)cin >> p[i];
  for(int i = 0;i < m;i++){
    int a, b;
    scanf("%d%d", &a, &b);
    a--,b--;
    deg[a]++;
    deg[b]++;
    edges.push_back(P(a, b));
  }
  for(int i = 0;i < m;i++){
    int a = edges[i].first;
    int b = edges[i].second;
    if(cmp(b, a))swap(a, b);
    edge[a].push_back(b);
  }
  sort(a, a + n, cmp);
  for(int i = 0;i < m;i++){
    int a = edges[i].first;
    int b = edges[i].second;
    if(cmp(b, a))swap(a, b);
    for(int j = 0;j < edge[a].size();j++){
      cnt[edge[a][j]]++;
    }
    for(int j = 0;j < edge[b].size();j++){
      if(cnt[edge[b][j]]){
	res += max(p[edge[b][j]], max(p[a], p[b]));
      }
    }
    for(int j = 0;j < edge[a].size();j++){
      cnt[edge[a][j]] = 0;
    }
  }
  printf("%lld\n", res);
  return 0;
}
