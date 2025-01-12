#pragma once

#include "math/Angle.hpp"
#include <cassert>
#include <limits>
#include <cstdint>
#include <cmath>


namespace Color
{

template <std::integral T>
class BasicRGB
{
public:
    using value_type = T;

    constexpr BasicRGB() = default;
    explicit constexpr BasicRGB(value_type r, value_type g, value_type b) : _red{ r }, _green{ g }, _blue{ b } { }

    static constexpr BasicRGB<T> min()
    {
        const T mn = std::numeric_limits<T>::min();

        return BasicRGB<T>( mn, mn, mn );
    }

    static constexpr BasicRGB<T> max()
    {
        const T mx = std::numeric_limits<T>::max();

        return BasicRGB<T>( mx, mx, mx );
    }

    static constexpr BasicRGB<T> zero() { return BasicRGB<T>(); }

    constexpr value_type red() const { return _red; }
    constexpr value_type green() const { return _green; }
    constexpr value_type blue() const { return _blue; }

    constexpr void red(const value_type input)
    {
        _red = input;
    }

    constexpr void green(const value_type input)
    {
        _green = input;
    }

    constexpr void blue(const value_type input)
    {
        _blue = input;
    }

protected:
    value_type _red{};
    value_type _green{};
    value_type _blue{};
};


template <std::floating_point T>
class BasicUnitRGB
{
public:
    using value_type = float;

    constexpr BasicUnitRGB() = default;
    explicit constexpr BasicUnitRGB(value_type r, value_type g, value_type b)
        :
        _red{ r },
        _green{ g },
        _blue{ b }
    {
        assert( _isInBounds( _red ) );
        assert( _isInBounds( _green ) );
        assert( _isInBounds( _blue ) );
    }
    constexpr BasicUnitRGB(const BasicUnitRGB<float> &other)
        :
        _red{   other._red   },
        _green{ other._green },
        _blue{  other._blue  }
    {
        assert( other.isNormalized() );
    }
    constexpr BasicUnitRGB<float> &operator =(const BasicUnitRGB<float> &other)
    {
        assert( other.isNormalized() );

        if ( this == &other )
            return *this;
        
        _red   = other._red;
        _green = other._green;
        _blue  = other._blue;

        return *this;
    }
    template<std::integral OtherT>
    constexpr BasicUnitRGB(const BasicRGB<OtherT> &other)
        :
        _red( other.red() ),
        _green( other.green() ),
        _blue( other.blue() )
    {
        const T Max{ std::numeric_limits<OtherT>::max() };

        _red /= Max;
        _green /= Max;
        _blue /= Max;

        assert( isNormalized() );
    }

    static constexpr BasicUnitRGB<float> min() { return zero(); }

    static constexpr BasicUnitRGB<float> max() { return BasicUnitRGB<T>( T{1.0}, T{1.0}, T{1.0} ); }

    static constexpr BasicUnitRGB<T> zero() { return BasicUnitRGB<T>(); }

    constexpr value_type red() const { return _red; }
    constexpr value_type green() const { return _green; }
    constexpr value_type blue() const { return _blue; }

    constexpr void red(const value_type input)
    {
        assert( _isInBounds( input ) );

        _red = input;
    }

    constexpr void green(const value_type input)
    {
        assert( _isInBounds( input ) );

        _green = input;
    }

    constexpr void blue(const value_type input)
    {
        assert( _isInBounds( input ) );

        _blue = input;
    }

    constexpr bool isNormalized() const
    {
        return _isInBounds( _red ) &&
               _isInBounds( _green ) &&
               _isInBounds( _blue );
    }
protected:
    value_type _red{};
    value_type _green{};
    value_type _blue{};

    constexpr bool _isInBounds(const value_type component) const
    {
        return (component >= value_type{0.0}) && (component <= value_type{1.0});
    }
};


template <std::floating_point T>
class BasicHSV
{
public:
    using value_type = T;

    enum Color {
        Red,
        Yellow,
        Green,
        Cyan,
        Blue,
        Magenta
    };

    constexpr BasicHSV() = default;
    constexpr BasicHSV(const Math::Degree<value_type> h, const value_type s, const value_type v)
        :
        _hue{ h },
        _saturation{ s },
        _value{ v }
    {
        assert( _isInBounds( _saturation ) );
        assert( _isInBounds( _value ) );
    }
    constexpr BasicHSV(const BasicHSV &other)
        :
        _hue{   other._hue   },
        _saturation{ other._saturation },
        _value{  other._value  }
    {
        assert( other.isNormalized() );
    }
    constexpr BasicHSV &operator =(const BasicHSV &other)
    {
        assert( other.isNormalized() );

        if ( this == &other )
            return *this;
        
        _hue    = other._hue;
        _saturation = other._saturation;
        _value  = other._value;

        return *this;
    }

    static constexpr BasicHSV<T> min()
    {
        return BasicHSV<T>( Math::Degree<T>(), 0.0, 0.0 );
    }

    static constexpr BasicHSV<T> max()
    {
        return BasicHSV<T>( Math::Degree<T>{ Math::Degree<T>::modulus() }, 1.0, 1.0 );
    }

    constexpr Math::Degree<value_type> hue() const { return _hue; }
    constexpr value_type saturation() const { return _saturation; }
    constexpr value_type value() const { return _value; }

    constexpr enum Color hueColor() const
    {
        const Math::Degree<T> mod = _hue.modulo();

        if ( _isInBoundsUpTo( mod.value(), 0.0, 60.0 ) )
            return Red;
        else if ( _isInBoundsUpTo( mod.value(), 60.0, 120.0 ) )
            return Yellow;
        else if ( _isInBoundsUpTo( mod.value(), 120.0, 180.0 ) )
            return Green;
        else if ( _isInBoundsUpTo( mod.value(), 180.0, 240.0 ) )
            return Cyan;
        else if ( _isInBoundsUpTo( mod.value(), 240.0, 300.0 ) )
            return Blue;

        // It must be in range 300 - 360
        return Magenta;
    }

    constexpr void hue(const Math::Degree<value_type> input)
    {
        _hue = input;
    }

    constexpr void saturation(const value_type input)
    {
        assert( _isInBounds( input ) );

        _saturation = input;
    }

    constexpr void value(const value_type input)
    {
        assert( _isInBounds( input ) );

        _value = input;
    }

    constexpr bool isNormalized() const
    {
        return _isInBoundsUpTo( _hue, 0.0, Math::Degree<value_type>::modulus() ) &&
               _isInBounds( _saturation ) &&
               _isInBounds( _value );
    }
protected:
    Math::Degree<value_type> _hue{};
    value_type               _saturation{};
    value_type               _value{};

    constexpr bool _isInBounds(const value_type component, const value_type lower_bound = 0.0, const value_type upper_bound = 1.0) const
    {
        return (component >= lower_bound) && (component <= upper_bound);
    }

    constexpr bool _isInBoundsUpTo(const value_type component, const value_type lower_bound = 0.0, const value_type upper_bound = 1.0) const
    {
        return (component >= lower_bound) && (component < upper_bound);
    }
};

template <class T>
using RGB = BasicRGB<T>;
using RGBb = RGB<uint8_t>;

template <class T>
using UnitRGB = BasicUnitRGB<T>;
using UnitRGBf = UnitRGB<float>;

template <class T>
using HSV = BasicHSV<T>;
using HSVf = HSV<float>;

}