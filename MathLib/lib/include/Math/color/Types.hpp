#pragma once

#include <Math/math/Angle.hpp>
#include <cassert>
#include <limits>
#include <cstdint>
#include <cmath>
#include <concepts>


/** @file
 *  
 *  Defines various color types
 *
 *  @hideincludegraph
 */

namespace Color
{

template <std::floating_point T>
class BasicUnitRGB;

/** The definition of an RGB color triple
 *  
 *  @headerfile <> <color/Types.hpp>
 */
template <std::integral T>
class BasicRGB
{
public:
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The type of the underlying implementation for each color
    /// @}

    /** @name Constructors
     *  @{
     */
    constexpr BasicRGB() = default; ///< Defaults to (0, 0, 0)
    constexpr BasicRGB(value_type r, value_type g, value_type b) : _red{ r }, _green{ g }, _blue{ b } { }
    constexpr BasicRGB(const std::tuple<T, T, T> &init_value)
        :
        _red{   std::get<0>(init_value) },
        _green{ std::get<1>(init_value) },
        _blue{  std::get<2>(init_value) }
    {
    }

    /// @}

    /** @name Constants
     *  @{
     */
    static constexpr BasicRGB<T> min()
    {
        const T mn = std::numeric_limits<T>::min();

        return { mn, mn, mn };
    }

    static constexpr BasicRGB<T> max()
    {
        const T mx = std::numeric_limits<T>::max();

        return { mx, mx, mx };
    }

    static constexpr BasicRGB<T> zero() { return { }; }
    /// @}

    /** @name Element Access
     *  @{
     */
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
    /// @}

    /** @name Conversion Operators
     *  @{
     */
    constexpr operator std::tuple<T, T, T>() const { return std::make_tuple( _red, _green, _blue ); }
    /// @}

protected:
    value_type _red{};
    value_type _green{};
    value_type _blue{};

    /** @name Operators
     *  @{
     */
    friend constexpr bool operator ==(const BasicRGB<T> &left, const BasicRGB<T> &right) = default;

    /** @addtogroup BasicRGBColorAlgebra RGB Color Algebra
     * 
     *  RGB Color Algebra
     * 
     *  @{
     */
    friend constexpr BasicRGB<T> operator +(const BasicRGB<T> &left, const BasicRGB<T> &right)
    {
        return { Math::saturate( left.red()   + right.red(),   min().red(),   max().red()   ),
                 Math::saturate( left.green() + right.green(), min().green(), max().green() ),
                 Math::saturate( left.blue()  + right.blue(),  min().blue(),  max().blue()  )
               };
    }

    friend constexpr BasicRGB<T> operator -(const BasicRGB<T> &left, const BasicRGB<T> &right)
    {
        return { Math::saturate( left.red()   - right.red(),   min().red(),   max().red()   ),
                 Math::saturate( left.green() - right.green(), min().green(), max().green() ),
                 Math::saturate( left.blue()  - right.blue(),  min().blue(),  max().blue()  )
               };
    }

    friend constexpr BasicRGB<T> operator *(const BasicRGB<T> &left, const BasicRGB<T> &right)
    {
        return { Math::saturate( left.red()   * right.red(),   min().red(),   max().red()   ),
                 Math::saturate( left.green() * right.green(), min().green(), max().green() ),
                 Math::saturate( left.blue()  * right.blue(),  min().blue(),  max().blue()  )
               };
    }

    friend constexpr BasicRGB<T> operator *(const BasicRGB<T> &left, T right)
    {
        return { Math::saturate( left.red()   * right, min().red(),   max().red()   ),
                 Math::saturate( left.green() * right, min().green(), max().green() ),
                 Math::saturate( left.blue()  * right, min().blue(),  max().blue()  )
               };
    }
    /// @} {BasicRGBColorAlgebra}
    /// @} {Operators}

    friend constexpr T min(const BasicRGB<T> &input)
    {
        // We know T is an integral type
        return std::min( std::min( input.red(), input.green() ), input.blue() );
    }

    friend constexpr T max(const BasicRGB<T> &input)
    {
        // We know T is an integral type
        return std::max( std::max( input.red(), input.green() ), input.blue() );
    }

    template <std::floating_point OT>
    friend BasicUnitRGB<OT> normalized(const BasicRGB<T> &input)
    {
        const OT max_value = std::numeric_limits<T>::max;

        return { input.red()   / max_value,
                 input.green() / max_value,
                 input.blue()  / max_value };
    }
};


/** The definition of an RGB color triple with normalized members between 0.0 and 1.0
 *  
 *  @headerfile <> <color/Types.hpp>
 * 
 *  @see BasicRGB
 */
template <std::floating_point T>
class BasicUnitRGB
{
public:
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The type of the underlying implementation for each color
    /// @}

    /** @name Constructors
     *  @{
     */
    constexpr BasicUnitRGB() = default;

    constexpr BasicUnitRGB(value_type r, value_type g, value_type b)
        :
        _red{ r },
        _green{ g },
        _blue{ b }
    {
        assert( isNormalized() );
    }
    constexpr BasicUnitRGB(const std::tuple<value_type, value_type, value_type> &init_value)
        :
        _red{   std::get<0>(init_value) },
        _green{ std::get<1>(init_value) },
        _blue{  std::get<2>(init_value) }
    {
        assert( isNormalized() );
    }

    constexpr BasicUnitRGB(const BasicUnitRGB<T> &other)
        :
        _red{   other._red   },
        _green{ other._green },
        _blue{  other._blue  }
    {
        assert( other.isNormalized() );
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
    /// @}

    /** @name Assignment
     *  @{
     */
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
    /// @}

    /** @name Constants
     *  @{
     */
    static constexpr BasicUnitRGB<T> min() { return zero(); }

    static constexpr BasicUnitRGB<T> max() { return BasicUnitRGB<T>( T{1.0}, T{1.0}, T{1.0} ); }

    static constexpr BasicUnitRGB<T> zero() { return BasicUnitRGB<T>(); }
    /// @}

    /** @name Element Access
     *  @{
     */
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
    /// @}

    constexpr bool isNormalized() const
    {
        return _isInBounds( _red ) &&
               _isInBounds( _green ) &&
               _isInBounds( _blue );
    }

    /** @name Invalid Value Check
     *  @{
     */
    constexpr bool isNaN() const { return std::isnan(_red) || std::isnan(_green) || std::isnan(_blue); }

    constexpr bool isInf() const { return std::isinf(_red) || std::isinf(_green) || std::isinf(_blue); }
    /// @}

    /** @name Conversion Operators
     *  @{
     */
    constexpr operator std::tuple<value_type, value_type, value_type>() const { return std::make_tuple( _red, _green, _blue ); }
    /// @}
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
    friend constexpr bool approximately_equal_to(const BasicUnitRGB<T> &value_to_test,
                                                 const BasicUnitRGB<T> &value_it_should_be,
                                                       T                tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.red(),   value_it_should_be.red(),   tolerance) &&
               approximately_equal_to(value_to_test.green(), value_it_should_be.green(), tolerance) &&
               approximately_equal_to(value_to_test.blue(),  value_it_should_be.blue(),  tolerance) ;
    }
    /// @}

    /** @name Operators
     *  @{
     */

    /** @addtogroup BasicUnitRGBColorAlgebra Unit RGB Color Algebra
     * 
     *  Unit RGB Color Algebra
     * 
     *  @{
     */
    friend constexpr BasicUnitRGB<T> operator +(const BasicUnitRGB<T> &left, const BasicUnitRGB<T> &right)
    {
        return { Math::saturate( left.red()   + right.red(),   min().red(),   max().red()   ),
                 Math::saturate( left.green() + right.green(), min().green(), max().green() ),
                 Math::saturate( left.blue()  + right.blue(),  min().blue(),  max().blue()  )
               };
    }

    friend constexpr BasicUnitRGB<T> operator -(const BasicUnitRGB<T> &left, const BasicUnitRGB<T> &right)
    {
        return { Math::saturate( left.red()   - right.red(),   min().red(),   max().red()   ),
                 Math::saturate( left.green() - right.green(), min().green(), max().green() ),
                 Math::saturate( left.blue()  - right.blue(),  min().blue(),  max().blue()  )
               };
    }

    friend constexpr BasicUnitRGB<T> operator *(const BasicUnitRGB<T> &left, const BasicUnitRGB<T> &right)
    {
        return { Math::saturate( left.red()   * right.red(),   min().red(),   max().red()   ),
                 Math::saturate( left.green() * right.green(), min().green(), max().green() ),
                 Math::saturate( left.blue()  * right.blue(),  min().blue(),  max().blue()  )
               };
    }

    friend constexpr BasicUnitRGB<T> operator *(const BasicUnitRGB<T> &left, T right)
    {
        return { Math::saturate( left.red()   * right, min().red(),   max().red()   ),
                 Math::saturate( left.green() * right, min().green(), max().green() ),
                 Math::saturate( left.blue()  * right, min().blue(),  max().blue()  )
               };
    }
    /// @}  {BasicUnitRGBColorAlgebra}
    /// @}  {Operators}

    friend constexpr T min(const BasicUnitRGB<T> &input)
    {
        return std::fmin( std::fmin( input.red(), input.green() ), input.blue() );
    }

    friend constexpr T max(const BasicUnitRGB<T> &input)
    {
        return std::fmax( std::fmax( input.red(), input.green() ), input.blue() );
    }
};


/** The definition of a Hue color
 *  
 *  @note The natural range is 0.0 - 360.0
 * 
 *  @headerfile <> <color/Types.hpp>
 * 
 *  @see BasicRGB
 */
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
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The type of the underlying implementation for each color
    /// @}

    /** @name Constructors
     *  @{
     */
    constexpr BasicHue() = default;
    constexpr BasicHue(Math::BasicDegree<T> init_value)
        :
        _value( init_value.modulo() )
    {
    }

    constexpr BasicHue(T init_value)
        :
        _value( Math::BasicDegree<T>{ init_value }.modulo() )
    {
    }
    /// @}

    /** @name Element Access
     *  @{
     */
    T value() const { return _value.value(); }
    /// @}

    /** @name Conversion Operators
     *  @{
     */
    operator T() const { return _value.value(); }

    operator Math::BasicDegree<T>() const { return _value; }
    /// @}

    /** @name Constants
     *  @{
     */
    static constexpr BasicHue<T> min() { return zero(); }

    static constexpr BasicHue<T> max() { return BasicHue<T>( Math::BasicDegree<T>::modulus(), not_checked{} ); }

    static constexpr BasicHue<T> zero() { return BasicHue<T>(); }
    /// @}
    
    constexpr BasicHue<T> modulo() const { return BasicHue<T>( _value.modulo() ); }

    /** @name Invalid Value Check
     *  @{
     */
    constexpr bool isNaN() const
    {
        return _value.isNan();
    }

    constexpr bool isInf() const
    {
        return _value.isInf();
    }
    /// @}

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

    /** @name Comparison
     *  @{
     */
    /** Define the spaceship operator
     *   
     *  @note We define ONLY the <=> AND == operators in order to get all the
     *        other relational operators (C++20).
     * 
     *  @{
     */
    friend constexpr auto operator <=>(const BasicHue<T> &left, const BasicHue<T> &right) = default;
    friend constexpr auto operator <=>(const BasicHue<T> &left, const Math::BasicDegree<T> &right)
    {
        return left.value() <=> right.value();
    }
    friend constexpr auto operator <=>(const BasicHue<T> &left, const T &right)
    {
        return left.value() <=> right;
    }
    /// @}
    /// @}  {Comparison}

    /** @name Equality
     *  @{
     */
    /** Defines equality of two BasicHue objects
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     * 
     *  @{
     */
    friend constexpr bool operator ==(const BasicHue<T> &left, const BasicHue<T> &right) = default;
    friend constexpr bool operator ==(const BasicHue<T> &left, const Math::BasicDegree<T> &right)
    {
        return left.value() == right.value();;
    }
    friend constexpr bool operator ==(const BasicHue<T> &left, const T &right)
    {
        return left.value() == right;
    }
    /// @}
    /// @}  {Equality}

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
    friend constexpr bool approximately_equal_to(const BasicHue<T> &value_to_test,
                                                 const BasicHue<T> &value_it_should_be,
                                                       T            tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
    }
    /// @}

    /** @name Operators
     *  @{
     */
    friend constexpr BasicHue<T> operator +(const BasicHue<T> &left, const BasicHue<T> &right)
    {
        return { left.value() + right.value() };
    }

    friend constexpr BasicHue<T> operator +(const BasicHue<T> &left, const Math::BasicDegree<T> &right)
    {
        return { left.value() + right.value() };
    }

    friend constexpr BasicHue<T> operator +(const Math::BasicDegree<T> &left, const BasicHue<T> &right)
    {
        return { left.value() + right.value() };
    }

    friend constexpr BasicHue<T> operator -(const BasicHue<T> &left, const BasicHue<T> &right)
    {
        return { left.value() - right.value() };
    }

    friend constexpr BasicHue<T> operator -(const BasicHue<T> &left, const Math::BasicDegree<T> &right)
    {
        return { left.value() - right.value() };
    }

    friend constexpr BasicHue<T> operator -(const Math::BasicDegree<T> &left, const BasicHue<T> &right)
    {
        return { left.value() - right.value() };
    }

    friend constexpr BasicHue<T> operator *(const BasicHue<T> &left, const BasicHue<T> &right)
    {
        return { left.value() * right.value() };
    }

    friend constexpr BasicHue<T> operator *(const BasicHue<T> &left, const Math::BasicDegree<T> &right)
    {
        return { left.value() * right.value() };
    }

    friend constexpr BasicHue<T> operator *(const Math::BasicDegree<T> &left, const BasicHue<T> &right)
    {
        return { left.value() * right.value() };
    }

    friend constexpr BasicHue<T> operator /(const BasicHue<T> &left, const BasicHue<T> &right)
    {
        return { left.value() / right.value() };
    }

    friend constexpr BasicHue<T> operator /(const BasicHue<T> &left, const Math::BasicDegree<T> &right)
    {
        return { left.value() / right.value() };
    }

    friend constexpr BasicHue<T> operator /(const Math::BasicDegree<T> &left, const BasicHue<T> &right)
    {
        return { left.value() / right.value() };
    }

    friend constexpr BasicHue<T> operator +(const BasicHue<T> &left, const T &right)
    {
        return { left.value() + right };
    }

    friend constexpr BasicHue<T> operator -(const BasicHue<T> &left, const T &right)
    {
        return { left.value() - right };
    }

    friend constexpr BasicHue<T> operator *(const BasicHue<T> &left, const T &right)
    {
        return { left.value() * right };
    }

    friend constexpr BasicHue<T> operator /(const BasicHue<T> &left, const T &right)
    {
        return { left.value() / right };
    }

    friend constexpr BasicHue<T> operator -(const BasicHue<T> &input)
    {
        return { -input.value() };
    }
    /// @}  {Operators}
};


/** The definition of an HSV color
 *  
 *  This represents a color as Hue, Saturation, and Value.
 * 
 *  @headerfile <> <color/Types.hpp>
 */
template <std::floating_point T>
class BasicHSV
{
public:
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The type of the underlying implementation for each color
    /// @}

    enum Color {
        Red,
        Yellow,
        Green,
        Cyan,
        Blue,
        Magenta
    };

    /** @name Constructors
     *  @{
     */
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
    /// @}

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

    /** @name Constants
     *  @{
     */
    static constexpr BasicHSV<T> min()
    {
        return { Math::BasicDegree<value_type>(), value_type{0.0}, value_type{0.0} };
    }

    static constexpr BasicHSV<T> max()
    {
        return { Math::BasicDegree<value_type>{ Math::BasicDegree<value_type>::modulus() },
                 value_type{1.0},
                 value_type{1.0} };
    }
    /// @}

    /** @name Element Access
     *  @{
     */
    constexpr Math::BasicDegree<value_type> hue() const { return _hue; }
    constexpr value_type saturation() const { return _saturation; }
    constexpr value_type value() const { return _value; }

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
    /// @}

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

    constexpr bool isNormalized() const
    {
        return _isInBoundsUpTo( _hue.value(), value_type{0.0}, Math::BasicDegree<value_type>::modulus() ) &&
               _isInBounds( _saturation ) &&
               _isInBounds( _value );
    }

    /** @name Invalid Value Check
     *  @{
     */
    constexpr bool isNaN() const { return std::isnan(_hue) || std::isnan(_saturation) || std::isnan(_value); }

    constexpr bool isInf() const { return std::isinf(_hue) || std::isinf(_saturation) || std::isinf(_value); }
    /// @}

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
    friend constexpr bool approximately_equal_to(const BasicHSV<T> &value_to_test,
                                                 const BasicHSV<T> &value_it_should_be,
                                                       T            tolerance = T{0.0002})
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
    friend constexpr BasicHSV<T> operator +(const BasicHSV<T> &left, const BasicHSV<T> &right)
    {
        return BasicHSV<T>( Math::BasicDegree<T>(left.hue() + right.hue()).modulo(),
                            Math::saturate( left.saturation() + right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.value()      + right.value(),      min().value(),      max().value()      )
                            );
    }

    friend constexpr BasicHSV<T> operator -(const BasicHSV<T> &left, const BasicHSV<T> &right)
    {
        return BasicHSV<T>( Math::BasicDegree<T>(left.hue() - right.hue()).modulo(),
                            Math::saturate( left.saturation() - right.saturation(), min().saturation(), max().saturation() ),
                            Math::saturate( left.value()      - right.value(),      min().value(),      max().value()      )
                            );
    }
    /// @}  {BasicHSVAlgebra}
    /// @}  {GlobalOperators}
};

/** The definition of an HSL color
 *  
 *  This represents a color as Hue, Saturation, and Lightness.
 * 
 *  @headerfile <> <color/Types.hpp>
 */
template <std::floating_point T>
class BasicHSL
{
public:
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The type of the underlying implementation for each color
    /// @}

    enum Color {
        Red,
        Yellow,
        Green,
        Cyan,
        Blue,
        Magenta
    };

    /** @name Constructors
     *  @{
     */
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
    /// @}

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

    /** @name Constants
     *  @{
     */
    static constexpr BasicHSL<T> min()
    {
        return { Math::BasicDegree<value_type>(), value_type{0.0}, value_type{0.0} };
    }

    static constexpr BasicHSV<T> max()
    {
        return { Math::BasicDegree<value_type>{ Math::BasicDegree<value_type>::modulus() },
                 value_type{1.0},
                 value_type{1.0} };
    }
    /// @}

    /** @name Element Access
     *  @{
     */
    constexpr Math::BasicDegree<value_type> hue() const { return _hue; }
    constexpr value_type saturation() const { return _saturation; }
    constexpr value_type lightness() const { return _lightness; }

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
    /// @}

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

    constexpr bool isNormalized() const
    {
        return _isInBoundsUpTo( _hue, 0.0, Math::BasicDegree<value_type>::modulus() ) &&
               _isInBounds( _saturation ) &&
               _isInBounds( _lightness );
    }

    /** @name Invalid Value Check
     *  @{
     */
    constexpr bool isNaN() const { return std::isnan(_hue) || std::isnan(_saturation) || std::isnan(_lightness); }

    constexpr bool isInf() const { return std::isinf(_hue) || std::isinf(_saturation) || std::isinf(_lightness); }
    /// @}

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
    friend constexpr bool approximately_equal_to(const BasicHSL<T> &value_to_test,
                                                 const BasicHSL<T> &value_it_should_be,
                                                       T            tolerance = T{0.0002})
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
    friend constexpr BasicHSL<T> operator +(const BasicHSL<T> &left, const BasicHSL<T> &right)
    {
        return { Math::BasicDegree<T>(left.hue() + right.hue()).modulo(),
                 Math::saturate( left.saturation() + right.saturation(), min().saturation(), max().saturation() ),
                 Math::saturate( left.lightness()  + right.lightness(),  min().lightness(),  max().lightness()  )
               };
    }

    friend constexpr BasicHSL<T> operator -(const BasicHSL<T> &left, const BasicHSL<T> &right)
    {
        return { Math::BasicDegree<T>(left.hue() - right.hue()).modulo(),
                 Math::saturate( left.saturation() - right.saturation(), min().saturation(), max().saturation() ),
                 Math::saturate( left.lightness()  - right.lightness(),  min().lightness(),  max().lightness()  )
               };
    }
    /// @}  {BasicHSLAlgebra}
    /// @}  {GlobalOperators}
};


/** @addtogroup Types Color Types
 * 
 *  Color Type-Alias Definitions 
 * 
 *  @{
 */

 /** @name Hue
  * 
  *  Various Hue class type aliases
  * 
  *  @see BasicHue
  * 
  *  @{
  */
using Huef = BasicHue<float>;
using Hued = BasicHue<double>;
using Hue  = BasicHue<double>;
using Huel = BasicHue<long double>;
/// @}

 /** @name RGB
  * 
  *  Various RGB class type aliases
  * 
  *  @see BasicRGB
  * 
  *  @{
  */

/// @{
using RGBb  = BasicRGB<uint8_t>;
using RGBs  = BasicRGB<unsigned short>;
using RGBi  = BasicRGB<unsigned int>;
/// @}

/// @{
using UnitRGBf = BasicUnitRGB<float>;
using UnitRGBd = BasicUnitRGB<double>;
using UnitRGB  = BasicUnitRGB<double>;
using UnitRGBl = BasicUnitRGB<long double>;
/// @}

/// @{
using RGB8  = BasicRGB<uint8_t>;
using RGB16 = BasicRGB<unsigned short>;
using RGB32 = BasicRGB<unsigned int>;
/// @}

/// @}

 /** @name HSV
  * 
  *  Various HSV class type aliases
  * 
  *  @{
  */
using HSVf  = BasicHSV<float>;
using HSVd  = BasicHSV<double>;
using HSV   = BasicHSV<double>;
using HSVld = BasicHSV<long double>;
/// @}

 /** @name HSL
  * 
  *  Various HSL class type aliases
  * 
  *  @{
  */
using HSLf = BasicHSL<float>;
using HSLd = BasicHSL<double>;
using HSL  = BasicHSL<double>;
using HSLl = BasicHSL<long double>;
/// @}

/// @}

}