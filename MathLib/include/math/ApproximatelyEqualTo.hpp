#pragma once

#include <cmath>

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

/** @addtogroup Comparison
 * 
 *  @{
 *  
 *  Compare two values for equality, less-than, or greater-than with a tolerance
 *  
 *  @param left      The left value to compare
 *  @param right     The right value to compare
 *  @param tolerance The minimum value for being considered equal
 * 
 *  @return @c 0 if the two are equal within @c tolerance , @c -1 if @c left < @c right , @c 1 if @c left > @c right
 * 
 *  @note This is similar to the three-way comparison operator (<=>), but with a tolerance for equality
 */
inline int three_way_compare(float left, float right, float tolerance = 0.0002f)
{
    if ( approximately_equal_to(left, right, tolerance) )
        return 0;

    return (left < right) ? -1 : 1;
}

inline int three_way_compare(double left, double right, double tolerance = 0.0002)
{
    if ( approximately_equal_to(left, right, tolerance) )
        return 0;

    return (left < right) ? -1 : 1;
}

inline int three_way_compare(long double left, long double right, long double tolerance = 0.0002l)
{
    if ( approximately_equal_to(left, right, tolerance) )
        return 0;

    return (left < right) ? -1 : 1;
}
/// @}

}