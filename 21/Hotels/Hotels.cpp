#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

typedef long long Int;

vector<int> edge[5010];
int depcnt[5010], n, a, b;
Int res, dp[2][5010];

void dfs(int x, int last, int d){
	for(int i = 0;i < edge[x].size();i++){
		int to = edge[x][i];
		if(to == last)continue;
		dfs(to, x, d + 1);
	}
	depcnt[d]++;
}

void cnt(int x){
	memset(dp, 0, sizeof(dp));
	for(int i = 0;i < edge[x].size();i++){
		memset(depcnt, 0, sizeof(depcnt));
		dfs(edge[x][i], x, 0);
		for(int i = 0;depcnt[i];i++){
			res += dp[1][i] * depcnt[i];
			dp[1][i] += dp[0][i] * depcnt[i];
			dp[0][i] += depcnt[i];
		}
	}
}

int main(){
  cin >> n;
  for(int i = 1;i < n;i++){
  	cin >> a >> b;
	edge[a].push_back(b);
	edge[b].push_back(a);
  }
  for(int i = 1;i <= n;i++)cnt(i);
  cout << res << endl;
  return 0;
}