#pragma once

#include <cassert>
#include <cmath>
#include <numbers>

/** @file
 *  
 *  @hideincludegraph
 */


template <class T>
inline T unnormalized_sinc(T radians)
{
    if ( radians == T{0} )
        return T{1};
    else
        return sin(radians) / radians;
}

template <class T>
inline T normalized_sinc(T radians)
{
    if ( radians == T{0} )
        return T{1};
    else
        return sin( std::numbers::pi_v<T> * radians) / (std::numbers::pi_v<T> * radians);
}
