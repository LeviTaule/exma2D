# ExMa2D (C++14 library)

ExMa2D is a tiny **ex**ternal **ma**th library for **2D**.

## Features

### no dependencies you have to take care about

We internally use [cppDegRag](https://github.com/grahamboree/cppDegRad) for 
user-defined literals of angles. Also, for tests we use 
[MosquitoNet](https://github.com/simon-bourne/MosquitoNet).

Both of these are 
header-only and they are present in the repo as submodules, so you don't have 
to explicitly take care of them.

### header-only

Yes, it takes a bit of compile-time, but that's the price for templates. It's 
easier to set up the library as well!

### templated help functions for your 2D vector class

These functions work on any vector class which has public `x` and `y` members, 
and can be initialized via argument list. For instance:

```cpp
struct VectorF
{
    float x, y;
};
```

## Example
```cpp
#include "exma2D/vector2D.hpp"
using namespace exma::vector;

struct VectorF
{
    float x, y;
};

constexpr VectorF vec{2.f, 5.f};
constexpr VectorF origin{0.f, 0.f};

constexpr auto crazy = -perpendicule(vec)
constexpr auto silly = project(crazy, vec) * 3;
constexpr auto crazy_silly = reflect(crazy, silly);
constexpr auto go_round = rotate(crazy_silly, origin, 180_deg);

auto length = len(go_round);
constexpr auto dot_product = dot(crazy, silly);
```

## Requirements

* C++14 compiler 

Tested with g++ 5.2.1 and clang 3.6.2
## License

ExMa2D is licensed under 
[zlib/libpng](http://opensource.org/licenses/zlib-license.php). You can use it 
in your projects, no matter whether they are free, commercial, open-source or 
closed-sourced.

It would be nice if you mentioned somewhere in your project description or 
documentation (or anywhere else) that you're using ExMa2D, but you're not 
legally obliged to do so.