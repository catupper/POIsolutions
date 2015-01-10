#include<iostream>
#include<algorithm>

using namespace std;
int n;
char c, a[1050000];
int up[1050000], down[1050000], last[2100000];
int num[1050000];
int res;
int main(){
	cin >> n;
		
	for(int i = 1;i <= n;i++){
		cin >> c;
		a[i] = c;
		if(c == 'j')num[i]--;
		else num[i]++;
		num[i] += num[i - 1];
	}
	
	fill(last, last + 2100000, n + 1);
	
	for(int i = n;i >= 0;i--){
		int tmp = num[i] + 1050000;
		up[i] = min(last[tmp + 1], last[tmp]);
		down[i] = last[tmp - 1];
		last[tmp] = i;
	}
	
	int s = 1;
	while(s <= n){
		while(s <= n && a[s] == 'j')s++;
		if(s > n)break;
		int t = s;
		while(up[t] < down[s - 1])t = up[t];
		res = max(res, t - s + 1);
		s = t + 1;
	}
	cout << res << endl;
	return 0;
}