#include "arrd.h"
#include "arrd_internal.h"
#include "helpers.h"
#include "gtest/gtest.h"

TEST(arrdInternalMap, ShouldMapAndNotMutate) {
  arrd4_t<int16_t> a = {{0,1,2}, 3};
  arrd4_t<int16_t> b;
  arrd_internal::map(&b, square, &a);
  EXPECT_EQ(b[0], 0);
  EXPECT_EQ(b[1], 1);
  EXPECT_EQ(b[2], 4);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a.len, 3);
}

TEST(arrdInternalMap, ShouldMapOneTypeToAnother) {
  arrd4_t<float> a = {{0.0,-1.1,2.7}, 3};
  arrd4_t<int16_t> b;
  arrd_internal::map(&b, sign, &a);

  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], -1);
  EXPECT_EQ(b[2], 1);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_FLOAT_EQ(a[0], 0.0);
  EXPECT_FLOAT_EQ(a[1], -1.1);
  EXPECT_FLOAT_EQ(a[2], 2.7);
  EXPECT_EQ(a.len, 3);
}

TEST(arrdInternalMap, ShouldMapTwoArrays) {
  arrd4_t<int16_t> a = {{1,2,3}, 3};
  arrd4_t<int16_t> b = {{7,8,9,10}, 4};
  arrd4_t<int16_t> r;
  arrd_internal::map(&r, sum, &a, &b);

  EXPECT_EQ(r[0], 8);
  EXPECT_EQ(r[1], 10);
  EXPECT_EQ(r[2], 12);
  EXPECT_EQ(r.len, 3);

  //And not mutate args
  EXPECT_FLOAT_EQ(a[0], 1);
  EXPECT_FLOAT_EQ(a[1], 2);
  EXPECT_FLOAT_EQ(a[2], 3);
  EXPECT_EQ(a.len, 3);

  EXPECT_FLOAT_EQ(b[0], 7);
  EXPECT_FLOAT_EQ(b[1], 8);
  EXPECT_FLOAT_EQ(b[2], 9);
  EXPECT_FLOAT_EQ(b[3], 10);
  EXPECT_EQ(b.len, 4);
}

TEST(arrdInternalMap, ShouldMapTwoArraysWithUpToThreeTypes) {
  arrd4_t<int16_t> a = {{1,2,3}, 3};
  arrd4_t<bool> b = {{true,false,true,false}, 4};
  arrd4_t<float> r;
  arrd_internal::map(&r, divAby10ifBTruthy, &a, &b);

  EXPECT_FLOAT_EQ(r[0], 0.1);
  EXPECT_FLOAT_EQ(r[1], 2);
  EXPECT_FLOAT_EQ(r[2], 0.3);
  EXPECT_FLOAT_EQ(r.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a.len, 3);

  EXPECT_EQ(b[0], true);
  EXPECT_EQ(b[1], false);
  EXPECT_EQ(b[2], true);
  EXPECT_EQ(b[3], false);
  EXPECT_EQ(b.len, 4);
}

TEST(arrdInternalMap, ShouldMapDifferentArraySizes) {
  arrd4_t<int16_t> a = {{5,6},2};
  arrd32_t<int16_t> b = {{19,20,21,22}, 4};
  arrd2_t<int16_t> r;
  arrd_internal::map(&r, sum, &a, &b);

  EXPECT_EQ(r[0], 24);
  EXPECT_EQ(r[1], 26);
  EXPECT_EQ(r.len, 2);

  //And not mutate args
  EXPECT_EQ(a[0], 5);
  EXPECT_EQ(a[1], 6);
  EXPECT_EQ(a.len, 2);

  EXPECT_EQ(b[0], 19);
  EXPECT_EQ(b[1], 20);
  EXPECT_EQ(b[2], 21);
  EXPECT_EQ(b[3], 22);
  EXPECT_EQ(b.len, 4);
}
