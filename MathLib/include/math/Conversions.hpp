#pragma once

#include <numbers>
#include <concepts>


/** @file
 *  
 *  @hideincludegraph
 */

namespace Math
{

/** @addtogroup Conversions
 * 
 *  Various ways to convert data from one measurement to another
 * 
 *  @{
 */
/// Convert degrees to radians
template <std::floating_point T>
constexpr inline T DegreesToRadians(T degrees)
{
    return degrees * (std::numbers::pi_v<T> / T{180});
}

/// Convert radians to degrees
template <std::floating_point T>
constexpr inline T RadiansToDegrees(T radians)
{
    return radians * (T{180} / std::numbers::pi_v<T>);
}
/// @}

}