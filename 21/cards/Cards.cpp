#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
#define size(x) (x?x->size:0)

struct Node{
  Node *l, *r, *p;
  int size;
 
  Node(){
    l = r = p = 0;
    size = 1;
  }
  
  int state(){
    if(p == 0)return 0;
    if(p->l == this)return 1;
    if(p->r == this)return -1;
    return 0;
  }

  void update(){
    size = 1 + size(l) + size(r);
  }

  void rotate(){
    Node *pp = p, *c;
    if(pp->l == this){
      c = r;
      r = pp;
      pp->l = c;
    }
    else if(pp->r == this){
      c = l;
      l = pp;
      pp->r = c;
    }
    p = pp->p;
    pp->p = this;
    if(c)c->p = pp;
    if(p && p->l == pp)p->l = this;
    if(p && p->r == pp)p->r = this;
    pp->update();
    update();
  }

  void zigzag(){
    while(state()){
      int s = state() * p->state();
      if(s == 1)p->rotate();
      if(s == -1)rotate();
      rotate();
    }
  }

  void splay(){
    for(Node *x = this;x;x = x->p){
      x->zigzag();
    }
    for(Node *x = this;x->p;x = x->p){
      x->p->l = x;
      x->p->update();
    }
    zigzag();
  }

  void link(Node *a){
    splay();
    a->splay();
    p = a;
  }
  void cut(){
    splay();
    if(r)r->p = 0;
    r = 0;
  }

};

Node node[432000];
int place[432000];
int y[432000];
int x[432000];
int depth(Node *x){
  x->splay();
  return size(x->r) + 1;
}

void connect(int p){
  int a = place[p - 1], b = place[p];
  if(y[a] <= x[b]){
    node[b * 2].link(&node[a * 2 + 1]);
  }
  else if(x[a] <= x[b]){
    node[b * 2].link(&node[a * 2]);
  }
  if(y[a] <= y[b]){
    node[b * 2 + 1].link(&node[a * 2 + 1]);
  }
  else if(x[a] <= y[b]){
    node[b * 2 + 1].link(&node[a * 2]);
  }
}

void disconnect(int p){
  p = place[p];
  node[p * 2].cut();
  node[p * 2 + 1].cut();
}

int main(){
  int n, m, a, b;
  scanf("%d", &n);
  for(int i = 0;i < n;i++){
    scanf("%d%d", &x[i], &y[i]);
    if(x[i] > y[i])swap(x[i], y[i]);
    place[i] = i;
    if(i){
      connect(i);
    }
  }
  scanf("%d", &m);
  while(m--){
    scanf("%d%d", &a, &b);a--,b--;
    if(a != b){
      if(a)disconnect(a);
      if(a + 1 < n)disconnect(a + 1);
      if(b)disconnect(b);
      if(b + 1 < n)disconnect(b + 1);   
      swap(place[a], place[b]);
      if(a)connect(a);
      if(a + 1 < n)connect(a + 1);
      if(b != a + 1 && b)connect(b);
      if(b + 1 != a && b + 1 < n)connect(b + 1);    
    }
    if(depth(&node[place[n - 1] * 2]) == n || depth(&node[place[n - 1] * 2 + 1]) == n)puts("TAK");
    else puts("NIE");
  }
  return 0;
}
