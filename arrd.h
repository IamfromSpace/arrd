#include <stdint.h>
#include <algorithm>

template<typename T>
class arrd4_t {
  public:
    T arr[4];
    uint8_t len;
    T& operator[] (const int i) {
      return arr[i];
    }
};

template<typename T>
class arrd8_t {
  public:
    T arr[8];
    uint8_t len;
    T& operator[] (const int i) {
      return arr[i];
    }
};

namespace arrd {
  template<template<typename> class T, typename A, typename B, typename C> T<C> map(C (*f)(A,B), T<A> a, T<B> b) {
    T<C> r;
    r.len = std::min(a.len, b.len);
    for (uint16_t i=0; i<r.len; i++) {
      r[i] = f(a[i], b[i]);
    }
    return r;
  }

  template<template<typename> class T, typename A> T<A> map(A (*f)(A), T<A> a) {
    T<A> b;
    b.len = a.len;
    for (uint16_t i=0; i<b.len; i++) {
      b[i] = f(a[i]);
    }
    return b;
  }

  template<template<typename> class A, typename T> A<T> conc(A<T> a, A<T> b) {
    A<T> r;
    r.len = a.len + b.len;
    for (uint16_t i=0; i<a.len; i++) {
      r[i] = a[i];
    }
    for (uint16_t i=0; i<b.len; i++) {
      r[i + a.len] = b[i];
    }
    return r;
  }

  template<template<typename> class T, typename A> T<A> filter(bool (*f)(A), T<A> a) {
    T<A> r;
    r.len = 0;
    for (uint16_t i=0; i<a.len; i++) {
      if (f(a[i]) == true) {
        r[r.len] = a[i];
        r.len++;
      }
    }
    return r;
  }
}

