#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_EPS 1e-100
#define S21_PI 3.14159265358979323846
#define S21_EXP 2.71828182845904523536
#define S21_LN2 0.69314718055994530941
#define S21_MAX 1e100
#define POS_INF 1.0 / 0.0L
#define NEG_INF -1.0 / 0.0L
#define S21_NaN (__builtin_nanf(""))
#define isNaN(x) (x != x)
#define isInf(x) (x == INF_POS || x == INF_NEG)
#define isNormal(x) (!isNaN(x) && !isNegInf(x) && !isPosInf(x))

long double s21_fmod(double x, double y);
long double s21_floor(double x);
long double s21_fabs(double x);
long double s21_ceil(double x);
long double s21_factorial(double x);
long double s21_pow(double x, double n);
long double s21_log(double x);
long double s21_exp(double x);
int s21_abs(int x);

int main() {
  char *x = "5.0";
  char *y = "-5.125";
  double cmpXFloat;
  double cmpYFloat;

  sscanf(x, "%lf", &cmpXFloat);
  sscanf(y, "%lf", &cmpYFloat);

  // s21_ceil(cmpYFloat);
  // s21_floor(cmpXFloat);
  s21_pow(cmpXFloat, cmpYFloat);
  s21_log(cmpXFloat);

  s21_exp(cmpXFloat);

  printf("EXP = %Lf exp = %lf\n", s21_exp(cmpXFloat), exp(cmpXFloat));
  // printf("%lf\n", log10(cmpXFloat));

  // s21_fmod(cmpXFloat, cmpYFloat);

  // printf("%.6Lf\n%.6lf\n", s21_fmod(cmpXFloat, cmpYFloat),
  //        fmod(cmpXFloat, cmpYFloat));

  return 0;
}

long double s21_factorial(double x) {
  long double resFactorial = 1;
  for (int i = 0; i < x && x < 25; i++) {
    resFactorial = resFactorial * (i + 1);
  }
  // long double resFactorialStiring =
  //     (sqrt(2 * S21_PI * x) * pow((x / S21_EXP), x) * (1 + (1 / (12 * x))));
  // long double resFact = (long long int)resFactorialStiring;
  // printf("resFactorial = %Lf %Lf %Lf\n", resFactorial, resFact,
  // resFactorialStiring);

  return resFactorial;
}

long double s21_pow(double x, double n) {
  long double resPow = 1;
  long double p = (long long int)n;
  if (n == 0) {
    return 1;
  }
  if (n > 0 && n == p) {
    while (n != 0) {
      if (s21_fmod(n, 2) == 1) {
        resPow *= x;
      }
      x *= x;
      n /= 2;
    }
  } else if (n < 0 && n == p) {
    n = s21_fabs(n);
    while (n > 0) {
      if (s21_fmod(n, 2) == 1) {
        resPow *= x;
      }
      x *= x;
      n /= 2;
    }
    resPow = 1 / resPow;
  } else if (n != p) {
    long double dec = s21_floor(n);
    if (dec < 0) {
      dec = s21_fabs(dec);
      while (dec > 0) {
        if (s21_fmod(dec, 2) == 1) {
          resPow *= x;
        }
        x *= x;
        dec /= 2;
      }
      resPow = 1 / resPow;
    }
    long double rest = n - dec;
    long double restPow = s21_exp(rest);
  }
  printf("%Lf\n", resPow);
  return resPow;
}

long double s21_sqrt(double x) {
  // check on 0 and 1
  long double start = 0;
  long double end;
  if (x > 1) {
    end = x;
  } else {
    end = 1;
  }
  long double middle = 0.5 * (start + end);

  while ((s21_pow(middle,2) - x) != 0) {
    if ((s21_pow(middle,2) - x) > 0) {
      end = middle;
    } else if ((s21_pow(middle,2) - x) < 0) {
      start = middle;
    }
  }
 
}

long double s21_exp(double x) {

  long double resEXP = 1.0;
  long double cur = 1.0;
  unsigned int n = 1;

  while (n < 200) {
    cur *= ((long double)x / n++);
    resEXP += cur;
  }
  return resEXP;
}

long double s21_log(double x) {
  long double start = 0;
  long double end = x;
  long double middle = 0.5 * (start + end);

  while ((s21_exp(middle) - x) != 0) {
    if ((s21_exp(middle) - x) > 0) {
      end = middle;
    } else if ((s21_exp(middle) - x) < 0) {
      start = middle;
    }
  }
}
// long double s21_sin(double x) { x - x; }

long double s21_fmod(double x, double y) {
  long double resMod;
  long double X = (int)x;
  long double Y = (int)y;
  long double Z;
  if (Y != 0) {
    Z = (long long int)(X / Y);
    resMod = X - (Y * Z);
  }
  if (x < 0) {
    resMod *= -1;
  }
  // printf("resMod = %Lf X = %Lf Y = %Lf Z = %Lf\n", resMod, X, Y, Z);
  return resMod;
}
long double s21_floor(double x) {
  long double resFloor = (long long int)x;
  if (resFloor > 0) {
    resFloor;
  } else if ((resFloor < 0) && (resFloor != x)) {
    resFloor -= 1;
  }
  return resFloor;
}

long double s21_ceil(double x) {
  long double resCeil = (long long int)x;
  if (x != resCeil) {
    resCeil = s21_floor(x) + 1;
  } else
    resCeil;
  return resCeil;
}

int s21_abs(int x) { return (int)s21_fabs(x); }

long double s21_fabs(double x) {

  if (x < 0) {
    x *= (-1.0);
  } else {
    x;
  }
  return x;
}

// long double s21_pow(double x, double y) {
//     long double rez;
//     rez = s21_exp(y * s21_log(x));
//     return rez;
// }

// long double s21_sin(double x) { 
//   long double rez;
//   rez = 1 / 
//   return rez;
// }

long double s21_sin(double x) {
  x = reader(x);
  long double rez = x, y = x;
  long double i = 1.;
  while (s21_fabs(rez) > s21_EPS) {
    rez = -1 * rez * x * x / (2 * i * (2 * i + 1));
    i += 1.;
    y += rez;
  }
  return y;
}

long double s21_cos(double x) {
  x = reader(x);
  return s21_sin((s21_PI / 2.0) - x);
}

long double s21_asin(double x) {
  long double rez = x, y = x;
  long double i = 1;
  while (s21_fabs(rez) > s21_EPS) {
    if (x < -1 || x > 1) {
      y = s21_NAN;
      break;
    }
    if (x == 1 || x == -1) {
      y = s21_PI / 2 * x;
      break;
    }
    rez *= x * x * (2 * i - 1) * (2 * i - 1) / ((2 * i + 1) * 2 * i);
    i += 1;
    y += rez;
  }
  return y;
}

long double s21_acos(double x) {
  if (x <= 1 && x >= -1) {
    x = s21_PI / 2. - s21_asin(x);
  } else {
    x = s21_NAN;
  }
  return x;
}
long double s21_acos(double x) {
  if (x <= 1 && x >= -1) {
    x = s21_PI / 2. - s21_asin(x);
  } else {
    x = s21_NAN;
  }
  return x;
}
