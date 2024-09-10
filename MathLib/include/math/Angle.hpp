#pragma once

#include "math/Conversions.hpp"

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

    T value() const { return _value; }
private:
    T _value{};
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

    T value() const { return _value; }

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

private:
    T _value{};
};

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

/** @addtogroup UserDefinedLiterals User-Defined Literals
 * 
 *  @{
 */
/// Creates a Degree<float> object with the given value
constexpr Degree<float> operator ""_deg_f(long double degrees)
{
    return Degree<float>{ static_cast<float>(degrees) };
}

/// Creates a Degree<double> object with the given value
constexpr Degree<double> operator ""_deg(long double degrees)
{
    return Degree<double>{ static_cast<double>(degrees) };
}

/// Creates a Degree<long double> object with the given value
constexpr Degree<long double> operator ""_deg_ld(long double degrees)
{
    return Degree{degrees};
}
/// @}


/** @name Degree Type Aliases
 * 
 *  @{
 */
using Degreef  = Degree<float>;
using Degreed  = Degree<double>;
using Degreeld = Degree<long double>;
/// @}

/** @name Radian Type Aliases
 * 
 *  @{
 */
using Radianf  = Radian<float>;
using Radiand  = Radian<double>;
using Radianld = Radian<long double>;
/// @}
