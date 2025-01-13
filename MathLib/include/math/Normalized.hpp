#pragma once


/** @file
 *  
 *  @hideincludegraph
 */

namespace Math
{

/** @addtogroup Normalized
 * 
 *  @{
 *  
 *  Normalize the input
 *  
 */

/** @name General Template Case
 *  
 *  @{
 */

/**  Computes the normalized value of the input
 * 
 *   @note This will just call @c input.normalized()
 */
template<class T>
constexpr T normalized(T input)
{
    return input.normalized();
}
/// @}

/// @}

}