#include<bits/stdc++.h>
using namespace std;
int t[300001], n, m, x[100001], k = 0, first[300001], last[300001];
vector <int> a[300001];
long long st[900001];
void inline read (int &cc) {
  char c = getchar ();
  while (c < '0' || c > '9') {
    c = getchar ();
  }
  cc = 0;
  while (c >= '0' && c <= '9') {
    cc = cc * 10 + c - '0';
    c = getchar ();
  }
}
void dfs (int u, int p) {
  t[++ k] = u;
  for (auto v : a[u]) {
    if (v != p) {
      dfs (v, u);
    }
  }
  t[++ k] = u;
}
void build (int id, int l, int r) {
  if (l == r) {
    st[id] = x[t[l]];
    return;
  }
  int mid = (l + r) / 2;
  build (id * 2, l, mid);
  build (id * 2 + 1, mid + 1, r);
  st[id] = st[id * 2] + st[id * 2 + 1];
}
void update (int id, int l, int r, int pos, int val) {
  if (r < pos || l > pos) return;
  if (l == r) {
    st[id] = val;
    return;
  }
  int mid = (l + r) / 2;
  update (id * 2, l, mid, pos, val);
  update (id * 2 + 1, mid + 1, r, pos, val);
  st[id] = st[id * 2] + st[id * 2 + 1];
}
long long get (int id, int l, int r, int u, int v) {
  if (l > v || r < u) return 0LL;
  if (l >= u && r <= v) {
    return st[id];
  }
  int mid = (l + r) / 2;
  return get (id * 2, l, mid, u, v) + get (id * 2 + 1, mid + 1, r, u, v);
}
int main () {
  if (fopen ("test.inp", "r")) {
    freopen ("test.inp", "r", stdin);
  }
  else {
    freopen("SCOMP.inp", "r", stdin);
    freopen("SCOMP.out", "w", stdout);
  }
//  ios_base :: sync_with_stdio (0);
//  cin.tie (nullptr);
//  cout.tie (nullptr);
  read (n);
  read (m);
  for (int i = 1; i <= n; ++ i) {
    read (x[i]);
  }
  for (int i = 1; i < n; ++ i) {
    int u, v;
    read (u);
    read (v);
    a[u].push_back (v);
    a[v].push_back (u);
  }
  dfs (1, 1);
  for (int i = 1; i <= k; ++ i) {//cerr << t[i] << " ";
    if (first[t[i]] == 0) {
      first[t[i]] = i;
    }
    else {
      last[t[i]] = i;
    }
  }//cerr << "\n";
  build (1, 1, k);
  while (m --) {
    char c = getchar ();
    //cin >> c;
    if (c == 'U') {
      int u, val;
      read (u);
      read (val);
      update (1, 1, k, first[u], val);
      update (1, 1, k, last[u], val);
    }
    else {
      int u;
      read (u);
      cout << get (1, 1, k, first[u], last[u]) / 2LL << "\n";
    }
  }
}
