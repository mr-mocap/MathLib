#pragma once

#include <tuple>

/** @file
 *  
 */

/** @addtogroup Triple
 * 
 *  @{
 *  
 *  A simple 3-tuple type
 */
template <class T>
using triple = std::tuple<T, T, T>;


/// Create a triple from 3 individual components
template <class T>
constexpr triple<T> make_triple(T x, T y, T z)
{
    return std::make_tuple(x, y, z);
}
/// @}