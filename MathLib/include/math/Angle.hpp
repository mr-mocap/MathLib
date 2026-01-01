#pragma once

#include <math/Functions.hpp>
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
 *
 *  @see @ref RadianLiterals for convenient user-defined literals.
 * 
 *  @headerfile <> <math/Angle.hpp>
 */
template <std::floating_point T>
class BasicRadian
{
public:
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The underlying implementation type
    /// @}

    /** @name Constructors
     *  @{
     */
    constexpr BasicRadian() = default; ///< Defaults to 0
    constexpr BasicRadian(T value) : _value(value) { }
    /// @}

    /** @name Constants
     *  @{
     */
    static constexpr BasicRadian<T> zero() { return BasicRadian<T>(); }
    /// @}

    /** @name Element Access
     *  @{
     */
    T value() const { return _value; }
    /// @}

    /** @name Operators
     *  @{
     */
    constexpr BasicRadian<T> &operator +=(const BasicRadian &other)
    {
        _value += other._value;
        return *this;
    }

    constexpr BasicRadian<T> &operator -=(const BasicRadian &other)
    {
        _value -= other._value;
        return *this;
    }

    constexpr BasicRadian<T> &operator *=(const BasicRadian &other)
    {
        _value *= other._value;
        return *this;
    }

    constexpr BasicRadian<T> &operator /=(const BasicRadian &other)
    {
        _value /= other._value;
        return *this;
    }

    constexpr BasicRadian<T> &operator /=(const T &other)
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
     *  @note We define ONLY the <=> in order to get all six of the
     *        relational operators (C++20).
     */
    friend constexpr auto operator <=>(const BasicRadian<T> &left, const BasicRadian<T> &right) = default;
    /// @}

    /** @name Invalid Value Check
     *  @{
     */
    constexpr bool isNaN() const
    {
        return std::isnan(_value);
    }

    constexpr bool isInf() const
    {
        return std::isinf(_value);
    }
    /// @}

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
    friend constexpr bool approximately_equal_to(const BasicRadian<T> &value_to_test, const BasicRadian<T> &value_it_should_be, T tolerance = T{0.0002})
    {
        return approximately_equal_to(value_to_test.value(), value_it_should_be.value(), tolerance);
    }
    /// @}

    /** @name Operators
     * 
     *  @relates BasicRadian
     * 
     *  @{
     */
    friend constexpr BasicRadian<T> operator +(const BasicRadian<T> &left, const BasicRadian<T> &right)
    {
        return BasicRadian<T>{ left.value() + right.value() };
    }

    friend constexpr BasicRadian<T> operator -(const BasicRadian<T> &left, const BasicRadian<T> &right)
    {
        return BasicRadian<T>{ left.value() - right.value() };
    }

    friend constexpr BasicRadian<T> operator *(const BasicRadian<T> &left, const BasicRadian<T> &right)
    {
        return BasicRadian<T>{ left.value() * right.value() };
    }

    friend constexpr BasicRadian<T> operator /(const BasicRadian<T> &left, const BasicRadian<T> &right)
    {
        return BasicRadian<T>{ left.value() / right.value() };
    }

    friend constexpr BasicRadian<T> operator -(const BasicRadian<T> &input)
    {
        return BasicRadian{ -input.value() };
    }
    /// @}  {Operators}
};


/** Class that stores its units in degrees
 *  
 *  This class exists to try to make it more obviously known what
 *  the units are that are being constructed and passed around.
 *  
 *  This class is mainly for displaying underlying angular units and
 *  therefore attempts have been made to make it easy to convert from
 *  Degree to Radian and vice versa.
 *
 *  @see @ref DegreeLiterals for convenient user-defined literals.
 *
 *  @headerfile <> <math/Angle.hpp>
 */
template <std::floating_point T>
class BasicDegree
{
public:
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The underlying implementation type
    /// @}

    /** @name Constructors
     *  @{
     */
    constexpr BasicDegree() = default; ///< Defaults to 0
    constexpr BasicDegree(T value) : _value(value) { }
    constexpr BasicDegree(const BasicRadian<T> &value) : _value( RadiansToDegrees(value.value()) ) { }
    /// @}

    /** @name Conversion Operators
     *  @{
     */
    operator BasicRadian<T>() { return BasicRadian<T>{DegreesToRadians(_value)}; }
    /// @}

    /** @name Constants
     *  @{
     */
    static constexpr BasicDegree<T> zero() { return BasicDegree<T>(); }
    /// @}

    /** @name Element Access
     *  @{
     */
    T value() const { return _value; }
    /// @}

    /** @name Operators
     *  @{
     */
    constexpr BasicDegree<T> &operator +=(const BasicDegree<T> &other)
    {
        _value += other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator +=(const T &other)
    {
        _value += other;
        return *this;
    }

    constexpr BasicDegree<T> &operator -=(const BasicDegree<T> &other)
    {
        _value -= other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator -=(const T &other)
    {
        _value -= other;
        return *this;
    }

    constexpr BasicDegree<T> &operator *=(const BasicDegree<T> &other)
    {
        _value *= other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator *=(const T &other)
    {
        _value *= other;
        return *this;
    }

    constexpr BasicDegree<T> &operator /=(const BasicDegree<T> &other)
    {
        _value /= other.value();
        return *this;
    }

    constexpr BasicDegree<T> &operator /=(const T &other)
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
     *  @note We define ONLY the <=> in order to get all six of the
     *        relational operators (C++20).
     * 
     *  @{
     */
    friend constexpr auto operator <=>(const BasicDegree<T> &left, const BasicDegree<T> &right) = default;
    /// @}
    /// @}

    static constexpr T modulus() { return 360; }
    constexpr BasicDegree<T> modulo() const
    {
        T modded;

        // Make in range of 0 - 360
        return BasicDegree<T>{ (0.0 <= (modded = std::fmod( _value, modulus() )) ? modded : modulus() + modded) };
    }

    /** @name Invalid Value Check
     *  @{
     */
    constexpr bool isNaN() const
    {
        return std::isnan(_value);
    }

    constexpr bool isInf() const
    {
        return std::isinf(_value);
    }
    /// @}

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

    /** @name Operators
     * 
     *  @relates BasicDegree
     * 
     *  @{
     */
    friend constexpr BasicDegree<T> operator +(const BasicDegree<T> &left, const BasicDegree<T> &right)
    {
        return BasicDegree<T>{ left.value() + right.value() };
    }

    friend constexpr BasicDegree<T> operator -(const BasicDegree<T> &left, const BasicDegree<T> &right)
    {
        return BasicDegree<T>{ left.value() - right.value() };
    }

    friend constexpr BasicDegree<T> operator *(const BasicDegree<T> &left, const BasicDegree<T> &right)
    {
        return BasicDegree<T>{ left.value() * right.value() };
    }

    friend constexpr BasicDegree<T> operator /(const BasicDegree<T> &left, const BasicDegree<T> &right)
    {
        return BasicDegree<T>{ left.value() / right.value() };
    }

    friend constexpr BasicDegree<T> operator +(const BasicDegree<T> &left, const T &right)
    {
        return BasicDegree<T>{ left.value() + right };
    }

    friend constexpr BasicDegree<T> operator -(const BasicDegree<T> &left, const T &right)
    {
        return BasicDegree<T>{ left.value() - right };
    }

    friend constexpr BasicDegree<T> operator *(const BasicDegree<T> left, const T &right)
    {
        return BasicDegree<T>{ left.value() * right };
    }

    friend constexpr BasicDegree<T> operator /(const BasicDegree<T> &left, const T &right)
    {
        return BasicDegree<T>{ left.value() / right };
    }

    friend constexpr BasicDegree<T> operator -(const BasicDegree<T> &input)
    {
        return BasicDegree{ -input.value() };
    }
    /// @}  {Operators}
};


namespace Literals
{

/** @defgroup DegreeUserDefinedLiterals Degree Literals

 *  Here are the user-defined literals for Radian
 * 
 *  @ingroup UserDefinedLiterals
 * 
 *  @{
 */
/** @name User-Defined Literals
 * 
 *  @relates BasicDegree
 *  @{
 */
/** Documentation */
constexpr BasicDegree<float> operator ""_deg_f(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

/** Documentation */
constexpr BasicDegree<float> operator ""_deg_F(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

/** Documentation */
constexpr BasicDegree<float> operator ""_degf(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

/** Documentation */
constexpr BasicDegree<float> operator ""_degF(long double degrees)
{
    return BasicDegree<float>{ static_cast<float>(degrees) };
}

/** Documentation */
constexpr BasicDegree<double> operator ""_deg(long double degrees)
{
    return BasicDegree<double>{ static_cast<double>(degrees) };
}

/** Documentation */
constexpr BasicDegree<long double> operator ""_deg_l(long double degrees)
{
    return BasicDegree<long double>{degrees};
}

/** Documentation */
constexpr BasicDegree<long double> operator ""_deg_L(long double degrees)
{
    return BasicDegree<long double>{degrees};
}

/** Documentation */
constexpr BasicDegree<long double> operator ""_degl(long double degrees)
{
    return BasicDegree<long double>{degrees};
}

/** Documentation */
constexpr BasicDegree<long double> operator ""_degL(long double degrees)
{
    return BasicDegree<long double>{degrees};
}
/// @}
/// @}  {User-Defined Literals}

}

namespace Literals
{

/** @defgroup RadianUserDefinedLiterals Radian Literals
 *  
 *  Here are the user-defined literals for Radian
 * 
 *  @ingroup UserDefinedLiterals
 * 
 *  @{
 */
/** @name User-Defined Literals
 * 
 *  @relates BasicRadian
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
/// @}
/// @}

}

/** @defgroup DegreeAliases Degree Types
 * 
 *  Here are the type aliases for Degrees
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicDegree
 *  @{
 */
using Degreef  = BasicDegree<float>;
using Degreed  = BasicDegree<double>;
using Degree   = BasicDegree<double>;
using Degreel  = BasicDegree<long double>;
/// @}
/// @}  {DegreeAliases}

/** @defgroup RadianAliases Radian Types
 * 
 *  Here are the type aliases for Radian
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicRadian
 *  @{
 */
using Radianf  = BasicRadian<float>;
using Radiand  = BasicRadian<double>;
using Radian   = BasicRadian<double>;
using Radianl  = BasicRadian<long double>;
/// @}
/// @}  {RadianAliases}

}