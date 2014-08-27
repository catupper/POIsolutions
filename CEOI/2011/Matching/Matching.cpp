#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
using namespace std;
typedef pair<int, int> P;

int n, m;
int p[1080000], h[1080000];
int s[1080000];
int back[1080000], next[1080000], prev[1080000];
vector<int> ans;

int leftp[1080000], rightp[1080000];


int main(){
  cin >> n >> m;
  for(int i = 1;i <= n;i++){
    cin >> s[i];
    p[s[i]] = i;
    leftp[i] = i - 1;
    rightp[i] = i + 1;
  }

  for(int i = n;i >= 1;i--){
    if(leftp[p[i]] != 0){
      prev[i] = s[ leftp[p[i]] ];
      prev[i] = i - prev[i];
      rightp[ leftp[p[i]] ] = rightp[p[i]];
    }
    if(rightp[p[i]] != n + 1){
      next[i] = s[ rightp[p[i]] ];
      next[i] = i - next[i];
      leftp[ rightp[p[i]] ] = leftp[p[i]];
    }
  }

  back[1] = 0;
  int pp = 0;
  for(int i = 2;i <= n;i++){
    while(pp && !(p[i - prev[ pp+1 ]] <= p[i] && p[i] <= p[i - next[ pp+1 ]]) ){
      pp = back[pp];
    }
    if(p[i - prev[ pp+1 ]] <= p[i] && p[i] <= p[i - next[ pp+1 ]] ){
      pp++;
    }
    back[i] = pp;
  }

  pp = 0;

  for(int i = 1;i <= m;i++){
    cin >> h[i];
    while(pp && !(h[i - prev[pp + 1]] <= h[i] && h[i] <= h[i - next[pp + 1]])){
      pp = back[pp];
    }
    if(h[i - prev[pp+1]] <= h[i] && h[i] <= h[i - next[pp+1]]){
      pp++;
    }
    if(pp == n){
      ans.push_back(i - n + 1);
      pp = back[pp];
    }
  }
  cout << ans.size() << endl;
  for(int i = 0;i < ans.size();i++){
    if(i)cout << " ";
    cout << ans[i];
  }cout << endl;
  return 0;
}
