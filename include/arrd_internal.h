#ifndef ARRD_INTERNAL_H
#define ARRD_INTERNAL_H
#include <stdint.h>

namespace arrd_internal {
  template<
    template<typename> class T,
    typename R,
    typename A
  > T<R>* map(T<R> *r, R (*f)(A), T<A> *a) {
    r->len = a->len;
    for (uint16_t i=0; i<r->len; i++) {
      (*r)[i] = f((*a)[i]);
    }
    return r;
  }

  template<
    template<typename> class RR,
    template<typename> class AA,
    template<typename> class BB,
    typename R,
    typename A,
    typename B
  > RR<R>* map(RR<R> *r, R (*f)(A, B), AA<A> *a, BB<B> *b) {
    r->len = a->len < b->len ? a->len : b->len;
    for (uint16_t i=0; i<r->len; i++) {
      (*r)[i] = f((*a)[i], (*b)[i]);
    }
    return r;
  }
}

#endif
