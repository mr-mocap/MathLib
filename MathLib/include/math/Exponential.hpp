#pragma once


/** @file
 *  
 *  @hideincludegraph
 */

/** @addtogroup Exponential
 * 
 *  @{
 *  
 *  Create the exponential form of the input
 *  
 */

/** @name General Template Case
 *  
 *  @{
 */

/**  Computes the exponential of the input
 * 
 *   @note This will just call @c input.exp()
 */
template<class T>
constexpr T exp(T input)
{
    return input.exp();
}
/// @}

/** @name Specializations
 * 
 *  These are the basic default template specializations for @c exp()
 *  from above
 */
/// @{
template<>
constexpr float exp<float>(float input)
{
    return std::exp(input);
}

template<>
constexpr double exp<double>(double input)
{
    return std::exp(input);
}

template<>
constexpr long double exp<long double>(long double input)
{
    return std::exp(input);
}
/// @}

/// @}
