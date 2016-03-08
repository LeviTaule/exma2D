////////////////////////////////////////////////////////////////////////////////
//
// ExMa2D - tiny EXternal MAth library for 2D
// Copyright (c) 2016 Levi Taule
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UTILS_CPP
#define UTILS_CPP

#include <type_traits>
#include <limits>

namespace exma { namespace utils {

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<T>::value>>
constexpr T abs (T number)
{
    if(number < 0)
        return -number;
    else
        return number;
};

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<T>::value>>
constexpr bool compare (T a, T b)
{
    // Due to the usage trigonometric functions, it seems, we must be 10 times 
    // as tolerant as usually.
    // So I decided we will be good people and raised the tolerance 10 times.
    if(abs(a-b) <=  std::numeric_limits<T>::epsilon() * 10)
        return true;
    return false;
};

}}

#endif