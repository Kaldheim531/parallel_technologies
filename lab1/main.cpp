#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>

// подынтегральная функция f(x) = sqrt(x*(3-x)) / (x+1)
double f(double x) {
  return std::sqrt(x * (3.0 - x)) / (x + 1.0);
}

// составная формула Симпсона на n отрезках (n должно быть четным)
// распараллелена по примеру из лекции: #pragma omp parallel for reduction(+:sum)
double simpson(double a, double b, int n) {
  double h = (b - a) / n;
  double sum = 0.0;

  #pragma omp parallel for reduction(+:sum)
  for (int i = 1; i < n; i++) {
    double x = a + i * h;
    double coef = (i % 2 == 0) ? 2.0 : 4.0;
    sum += coef * f(x);
  }

  sum += f(a) + f(b);

  return sum * h / 3.0;
}

int main(int argc, char** argv) {
  double a = 1.0;
  double b = 1.2;
  double eps = 1e-6;

  int threads = 4;
  if (argc > 1) {
    threads = std::atoi(argv[1]);
  }
  omp_set_num_threads(threads);

  // находим n по правилу Рунге с точностью eps.
  // для метода Симпсона (4й порядок) знаменатель в правиле Рунге равен
  // 2^4 - 1 = 15 (это видно на доске с лекции)
  int n = 2;
  double I_prev = simpson(a, b, n);
  double I_cur = I_prev;

  double start = omp_get_wtime();

  while (true) {
    n *= 2;
    I_cur = simpson(a, b, n);

    double runge = std::fabs(I_cur - I_prev) / 15.0;

    if (runge < eps) {
      break;
    }

    I_prev = I_cur;
  }

  double end = omp_get_wtime();

  // формат вывода: потоков n значение_интеграла время
  // (удобно парсить в bench.txt для построения графика)
  printf("%d %d %.10f %.6f\n", threads, n, I_cur, end - start);

  return 0;
}