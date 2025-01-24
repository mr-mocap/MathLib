#pragma once

#include <cmath>
#include <concepts>


/** @file
 *  
 *  @hideincludegraph
 */

namespace Math
{

/** @addtogroup Equality
 * 
 *  @{
 *  
 *  Compare two values for equality with a tolerance
 *  
 *  @param input     The first value to compare
 *  @param near_to   The second value to compare
 *  @param tolerance The minimum value for being considered equal
 * 
 *  @return @c true if the two are equal within @c tolerance , @c false otherwise
 */
template <std::floating_point Type>
inline bool approximately_equal_to(Type input, Type near_to, float tolerance = 0.0002f)
{
    return std::abs(near_to - input) <= tolerance;
}
/// @}

}