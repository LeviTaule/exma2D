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

#ifndef VECTOR_CPP
#define VECTOR_CPP
#include <cmath>
#include <limits>
#include <type_traits>
#include "../vector2D.hpp"
#include "../impl/utils.cpp"

namespace exma { namespace vector {

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr T operator+(const T a_vector, const T b_vector)
{
    return{a_vector.x + b_vector.x, a_vector.y + b_vector.y};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr T operator-(const T a_vector, const T b_vector)
{
    return{a_vector.x - b_vector.x, a_vector.y - b_vector.y};
}

template <
  typename N,
  typename T,
  typename = 
std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>,
  typename = typename std::enable_if_t<std::is_arithmetic<N>{}>>
constexpr T operator*(const T vector, const N factor)
{
    return {vector.x * factor, vector.y * factor};
}

template <
  typename T,
  typename N,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>,
  typename = typename std::enable_if_t<std::is_arithmetic<N>{}>>
constexpr T operator*(const N factor, const T vector)
{
    return vector * factor;
}

template <
  typename N,
  typename T,
  typename = 
std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>,
  typename = typename std::enable_if_t<std::is_arithmetic<N>{}>>
constexpr T operator/(const T vector, const N factor)
{
    if(exma::utils::compare(factor, static_cast<N>(0)))
    {
        return
        {
            std::numeric_limits<decltype(std::declval<T>().x)>::quiet_NaN(),
            std::numeric_limits<decltype(std::declval<T>().y)>::quiet_NaN()
        };
    }
    return {vector.x / factor, vector.y / factor};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr bool operator==(const T a_vector, const T b_vector)
{
    return
        exma::utils::compare(a_vector.x, b_vector.x) &&
        exma::utils::compare(a_vector.y, b_vector.y);
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr bool operator!=(const T a_vector, const T b_vector)
{
    return
        !(exma::utils::compare(a_vector.x, b_vector.x) &&
        exma::utils::compare(a_vector.y, b_vector.y));
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr T operator-(const T vector)
{
    return {-vector.x, -vector.y};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr T perpendicule(const T vector)
{
    return {-vector.y, vector.x};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr auto dot(const T a_vector, const T b_vector) ->
decltype(a_vector.x + b_vector.x)
{
    return (a_vector.x * b_vector.x) + (a_vector.y * b_vector.y);
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr auto cross(const T a_vector, const T b_vector) ->
decltype(a_vector.x + b_vector.x)
{
    return (a_vector.x * b_vector.y) - (a_vector.y * b_vector.x);
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr auto len2(const T vector) ->
decltype(vector.x + vector.y)
{
    return dot(vector, vector);
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
auto len(const T vector) ->
decltype(vector.x + vector.y)
{
    return sqrt(len2(vector));
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
auto distance(const T a_vector, const T b_vector) ->
decltype(a_vector.x + a_vector.y + b_vector.x + b_vector.y)
{
    return len(a_vector - b_vector);
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>,
  typename = std::enable_if<
    std::numeric_limits<decltype(std::declval<T>().x)>::has_quiet_NaN>,
  typename = std::enable_if<
    std::numeric_limits<decltype(std::declval<T>().y)>::has_quiet_NaN>>
auto normalize(const T vector) ->
decltype(vector)
{
    auto length = len(vector);
    if(exma::utils::compare(length, 0.f))
    {
        return
        {
            std::numeric_limits<decltype(std::declval<T>().x)>::quiet_NaN(),
            std::numeric_limits<decltype(std::declval<T>().y)>::quiet_NaN()
        };
    }
    else
    {
        return {vector.x / length, vector.y/length};
    }
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>,
  typename = std::enable_if<
    std::numeric_limits<decltype(std::declval<T>().x)>::has_quiet_NaN>,
  typename = std::enable_if<
    std::numeric_limits<decltype(std::declval<T>().y)>::has_quiet_NaN>>
constexpr auto project(const T vector, const T axis) ->
decltype(vector)
{
    if(exma::utils::compare(axis.x, 0.f) && exma::utils::compare(axis.y, 0.f))
        return
        {
            std::numeric_limits<decltype(std::declval<T>().x)>::quiet_NaN(),
            std::numeric_limits<decltype(std::declval<T>().y)>::quiet_NaN()
        };
    auto quantifier = dot(vector, axis) / len2(axis);
    return {axis.x * quantifier, axis.y * quantifier};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr auto projectN(const T vector, const T axis) ->
decltype(vector)
{
    auto quantifier = dot(vector, axis);
    return {axis.x * quantifier, axis.y * quantifier};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>,
  typename = std::enable_if<
    std::numeric_limits<decltype(std::declval<T>().x)>::has_quiet_NaN>,
  typename = std::enable_if<
    std::numeric_limits<decltype(std::declval<T>().y)>::has_quiet_NaN>>
constexpr auto reflect(const T vector, const T axis) ->
decltype(vector)
{
    if(exma::utils::compare(axis.x, 0.f) && exma::utils::compare(axis.y, 0.f))
        return
        {
            std::numeric_limits<decltype(std::declval<T>().x)>::quiet_NaN(),
            std::numeric_limits<decltype(std::declval<T>().y)>::quiet_NaN()
        };
    auto result = project(vector, axis) * 2;
    return {vector.x - result.x, vector.y - result.y};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
constexpr auto reflectN(const T vector, const T axis) ->
decltype(vector)
{
    auto result = projectN(vector, axis) * 2;
    return {vector.x - result.x, vector.y - result.y};
}

template <
  typename T,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().x)>{}>,
  typename = 
    std::enable_if_t<std::is_arithmetic<decltype(std::declval<T>().y)>{}>>
auto rotate(const T vector, const T origin, Radians angle) ->
decltype(vector)
{
    const auto cr = cos(angle.getValue());
    const auto sr = sin(angle.getValue());
    const auto x = origin.x + (
        (vector.x - origin.x) * cr - (vector.y - origin.y) * sr
    );
    const auto y = origin.y + (
        (vector.x - origin.x) * sr + (vector.y - origin.y) * cr
    );
    return {
        static_cast<decltype(std::declval<T>().x)>(x),
        static_cast<decltype(std::declval<T>().y)>(y)
    };
}

}}
#endif
