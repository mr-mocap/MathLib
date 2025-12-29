#pragma once

#include "color/Types.hpp"
#include "math/ApproximatelyEqualTo.hpp"
#include "math/Vector3D.hpp"
#include "math/Vector4D.hpp"
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

#if 1
    T cmax = max( input );
    T cmin = min( input );
    T delta = cmax - cmin;

    T v = cmax;

    T saturation;

    // When delta is zero, avoid dividing by delta (0)
    if ( Math::approximately_equal_to( cmax, cmin ) )
        return HSV<T>{ Math::BasicDegree<T>(), T{}, v};

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
    return HSV<T>{ Math::BasicDegree<T>(hue * Math::BasicDegree<T>::modulus()).modulo(), saturation, v };
#else
    // https://web.archive.org/web/20200207113336/http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
    using namespace Math;

    Vector4D<T> K{ T{0.0}, T{-1.0} / T{3.0}, T{2.0} / T{3.0}, T{-1.0} };
    Vector4D<T> p = (input.g() < input.b()) ? Vector4D<T>{input.b(), input.g(), K.w, K.z} : Vector4D<T>{input.g(), input.b(), K.x, K.y};
    Vector4D<T> q = (input.r() < p.x)       ? Vector4D<T>{p.x, p.y, p.w, input.r()}       : Vector4D<T>{input.r(), p.y, p.z, p.x};

    T d = q.x - std::min(q.w, q.y);
    T e = 1.0e-10;

    return HSV<T>(
                   BasicDegree<T>( std::abs(q.z + (q.w - q.y) / (T{6.0} * d + e)) ) * BasicDegree<T>::modulus(),
                   d / (q.x + e),
                   q.x
                 );
#endif
}

template <std::floating_point T>
UnitRGB<T> ToRGB(const HSV<T> &input_hsv)
{
    // https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
#if 1
    if ( Math::approximately_equal_to( input_hsv.saturation(), T{0} ) )
        return UnitRGB<T>{ input_hsv.value(), input_hsv.value(), input_hsv.value() };

    Math::BasicDegree<T> hh = input_hsv.hue().modulo();

    hh /= T{60.0};

    long i = hh.value();
    T ff = hh.value() - i;
    T p = input_hsv.value() * (T{1.0} - input_hsv.saturation());
    T q = input_hsv.value() * (T{1.0} - (input_hsv.saturation() * ff));
    T t = input_hsv.value() * (T{1.0} - (input_hsv.saturation() * (T{1.0} - ff)));

    UnitRGB<T> out;

    switch ( i )
    {
        case 0:
            out = UnitRGB<T>{ input_hsv.value(), t, p };
            break;
        case 1:
            out = UnitRGB<T>{ q, input_hsv.value(), p };
            break;
        case 2:
            out = UnitRGB<T>{ p, input_hsv.value(), t };
            break;
        case 3:
            out = UnitRGB<T>{ p, q, input_hsv.value() };
            break;
        case 4:
            out = UnitRGB<T>{ t, p, input_hsv.value() };
            break;
        case 5:
        default:
            out = UnitRGB<T>{ input_hsv.value(), p, q };
            break;
    }

    return out;
#else
#if 0
    T h = std::fmod( T{100.0} + input_hsv.hue().value(), T{1.0} );
    T hue_slice = T{6.0} * h;
    T hue_slice_integer = std::floor( hue_slice );
    T hue_slice_interpolant = hue_slice - hue_slice_integer;

    Math::Vector3D<T> temp_rgb{ input_hsv.value() * (T{1.0} - input_hsv.saturation()),
                                input_hsv.value() * (T{1.0} - input_hsv.saturation() * hue_slice_interpolant),
                                input_hsv.value() * (T{1.0} - input_hsv.saturation() * (T{1.0} - hue_slice_interpolant))};

    T is_odd_slice = std::fmod( hue_slice_integer, T{2.0} );
    T three_slice_selector = T{0.5} * (hue_slice_integer - is_odd_slice);
    
    Math::Vector3D<T> scrolling_rgb_for_even_slices{ input_hsv.value(), temp_rgb.z, temp_rgb.x };
    Math::Vector3D<T> scrolling_rgb_for_odd_slices{ temp_rgb.y, input_hsv.value(), temp_rgb.x };
    Math::Vector3D<T> scrolling_rgb{ lerp( scrolling_rgb_for_even_slices, scrolling_rgb_for_odd_slices, is_odd_slice ) };

    T is_not_first_slice = Math::saturate( three_slice_selector, T{0.0}, T{1.0} );
    T is_not_second_slice = Math::saturate( three_slice_selector - T{1.0}, T{0.0}, T{1.0} );

    return Math::lerp( UnitRGB<T>{ scrolling_rgb.x, scrolling_rgb.y, scrolling_rgb.z },
                       Math::lerp( UnitRGB<T>{ scrolling_rgb.z, scrolling_rgb.x, scrolling_rgb.y }, UnitRGB<T>{ scrolling_rgb.y, scrolling_rgb.z, scrolling_rgb.x }, is_not_second_slice ),
                       is_not_first_slice
                     );
#else
    Math::Vector4D<T> K{ T{1.0}, T{2.0} / T{3.0}, T{1.0} / T{3.0}, T{3.0} };

    Math::Vector3D<T> input_xxx{ input_hsv.hue().value(), input_hsv.hue().value(), input_hsv.hue().value() };

    Math::Vector3D<T> p{ Math::abs( Math::fract(input_xxx + K.xyz()) * T{6.0} - K.www() ) };

    Math::Vector3D<T> out{ Math::mix( K.xxx(), Math::saturate( p - K.xxx(), T{0.0}, T{1.0} ), input_hsv.saturation() ) };

    return input_hsv.value() * out;
#endif
#endif
}

template <std::floating_point T>
HSL<T> ToHSL(const HSV<T> &input_hsv)
{
    // https://en.wikipedia.org/wiki/HSL_and_HSV (HSV to HSL)
    // 
    // TODO: Use algorithms from Computer Graphics: Principles and Practice
    T lightness = input_hsv.value() * (T{1.0} - input_hsv.saturation() / T{2.0});
    T saturation;

    if ( approximately_equal_to( lightness, T{0.0} ) || approximately_equal_to( lightness, T{1.0} ) )
        saturation = T{0};
    else
        saturation = (input_hsv.value() - lightness) / std::min(lightness, T{1.0} - lightness);

    return HSL<T>{ input_hsv.value(), saturation, lightness };
}

template <std::floating_point T>
HSV<T> ToHSV(const HSL<T> &input_hsl)
{
    // https://en.wikipedia.org/wiki/HSL_and_HSV (HSV to HSL)
    // 
    // TODO: Use algorithms from Computer Graphics: Principles and Practice
    T value = input_hsl.lightness() + input_hsl.saturation() * std::min(input_hsl.lightness(), T{1.0} - input_hsl.lightness());
    T saturation;

    if ( approximately_equal_to( value, T{0.0} ) )
        saturation = T{0.0};
    else
        saturation = T{2.0} * (T{1.0} - input_hsl.lightness() / value);

    return HSV<T>{ input_hsl.hue(), saturation, value };
}

}