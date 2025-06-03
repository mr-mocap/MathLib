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
inline bool approximately_equal_to(float input, float near_to, float tolerance = 0.0002f)
{
    return std::abs(near_to - input) <= tolerance;
}

inline bool approximately_equal_to(double input, double near_to, double tolerance = 0.0002)
{
    return std::abs(near_to - input) <= tolerance;
}

inline bool approximately_equal_to(long double input, long double near_to, long double tolerance = 0.0002l)
{
    return std::abs(near_to - input) <= tolerance;
}
/// @}

}