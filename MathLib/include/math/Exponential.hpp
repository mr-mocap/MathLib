#pragma once


/** @file
 *  
 *  @hideincludegraph
 */

namespace Math
{

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
/// @}  {Log}

}