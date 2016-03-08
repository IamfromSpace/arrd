#include <stdint.h>

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
  template<template<typename> class T, typename A> T<A> map(A (*f)(A), T<A> a) {
    T<A> b;
    b.len = a.len;
    for (uint16_t i=0; i<b.len; i++) {
      b[i] = f(a[i]);
    }
    return b;
  }
}

