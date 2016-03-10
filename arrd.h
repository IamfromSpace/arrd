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

  template<template<typename> class T, typename A, typename B> B reduce(B (*f)(B, A), B b, T<A> a) {
    B r = b;
    for (uint16_t i=0; i<a.len; i++) {
      r = f(r, a[i]);
    }
    return r;
  }

  template<template<typename> class T, typename A> A reduce(A (*f)(A, A), T<A> a) {
    if (a.len == 0) {
      return (A) 0;
    }
    if (a.len == 1) {
      return a[0];
    }
    A r = f(a[0],a[1]);
    for (uint16_t i=2; i<a.len; i++) {
      r = f(r, a[i]);
    }
    return r;
  }

  template<template<typename> class T, typename A> T<A> reverse(T<A> a) {
    T<A> r;
    r.len = a.len;
    if (r.len != 0) {
      for (uint16_t i=0; i<r.len; i++) {
        r[i] = a[a.len - i - 1];
      }
    }
    return r;
  }

  template<template<typename> class T, typename A> T<A> take(T<A> a, uint16_t count) {
    T<A> r;
    r.len = count;
    if (r.len != 0) {
      for (uint16_t i=0; i<count; i++) {
        r[i] = a[i];
      }
    }
    return r;
  }
}

