#pragma once

#include "math/ApproximatelyEqualTo.hpp"
#include <format>
#include <iostream>

/** @file
 *  
 *  @hideincludegraph
 */

namespace Math
{

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
        std::cout << std::format("input: {:.6} is not equal to near_to: {:.6} within tolerance: {:.6}.  Difference is {:.6}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_equal(double input, double near_to, double tolerance = 0.0002)
{
    if (!approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {:.6} is not equal to near_to: {:.6} within tolerance: {:.6}.  Difference is {:.6}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_equal(long double input, long double near_to, long double tolerance = 0.0002l)
{
    if (!approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {:.6} is not equal to near_to: {:.6} within tolerance: {:.6}.  Difference is {:.6}.", input, near_to, tolerance, near_to - input) << std::endl;
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
        std::cout << std::format("input: {:.6} is not equal to near_to: {:.6} within tolerance: {:.6}.  Difference is {:.6}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_not_equal(double input, double near_to, double tolerance = 0.0002)
{
    if (approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {:.6} is not equal to near_to: {:.6} within tolerance: {:.6}.  Difference is {:.6}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}

inline bool check_if_not_equal(long double input, long double near_to, long double tolerance = 0.0002l)
{
    if (approximately_equal_to(input, near_to, tolerance))
    {
        std::cout << std::format("input: {:.6} is not equal to near_to: {:.6} within tolerance: {:.6}.  Difference is {:.6}.", input, near_to, tolerance, near_to - input) << std::endl;
        return  false;
    }
    return true;
}
/// @}

inline void CHECK_IF_EQUAL(float input, float near_to, float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_EQUAL(double input, double near_to, double tolerance = 0.0002)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_EQUAL(long double input, long double near_to, long double tolerance = 0.0002l)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_NOT_EQUAL(float input, float near_to, float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_NOT_EQUAL(double input, double near_to, double tolerance = 0.0002)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_NOT_EQUAL(long double input, long double near_to, long double tolerance = 0.0002l)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

inline void CHECK_IF_ZERO(float input, float tolerance = 0.0002f)
{
    assert( check_if_equal(input, 0.0f, tolerance) );
}

inline void CHECK_IF_ZERO(double input, double tolerance = 0.0002)
{
    assert( check_if_equal(input, 0.0, tolerance) );
}

inline void CHECK_IF_ZERO(long double input, long double tolerance = 0.0002l)
{
    assert( check_if_equal(input, 0.0l, tolerance) );
}

}