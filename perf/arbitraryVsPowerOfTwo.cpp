#include <hayai.hpp>

const uint16_t RUNS = 100;
const uint32_t ITERS = 10000;

namespace avpt {
  template<typename T>
  class arrd32 {
    public:
      T arr[32];
      uint8_t len;
      T& operator[] (const int i) {
        return arr[i];
      }
  };

  template<typename T>
  class arrd1024 {
    public:
      T arr[1024];
      uint16_t len;
      T& operator[] (const int i) {
        return arr[i];
      }
  };

  template<typename T, uint16_t N>
  class arrd_arb {
    public:
      T arr[N];
      uint16_t len;
      T& operator[] (const int i) {
        return arr[i];
      }
  };

  arrd32<int> fixed = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89}, 24};
  arrd_arb<int, 24> arb = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89}, 24};

  template<
    template<typename> class T,
    typename R,
    typename A
  > inline T<R>* mapFixed(T<R> *r, R (*f)(A), T<A> *a) {
    r->len = a->len;
    for (uint16_t i=0; i<r->len; i++) {
      (*r)[i] = f((*a)[i]);
    }
    return r;
  }

  template<
    template<typename, uint16_t> class T,
    typename R,
    typename A,
    uint16_t N
  > inline T<R,N>* mapArb(T<R,N> *r, R (*f)(A), T<A,N> *a) {
    r->len = a->len;
    for (uint16_t i=0; i<r->len; i++) {
      (*r)[i] = f((*a)[i]);
    }
    return r;
  }

  template<typename T>
  T asIs(T a) {
    return a;
  }
}

class arbitraryVsPowerOfTwo : public ::hayai::Fixture {
  public:
    virtual void SetUp() {
      int size = 768;
      this->fixed_1024.len = size;
      this->arb_768.len = size;
      this->arb_1024.len = size;
      for (int i=0; i<size; i++) {
        this->fixed_1024[i] = i;
        this->arb_768[i] = i;
        this->arb_1024[i] = i;
      }
    }

    avpt::arrd1024<int> fixed_1024;
    avpt::arrd_arb<int,1024> arb_1024;
    avpt::arrd_arb<int,768> arb_768;
};

BENCHMARK(arbitraryVsPowerOfTwo, powerOfTwo32, RUNS, ITERS) {
  avpt::arrd32<int> b;
  avpt::mapFixed(&b, avpt::asIs, &avpt::fixed);
}

BENCHMARK(arbitraryVsPowerOfTwo, arbitrary32, RUNS, ITERS) {
  avpt::arrd_arb<int, 24> b;
  avpt::mapArb(&b, avpt::asIs, &avpt::arb);
}

BENCHMARK_F(arbitraryVsPowerOfTwo, powerOfTwo1024, RUNS, ITERS/10) {
  avpt::arrd1024<int> b;
  avpt::mapFixed(&b, avpt::asIs, &fixed_1024);
}

BENCHMARK_F(arbitraryVsPowerOfTwo, arbitrary768, RUNS, ITERS/10) {
  avpt::arrd_arb<int, 768> b;
  avpt::mapArb(&b, avpt::asIs, &arb_768);
}

BENCHMARK_F(arbitraryVsPowerOfTwo, arbitrary1024, RUNS, ITERS/10) {
  avpt::arrd_arb<int, 1024> b;
  avpt::mapArb(&b, avpt::asIs, &arb_1024);
}
