#pragma once

#include "math/ApproximatelyEqualTo.hpp"
#include <format>
#include <iostream>

/** @file
 *  
 *  @hideincludegraph
 */


/** @addtogroup Checks
 * 
 *  @{
 *  
 *  Compare two values for equality with a tolerance and prints debug information when false
 *  
 *  @param input     The first value to compare
 *  @param near_to   The second value to compare
 *  @param tolerance The minimum value for being considered equal
 * 
 *  @return @c true if the two are equal within @c tolerance , @c false otherwise
 */
inline bool check_if_equal(float input, float near_to, float tolerance = 0.0002f)
{
    if (!approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_equal(double input, double near_to, float tolerance = 0.0002f)
{
    if (!approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_equal(long double input, long double near_to, float tolerance = 0.0002f)
{
    if (!approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}
/// @}

/** @addtogroup Checks
 * 
 *  @{
 *  
 *  Compare two values for inequality with a tolerance and prints debug information when false
 *  
 *  @param input     The first value to compare
 *  @param near_to   The second value to compare
 *  @param tolerance The minimum value for being considered equal
 * 
 *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
 */
inline bool check_if_not_equal(float input, float near_to, float tolerance = 0.0002f)
{
    if (approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_not_equal(double input, double near_to, float tolerance = 0.0002f)
{
    if (approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_not_equal(long double input, long double near_to, float tolerance = 0.0002f)
{
    if (approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}
/// @}

inline void CHECK_IF_EQUAL(const float input, const float near_to, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_EQUAL(const double input, const double near_to, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_EQUAL(const long double input, const long double near_to, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_NOT_EQUAL(const float input, const float near_to, const float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_NOT_EQUAL(const double input, const double near_to, const float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_NOT_EQUAL(const long double input, const long double near_to, const float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}
