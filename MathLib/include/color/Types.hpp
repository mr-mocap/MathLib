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

    constexpr value_type r() const { return _red; }
    constexpr value_type g() const { return _green; }
    constexpr value_type b() const { return _blue; }

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

    constexpr void r(const value_type input)
    {
        red( input );
    }

    constexpr void g(const value_type input)
    {
        green( input );
    }

    constexpr void b(const value_type input)
    {
        blue( input );
    }

protected:
    value_type _red{};
    value_type _green{};
    value_type _blue{};

    /** @name Global Operators
     * 
     *  @relates BasicRGB
     * 
     *  @{
     */

    /** @addtogroup BasicRGB Color Algebra
     * 
     *  RGB Color Algebra
     * 
     *  @{
     */

    /** @name Addition
     *  @{
     */
    /** Defines addition of two BasicRGB objects
     */
    friend constexpr BasicRGB<T> operator +(const BasicRGB<T> &left, const BasicRGB<T> &right)
    {
        return BasicRGB<T>( Math::saturate( left.red()   + right.red(),   min().red(),   max().red()   ),
                            Math::saturate( left.green() + right.green(), min().green(), max().green() ),
                            Math::saturate( left.blue()  + right.blue(),  min().blue(),  max().blue()  )
                          );
    }
    /// @}  {Addition}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two BasicRGB objects
     */
    friend constexpr BasicRGB<T> operator -(const BasicRGB<T> &left, const BasicRGB<T> &right)
    {
        return BasicRGB<T>( Math::saturate( left.red()   - right.red(),   min().red(),   max().red()   ),
                            Math::saturate( left.green() - right.green(), min().green(), max().green() ),
                            Math::saturate( left.blue()  - right.blue(),  min().blue(),  max().blue()  )
                          );
    }
    /// @}  {Subtraction}

    /** @name Multiplication
     *  @{
     */
    /** Defines multiplication of two BasicRGB objects
     */
    friend constexpr BasicRGB<T> operator *(const BasicRGB<T> &left, const BasicRGB<T> &right)
    {
        return BasicRGB<T>( Math::saturate( left.red()   * right.red(),   min().red(),   max().red()   ),
                            Math::saturate( left.green() * right.green(), min().green(), max().green() ),
                            Math::saturate( left.blue()  * right.blue(),  min().blue(),  max().blue()  )
                          );
    }

    friend constexpr BasicRGB<T> operator *(const BasicRGB<T> &left, const T right)
    {
        return BasicRGB<T>( Math::saturate( left.red()   * right, min().red(),   max().red()   ),
                            Math::saturate( left.green() * right, min().green(), max().green() ),
                            Math::saturate( left.blue()  * right, min().blue(),  max().blue()  )
                          );
    }
    /// @}  {Multiplication}
    /// @}  {RGBColorAlgebra}
    /// @}  {GlobalOperators}
};


template <std::floating_point T>
class BasicUnitRGB
{
public:
    using value_type = T;

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
    constexpr BasicUnitRGB(const BasicUnitRGB<T> &other)
        :
        _red{   other._red   },
        _green{ other._green },
        _blue{  other._blue  }
    {
        assert( other.isNormalized() );
    }
    constexpr BasicUnitRGB<T> &operator =(const BasicUnitRGB<T> &other)
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

    static constexpr BasicUnitRGB<T> min() { return zero(); }

    static constexpr BasicUnitRGB<T> max() { return BasicUnitRGB<T>( T{1.0}, T{1.0}, T{1.0} ); }

    static constexpr BasicUnitRGB<T> zero() { return BasicUnitRGB<T>(); }

    constexpr value_type red() const { return _red; }
    constexpr value_type green() const { return _green; }
    constexpr value_type blue() const { return _blue; }

    constexpr value_type r() const { return _red; }
    constexpr value_type g() const { return _green; }
    constexpr value_type b() const { return _blue; }

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

    constexpr void r(const value_type input)
    {
        red( input );
    }

    constexpr void g(const value_type input)
    {
        green( input );
    }

    constexpr void b(const value_type input)
    {
        blue( input );
    }

    constexpr bool isNormalized() const
    {
        return _isInBounds( _red ) &&
               _isInBounds( _green ) &&
               _isInBounds( _blue );
    }

    bool isNaN() const { return std::isnan(_red) || std::isnan(_green) || std::isnan(_blue); }

    bool isInf() const { return std::isinf(_red) || std::isinf(_green) || std::isinf(_blue); }

protected:
    value_type _red{};
    value_type _green{};
    value_type _blue{};

    constexpr bool _isInBounds(const value_type component) const
    {
        return (component >= value_type{0.0}) && (component <= value_type{1.0});
    }

    /** @addtogroup Equality
     * 
     *  @relates BasicUnitRGB
     * 
     *  @{
     * 
     *  Compares two BasicUnitRGB inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     */
    friend constexpr bool approximately_equal_to(const BasicUnitRGB<T> &value_to_test, const BasicUnitRGB<T> &value_it_should_be, const T tolerance = 0.0002f)
    {
        return approximately_equal_to(value_to_test.red(), value_it_should_be.red(), tolerance) &&
               approximately_equal_to(value_to_test.green(), value_it_should_be.green(), tolerance) &&
               approximately_equal_to(value_to_test.blue(), value_it_should_be.blue(), tolerance) ;
    }
    /// @}

    /** @name Global Operators
     * 
     *  @relates BasicUnitRGB
     * 
     *  @{
     */

    /** @addtogroup BasicUnitRGB Color Algebra
     * 
     *  RGB Color Algebra
     * 
     *  @{
     */

    /** @name Addition
     *  @{
     */
    /** Defines addition of two BasicUnitRGB objects
     */
    friend constexpr BasicUnitRGB<T> operator +(const BasicUnitRGB<T> &left, const BasicUnitRGB<T> &right)
    {
        return BasicUnitRGB<T>( Math::saturate( left.red()   + right.red(),   min().red(),   max().red()   ),
                                Math::saturate( left.green() + right.green(), min().green(), max().green() ),
                                Math::saturate( left.blue()  + right.blue(),  min().blue(),  max().blue()  )
                              );
    }
    /// @}  {Addition}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two BasicHSV objects
     */
    friend constexpr BasicUnitRGB<T> operator -(const BasicUnitRGB<T> &left, const BasicUnitRGB<T> &right)
    {
        return BasicUnitRGB<T>( Math::saturate( left.red()   - right.red(),   min().red(),   max().red()   ),
                                Math::saturate( left.green() - right.green(), min().green(), max().green() ),
                                Math::saturate( left.blue()  - right.blue(),  min().blue(),  max().blue()  )
                            );
    }
    /// @}  {Subtraction}

    /** @name Multiplication
     *  @{
     */
    /** Defines multiplication of two BasicUnitRGB objects
     */
    friend constexpr BasicUnitRGB<T> operator *(const BasicUnitRGB<T> &left, const BasicUnitRGB<T> &right)
    {
        return BasicUnitRGB<T>( Math::saturate( left.red()   * right.red(),   min().red(),   max().red()   ),
                                Math::saturate( left.green() * right.green(), min().green(), max().green() ),
                                Math::saturate( left.blue()  * right.blue(),  min().blue(),  max().blue()  )
                            );
    }

    friend constexpr BasicUnitRGB<T> operator *(const BasicUnitRGB<T> &left, const T right)
    {
        return BasicUnitRGB<T>( Math::saturate( left.red()   * right, min().red(),   max().red()   ),
                                Math::saturate( left.green() * right, min().green(), max().green() ),
                                Math::saturate( left.blue()  * right, min().blue(),  max().blue()  )
                            );
    }
    /// @}  {Multiplication}
    /// @}  {RGBColorAlgebra}
    /// @}  {GlobalOperators}
};


template <std::floating_point T = float>
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
        return BasicHSV<T>( Math::Degree<value_type>(), 0.0, 0.0 );
    }

    static constexpr BasicHSV<T> max()
    {
        return BasicHSV<T>( Math::Degree<value_type>{ Math::Degree<value_type>::modulus() }, value_type{1.0}, value_type{1.0} );
    }

    constexpr Math::Degree<value_type> hue() const { return _hue; }
    constexpr value_type saturation() const { return _saturation; }
    constexpr value_type value() const { return _value; }

    constexpr enum Color hueColor() const
    {
        const Math::Degree<value_type> mod = _hue.modulo();

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

    bool isNaN() const { return std::isnan(_hue) || std::isnan(_saturation) || std::isnan(_value); }

    bool isInf() const { return std::isinf(_hue) || std::isinf(_saturation) || std::isinf(_value); }

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

    /** @addtogroup Equality
     * 
     *  @relates BasicHSV
     * 
     *  @{
     * 
     *  Compares two BasicHSV inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     */
    friend constexpr bool approximately_equal_to(const BasicHSV<T> &value_to_test, const BasicHSV<T> &value_it_should_be, const T tolerance = 0.0002f)
    {
        return approximately_equal_to(value_to_test.hue().value(), value_it_should_be.hue().valuee(), tolerance) &&
               approximately_equal_to(value_to_test.saturation(),  value_it_should_be.saturation(),   tolerance) &&
               approximately_equal_to(value_to_test.value(),       value_it_should_be.value(),        tolerance);
    }
    /// @}

    /** @name Global Operators
     * 
     *  @relates BasicHSV
     * 
     *  @{
     */

    /** @addtogroup BasicHSVAlgebra HSV Color Algebra
     * 
     *  HSV Color Algebra
     * 
     *  @{
     */

    /** @name Addition
     *  @{
     */
    /** Defines addition of two BasicHSV objects
     */
    friend constexpr BasicHSV<T> operator +(const BasicHSV<T> &left, const BasicHSV<T> &right)
    {
        return BasicHSV<T>( Degree<T>(left.hue() + right.hue()).modulo(),
                            Math::saturate( left.saturation() + right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.value()      + right.value(),      min.value(),        max.value()        )
                            );
    }
    /// @}  {Addition}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two BasicHSV objects
     */
    friend constexpr BasicHSV<T> operator -(const BasicHSV<T> &left, const BasicHSV<T> &right)
    {
        return BasicHSV<T>( Degree<T>(left.hue() - right.hue()).modulo(),
                            Math::saturate( left.saturation() - right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.value()      - right.value(),      min.value(),        max.value()        )
                            );
    }
    /// @}  {Subtraction}

    /// @}  {BasicHSVAlgebra}
    /// @}  {GlobalOperators}
};

template <std::floating_point T = float>
class BasicHSL
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

    constexpr BasicHSL() = default;
    constexpr BasicHSL(const Math::Degree<value_type> h, const value_type s, const value_type l)
        :
        _hue{ h },
        _saturation{ s },
        _lightness{ l }
    {
        assert( _isInBounds( _saturation ) );
        assert( _isInBounds( _lightness ) );
    }
    constexpr BasicHSL(const BasicHSL &other)
        :
        _hue{   other._hue   },
        _saturation{ other._saturation },
        _lightness{  other._lightness  }
    {
        assert( other.isNormalized() );
    }
    constexpr BasicHSL &operator =(const BasicHSL &other)
    {
        assert( other.isNormalized() );

        if ( this == &other )
            return *this;
        
        _hue    = other._hue;
        _saturation = other._saturation;
        _lightness  = other._lightness;

        return *this;
    }

    constexpr Math::Degree<value_type> hue() const { return _hue; }
    constexpr value_type saturation() const { return _saturation; }
    constexpr value_type lightness() const { return _lightness; }

    constexpr enum Color hueColor() const
    {
        const Math::Degree<value_type> mod = _hue.modulo();

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

    constexpr void lightness(const value_type input)
    {
        assert( _isInBounds( input ) );

        _lightness = input;
    }

    constexpr bool isNormalized() const
    {
        return _isInBoundsUpTo( _hue, 0.0, Math::Degree<value_type>::modulus() ) &&
               _isInBounds( _saturation ) &&
               _isInBounds( _lightness );
    }

    bool isNaN() const { return std::isnan(_hue) || std::isnan(_saturation) || std::isnan(_lightness); }

    bool isInf() const { return std::isinf(_hue) || std::isinf(_saturation) || std::isinf(_lightness); }

protected:
    Math::Degree<value_type> _hue{};
    value_type               _saturation{};
    value_type               _lightness{};

    constexpr bool _isInBounds(const value_type component, const value_type lower_bound = 0.0, const value_type upper_bound = 1.0) const
    {
        return (component >= lower_bound) && (component <= upper_bound);
    }

    constexpr bool _isInBoundsUpTo(const value_type component, const value_type lower_bound = 0.0, const value_type upper_bound = 1.0) const
    {
        return (component >= lower_bound) && (component < upper_bound);
    }

    /** @addtogroup Equality
     * 
     *  @relates BasicHSL
     * 
     *  @{
     * 
     *  Compares two BasicHSL inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     */
    friend constexpr bool approximately_equal_to(const BasicHSL<T> &value_to_test, const BasicHSL<T> &value_it_should_be, const T tolerance = 0.0002f)
    {
        return approximately_equal_to(value_to_test.hue().value(), value_it_should_be.hue().valuee(), tolerance) &&
               approximately_equal_to(value_to_test.saturation(),  value_it_should_be.saturation(),   tolerance) &&
               approximately_equal_to(value_to_test.lightness(),   value_it_should_be.lightness(),    tolerance);
    }
    /// @}
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

template <class T>
using HSL = BasicHSL<T>;
using HSLf = HSL<float>;
}