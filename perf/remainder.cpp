#include <hayai.hpp>
#include "arrd.h"

using namespace arrd;

const uint16_t RUNS = 100;
const uint32_t ITERS = 10000;

arrd32_t<int> primes = {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113}, 30};
arrd32_t<int> offsetPrimes = {{5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131}, 30};

int shift32(int a) {
  return a - ((a >> 5) << 5);
}

int and32(int a) {
  return a & 31;
}

int rem32(int a) {
  return a % 32;
}

int rem31(int a) {
  return a % 31;
}

int shift32wStart(int a, int b) {
  int c = a + b;
  return c - ((c >> 5) << 5);
}

int and32wStart(int a, int b) {
  return (a + b) & 31;
}

int rem32wStart(int a, int b) {
  return (a + b) % 32;
}

int rem31wStart(int a, int b) {
  return (a + b) % 31;
}

BENCHMARK(Remainder, PowerOfTwoRemainderOperator, RUNS, ITERS) {
  map(rem32, primes);
}

BENCHMARK(Remainder, MersennePrimeRemainderOperator, RUNS, ITERS) {
  map(rem31, primes);
}

BENCHMARK(Remainder, PowerOfTwoBitShifting, RUNS, ITERS) {
  map(shift32, primes);
}

BENCHMARK(Remainder, PowerOfTwoBitAnd, RUNS, ITERS) {
  map(and32, primes);
}

BENCHMARK(RemainderWStart, PowerOfTwoRemainderOperator, RUNS, ITERS) {
  map(rem32wStart, primes, offsetPrimes);
}

BENCHMARK(RemainderWStart, MersennePrimeRemainderOperator, RUNS, ITERS) {
  map(rem31wStart, primes, offsetPrimes);
}

BENCHMARK(RemainderWStart, PowerOfTwoBitShifting, RUNS, ITERS) {
  map(shift32wStart, primes, offsetPrimes);
}

BENCHMARK(RemainderWStart, PowerOfTwoBitAnd, RUNS, ITERS) {
  map(and32wStart, primes, offsetPrimes);
}

int main()
{ 
    hayai::ConsoleOutputter consoleOutputter;
 
    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
    return 0;
}
