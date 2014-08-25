#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
  int n;
  vector<int> length;
  int cnt = 50;
  while(scanf("%d", &n), n){
    if(cnt-- == 0)break;
    if(n <= 1000000000)
      length.push_back(n);
  }
  
  sort(length.begin(), length.end());
  
  for(int i = 2;i < length.size();i++){
    int a = length[i - 2];
    int b = length[i - 1];
    int c = length[i];
    if(a + b > c){
      printf("%d %d %d\n", a, b, c);
      return 0;
    }
  }
  puts("NIE");
  return 0;  
}
