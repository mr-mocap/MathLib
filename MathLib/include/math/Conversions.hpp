#pragma once

#include <numbers>


/** @file
 *  
 *  @hideincludegraph
 */


/** @addtogroup Conversions
 * 
 *  Various ways to convert data from one measurement to another
 * 
 *  @{
 */
/// Convert degrees to radians
template <class T>
constexpr inline T DegreesToRadians(T degrees)
{
    return degrees * (T{std::numbers::pi} / T{180});
}

/// Convert radians to degrees
template <class T>
constexpr inline T RadiansToDegrees(T radians)
{
    return radians * (T{180} / T{std::numbers::pi});
}

/** @addtogroup UserDefinedLiterals User-Defined Literals
 * 
 *  @{
 */
/// Converts to radians and returns a float
constexpr float operator ""_deg_f(long double degrees)
{
    return DegreesToRadians( static_cast<float>(degrees) );
}

/// Converts to radians and returns a double
constexpr double operator ""_deg(long double degrees)
{
    return DegreesToRadians( static_cast<double>(degrees) );
}

/// Converts to radians and returns a long double
constexpr long double operator ""_deg_ld(long double degrees)
{
    return DegreesToRadians(degrees);
}
/// @}

/// @}