#pragma once

#include <math/Vector3D.hpp>
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
Vector3Df palette(float t, Vector3Df a, Vector3Df b, Vector3Df c, Vector3Df d)
{
    return a + b * std::cos( 2 * std::pi_v<float> * (c * t + d) );
}

}