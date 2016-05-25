#include <bits/stdc++.h>
#define D(x) cout << #x << ": " << x << endl
using namespace std;
 
double EPS = 1e-8;
 
double x_sub_i(double l, double v) {
  return (l * v * 100) / sqrt(1 - (l * l * v * v));
}
 
double bs(double l, double h, vector<double> s, double d) {
  while (true) {
    double m = (l + h) / 2.0;
    double sum = 0;
    for (int i = 0; i < s.size(); ++i) sum += x_sub_i(m, s[i]);
    if (fabs(sum - d) < EPS) return m;
    if (sum < d) l = m;
    else h = m;
  }
}
 
int main() {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    int n, d; cin >> n >> d;
    vector<double> s(n);
    double max_speed = 0;
    for (int i = 0; i < s.size(); ++i) {
      double speed; cin >> speed;
      s[i] = speed;
      max_speed = max(speed, max_speed);
    }
    double lambda = bs(-1/max_speed, 1/max_speed, s, d);
    cout << "Case " << t + 1 << ": " << endl;
    double target = 0;
    for (int i = 0; i < s.size(); ++i) {
      double xi = x_sub_i(lambda, s[i]);
      if (i) cout << ", ";
      cout << "X" << i + 1 << " = " << xi;
      target += sqrt(xi * xi + 100 * 100) / s[i];
    }
    cout << endl << "Función Objetivo: " << fixed << setprecision(8) << target << endl;
    cout << endl;
  }
  return 0;
}