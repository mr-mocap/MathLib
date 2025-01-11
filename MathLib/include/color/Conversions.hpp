#pragma once

#include "color/Types.hpp"
#include "math/ApproximatelyEqualTo.hpp"
#include <concepts>
#include <limits>
#include <type_traits>
#include <cmath>


template <std::integral T, class OT = float>
constexpr UnitRGB<OT> normalized(const RGB<T> &input)
{
    const OT max_value = std::numeric_limits<T>::max;

    return UnitRGB<OT>{ input.red() / max_value, input.green() / max_value, input.blue() / max_value };
}

template <class T>
constexpr T min(const RGB<T> &input)
{
    if constexpr ( std::is_floating_point_v<T> )
        return std::fmin( std::fmin( input.red(), input.green() ), input.blue() );
    else if constexpr ( std::is_integral_v<T> )
        return std::min( std::min( input.red(), input.green() ), input.blue() );
    else
        static_assert( false, "Must be either integer or floating-point type");
}

template <class T>
constexpr T min(const UnitRGB<T> &input)
{
    return std::fmin( std::fmin( input.red(), input.green() ), input.blue() );
}

template <class T>
constexpr T max(const RGB<T> &input)
{
    if constexpr ( std::is_floating_point_v<T> )
        return std::fmax( std::fmax( input.red(), input.green() ), input.blue() );
    else if constexpr ( std::is_integral_v<T> )
        return std::max( std::max( input.red(), input.green() ), input.blue() );
    else
        static_assert( false, "Must be either integer or floating-point type");
}

template <class T>
constexpr T max(const UnitRGB<T> &input)
{
    return std::fmax( std::fmax( input.red(), input.green() ), input.blue() );
}

template <std::floating_point T>
HSV<T> ToHSV(const UnitRGB<T> &input)
{
    assert( input.isNormalized() );

    T cmax = max( input );
    T cmin = min( input );
    T delta = cmax - cmin;

    T v = cmax;

    T saturation;

    // When delta is zero, avoid dividing by delta (0)
    if ( approximately_equal_to( cmax, cmin ) )
        return HSV<T>{ Degree<T>(), T{}, v};

    // Saturation
    if ( approximately_equal_to( v, T{} ) )
        saturation = T{};
    else if ( approximately_equal_to( delta, T{} ) )
        saturation = T{};
    else
        saturation = delta / cmax;

    T rc = ( cmax - input.red() ) / delta;
    T gc = ( cmax - input.green() ) / delta;
    T bc = ( cmax - input.blue() ) / delta;
    T hue;

    // Hue
    if ( approximately_equal_to( input.red(), cmax ) )
        hue = T{0.0} + bc - gc;
    else if ( approximately_equal_to( input.green(), cmax ) )
        hue = T{2.0} + rc - bc;
    else
        hue = T{4.0} + gc - rc;

    // Let hue be possibly negative
    hue = std::fmod( hue / T{6.0}, T{1.0} );

    // But make hue be 0 - 360 upon return...
    return HSV<T>{ Degree<T>(hue * Degree<T>::modulus()).modulo(), saturation, v };
}