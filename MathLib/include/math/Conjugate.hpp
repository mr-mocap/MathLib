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

/** @name General Template Case
 *  
 *  @{
 */

/**  Computes the conjugate of the input
 * 
 *   @note This will just call @c input.conjugate()
 */
template<class T>
constexpr T conjugate(T input)
{
    return input.conjugate();
}
/// @}

/** @name Specializations
 * 
 *  These are the basic default template specializations for @c conjugate()
 *  from above
 */
/// @{
template<>
constexpr float conjugate<float>(float input)
{
    return -input;
}

template<>
constexpr double conjugate<double>(double input)
{
    return -input;
}

template<>
constexpr long double conjugate<long double>(long double input)
{
    return -input;
}
/// @}

/// @}

}