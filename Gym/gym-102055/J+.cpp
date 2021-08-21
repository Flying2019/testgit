#include <bits/stdc++.h>

using namespace std;

const int md0 = (int) (1e9 + 7);
const int md1 = (int) (1e9 + 9);

inline int inv(int a, int md) {
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  if (u < 0) {
    u += md;
  }
  return u;
}

struct hashv {
  int h0, h1;

  hashv(int h0 = 0, int h1 = 0): h0(h0), h1(h1) {
  }

  hashv operator * (const hashv &x) const {
    return hashv((long long) h0 * x.h0 % md0, (long long) h1 * x.h1 % md1);
  }

  hashv operator + (const hashv &x) const {
    return hashv((h0 + x.h0) % md0, (h1 + x.h1) % md1);
  }

  hashv operator - (const hashv &x) const {
    return hashv((h0 + md0 - x.h0) % md0, (h1 + md1 - x.h1) % md1);
  }

  inline long long get() {
    return (long long) h0 * md1 + h1;
  }
};

int main() {
#ifdef wxh010910
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; ++qq) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    vector<bool> ban(n);
    while (m--) {
      int x;
      cin >> x;
      --x;
      ban[x] = true;
    }
    vector<hashv> p(n * 2);
    vector<hashv> inv_p(n * 2);
    p[0] = inv_p[0] = hashv(1, 1);
    hashv base(2333, 2333);
    hashv inv_base(inv(2333, md0), inv(2333, md1));
    for (int i = 1; i < n * 2; ++i) {
      p[i] = p[i - 1] * base;
      inv_p[i] = inv_p[i - 1] * inv_base;
    }
    vector<hashv> pref(n * 2 + 1);
    auto query = [&](int l, int r) {
      return ((pref[r] - pref[l]) * inv_p[l]).get();
    };
    vector<int> b(n * 2);
    int l0 = n, r0 = n, l1 = n, r1 = n;
    for (int i = 0; i < n; ++i) {
      b[r1] = a[i];
      pref[r1 + 1] = pref[r1] + p[r1] * a[i];
      ++r1;
      --l0;
      b[l0] = a[i];
      pref[l0] = pref[l0 + 1] - p[l0] * a[i];
      if (!ban[i]) {
        int l = 0, r = r0 - l0;
        while (l < r) {
          int mid = (l + r + 1) >> 1;
          if (query(l0, l0 + mid) == query(l1, l1 + mid)) {
            l = mid;
          } else {
            r = mid - 1;
          }
        }
        if (l == r0 - l0 || b[l0 + l] < b[l1 + l]) {
          l1 = l0;
          r1 = r0;
        } else {
          l0 = l1;
          r0 = r1;
        }
      }
    }
    int ans = 0;
    for(int i=l1;i<r1;i++) cout<<b[i]<<" ";cout<<"\n";
    // for (int i = r1 - 1; i >= l1; --i) {
    //   ans = (37ll * ans + b[i]) % 20181125;
    // }
    // cout << "Case " << qq << ": " << ans << "\n";
  }
  return 0;
}