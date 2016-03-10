#include "arrd.h"
#include "gtest/gtest.h"

using namespace arrd;

template<typename T>
T square(T a) {
  return a * a;
}

template<typename T>
T sum(T a, T b) {
  return a + b;
}

TEST(arrd, CanAccessAllMembers) {
  arrd4_t<int16_t> a = {{0, 1, 4, 9}, 4};
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 4);
  EXPECT_EQ(a[3], 9);
}

TEST(arrd, CanChangeInSize) {
  arrd4_t<int16_t> a = {{0, 1}, 2};
  a[2] = 7;
  a.len++;

  EXPECT_EQ(a.len, 3);
  EXPECT_EQ(a[2], 7);
}

TEST(arrd, CanBeMultiDimensional) {
  arrd4_t< arrd4_t<int16_t> > a = {{{{5, 6}, 2}, {{7, 8, 9}, 3}}, 2};
  EXPECT_EQ(a.len, 2);
  EXPECT_EQ(a[0][0], 5);
  EXPECT_EQ(a[0][1], 6);
  EXPECT_EQ(a[1][0], 7);
  EXPECT_EQ(a[1][1], 8);
  EXPECT_EQ(a[1][2], 9);
  EXPECT_EQ(a.len, 2);
  EXPECT_EQ(a[0].len, 2);
  EXPECT_EQ(a[1].len, 3);
}

TEST(arrd, CanAcceptComplexAssignment) {
  arrd4_t< arrd4_t<int16_t> > a = {{{{5, 6}, 2}, {{7, 8, 9}, 3}}, 2};
  arrd4_t<int16_t> b = {{10, 11, 12, 13}, 4};
  a[0] = b;
  EXPECT_EQ(a[0][0], 10);
  EXPECT_EQ(a[0][1], 11);
  EXPECT_EQ(a[0][2], 12);
  EXPECT_EQ(a[0][3], 13);
  EXPECT_EQ(a.len, 2);
  EXPECT_EQ(a[0].len, 4);
  EXPECT_EQ(a[1].len, 3);
}

TEST(arrd, ShouldDeepCopyOnAssignment) {
  arrd4_t<int16_t> a = {{0,1,2}, 3};
  arrd4_t< arrd4_t<int16_t> > b = { {}, 0};
  b[0] = a; b.len++;
  b[1] = a; b.len++;
  a[1] = 19;
  b[0][1] = 50;
  EXPECT_EQ(b[0][1], 50);
  EXPECT_EQ(b[1][1], 1);
}

TEST(arrdMap, ShouldMap) {
  arrd4_t<int16_t> a = {{0,1,2}, 3};
  arrd4_t<int16_t> b = map(square, a);
  EXPECT_EQ(b[0], 0);
  EXPECT_EQ(b[1], 1);
  EXPECT_EQ(b[2], 4);
}

TEST(arrdMap, ShouldMapMultipleTypes) {
  arrd8_t<float> a = {{0,1,2}, 3};
  arrd8_t<float> b = map(square, a);
  EXPECT_EQ(b[0], 0);
  EXPECT_EQ(b[1], 1);
  EXPECT_EQ(b[2], 4);
}

TEST(arrdMap, ShouldMapTwoArrds) {
  arrd4_t<int16_t> a = {{0,1,2}, 3};
  arrd4_t<int16_t> b = {{0,1,2,3}, 4};
  arrd4_t<int16_t> c = map(sum<int16_t>, a, b);
  EXPECT_EQ(c[0], 0);
  EXPECT_EQ(c[1], 2);
  EXPECT_EQ(c[2], 4);
  EXPECT_EQ(c.len, 3);
}
