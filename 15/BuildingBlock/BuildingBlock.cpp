#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

multiset<int> low, high;
multiset<int>::iterator it;

long long int n, k, h[108000], hsum, lsum;
long long int vmed, pos, val = 1LL << 60;
int main(){
  cin >> n >> k;
  long long sum = 0;
  
  for(int i = 0;i < n;i++){
    cin >> h[i];
    if(h[i] < *high.begin()){
      low.insert(h[i]);
      lsum += h[i];
    }    
    else{
      high.insert(h[i]);
      hsum += h[i];
    }
    if(low.size() + high.size() < k)continue;

    if(i - k >= 0){
      it = low.find(h[i - k]);
      if(it != low.end()){
	low.erase(it);
	lsum -= h[i - k];
      }
      else{
	it = high.find(h[i - k]);
	high.erase(it);
	hsum -= h[i - k];
      }
    }

    while((int)low.size() > k / 2){
      it = low.end();
      --it;
      hsum += *it;
      lsum -= *it;
      high.insert(*it);
      low.erase(it);
    }
    while((int)low.size() < k / 2){
      lsum += *high.begin();
      hsum -= *high.begin();
      low.insert(*high.begin());
      high.erase(high.begin());
    }
    long long med = *high.begin();
    long long tmp = hsum - med * high.size() + med * low.size() - lsum;
   
    if(tmp < val){
      val = tmp;
      pos = i;
      vmed = med;
    }

  }
  cout << val << endl;
  for(int i = 0;i < n;i++){
    if(pos - k < i && i <= pos){
      cout << vmed << endl;
    }
    else{
      cout << h[i] << endl;
    }
  }
  return 0;
}
