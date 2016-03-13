#ifndef HELPERS_H
#define HELPERS_H
#include <stdint.h>

template<typename T>
T square(T a) {
  return a * a;
}

template<typename T>
T sum(T a, T b) {
  return a + b;
}

template<typename T>
bool isPositive(T a) {
  return a >= 0;
}

template<typename T>
T incIf(T a, bool b) {
  if (b) {
    return a + 1;
  } else {
    return a;
  }
}

template<typename A>
int16_t sign(A a) {
  if (isPositive(a)) {
    return 1;
  } else {
    return -1;
  }
}

template<typename R, typename A, typename B>
R divAby10ifBTruthy(A a, B b) {
  if((bool) b) {
    return ((R) a) / 10;
  } else {
    return (R) a;
  }
}
#endif
