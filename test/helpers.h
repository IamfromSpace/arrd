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
#endif
