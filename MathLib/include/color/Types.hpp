#pragma once

#include "math/Angle.hpp"
#include <cassert>
#include <limits>
#include <cstdint>
#include <cmath>
#include <concepts>


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

    constexpr void red(value_type input)
    {
        _red = input;
    }

    constexpr void green(value_type input)
    {
        _green = input;
    }

    constexpr void blue(value_type input)
    {
        _blue = input;
    }

    constexpr void r(value_type input)
    {
        red( input );
    }

    constexpr void g(value_type input)
    {
        green( input );
    }

    constexpr void b(value_type input)
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

    friend constexpr BasicRGB<T> operator *(const BasicRGB<T> &left, T right)
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

    constexpr void red(value_type input)
    {
        assert( _isInBounds( input ) );

        _red = input;
    }

    constexpr void green(value_type input)
    {
        assert( _isInBounds( input ) );

        _green = input;
    }

    constexpr void blue(value_type input)
    {
        assert( _isInBounds( input ) );

        _blue = input;
    }

    constexpr void r(value_type input)
    {
        red( input );
    }

    constexpr void g(value_type input)
    {
        green( input );
    }

    constexpr void b(value_type input)
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

    constexpr bool _isInBounds(value_type component) const
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
    friend constexpr bool approximately_equal_to(const BasicUnitRGB<T> &value_to_test, const BasicUnitRGB<T> &value_it_should_be, T tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.red(),   value_it_should_be.red(),   tolerance) &&
               approximately_equal_to(value_to_test.green(), value_it_should_be.green(), tolerance) &&
               approximately_equal_to(value_to_test.blue(),  value_it_should_be.blue(),  tolerance) ;
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

    friend constexpr BasicUnitRGB<T> operator *(const BasicUnitRGB<T> &left, T right)
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


template <std::floating_point T>
class BasicHue
{
    struct not_checked { };

    explicit constexpr BasicHue(T init_value, struct not_checked )
        :
        _value( init_value )
    {
    }

public:
    using value_type = T;

    constexpr BasicHue() = default;
    constexpr BasicHue(Math::BasicDegree<T> init_value)
        :
        _value( init_value.modulo() )
    {
    }

    explicit constexpr BasicHue(T init_value)
        :
        _value( Math::BasicDegree<T>{ init_value }.modulo() )
    {
    }

    /** @name Element Access
     *  @{
     */
    T value() const { return _value.value(); }
    /// @}

    operator T() const { return _value.value(); }

    operator Math::BasicDegree<T>() const { return _value; }

    static constexpr BasicHue<T> min() { return zero(); }

    static constexpr BasicHue<T> max() { return BasicHue<T>( Math::BasicDegree<T>::modulus(), not_checked{} ); }

    static constexpr BasicHue<T> zero() { return BasicHue<T>(); }
    
    constexpr BasicHue<T> modulo() const { return BasicHue<T>( _value.modulo() ); }

    constexpr bool isNaN() const
    {
        return _value.isNan();
    }

    constexpr bool isInf() const
    {
        return _value.isInf();
    }

    /** @name Operators
     *  @{
     */
    constexpr BasicHue<T> &operator +=(BasicHue<T> other)
    {
        _value += other._value;
        return *this;
    }

    constexpr BasicHue<T> &operator +=(Math::BasicDegree<T> other)
    {
        _value += other;
        return *this;
    }

    constexpr BasicHue<T> &operator +=(T other)
    {
        _value += other;
        return *this;
    }

    constexpr BasicHue<T> &operator -=(BasicHue<T> other)
    {
        _value -= other._value;
        return *this;
    }

    constexpr BasicHue<T> &operator -=(Math::BasicDegree<T> other)
    {
        _value -= other;
        return *this;
    }

    constexpr BasicHue<T> &operator -=(T other)
    {
        _value -= other;
        return *this;
    }

    constexpr BasicHue<T> &operator *=(BasicHue<T> other)
    {
        _value *= other._value;
        return *this;
    }

    constexpr BasicHue<T> &operator *=(Math::BasicDegree<T> other)
    {
        _value *= other;
        return *this;
    }

    constexpr BasicHue<T> &operator *=(T other)
    {
        _value *= other;
        return *this;
    }

    constexpr BasicHue<T> &operator /=(BasicHue<T> other)
    {
        _value /= other._value;
        return *this;
    }

    constexpr BasicHue<T> &operator /=(Math::BasicDegree<T> other)
    {
        _value /= other;
        return *this;
    }

    constexpr BasicHue<T> &operator /=(T other)
    {
        _value /= other;
        return *this;
    }
    /// @}  {Operators}

    /** Define the spaceship operator
     *   
     *  @note We define ONLY the <=> AND == operators in order to get all the
     *        other relational operators (C++20).
     * 
     *  @{
     */
    constexpr auto operator <=>(const BasicHue<T> &other) const = default;
    constexpr auto operator <=>(const Math::BasicDegree<T> &other) const
    {
        return _value.value() <=> other.value();
    }
    constexpr auto operator <=>(const T &other) const
    {
        return _value.value() <=> other;
    }
    /// @}

    /** Defines equality of two BasicHues
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     * 
     *  @{
     */
    constexpr bool operator ==(const BasicHue<T> &right) const
    {
        return _value == right._value;
    }
    constexpr bool operator ==(const Math::BasicDegree<T> &right) const
    {
        return _value == right;
    }
    constexpr bool operator ==(const T &right) const
    {
        return _value.value() == right;
    }
    /// @}

protected:
    Math::BasicDegree<T> _value{};

    /** @addtogroup Equality
     * 
     *  @relates BasicHue
     *  
     *  @{
     * 
     *  Compares two BasicHue inputs equal to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     *  
     *  @see Equality
     */
    friend constexpr bool approximately_equal_to(const BasicHue<T> &value_to_test, const BasicHue<T> &value_it_should_be, T tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
    }
    /// @}

    /** @name BasicHue Global Operators
     * 
     *  @relates BasicHue
     * 
     *  @{
     */
    friend constexpr BasicHue<T> operator +(BasicHue<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() + right.value() };
    }

    friend constexpr BasicHue<T> operator +(BasicHue<T> left, Math::BasicDegree<T> right)
    {
        return BasicHue<T>{ left.value() + right.value() };
    }

    friend constexpr BasicHue<T> operator +(Math::BasicDegree<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() + right.value() };
    }

    friend constexpr BasicHue<T> operator -(BasicHue<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() - right.value() };
    }

    friend constexpr BasicHue<T> operator -(BasicHue<T> left, Math::BasicDegree<T> right)
    {
        return BasicHue<T>{ left.value() - right.value() };
    }

    friend constexpr BasicHue<T> operator -(Math::BasicDegree<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() - right.value() };
    }

    friend constexpr BasicHue<T> operator *(BasicHue<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() * right.value() };
    }

    friend constexpr BasicHue<T> operator *(BasicHue<T> left, Math::BasicDegree<T> right)
    {
        return BasicHue<T>{ left.value() * right.value() };
    }

    friend constexpr BasicHue<T> operator *(Math::BasicDegree<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() * right.value() };
    }

    friend constexpr BasicHue<T> operator /(BasicHue<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() / right.value() };
    }

    friend constexpr BasicHue<T> operator /(BasicHue<T> left, Math::BasicDegree<T> right)
    {
        return BasicHue<T>{ left.value() / right.value() };
    }

    friend constexpr BasicHue<T> operator /(Math::BasicDegree<T> left, BasicHue<T> right)
    {
        return BasicHue<T>{ left.value() / right.value() };
    }

    friend constexpr BasicHue<T> operator +(BasicHue<T> left, T right)
    {
        return BasicHue<T>{ left.value() + right };
    }

    friend constexpr BasicHue<T> operator -(BasicHue<T> left, T right)
    {
        return BasicHue<T>{ left.value() - right };
    }

    friend constexpr BasicHue<T> operator *(BasicHue<T> left, T right)
    {
        return BasicHue<T>{ left.value() * right };
    }

    friend constexpr BasicHue<T> operator /(BasicHue<T> left, T right)
    {
        return BasicHue<T>{ left.value() / right };
    }

    friend constexpr BasicHue<T> operator -(BasicHue<T> input)
    {
        return BasicHue{ -input.value() };
    }
    /// @}  {BasicHue}
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
    constexpr BasicHSV(Math::BasicDegree<value_type> h, value_type s, value_type v)
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
        _hue{ other._hue },
        _saturation{ other._saturation },
        _value{ other._value }
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
        return BasicHSV<T>( Math::BasicDegree<value_type>(), value_type{0.0}, value_type{0.0} );
    }

    static constexpr BasicHSV<T> max()
    {
        return BasicHSV<T>( Math::BasicDegree<value_type>{ Math::BasicDegree<value_type>::modulus() }, value_type{1.0}, value_type{1.0} );
    }

    constexpr Math::BasicDegree<value_type> hue() const { return _hue; }
    constexpr value_type saturation() const { return _saturation; }
    constexpr value_type value() const { return _value; }

    constexpr enum Color hueColor() const
    {
        const Math::BasicDegree<value_type> mod = _hue.modulo();

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

    constexpr void hue(Math::BasicDegree<value_type> input)
    {
        _hue = input;
    }

    constexpr void saturation(value_type input)
    {
        assert( _isInBounds( input ) );

        _saturation = input;
    }

    constexpr void value(value_type input)
    {
        assert( _isInBounds( input ) );

        _value = input;
    }

    constexpr bool isNormalized() const
    {
        return _isInBoundsUpTo( _hue.value(), value_type{0.0}, Math::BasicDegree<value_type>::modulus() ) &&
               _isInBounds( _saturation ) &&
               _isInBounds( _value );
    }

    bool isNaN() const { return std::isnan(_hue) || std::isnan(_saturation) || std::isnan(_value); }

    bool isInf() const { return std::isinf(_hue) || std::isinf(_saturation) || std::isinf(_value); }

protected:
    Math::BasicDegree<value_type> _hue{};
    value_type               _saturation{};
    value_type               _value{};

    constexpr bool _isInBounds(value_type component, value_type lower_bound = 0.0, value_type upper_bound = 1.0) const
    {
        return (component >= lower_bound) && (component <= upper_bound);
    }

    constexpr bool _isInBoundsUpTo(value_type component, value_type lower_bound = 0.0, value_type upper_bound = 1.0) const
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
    friend constexpr bool approximately_equal_to(const BasicHSV<T> &value_to_test, const BasicHSV<T> &value_it_should_be, T tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.hue().value(), value_it_should_be.hue().value(), tolerance) &&
               approximately_equal_to(value_to_test.saturation(),  value_it_should_be.saturation(),  tolerance) &&
               approximately_equal_to(value_to_test.value(),       value_it_should_be.value(),       tolerance);
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
        return BasicHSV<T>( Math::BasicDegree<T>(left.hue() + right.hue()).modulo(),
                            Math::saturate( left.saturation() + right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.value()      + right.value(),      min().value(),      max().value()      )
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
        return BasicHSV<T>( Math::BasicDegree<T>(left.hue() - right.hue()).modulo(),
                            Math::saturate( left.saturation() - right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.value()      - right.value(),      min().value(),      max().value()      )
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
    constexpr BasicHSL(Math::BasicDegree<value_type> h, value_type s, value_type l)
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

    static constexpr BasicHSL<T> min()
    {
        return BasicHSL<T>( Math::BasicDegree<value_type>(), value_type{0.0}, value_type{0.0} );
    }

    static constexpr BasicHSV<T> max()
    {
        return BasicHSV<T>( Math::BasicDegree<value_type>{ Math::BasicDegree<value_type>::modulus() }, value_type{1.0}, value_type{1.0} );
    }

    constexpr Math::BasicDegree<value_type> hue() const { return _hue; }
    constexpr value_type saturation() const { return _saturation; }
    constexpr value_type lightness() const { return _lightness; }

    constexpr enum Color hueColor() const
    {
        const Math::BasicDegree<value_type> mod = _hue.modulo();

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

    constexpr void hue(Math::BasicDegree<value_type> input)
    {
        _hue = input;
    }

    constexpr void saturation(value_type input)
    {
        assert( _isInBounds( input ) );

        _saturation = input;
    }

    constexpr void lightness(value_type input)
    {
        assert( _isInBounds( input ) );

        _lightness = input;
    }

    constexpr bool isNormalized() const
    {
        return _isInBoundsUpTo( _hue, 0.0, Math::BasicDegree<value_type>::modulus() ) &&
               _isInBounds( _saturation ) &&
               _isInBounds( _lightness );
    }

    bool isNaN() const { return std::isnan(_hue) || std::isnan(_saturation) || std::isnan(_lightness); }

    bool isInf() const { return std::isinf(_hue) || std::isinf(_saturation) || std::isinf(_lightness); }

protected:
    Math::BasicDegree<value_type> _hue{};
    value_type               _saturation{};
    value_type               _lightness{};

    constexpr bool _isInBounds(value_type component, value_type lower_bound = 0.0, value_type upper_bound = 1.0) const
    {
        return (component >= lower_bound) && (component <= upper_bound);
    }

    constexpr bool _isInBoundsUpTo(value_type component, value_type lower_bound = 0.0, value_type upper_bound = 1.0) const
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
    friend constexpr bool approximately_equal_to(const BasicHSL<T> &value_to_test, const BasicHSL<T> &value_it_should_be, T tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.hue().value(), value_it_should_be.hue().valuee(), tolerance) &&
               approximately_equal_to(value_to_test.saturation(),  value_it_should_be.saturation(),   tolerance) &&
               approximately_equal_to(value_to_test.lightness(),   value_it_should_be.lightness(),    tolerance);
    }
    /// @}

    /** @name Global Operators
     * 
     *  @relates BasicHSL
     * 
     *  @{
     */

    /** @addtogroup BasicHSLAlgebra HSL Color Algebra
     * 
     *  HSL Color Algebra
     * 
     *  @{
     */

    /** @name Addition
     *  @{
     */
    /** Defines addition of two BasicHSL objects
     */
    friend constexpr BasicHSL<T> operator +(const BasicHSL<T> &left, const BasicHSL<T> &right)
    {
        return BasicHSL<T>( Math::BasicDegree<T>(left.hue() + right.hue()).modulo(),
                            Math::saturate( left.saturation() + right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.lightness()  + right.lightness(),  min().lightness(),  max().lightness()  )
                          );
    }
    /// @}  {Addition}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two BasicHSL objects
     */
    friend constexpr BasicHSL<T> operator -(const BasicHSL<T> &left, const BasicHSL<T> &right)
    {
        return BasicHSL<T>( Math::BasicDegree<T>(left.hue() - right.hue()).modulo(),
                            Math::saturate( left.saturation() - right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.lightness()  - right.lightness(),  min().lightness(),  max().lightness()  )
                          );
    }
    /// @}  {Subtraction}

    /// @}  {BasicHSLAlgebra}
    /// @}  {GlobalOperators}
};

typedef BasicHue<float>  Huef;
typedef BasicHue<double> Hue;
typedef BasicHue<double> Hued;
typedef BasicHue<long double> Huel;

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