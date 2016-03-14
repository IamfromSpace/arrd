#include <hayai.hpp>

const uint16_t RUNS = 100;
const uint32_t ITERS = 10000;

namespace avd {
  template<typename T>
  class arrd {
    public:
      T arr[32];
      uint8_t len;
      T& operator[] (const int i) {
        return arr[i];
      }
  };

  arrd<int> a = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};
  arrd<int> b = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};
  arrd<int> c = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};
  arrd<int> d = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};
  arrd<int> e = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};

  template<
    template<typename> class T,
    typename R,
    typename A
  > T<R>* mapAbstract(T<R> *r, R (*f)(A), T<A> *a) {
    r->len = a->len;
    for (uint16_t i=0; i<r->len; i++) {
      (*r)[i] = f((*a)[i]);
    }
    return r;
  }

  template<
    template<typename> class T,
    typename R,
    typename A
  > inline T<R>* mapAbstractInline(T<R> *r, R (*f)(A), T<A> *a) {
    r->len = a->len;
    for (uint16_t i=0; i<r->len; i++) {
      (*r)[i] = f((*a)[i]);
    }
    return r;
  }

  template<template<typename> class T, typename A> T<A> mapDirect(A (*f)(A), T<A> a) {
    T<A> b;
    b.len = a.len;
    for (uint16_t i=0; i<b.len; i++) {
      b[i] = f(a[i]);
    }
    return b;
  }

  template<template<typename> class T, typename A> T<A> mapAbstracted(A (*f)(A), T<A> a) {
    T<A> b;
    mapAbstract(&b, f, &a);
    return b;
  }

  template<template<typename> class T, typename A> T<A> mapAbstractedInline(A (*f)(A), T<A> a) {
    T<A> b;
    mapAbstractInline(&b, f, &a);
    return b;
  }

  template<typename T>
  T asIs(T a) {
    return a;
  }
}

BENCHMARK(abstractedVsDirect, abstracted, RUNS, ITERS) {
  avd::mapAbstracted(avd::asIs, avd::a);
}

BENCHMARK(abstractedVsDirect, abstractedInline, RUNS, ITERS) {
  avd::mapAbstractedInline(avd::asIs, avd::b);
}

BENCHMARK(abstractedVsDirect, direct, RUNS, ITERS) {
  avd::mapDirect(avd::asIs, avd::c);
}

BENCHMARK(abstractedVsDirect, manuallyAbstract, RUNS, ITERS) {
  avd::arrd<int> r;
  avd::mapAbstract(&r, avd::asIs, &avd::d);
}

BENCHMARK(abstractedVsDirect, manuallyAbstractInline, RUNS, ITERS) {
  avd::arrd<int> r;
  avd::mapAbstractInline(&r, avd::asIs, &avd::e);
}
