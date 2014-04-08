#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> color[1080000];
vector<int> ans;
int x[1080000];
int y[1080000];
int down[1080000];
int up[1080000];
int c[1080000];
int ok[1080000];
int m, l, n, k;

bool update(int l){
  while(up[0] < color[x[0]].size() && color[x[0]][up[0]] <= l)up[0]++;
  if(up[0] == color[x[0]].size() || color[x[0]][up[0]] < l)return false;
  for(int i = 1;i < m;i++){
    while(up[i] < color[x[i]].size() && color[x[i]][up[i]] < color[x[i - 1]][up[i - 1]])up[i]++;
    if(up[i] == color[x[i]].size() || color[x[i]][up[i]] < color[x[i - 1]][up[i - 1]])return false;
  }
  return true;
}

bool downdate(int r){
  while(down[0] + 1 < color[y[0]].size() && color[y[0]][down[0] + 1] < r)down[0]++;
  if(color[y[0]][down[0]] >= r)return false;
  for(int i = 1;i < l;i++){
    while(down[i] + 1 < color[y[i]].size() && color[y[i]][down[i] + 1] < color[y[i - 1]][down[i - 1]])down[i]++;
    if(color[y[i]][down[i]] >= color[y[i - 1]][down[i - 1]])return false;
  }
  return true;
}

int main(){
scanf("%d%d", &n, &k);
  for(int i = 0;i < n;i++){
  	scanf("%d", &c[i]);
    color[c[i]].push_back(i);
  }
  scanf("%d%d", &m, &l);
  for(int i = 0;i < m;i++){
  	scanf("%d", &x[i]);
    up[i] = 0;
  }
  for(int i = 0;i < l;i++){
	scanf("%d", &y[i]);
    down[i] = 0;
    if(color[y[i]].size() == 0){
	  puts("0");
      return 0;
    }               
  }
  int ledge = 0;
  for(int i = 0;i < n;i++){
    if(ledge >= color[c[i]].back())continue;
    ledge = color[c[i]].back();
    bool u = update(i);
    bool d = downdate(ledge);
    if(u && d){
      if(color[x[m - 1]][up[m - 1]] <= color[y[l - 1]][down[l - 1]]){
	ok[color[x[m - 1]][up[m - 1]]]++;
	ok[color[y[l - 1]][down[l - 1]]+1]--;
      }
    }
    if(!u)break;
  }
  for(int i = 1;i < n-1;i++){
    ok[i] += ok[i - 1];
    if(ok[i] && c[i] == y[l - 1])ans.push_back(i);
  }
  printf("%d\n", ans.size());
  for(int i = 0;i < ans.size();i++){
    if(i)printf(" ");
	printf("%d", ans[i] + 1);
  }
  printf("\n");
  return 0;
}
