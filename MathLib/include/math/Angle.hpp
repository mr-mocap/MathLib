#pragma once

#include "math/Functions.hpp"
#include <concepts>
#include <compare>

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
template <std::floating_point T>
class BasicRadian
{
public:
    constexpr BasicRadian() = default;
    explicit constexpr BasicRadian(T value) : _value(value) { }

    static constexpr BasicRadian<T> zero() { return BasicRadian<T>(); }

    /** @name Element Access
     *  @{
     */
    T value() const { return _value; }
    /// @}

    constexpr BasicRadian<T> &operator +=(BasicRadian other)
    {
        _value += other._value;
        return *this;
    }

    constexpr BasicRadian<T> &operator -=(BasicRadian other)
    {
        _value -= other._value;
        return *this;
    }

    constexpr BasicRadian<T> &operator *=(BasicRadian other)
    {
        _value *= other._value;
        return *this;
    }

    constexpr BasicRadian<T> &operator /=(BasicRadian other)
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
    constexpr auto operator <=>(const BasicRadian<T> &other) const = default;
    constexpr auto operator <=>(const T &other) const
    {
        return _value <=> other;
    }
    /// @}

    /** Defines equality of two BasicRadians
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     * 
     *  @{
     */
    constexpr bool operator ==(const BasicRadian<T> &right) const = default;
    constexpr bool operator ==(const T &right) const
    {
        return value() == right;
    }
    /// @}

    constexpr bool isNaN() const
    {
        return std::isnan(_value);
    }

    constexpr bool isInf() const
    {
        return std::isinf(_value);
    }

private:
    T _value{};

    /** @addtogroup Equality
     * 
     *  @relates BasicRadian
     *  
     *  @{
     * 
     *  Compares two BasicRadian inputs equal to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     *  
     *  @see Equality
     */
    friend constexpr bool approximately_equal_to(BasicRadian<T> value_to_test, BasicRadian<T> value_it_should_be, T tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
    }
    /// @}

    /** @name BasicRadian Global Operators
     * 
     *  @relates BasicRadian
     * 
     *  @{
     */
    friend constexpr BasicRadian<T> operator +(BasicRadian<T> left, BasicRadian<T> right)
    {
        return BasicRadian<T>{ left.value() + right.value() };
    }

    friend constexpr BasicRadian<T> operator -(BasicRadian<T> left, BasicRadian<T> right)
    {
        return BasicRadian<T>{ left.value() - right.value() };
    }

    friend constexpr BasicRadian<T> operator *(BasicRadian<T> left, BasicRadian<T> right)
    {
        return BasicRadian<T>{ left.value() * right.value() };
    }

    friend constexpr BasicRadian<T> operator /(BasicRadian<T> left, BasicRadian<T> right)
    {
        return BasicRadian<T>{ left.value() / right.value() };
    }

    friend constexpr BasicRadian<T> operator -(BasicRadian<T> input)
    {
        return BasicRadian{ -input.value() };
    }
    /// @}  {BasicRadian Global Operators}
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
template <std::floating_point T>
class BasicDegree
{
public:
    constexpr BasicDegree() = default;
    explicit constexpr BasicDegree(T value) : _value(value) { }
    constexpr BasicDegree(BasicRadian<T> value) : _value( RadiansToDegrees(value.value()) ) { }

    operator BasicRadian<T>() { return BasicRadian<T>{DegreesToRadians(_value)}; }

    static constexpr BasicDegree<T> zero() { return BasicDegree<T>(); }

    /** @name Element Access
     *  @{
     */
    T value() const { return _value; }
    /// @}

    /** @name Operators
     *  @{
     */
    constexpr BasicDegree<T> &operator +=(BasicDegree<T> other)
    {
        _value += other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator +=(T other)
    {
        _value += other;
        return *this;
    }

    constexpr BasicDegree<T> &operator -=(BasicDegree<T> other)
    {
        _value -= other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator -=(T other)
    {
        _value -= other;
        return *this;
    }

    constexpr BasicDegree<T> &operator *=(BasicDegree<T> other)
    {
        _value *= other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator *=(T other)
    {
        _value *= other;
        return *this;
    }

    constexpr BasicDegree<T> &operator /=(BasicDegree<T> other)
    {
        _value /= other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator /=(T other)
    {
        _value /= other;
        return *this;
    }
    /// @}  {Operators}

    /** Define the spaceship operator
     *   
     *  @note We define ONLY the <=> AND == operators in order to get all the
     *        other relational operators (C++20).
     *        If we only allowed comparison of ONLY this class type to itself then
     *        we would only need the defaulted <=> operator.
     * 
     *  @{
     */
    constexpr auto operator <=>(const BasicDegree<T> &other) const = default;
    constexpr auto operator <=>(T other) const
    {
        return _value <=> other;
    }
    /// @}

    /** Defines equality of two BasicDegrees
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     * 
     *  @{
     */
    constexpr bool operator ==(const BasicDegree<T> &right) const = default;
    constexpr bool operator ==(T right) const
    {
        return value() == right;
    }
    /// @}

    
    static constexpr T modulus() { return 360; }
    constexpr BasicDegree<T> modulo() const
    {
        T modded;

        // Make in range of 0 - 360
        return BasicDegree<T>{ (0.0 <= (modded = std::fmod( _value, modulus() )) ? modded : modulus() + modded) };
    }

    constexpr bool isNaN() const
    {
        return std::isnan(_value);
    }

    constexpr bool isInf() const
    {
        return std::isinf(_value);
    }

private:
    T _value{};

    /** @addtogroup Equality
     * 
     *  @relates BasicDegree
     *  
     *  @{
     * 
     *  Compares two BasicDegree inputs equal to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     *  
     *  @see Equality
     */
    friend constexpr bool approximately_equal_to(const BasicDegree<T> &value_to_test, const BasicDegree<T> &value_it_should_be, T tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
    }
    /// @}

    /** @name BasicDegree Global Operators
     * 
     *  @relates BasicDegree
     * 
     *  @{
     */
    friend constexpr BasicDegree<T> operator +(BasicDegree<T> left, BasicDegree<T> right)
    {
        return BasicDegree<T>{ left.value() + right.value() };
    }

    friend constexpr BasicDegree<T> operator -(BasicDegree<T> left, BasicDegree<T> right)
    {
        return BasicDegree<T>{ left.value() - right.value() };
    }

    friend constexpr BasicDegree<T> operator *(BasicDegree<T> left, BasicDegree<T> right)
    {
        return BasicDegree<T>{ left.value() * right.value() };
    }

    friend constexpr BasicDegree<T> operator /(BasicDegree<T> left, BasicDegree<T> right)
    {
        return BasicDegree<T>{ left.value() / right.value() };
    }

    friend constexpr BasicDegree<T> operator +(BasicDegree<T> left, T right)
    {
        return BasicDegree<T>{ left.value() + right };
    }

    friend constexpr BasicDegree<T> operator -(BasicDegree<T> left, T right)
    {
        return BasicDegree<T>{ left.value() - right };
    }

    friend constexpr BasicDegree<T> operator *(BasicDegree<T> left, T right)
    {
        return BasicDegree<T>{ left.value() * right };
    }

    friend constexpr BasicDegree<T> operator /(BasicDegree<T> left, T right)
    {
        return BasicDegree<T>{ left.value() / right };
    }

    friend constexpr BasicDegree<T> operator -(BasicDegree<T> input)
    {
        return BasicDegree{ -input.value() };
    }
    /// @}  {BasicDegree}
};


namespace Literals
{
/** @name User-Defined Literals
 * 
 *  @relates BasicDegree
 * 
 *  @{
 */
constexpr BasicDegree<float> operator ""_deg_f(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

constexpr BasicDegree<float> operator ""_deg_F(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

constexpr BasicDegree<float> operator ""_degf(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

constexpr BasicDegree<float> operator ""_degF(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

constexpr BasicDegree<double> operator ""_deg(long double degrees)
{
    return BasicDegree<double>{ static_cast<double>(degrees) };
}

constexpr BasicDegree<long double> operator ""_deg_l(long double degrees)
{
    return BasicDegree<long double>{degrees};
}

constexpr BasicDegree<long double> operator ""_deg_L(long double degrees)
{
    return BasicDegree<long double>{degrees};
}

constexpr BasicDegree<long double> operator ""_degl(long double degrees)
{
    return BasicDegree<long double>{degrees};
}

constexpr BasicDegree<long double> operator ""_degL(long double degrees)
{
    return BasicDegree<long double>{degrees};
}
/// @}  {User-Defined Literals}

/** @name User-Defined Literals
 * 
 *  @relates BasicRadian
 * 
 *  @{
 */
constexpr BasicRadian<float> operator ""_rad_f(long double radians)
{
    return BasicRadian<float>{ static_cast<float>(radians) };
}

constexpr BasicRadian<float> operator ""_rad_F(long double radians)
{
    return BasicRadian<float>{ static_cast<float>(radians) };
}

constexpr BasicRadian<float> operator ""_radf(long double radians)
{
    return BasicRadian<float>{ static_cast<float>(radians) };
}

constexpr BasicRadian<float> operator ""_radF(long double radians)
{
    return BasicRadian<float>{ static_cast<float>(radians) };
}

constexpr BasicRadian<double> operator ""_rad(long double radians)
{
    return BasicRadian<double>{ static_cast<double>(radians) };
}

constexpr BasicRadian<long double> operator ""_rad_l(long double radians)
{
    return BasicRadian<long double>{radians};
}

constexpr BasicRadian<long double> operator ""_rad_L(long double radians)
{
    return BasicRadian<long double>{radians};
}

constexpr BasicRadian<long double> operator ""_radl(long double radians)
{
    return BasicRadian<long double>{radians};
}

constexpr BasicRadian<long double> operator ""_radL(long double radians)
{
    return BasicRadian<long double>{radians};
}
/// @}  {User-Defined Literals}
}

/** @name Degree Type Aliases
 * 
 *  @relates Degree
 * 
 *  @{
 */
using Degreef  = BasicDegree<float>;
using Degreed  = BasicDegree<double>;
using Degree   = BasicDegree<double>;
using Degreel  = BasicDegree<long double>;
/// @} {Degree Type Aliases}

/** @name Radian Type Aliases
 * 
 *  @relates Radian
 * 
 *  @{
 */
using Radianf  = BasicRadian<float>;
using Radiand  = BasicRadian<double>;
using Radian   = BasicRadian<double>;
using Radianl  = BasicRadian<long double>;
/// @}  {Radian Type Aliases}

}