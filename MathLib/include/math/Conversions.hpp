#pragma once

#include <numbers>


/** @file
 *  
 */


/** Convert degrees to radians
 */
template <class T>
constexpr inline T DegreesToRadians(T degrees)
{
    return degrees * (T{std::numbers::pi} / T{180});
}

/** Convert radians to degrees
 */
template <class T>
constexpr inline T RadiansToDegrees(T radians)
{
    return radians * (T{180} / T{std::numbers::pi});
}
