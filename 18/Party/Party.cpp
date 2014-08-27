#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

int n, m, a, b;
bool exist[10000000];
bool reject[32400];
int cnt;
int main(){
  scanf("%d%d", &n, &m);
  for(int i = 0;i < m;i++){
    scanf("%d%d", &a, &b);
    exist[a * 3001 + b] = true;
    exist[b * 3001 + a] = true;
  }

  for(int i = 1;i <= n;i++){
    if(reject[i])continue;
    for(int j = i + 1;j <= n;j++){
      if(!reject[i] && !reject[j] && !exist[i * 3001 + j]){
	reject[i] = reject[j] = true;
	cnt++;
	if(cnt == n/3)goto done;
	break;
      }
    }
  }
 
 done:
  int pp = 0;
  for(int i = 1;i <= n;i++){
    if(pp == n/3)break;
    if(reject[i])continue;
    if(pp)cout << " ";
    cout << i;
    cnt--;
    pp++;
  }cout << endl;
  return 0;

}
