#include "arrd.h"
#include "helpers.h"
#include "gtest/gtest.h"

using namespace arrd;

TEST(arrd, CanAccessAllMembers) {
  arrd4_t<int16_t> a = {{0, 1, 4, 9}, 4};
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 4);
  EXPECT_EQ(a[3], 9);
  EXPECT_EQ(a.len, 4);
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
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a.len, 3);
}

TEST(arrdMap, ShouldMapMultipleTypes) {
  // TODO: This is testing the wrong thing.  Should be testing A f(B);
  arrd8_t<float> a = {{0,1,2}, 3};
  arrd8_t<float> b = map(square, a);
  EXPECT_EQ(b[0], 0);
  EXPECT_EQ(b[1], 1);
  EXPECT_EQ(b[2], 4);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a.len, 3);
}

TEST(arrdMap, ShouldMapTwoArrds) {
  arrd4_t<int16_t> a = {{0,1,2}, 3};
  arrd4_t<int16_t> b = {{0,1,2,3}, 4};
  arrd4_t<int16_t> c = map(sum<int16_t>, a, b);
  EXPECT_EQ(c[0], 0);
  EXPECT_EQ(c[1], 2);
  EXPECT_EQ(c[2], 4);
  EXPECT_EQ(c.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a.len, 3);

  EXPECT_EQ(b[0], 0);
  EXPECT_EQ(b[1], 1);
  EXPECT_EQ(b[2], 2);
  EXPECT_EQ(b[3], 3);
  EXPECT_EQ(b.len, 4);
}

TEST(arrdConcat, ShouldCombineTwoArrds) {
  arrd4_t<int16_t> a = {{7},1};
  arrd4_t<int16_t> b = {{8,9},2};
  arrd4_t<int16_t> c = concat(a,b);
  EXPECT_EQ(c[0], 7);
  EXPECT_EQ(c[1], 8);
  EXPECT_EQ(c[2], 9);
  EXPECT_EQ(c.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 7);
  EXPECT_EQ(a.len, 1);

  EXPECT_EQ(b[0], 8);
  EXPECT_EQ(b[1], 9);
  EXPECT_EQ(b.len, 2);
}

TEST(arrdConcat, ShouldCombineArrdsOfVariousSize) {
  arrd2_t<int16_t> a = {{7},1};
  arrd4_t<int16_t> b = {{8,9,10,11},4};
  arrd8_t<int16_t> c = concat<arrd8_t>(a,b);
  EXPECT_EQ(c[0], 7);
  EXPECT_EQ(c[1], 8);
  EXPECT_EQ(c[2], 9);
  EXPECT_EQ(c[3], 10);
  EXPECT_EQ(c[4], 11);
  EXPECT_EQ(c.len, 5);

  //And not mutate args
  EXPECT_EQ(a[0], 7);
  EXPECT_EQ(a.len, 1);

  EXPECT_EQ(b[0], 8);
  EXPECT_EQ(b[1], 9);
  EXPECT_EQ(b[2], 10);
  EXPECT_EQ(b[3], 11);
  EXPECT_EQ(b.len, 4);
}

TEST(arrdFilter, ShouldFilter) {
  arrd8_t<int16_t> a = {{1, -1, 0, -17, -5, 12, 1923}, 7};
  arrd8_t<int16_t> b = filter(isPositive<int16_t>, a);
  EXPECT_EQ(b[0],1);
  EXPECT_EQ(b[1],0);
  EXPECT_EQ(b[2],12);
  EXPECT_EQ(b[3],1923);
  EXPECT_EQ(b.len,4);

  //And not mutate args
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], -1);
  EXPECT_EQ(a[2], 0);
  EXPECT_EQ(a[3], -17);
  EXPECT_EQ(a[4], -5);
  EXPECT_EQ(a[5], 12);
  EXPECT_EQ(a[6], 1923);
  EXPECT_EQ(a.len, 7);
}

TEST(arrdReduce, ShouldAcceptAStartingValue) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  int16_t b = reduce(sum<int16_t>, (int16_t) 10, a);
  EXPECT_EQ(b, 25);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdReduce, ShouldAcceptAStartingValOfDifferentType) {
  arrd8_t<bool> a = {{true,false,false,true,true,true},6};
  int16_t b = reduce(incIf, (int16_t) 0, a);
  EXPECT_EQ(b, 4);

  //And not mutate args
  EXPECT_EQ(a[0], true);
  EXPECT_EQ(a[1], false);
  EXPECT_EQ(a[2], false);
  EXPECT_EQ(a[3], true);
  EXPECT_EQ(a[4], true);
  EXPECT_EQ(a[5], true);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdReduce, ShouldWorkWithoutAStartingValue) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  int16_t b = reduce(sum<int16_t>, a);
  EXPECT_EQ(b, 15);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdReduce, ShouldReturnTheFirstElementWhenLengthIsOne) {
  arrd8_t<int16_t> a = {{90},1};
  int16_t b = reduce(sum<int16_t>, a);
  EXPECT_EQ(b, 90);

  //And not mutate args
  EXPECT_EQ(a[0], 90);
  EXPECT_EQ(a.len, 1);
}

TEST(arrdReduce, ShouldReturnATypeCast0IfEmpty) {
  arrd8_t<bool> a = {{},0};
  bool b = reduce(sum<bool>, a);
  EXPECT_EQ(b, false);

  //And not mutate args
  EXPECT_EQ(a.len, 0);
}

TEST(arrdReverse, ShouldReverseAnArray) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  arrd8_t<int16_t> b = reverse(a);
  EXPECT_EQ(b[0], 5);
  EXPECT_EQ(b[1], 4);
  EXPECT_EQ(b[2], 3);
  EXPECT_EQ(b[3], 2);
  EXPECT_EQ(b[4], 1);
  EXPECT_EQ(b[5], 0);
  EXPECT_EQ(b.len, 6);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdReverse, ShouldReturnAnEmptyArrayWhenReversingAZeroLengthArray) {
  arrd8_t<int16_t> a = {{},0};
  arrd8_t<int16_t> b = reverse(a);
  EXPECT_EQ(b.len, 0);

  //And not mutate args
  EXPECT_EQ(a.len, 0);
}

TEST(arrdTake, ShouldReturnASubsetOfTheTargetArray) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  arrd8_t<int16_t> b = take(a, 3);
  EXPECT_EQ(b[0],0);
  EXPECT_EQ(b[1],1);
  EXPECT_EQ(b[2],2);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdTake, ShouldReturnAnEmptyArrayWhenTakingZero) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  arrd8_t<int16_t> b = take(a, 0);
  EXPECT_EQ(b.len, 0);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdTake, ShouldBeAbleToReturnADifferentCapacityArray) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  arrd4_t<int16_t> b = take<arrd4_t>(a, 3);
  EXPECT_EQ(b[0],0);
  EXPECT_EQ(b[1],1);
  EXPECT_EQ(b[2],2);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdDrop, ShouldReturnASubsetOfTheTargetArray) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  arrd8_t<int16_t> b = drop(a, 3);
  EXPECT_EQ(b[0],3);
  EXPECT_EQ(b[1],4);
  EXPECT_EQ(b[2],5);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(arrdDrop, ShouldReturnAnIdenticalArrayWhenDroppingZero) {
  arrd8_t<int16_t> a = {{0,1,2,3},4};
  arrd8_t<int16_t> b = drop(a, 0);
  EXPECT_EQ(b[0],0);
  EXPECT_EQ(b[1],1);
  EXPECT_EQ(b[2],2);
  EXPECT_EQ(b[3],3);
  EXPECT_EQ(b.len, 4);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a.len, 4);
}

TEST(arrdDrop, ShouldBeAbleToReturnADifferentCapacityArray) {
  arrd8_t<int16_t> a = {{0,1,2,3,4,5},6};
  arrd4_t<int16_t> b = drop<arrd4_t>(a, 3);
  EXPECT_EQ(b[0],3);
  EXPECT_EQ(b[1],4);
  EXPECT_EQ(b[2],5);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 0);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a.len, 6);
}

TEST(takeWhile, ShouldTakeTheCorrectValues) {
  arrd8_t<int16_t> a = {{3,2,1,0,-1,-2,3},7};
  arrd8_t<int16_t> b = takeWhile(isPositive, a);
  EXPECT_EQ(b[0], 3);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 1);
  EXPECT_EQ(b[3], 0);
  EXPECT_EQ(b.len, 4);

  //And not mutate args
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 1);
  EXPECT_EQ(a[3], 0);
  EXPECT_EQ(a[4], -1);
  EXPECT_EQ(a[5], -2);
  EXPECT_EQ(a[6], 3);
  EXPECT_EQ(a.len, 7);
}

TEST(takeWhile, ShouldReturnAnIdenticalArrayIfAllMatch) {
  arrd8_t<int16_t> a = {{3,2,1,0},4};
  arrd8_t<int16_t> b = takeWhile(isPositive, a);
  EXPECT_EQ(b[0], 3);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 1);
  EXPECT_EQ(b[3], 0);
  EXPECT_EQ(b.len, 4);

  //And not mutate args
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 1);
  EXPECT_EQ(a[3], 0);
  EXPECT_EQ(a.len, 4);
}

TEST(takeWhile, ShouldReturnAnEmptyArrayIfTheFirstValueDoesntMatch) {
  arrd8_t<int16_t> a = {{-3,2,1,0},4};
  arrd8_t<int16_t> b = takeWhile(isPositive, a);
  EXPECT_EQ(b.len, 0);

  //And not mutate args
  EXPECT_EQ(a[0], -3);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 1);
  EXPECT_EQ(a[3], 0);
  EXPECT_EQ(a.len, 4);
}

TEST(takeWhile, ShouldBeAbleToReturnADifferentSizedArrd) {
  arrd8_t<int16_t> a = {{3,2,1,0,-1,-2,3},7};
  arrd4_t<int16_t> b = takeWhile<arrd4_t>(isPositive, a);
  EXPECT_EQ(b[0], 3);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 1);
  EXPECT_EQ(b[3], 0);
  EXPECT_EQ(b.len, 4);

  //And not mutate args
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 1);
  EXPECT_EQ(a[3], 0);
  EXPECT_EQ(a[4], -1);
  EXPECT_EQ(a[5], -2);
  EXPECT_EQ(a[6], 3);
  EXPECT_EQ(a.len, 7);
}

TEST(dropWhile, ShouldDropTheCorrectValues) {
  arrd8_t<int16_t> a = {{3,2,1,0,-1,-2,3},7};
  arrd8_t<int16_t> b = dropWhile(isPositive, a);
  EXPECT_EQ(b[0], -1);
  EXPECT_EQ(b[1], -2);
  EXPECT_EQ(b[2], 3);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 1);
  EXPECT_EQ(a[3], 0);
  EXPECT_EQ(a[4], -1);
  EXPECT_EQ(a[5], -2);
  EXPECT_EQ(a[6], 3);
  EXPECT_EQ(a.len, 7);
}

TEST(dropWhile, ShouldReturnAnEmptyArrayIfAllMatch) {
  arrd8_t<int16_t> a = {{4,3,2,1},4};
  arrd8_t<int16_t> b = dropWhile(isPositive, a);
  EXPECT_EQ(b.len, 0);

  //And not mutate args
  EXPECT_EQ(a[0], 4);
  EXPECT_EQ(a[1], 3);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 1);
  EXPECT_EQ(a.len, 4);
}

TEST(dropWhile, ShouldReturnTheSameArrayIfAllValuesDoNotMatch) {
  arrd8_t<int16_t> a = {{-3,-2,-1,0},4};
  arrd8_t<int16_t> b = dropWhile(isPositive, a);
  EXPECT_EQ(b[0], -3);
  EXPECT_EQ(b[1], -2);
  EXPECT_EQ(b[2], -1);
  EXPECT_EQ(b[3], -0);
  EXPECT_EQ(b.len, 4);

  //And not mutate args
  EXPECT_EQ(a[0], -3);
  EXPECT_EQ(a[1], -2);
  EXPECT_EQ(a[2], -1);
  EXPECT_EQ(a[3], 0);
  EXPECT_EQ(a.len, 4);
}

TEST(dropWhile, ShouldBeAbleToReturnADifferentSizeedArrd) {
  arrd8_t<int16_t> a = {{3,2,1,0,-1,-2,3},7};
  arrd4_t<int16_t> b = dropWhile<arrd4_t>(isPositive, a);
  EXPECT_EQ(b[0], -1);
  EXPECT_EQ(b[1], -2);
  EXPECT_EQ(b[2], 3);
  EXPECT_EQ(b.len, 3);

  //And not mutate args
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 1);
  EXPECT_EQ(a[3], 0);
  EXPECT_EQ(a[4], -1);
  EXPECT_EQ(a[5], -2);
  EXPECT_EQ(a[6], 3);
  EXPECT_EQ(a.len, 7);
}
