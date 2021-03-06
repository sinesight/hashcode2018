#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;

long long rdtsc() {
  long long tmp;
  asm("rdtsc" : "=A"(tmp));
  return tmp;
}

inline int myrand() {
#ifdef _WIN32
  return abs((rand() << 15) ^ rand());
#else
  return rand();
#endif
}

inline int rnd(int x) {
  return myrand() % x;
}

#ifdef LOCAL
#define LLD "%lld"
#else
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#endif

#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stdout)
#else
#define eprintf(...) ;
#endif

#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define TASK "text"

void precalc() {
}

struct Pnt {
  int x, y;

  Pnt(): x(), y() {}
  Pnt(int x, int y): x(x), y(y) {}

  int dist(const Pnt & p) const {
    return abs(x - p.x) + abs(y - p.y);
  }
};

struct Ride {
  Pnt s, f;
  int ts, tf;
  int num;

  void read() {
    scanf("%d%d%d%d%d%d", &s.x, &s.y, &f.x, &f.y, &ts, &tf);
  }

  bool operator <(const Ride & r) const {
    return ts < r.ts;
  }
};

const int maxn = 10010;
const int maxx = 10010;
const int maxf = 1010;

int r, c, f, n, b, t;
Ride rides[maxn];

bool read() {
  if (scanf("%d%d%d%d%d%d", &r, &c, &f, &n, &b, &t) < 6) {
    return false;
  }
  for (int i = 0; i < n; ++i) {
    rides[i].read();
    rides[i].num = i;
  }
  return true;
}

vector<int> ans[maxf];
Pnt pos[maxf];
int tfree[maxf];
bool used[maxn];

void solve() {
  for (int i = 0; i < f; ++i) {
    ans[i].clear();
    pos[i] = Pnt(0, 0);
    tfree[i] = 0;
  }

  bool flag = true;
  while (flag) {
  	flag = false;
	for (int i = 0; i < f; i++) {
	  long long dist = 1e9;
	  int opt = -1;
	  for (int j = 0; j < n; j++) {
        if (!used[j]) {
          int tm = max(tfree[i] + pos[i].dist(rides[j].s), rides[j].ts) + rides[j].s.dist(rides[j].f);
          if (tm > rides[j].tf) continue;
          if (pos[i].dist(rides[j].s) < dist) {
          	dist = pos[i].dist(rides[j].s);
          	opt = j;
          }
        }
	  }
	  if (opt != -1) {
	  	flag = true;
	    ans[i].push_back(opt);
	    used[opt] = true;
	    tfree[i] = max(tfree[i] + pos[i].dist(rides[opt].s), rides[opt].ts) + rides[opt].s.dist(rides[opt].f);
	    pos[i] = rides[opt].f;
	  }
	}
  }
  for (int i = 0; i < f; ++i) {
    printf("%d", sz(ans[i]));
    for (int j = 0; j < sz(ans[i]); ++j) {
      printf(" %d", ans[i][j]);
    }
    printf("\n");
  }
}

int main() {
  srand(rdtsc());
  precalc();
  freopen("c_no_hurry.in", "r", stdin);
  freopen("c_no_hurry.out", "w", stdout);

  while (true) {
    if (!read()) {
      break;
    }
    solve();
#ifdef DEBUG
    eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  }
  return 0;
}


