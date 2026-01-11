#pragma once

#include <Math/math/Vector3D.hpp>
#include <cstdlib>
#include <numbers>

/** @file
 *  
 *  Defines various palette functions
 *
 *  @hideincludegraph
 */

namespace Color
{

/** Generate a continuous color gradient
 *   
 *   @param t 
 *   @param a 
 *   @param b 
 *   @param c 
 *   @param d 
 * 
 *   @return vec3 
 * 
 *   @note Borrowed from: https://iquilezles.org/articles/palettes/
 */
template <std::floating_point T>
Math::BasicVector3D<T> palette(T t,
                               Math::BasicVector3D<T> a,
                               Math::BasicVector3D<T> b,
                               Math::BasicVector3D<T> c,
                               Math::BasicVector3D<T> d)
{
    return a + b * std::cos( 2 * std::numbers::pi_v<T> * (c * t + d) );
}

}