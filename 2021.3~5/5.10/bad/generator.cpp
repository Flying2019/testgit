#include <iostream>

class MT_gen {
  const unsigned A = 2567483615u, B = 2636928640u, C = 4022730752u, F = 1812433253u;
  unsigned MT[624], tot;
  unsigned keep(unsigned index) { return index >= 624 ? index - 624 : index; }

 public:
  MT_gen(unsigned seed) {
    MT[0] = seed;
    tot = 0;
    for (int i = 1; i < 624; ++i) MT[i] = F * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
  }
  void twist() {
    for (int i = 0; i < 624; ++i) {
      unsigned tmp = (MT[i] & 0x80000000) | (MT[keep(i + 1)] & 0x7fffffff);
      tmp = (tmp & 1) ? (tmp >> 1) ^ A : (tmp >> 1);
      MT[i] = MT[keep(i + 397)] ^ tmp;
    }
  }
  unsigned operator()() {
    if (tot == 0) twist();
    unsigned tmp = MT[tot];
    tmp ^= tmp >> 11;
    tmp ^= tmp << 7 & B;
    tmp ^= tmp << 15 & C;
    tmp ^= tmp >> 18;
    tot = keep(tot + 1);
    return tmp;
  }
};

char c[10000005];

int main() {
  int n;
  unsigned seed;
  std::cin >> n >> seed;
  MT_gen rnd(seed);
  for (int i = 1; i <= n / 2; ++i) c[i] = '(';
  for (int i = n / 2 + 1; i <= n; ++i) c[i] = ')';
  for (int i = n; i >= 1; --i) std::swap(c[i], c[rnd() % i + 1]);
  std::cout << c + 1 << std::endl;
  return 0;
}
