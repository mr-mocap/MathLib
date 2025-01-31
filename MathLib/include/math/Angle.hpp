#pragma once

#include "math/Functions.hpp"

/** @file
 *  
 *  Contains the definition of Radian and Degree classes
 * 
 *  @hideincludegraph
 */

namespace Math
{

/** Class that stores its units in radians
 *  
 *  This class exists to try to make it more obviously known what
 *  the units are that are being constructed and passed around.
 */
template <class T>
class Radian
{
public:
    constexpr Radian() = default;
    explicit constexpr Radian(const T value) : _value(value) { }

    static constexpr Radian<T> zero() { return Radian<T>(); }

    /** @name Element Access
     *  @{
     */
    T value() const { return _value; }
    /// @}

    Radian<T>& operator +=(const Radian other)
    {
        _value += other._value;
        return *this;
    }

    Radian<T>& operator -=(const Radian other)
    {
        _value -= other._value;
        return *this;
    }

    Radian<T>& operator *=(const Radian other)
    {
        _value *= other._value;
        return *this;
    }

    Radian<T>& operator /=(const Radian other)
    {
        _value /= other._value;
        return *this;
    }

    /** Define the spaceship operator
     *   
     *  @note We define ONLY the <=> AND == operators in order to get all the
     *        other relational operators (C++20).
     * 
     *  @{
     */
    constexpr std::strong_ordering operator <=>(const Radian<T> other) const
    {
        return _value <=> other._value;
    }
    constexpr std::strong_ordering operator <=>(const T other) const
    {
        return _value <=> other;
    }
    /// @}

    /** Defines equality of two Radians
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     * 
     *  @{
     */
    constexpr bool operator ==(const Radian<T> right) const
    {
        return value() == right.value();
    }
    constexpr bool operator ==(const T right) const
    {
        return value() == right;
    }
    /// @}

private:
    T _value{};

    /** @addtogroup Equality
     * 
     *  @relates Radian
     *  
     *  @{
     * 
     *  Compares two Radian inputs equal to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     *  
     *  @see Equality
     */
    friend constexpr bool approximately_equal_to(const Radian<T> &value_to_test, const Radian<T> &value_it_should_be, const float tolerance = 0.0002f)
    {
        return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
    }
    /// @}

    /** @name Radian Global Operators
     * 
     *  @relates Radian
     * 
     *  @{
     */
    friend Radian<T> operator +(const Radian<T> left, const Radian<T> right)
    {
        return Radian<T>{ left.value() + right.value() };
    }

    friend Radian<T> operator -(const Radian<T> left, const Radian<T> right)
    {
        return Radian<T>{ left.value() - right.value() };
    }

    friend Radian<T> operator *(const Radian<T> left, const Radian<T> right)
    {
        return Radian<T>{ left.value() * right.value() };
    }

    friend Radian<T> operator /(const Radian<T> left, const Radian<T> right)
    {
        return Radian<T>{ left.value() / right.value() };
    }

    friend Radian<T> operator -(const Radian<T> input)
    {
        return Radian{ -input.value() };
    }
    /// @}  {Radian Global Operators}
};


/** Class that stores its units in degrees
 *  
 *  This class exists to try to make it more obviously known what
 *  the units are that are being constructed and passed around.
 *  
 *  This class is mainly for displaying underlying angular units and
 *  therefore attempts have been made to make it easy to convert from
 *  Degree to Radian and vice versa.
 */
template <class T>
class Degree
{
public:
    constexpr Degree() = default;
    explicit constexpr Degree(const T value) : _value(value) { }
    constexpr Degree(const Radian<T> value) : _value( RadiansToDegrees(value.value()) ) { }

    operator Radian<T>() { return Radian<T>{DegreesToRadians(_value)}; }

    static constexpr Degree<T> zero() { return Degree<T>(); }

    /** @name Element Access
     *  @{
     */
    T value() const { return _value; }
    /// @}

    /** @name Operators
     *  @{
     */
    Degree<T> operator +=(const Degree<T> other)
    {
        _value += other.value();
        return *this;
    }

    Degree<T> operator +=(const T other)
    {
        _value += other;
        return *this;
    }

    Degree<T> &operator -=(const Degree<T> other)
    {
        _value -= other.value();
        return *this;
    }

    Degree<T> &operator -=(const T other)
    {
        _value -= other;
        return *this;
    }

    Degree<T> &operator *=(const Degree<T> other)
    {
        _value *= other.value();
        return *this;
    }

    Degree<T> &operator *=(const T other)
    {
        _value *= other;
        return *this;
    }

    Degree<T> &operator /=(const Degree<T> other)
    {
        _value /= other.value();
        return *this;
    }

    Degree<T> &operator /=(const T other)
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
    constexpr std::strong_ordering operator <=>(const Degree<T> other) const
    {
        return _value <=> other._value;
    }
    constexpr std::strong_ordering operator <=>(const T other) const
    {
        return _value <=> other;
    }
    /// @}

    /** Defines equality of two Radians
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     * 
     *  @{
     */
    constexpr bool operator ==(const Degree<T> right) const
    {
        return value() == right.value();
    }
    constexpr bool operator ==(const T right) const
    {
        return value() == right;
    }
    /// @}
    static constexpr T modulus() { return 360; }

    constexpr Degree<T> modulo() const
    {
        T modded;

        // Make in range of 0 - 360
        return Degree{ (0.0 <= (modded = std::fmod( _value, modulus() )) ? modded : modulus() + modded) };
    }
private:
    T _value{};

    /** @addtogroup Equality
     * 
     *  @relates Degree
     *  
     *  @{
     * 
     *  Compares two Degree inputs equal to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     *  
     *  @see Equality
     */
    friend constexpr bool approximately_equal_to(const Degree<T> &value_to_test, const Degree<T> &value_it_should_be, const float tolerance = 0.0002f)
    {
        return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
    }
    /// @}

    /** @name Degree Global Operators
     * 
     *  @relates Degree
     * 
     *  @{
     */
    friend Degree<T> operator +(const Degree<T> left, const Degree<T> right)
    {
        return Degree<T>{ left.value() + right.value() };
    }

    friend Degree<T> operator -(const Degree<T> left, const Degree<T> right)
    {
        return Degree<T>{ left.value() - right.value() };
    }

    friend Degree<T> operator *(const Degree<T> left, const Degree<T> right)
    {
        return Degree<T>{ left.value() * right.value() };
    }

    friend Degree<T> operator /(const Degree<T> left, const Degree<T> right)
    {
        return Degree<T>{ left.value() / right.value() };
    }

    friend Degree<T> operator +(const Degree<T> left, const T right)
    {
        return Degree<T>{ left.value() + right };
    }

    friend Degree<T> operator -(const Degree<T> left, const T right)
    {
        return Degree<T>{ left.value() - right };
    }

    friend Degree<T> operator *(const Degree<T> left, const T right)
    {
        return Degree<T>{ left.value() * right };
    }

    friend Degree<T> operator /(const Degree<T> left, const T right)
    {
        return Degree<T>{ left.value() / right };
    }

    friend Degree<T> operator -(const Degree<T> input)
    {
        return Degree{ -input.value() };
    }
    /// @}  {Degree}
};


namespace Literals
{
/** @name User-Defined Literals
 * 
 *  @relates Degree
 * 
 *  @{
 */
constexpr Degree<float> operator ""_deg_f(long double degrees)
{
    return Degree<float>{ static_cast<float>(degrees) };
}

constexpr Degree<double> operator ""_deg(long double degrees)
{
    return Degree<double>{ static_cast<double>(degrees) };
}

constexpr Degree<long double> operator ""_deg_ld(long double degrees)
{
    return Degree{degrees};
}
/// @}  {User-Defined Literals}
}

/** @name Degree Type Aliases
 * 
 *  @relates Degree
 * 
 *  @{
 */
using Degreef  = Degree<float>;
using Degreed  = Degree<double>;
using Degreeld = Degree<long double>;
/// @} {Degree Type Aliases}

/** @name Radian Type Aliases
 * 
 *  @relates Radian
 * 
 *  @{
 */
using Radianf  = Radian<float>;
using Radiand  = Radian<double>;
using Radianld = Radian<long double>;
/// @}  {Radian Type Aliases}

}