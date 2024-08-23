#pragma once

#include <numbers>


/** @file
 *  
 */


/** @addtogroup Conversions
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
/// @}

constexpr float operator ""_deg_f(long double degrees)
{
    return DegreesToRadians( static_cast<float>(degrees) );
}

constexpr double operator ""_deg(long double degrees)
{
    return DegreesToRadians( static_cast<double>(degrees) );
}

constexpr long double operator ""_deg_ld(long double degrees)
{
    return DegreesToRadians(degrees);
}