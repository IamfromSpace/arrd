#ARRD

arrd (as in arr[ay]d[ynamic] and arrd[uino]) is a lightweight and flexible library that is meant to bring dynamic arrays and functional programming to arduino (or other targets) without being overly expensive.

###Goals

#####Stay on the stack
Arrd does not use malloc, so there is (usually) no need to free or delete.  Ideally, a couple Arrds can be initialized as buffers on the heap, and then the rest can live as local variables.  The great thing about local variables is that they are immediately destroyed once the function call ends--no deletion needed and no risk of a fragmented heap.

#####Intuitive Sizing
Arrds are created in the form `arrd${power of two}_t` much like types `uint16_t` and `int32_t`.  This lets you fine-tune memory usage in familiar ways.  `arrd16_t` holds a maximum of 16 elements.  Also, when using concat, you can easily know which array size to jump to to ensure no undefined behavior.  For example, assigning to a `arrd16_t` when concat two `arrd8_t` guarantees all items can be contained.

As an added benefit of using powers of two, we can cheaply push, unshift, and protect from worst case undefined behaviors.  Arrds have a variable `start` member which determines what member of their internal array should be considered element 0.  Also if try to access an index that is outside of the bounds of the array, the arrd with return `arrd[index % capacity]`.  While this is still undefined behavior, it prevents catastrophic assignments.  `%` is normally expensive, but not when using powers of two.

#####Be Functional
Arrds themselves offer very few methods.  Instead, the arrd namespace includes a number of high-order functions which will be familiar to functional programmers.  These are all expressed in templates, making these functions incredibly flexible.  As an example:

```c++
int square(int a) {
  return a * a;
}

arrd4_t<int> a = {{1, 2, 3}, 3}
aarrd4_t<int> b = arrd::map(square, a); //b is {{1, 4, 9}, 3};
```

In `arrd::map` simplest use case it accepts a function (which must accept and return a type, in this case int) and an arrd.  It returns a new arrd, where each value of the array has passed through the function.  So `[1 => 1, 2 => 4, 3 => 9]`.

We can then nest these functions together:

```c++
arrd4_t<int> a = {{1, 2, 3}, 3}
aarrd4_t<int> b = arrd::map(square, arrd::map(square, a)); //b is {{1, 16, 81}, 3};
```

While maybe not as efficient as `arrd::map(toTheFourth, a)` this shows how these functions can be chained together to create powerful data transforms.

Since arrd::map and others are highly templatized, you can be sure that you can use any types.

```c++
SomeCrazyType a = ...
arrd8_t<SomeCrazyType> b = ...

SomeOtherCrazyType someCrazyFunction(someCrazyType) { ... }

arrd8_t<SomeOtherCrazyType> c = arrd::map(someCrazyFunction, b);
```

###Installing
Simply place the `arrd.h` file into your libraries and add `#include "arrd.h"` to your sketch/project.  To use functions directly instead of namespacing, just add the line `using namespace arrd;`.

###Running Tests
Tests are run using [Google Test](https://github.com/google/googletest).  This library needs to be downloaded and built, and then added to your default include/lib locations.  Please check their readme for details.

Once that is complete, you can run `make test` from this root directory to run all tests.

###Running Perf
This library has some performance tests to guide design decisions.  To run these, you'll need [hayai](https://github.com/nickbruun/hayai).  Currently this assumes you have the source code in a peer folder to arrd.  With that project built (you can do this via cmake, see hayai's README), you can run the performance tests via `make perf`.
