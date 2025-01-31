#pragma once


/** @file
 *  
 *  @hideincludegraph
 */

namespace Math
{

/** @addtogroup Conjugate
 * 
 *  @{
 *  
 *  Create the conjugate of the input
 *  
 */

/** Computes the conjugate of the input
 * 
 *  @param input The value to take the conjugate of
 * 
 *  @return The conjugate of the input
 */
/// @{
constexpr float conjugate(float input)
{
    return -input;
}

constexpr double conjugate(double input)
{
    return -input;
}

constexpr long double conjugate(long double input)
{
    return -input;
}
/// @}

/// @}

}