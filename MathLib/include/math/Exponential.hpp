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
T exp(T input)
{
    return input.exp();
}
/// @}  {General Template Case}

/** @name Specializations
 * 
 *  These are the basic default template specializations for @c exp()
 *  from above
 */
/// @{
template<>
float exp<float>(float input)
{
    return std::exp(input);
}

template<>
double exp<double>(double input)
{
    return std::exp(input);
}

template<>
long double exp<long double>(long double input)
{
    return std::exp(input);
}
/// @}  {Specializations}
/// @}  {Exponential}


/** @addtogroup Log
 * 
 *  @{
 *  
 *  Create the log form of the input
 *  
 */

/** @name General Template Case
 *  
 *  @{
 */

/**  Computes the log of the input
 * 
 *   @note This will just call @c input.log()
 */
template<class T>
T log(T input)
{
    return input.log();
}
/// @}  {General Template Case}

/** @name Specializations
 * 
 *  These are the basic default template specializations for @c log()
 *  from above
 */
/// @{
template<>
float log<float>(float input)
{
    return std::log(input);
}

template<>
double log<double>(double input)
{
    return std::log(input);
}

template<>
long double log<long double>(long double input)
{
    return std::log(input);
}
/// @}  {Specializations}
/// @}  {Log}
