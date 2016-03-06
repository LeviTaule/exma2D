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

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <type_traits>
#include "vendor/degrad/degrad.h"

/// @file

namespace exma {

/// @brief Definitions of common 2D vector operations
/// @details These functions work on any vector class which has public
/// **x** and **y** members, and can be initialized via argument list.
/// For instance:
/// @code
/// struct VectorF
/// {
///     float x, y;
/// };
/// @endcode

namespace vector {

/// @brief Creates a vector from addition of two vectors
///
/// @param a_vector
/// @param b_vector
///
/// @return
/// A copy of the two vectors added
template<typename T, typename>
constexpr T operator+(const T a_vector, const T b_vector);

/// @brief Creates a vector from subtraction of two vectors
///
/// @param a_vector
/// @param b_vector
///
/// @return
/// A copy of the two vectors subtracted
template<typename T, typename>
constexpr T operator-(const T a_vector, const T b_vector);

/// @brief Creates a vector of the same direction as **vector**, but 
/// **factor** times longer.
///
/// @param vector
/// @param factor
/// *Must be of an arithmetic (an integer or a floating-point number) type.*
/// Decides how many times longer should be the returned vector. For instance, 
/// 1.1 means that the returned vector will be of 110% length than the 
/// **vector** passed in. 
/// @return
/// A copy of the vector with the altered length
template <typename T, typename N, typename, typename, typename>
constexpr T operator*(const T vector, const N factor);

/// @brief Creates a vector of the same direction as **vector**, but 
/// **factor** times longer.
///
/// @param vector
/// @param factor
/// *Must be of an arithmetic (an integer or a floating-point number) type.*
/// Decides how many times longer should be the returned vector. For instance, 
/// 1.1 means that the returned vector will be of 110% length than the 
/// **vector** passed in. 
/// @return
/// A copy of the vector with the altered length
template <typename N, typename T, typename, typename, typename>
constexpr T operator*(const N factor, const T vector);

/// @brief Creates a vector of the same direction as **vector**, but 
/// **factor** times shorter.
///
/// @param vector
/// @param factor
/// *Must be of an arithmetic (an integer or a floating-point number) type.*
/// Decides how many times shorter should be the returned vector. For instance, 
/// 2 means that the returned vector will be of 50% length than the 
/// **vector** passed in. 
/// @return
/// A copy of the vector with the altered length
template <typename T, typename N, typename, typename, typename>
constexpr T operator/(const T vector, const N factor);

/// @brief Answers if the vectors have the same components
/// @details
/// The tolerance for the component comparison is 
/// `std::numeric_limits<T>::epsilon() * 10`
/// @param a_vector
/// @param b_vector
///
/// @return
/// `true` if the vectors have the same values (with some tolerance),
/// `false` otherwise
template<typename T, typename>
constexpr bool operator==(const T a_vector, const T b_vector);

/// @brief Answers if the vectors have the same components
/// @details
/// The tolerance for the component comparison is 
/// `std::numeric_limits<T>::epsilon() * 10`
/// @param a_vector
/// @param b_vector
///
/// @return
/// `true` if the vectors have the same values (with some tolerance),
/// `false` otherwise
template<typename T, typename>
constexpr bool operator!=(const T a_vector, const T b_vector);

/// @brief Creates a reversed vector
/// @details
/// Multiplies both **x** and **y** component of a vector by -1
///
/// @param vector
/// Vector to reverse
///
/// @return
/// A copy of the reversed vector
template<typename T, typename>
constexpr T operator-(const T vector);

/// @brief Creates a perpendicular vector
/// @details
/// Vectors **a** and **b** are perpendicular if their inner angle is exactly 
/// 90 degrees. To each vector there exist 2 vectors which are perpendicular 
/// to it. One of those has **x** component reversed, the other one has 
/// reversed **y** component. This function always returns the former one.
///
/// @param vector
/// Vector to create the perpendicular vector to
///
/// @return
/// A copy of the reversed vector
template<typename T, typename>
constexpr T perpendicule(const T vector);

/// @brief Finds out the **dot**(**scalar**) product
///
/// @param a_vector
/// @param b_vector
///
/// @return
/// The dot product of **a_vector** and **b_vector**
template <typename T, typename, typename>
constexpr auto dot(const T a_vector, const T b_vector);

/// @brief Finds out the **cross**(**exterior**) product
///
/// @param a_vector
/// @param b_vector
///
/// @return
/// The cross product of **a_vector** and **b_vector**
template <typename T, typename, typename>
constexpr auto cross(const T a_vector, const T b_vector);

/// @brief Finds out the squared length of the vector
/// @details
/// *This function does not check for under/overflows.*\n
/// If you don't need to know the exact length of the vector, but you only 
/// care about, let's say, how the vectors' length compare to each other, it's 
/// better to use this function than len(), as it is more efficient.
///
/// @param vector
///
/// @return
/// The length of the vector to the power of 2
template <typename T, typename, typename>
constexpr auto len2(const T vector);

/// @brief Finds out the length of the vector
/// @details
/// *This function does not check for under/overflows. If you do need such 
/// thing, check out `std::hypot()` for that purpose.* \n
/// This function calls costly `std::sqrt()`, so if you don't care about the 
/// actual length, see len2(). Note that due to the usage of `std::sqrt()`
/// this function may not be `constexpr`.
///
/// @param vector
///
/// @return
/// The length of the vector
template <typename T, typename, typename>
auto len(const T vector);

/// @brief Finds out the distance between the vectors
/// @details
/// Note that due to the usage of len() (which calls `std::sqrt()`) this 
/// function may not be `constexpr`.
/// @param a_vector
/// @param b_vector
///
/// @return
/// The distance between the two vectors
template <typename T, typename, typename>
auto distance(const T a_vector, const T b_vector);

/// @brief Creates a new vector of unit length and the same direction as 
/// **vector**
/// @details
/// Note that due to the usage of len() (which calls `std::sqrt()`) this 
/// function may not be `constexpr`.
///
/// @param vector
///
/// @return
/// A copy of a **vector** of unit length
template <typename T, typename, typename, typename, typename>
T normalize(const T vector);

/// @brief Creates a projection of **vector** on **axis**
///
/// @param vector
/// @param axis
///
/// @return
/// A copy of **vector** projection
template <typename T, typename, typename, typename, typename>
constexpr T project(const T vector, const T axis);

/// @brief Creates a projection of **vector** on *unit **axis** vector*
///
/// @param vector
/// @param axis
///
/// @return
/// A copy of **vector** projection
template <typename T, typename, typename>
constexpr T projectN(const T vector, const T axis);

/// @brief Creates a reflection of **vector** on **axis** vector
///
/// @param vector
/// @param axis
/// Must be a unit vector
///
/// @return
/// A copy of **vector** reflection
template <typename T, typename, typename>
constexpr T reflect(const T vector, const T axis);

/// @brief Creates a reflection of **vector** on *unit **axis** vector*
///
/// @param vector
/// @param axis
/// Must be a unit vector
///
/// @return
/// A copy of **vector** reflection
template <typename T, typename, typename>
constexpr T reflectN(const T vector, const T axis);

/// @brief Creates a rotated vector from **vector** around **origin**
/// @details
/// The **vector** is rotated about the **origin** by **angle** in clock-wise 
/// order\n
/// Note that due to the usage of `std::cos()` and `std::sin()` this 
/// function may not be `constexpr`.
///
/// @param vector
/// @param origin
/// The point to rotate the vector around
/// @param angle
/// Angle by which **vector** is rotated
///
/// @return
/// A copy of rotated **vector**
template <typename T, typename, typename>
T rotate(const T vector, const T origin, Radians angle);

}
}

#include "impl/vector2D.cpp"

#endif
