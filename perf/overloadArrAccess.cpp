#include <hayai.hpp>

const uint16_t RUNS = 100;
const uint32_t ITERS = 10000;

template<typename T>
class arrd32_noSafety {
  public:
    T arr[32];
    uint8_t len;
    T& operator[] (const int i) {
      return arr[i];
    }
};

template<typename T>
class arrd32_withSafety {
  public:
    T arr[32];
    uint8_t len;
    T& operator[] (const int i) {
      return arr[31 & i];
    }
};

template<typename T>
class arrd32_withStart {
  public:
    T arr[32];
    uint8_t len;
    uint8_t start;
    T& operator[] (const int i) {
      return arr[31 & (i + start)];
    }
};

template<typename T>
T asIs(T a) {
  return a;
}

template<template<typename> class T, typename A> void map_cheap(A (*f)(A), T<A> a) {
  for (int i = 0; i < a.len; i++) {
    a[i] = f(a[i]);
  }
}

arrd32_noSafety<int> a = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};
arrd32_withSafety<int> b = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};
arrd32_withStart<int> c = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131}, 30, 7};

BENCHMARK(overloadArrAccess, noSafety, RUNS, ITERS) {
  map_cheap(asIs, a);
}

BENCHMARK(overloadArrAccess, withSafety, RUNS, ITERS) {
  map_cheap(asIs, b);
}

BENCHMARK(overloadArrAccess, withStart, RUNS, ITERS) {
  map_cheap(asIs, c);
}
