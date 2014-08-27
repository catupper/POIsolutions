#include<iostream>
#include<algorithm>

using namespace std;
double dp[600][600*6];
int main(){
  int t, n, k;
  cin >> t;
  dp[0][0] = 1;
    
  for(int i = 1;i < 600;i++){
    for(int j = 0;j < 600 * 6;j++){
      for(int k = 1;k <= 6;k++){
	if(j - k >= 0)
	  dp[i][j] += dp[i - 1][j - k]/6;
      }
    }
  }

  for(int i = 0;i < t;i++){
    cin >> n >> k;
    if(n > 600 || k > n * 6){
      cout << 0 << endl;
      continue;
    }
    cout << (int)(dp[n][k] * 100) << endl;
  }
  return 0;
}
