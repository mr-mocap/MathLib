#pragma once

#include "math/Functions.hpp"

/** @file
 *  
 *  @hideincludegraph
 */


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

    /** @name Element Access
     *  @{
     */
    T value() const { return _value; }
    /// @}
private:
    T _value{};
};

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
template <class T>
constexpr bool approximately_equal_to(const Radian<T> &value_to_test, const Radian<T> &value_it_should_be, const float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
}
/// @}



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

    Degree<T> &operator -=(const Degree<T> other)
    {
        _value -= other.value();
        return *this;
    }

    Degree<T> &operator *=(const Degree<T> other)
    {
        _value *= other.value();
        return *this;
    }

    Degree<T> &operator /=(const Degree<T> other)
    {
        _value *= other.value();
        return *this;
    }
    /// @}  {Operators}

private:
    T _value{};
};

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
template <class T>
constexpr bool approximately_equal_to(const Degree<T> &value_to_test, const Degree<T> &value_it_should_be, const float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
}
/// @}

/** @name Global Operators
 * 
 *  @relates Degree
 * 
 *  @{
 */
template <class T>
Degree<T> operator +(const Degree<T> left, const Degree<T> right)
{
    return Degree<T>{ left.value() + right.value() };
}

template <class T>
Degree<T> operator -(const Degree<T> left, const Degree<T> right)
{
    return Degree<T>{ left.value() - right.value() };
}

template <class T>
Degree<T> operator *(const Degree<T> left, const Degree<T> right)
{
    return Degree<T>{ left.value() * right.value() };
}

template <class T>
Degree<T> operator /(const Degree<T> left, const Degree<T> right)
{
    return Degree<T>{ left.value() / right.value() };
}

template <class T>
Degree<T> operator +(const Degree<T> left, const T right)
{
    return Degree<T>{ left.value() + right };
}

template <class T>
Degree<T> operator -(const Degree<T> left, const T right)
{
    return Degree<T>{ left.value() - right };
}

template <class T>
Degree<T> operator *(const Degree<T> left, const T right)
{
    return Degree<T>{ left.value() * right };
}

template <class T>
Degree<T> operator /(const Degree<T> left, const T right)
{
    return Degree<T>{ left.value() / right };
}

template <class T>
Degree<T> operator -(const Degree<T> input)
{
    return Degree{ -input.value() };
}
/// @}  {Degree}

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