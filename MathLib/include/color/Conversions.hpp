#pragma once

#include "color/Types.hpp"
#include "math/ApproximatelyEqualTo.hpp"
#include "math/Vector3D.hpp"
#include "math/Functions.hpp"
#include <concepts>
#include <limits>
#include <type_traits>
#include <cmath>


namespace Color
{

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
    if ( Math::approximately_equal_to( cmax, cmin ) )
        return HSV<T>{ Math::Degree<T>(), T{}, v};

    // Saturation
    if ( Math::approximately_equal_to( v, T{} ) )
        saturation = T{};
    else if ( Math::approximately_equal_to( delta, T{} ) )
        saturation = T{};
    else
        saturation = delta / cmax;

    T rc = ( cmax - input.red() ) / delta;
    T gc = ( cmax - input.green() ) / delta;
    T bc = ( cmax - input.blue() ) / delta;
    T hue;

    // Hue
    if ( Math::approximately_equal_to( input.red(), cmax ) )
        hue = T{0.0} + bc - gc;
    else if ( Math::approximately_equal_to( input.green(), cmax ) )
        hue = T{2.0} + rc - bc;
    else
        hue = T{4.0} + gc - rc;

    // Let hue be possibly negative
    hue = std::fmod( hue / T{6.0}, T{1.0} );

    // But make hue be 0 - 360 upon return...
    return HSV<T>{ Math::Degree<T>(hue * Math::Degree<T>::modulus()).modulo(), saturation, v };
}

template <std::floating_point T>
UnitRGB<T> ToRGB(const HSV<T> &input_hsv)
{
    T h = std::fmod( T{100.0} + input_hsv.hue().value(), T{1.0} );
    T hue_slice = T{6.0} * h;
    T hue_slice_integer = std::floor( hue_slice );
    T hue_slice_interpolant = hue_slice - hue_slice_integer;

    Math::Vector3D<T> temp_rgb{ input_hsv.value() * (T{1.0} - input_hsv.saturation()),
                                input_hsv.value() * (T{1.0} - input_hsv.saturation() * hue_slice_interpolant),
                                input_hsv.value() * (T{1.0} - input_hsv.saturation() * (T{1.0} - hue_slice_interpolant))};

    T is_odd_slice = std::fmod( hue_slice_integer, T{2.0} );
    T three_slice_selector = T{0.5} * (hue_slice_integer - is_odd_slice);
    
    Math::Vector3D<T> scrolling_rgb_for_even_slices{ input_hsv.value(), temp_rgb.z(), temp_rgb.x() };
    Math::Vector3D<T> scrolling_rgb_for_odd_slices{ temp_rgb.y(), input_hsv.value(), temp_rgb.x() };
    Math::Vector3D<T> scrolling_rgb{};

    //T is_not_first_slice = ;
    //T is_not_second_slice = ;

    return UnitRGB<T>{ };
}

}