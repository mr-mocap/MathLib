#pragma once

#include "math/Functions.hpp"
#include <cassert>


/** @file
 *  
 *  Contains the definition of the Dual class along with
 *  various helper functions.
 *
 *  @hideincludegraph
 */

namespace Math
{

/** Class representing the concept of a dual number
 *  
 *  @headerfile "math/Dual.hpp"
 */
template<class T>
class Dual
{
public:
    using value_type = T;

    Dual() = default;
    explicit constexpr Dual(const T &r) : real(r) { }
    explicit constexpr Dual(const T &r, const T &e) : real(r), dual(e) { }

    /** @name Constants
     *  @{
     */
    constexpr static Dual<T> identity() { return Dual{ T{1}, T{0} }; }
    constexpr static Dual<T> zero() { return Dual{}; }
    /// @}

    constexpr Dual<T> conjugate() const { return Dual{ real, Math::conjugate(dual) }; }
    constexpr T       magnitude() const { return real; }

    /** @name Convenience Creation Functions
     *  @{
     */
    /** Creates a pure Dual with @c input
     *  
     *  @param input
     *  
     *  @post output.real == 0
     *        output.dual == @c input
     *  
     *  @note A pure Dual is one which has the real component set to 0
     */
    constexpr static Dual<T> make_pure(const T &input)
    {
        return Dual<T>{ T{}, input };
    }
    /// @}

    bool isNaN() const
    {
        return std::isnan(real) || std::isnan(dual);
    }

    bool isInf() const
    {
        return std::isinf(real) || std::isinf(dual);
    }

    /** @name Element Access
     *  @{
     */
    T real{};
    T dual{};
    /// @}
};

/** @addtogroup Equality
 * 
 *  @{
 *  
 *  Compare two values for equality with a tolerance
 *  
 *  @param input     The first value to compare
 *  @param near_to   The second value to compare
 *  @param tolerance The minimum value for being considered equal
 * 
 *  @return @c true if the two are equal within @c tolerance , @c false otherwise
 * 
 *  @relates Dual
 */
template<class T>
constexpr bool approximately_equal_to(const Dual<T> &value_to_test, const Dual<T> &value_it_should_be, float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.real, value_it_should_be.real, tolerance) &&
           approximately_equal_to(value_to_test.dual, value_it_should_be.dual, tolerance);
}
/// @}  {Equality}

/** @name Global Operators
 * 
 *  @relates Dual
 * 
 *  @{
 */

/** Defines equality of two Duals
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 */
template<class T>
constexpr bool operator ==(const Dual<T> &left, const Dual<T> &right)
{
    return approximately_equal_to(left, right);
}

/** Defines inequality of two Duals
 *  
 *  @note Uses operator ==()
 *  
 *  @see Equality
 */
template<class T>
constexpr bool operator !=(const Dual<T> &left, const Dual<T> &right)
{
    return !(left == right);
}

/** @addtogroup DualAlgebra Dual Number Algebra
 *  @{
 */

/** @name Multiplication
 *  @{
 */
/** Defines multiplication of two Duals
 */
template<class T>
constexpr Dual<T> operator *(const Dual<T> &left, const Dual<T> &right)
{
    return Dual<T>(left.real * right.real,
                   left.real * right.dual + right.real * left.dual);
}

/** Defines multiplication of a single-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator *(const float scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) * d;
}

/** Defines multiplication of a Dual and a single-precision scalar
 */
template<class T>
constexpr Dual<T> operator *(const Dual<T> &d, const float scalar)
{
    return d * Dual<T>( T(scalar) );
}

/** Defines multiplication of a double-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator *(const double scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) * d;
}

/** Defines multiplication of a Dual and a double-precision scalar
 */
template<class T>
constexpr Dual<T> operator *(const Dual<T> &d, const double scalar)
{
    return d * Dual<T>( T(scalar) );
}
/// @}

/** @name Division
 *  @{
 */
/** Defines division of two Duals
 */
template<class T>
constexpr Dual<T> operator /(const Dual<T> &left, const Dual<T> &right)
{
    return Dual<T>(left.real * right.real / (right.real * right.real),
        (left.dual * right.real - left.real * right.dual) / (right.real * right.real));
}

/** Defines division of a single-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator /(const float scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) / d;
}

/** Defines division of a Dual and a single-precision scalar
 */
template<class T>
constexpr Dual<T> operator /(const Dual<T> &d, const float scalar)
{
    return d / Dual<T>( T(scalar) );
}

/** Defines division of a double-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator /(const double scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) / d;
}

/** Defines division of a Dual and a double-precision scalar
 */
template<class T>
constexpr Dual<T> operator /(const Dual<T> &d, const double scalar)
{
    return d / Dual<T>( T(scalar) );
}
/// @}

/** @name Addition
 *  @{
 */
/** Defines addition of two Duals
 */
template<class T>
constexpr Dual<T> operator +(const Dual<T> &left, const Dual<T> &right)
{
    return Dual<T>(left.real + right.real, left.dual + right.dual);
}

/** Defines addition of a single-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator +(const float scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) + d;
}

/** Defines addition of a Dual and a single-precision scalar
 */
template<class T>
constexpr Dual<T> operator +(const Dual<T> &d, const float scalar)
{
    return d + Dual<T>( T(scalar) );
}

/** Defines addition of a double-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator +(const double scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) + d;
}

/** Defines addition of a Dual and a double-precision scalar
 */
template<class T>
constexpr Dual<T> operator +(const Dual<T> &d, const double scalar)
{
    return d + Dual<T>( T(scalar) );
}
/// @}

/** @name Subtraction
 *  @{
 */
/** Defines subtraction of two Duals
 */
template<class T>
constexpr Dual<T> operator -(const Dual<T> &left, const Dual<T> &right)
{
    return Dual<T>(left.real - right.real, left.dual - right.dual);
}

/** Defines subtraction of a single-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator -(const float scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) - d;
}

/** Defines subtraction of a Dual and a single-precision scalar
 */
template<class T>
constexpr Dual<T> operator -(const Dual<T> &d, const float scalar)
{
    return d - Dual<T>( T(scalar) );
}

/** Defines subtraction of a double-precision scalar and a Dual
 */
template<class T>
constexpr Dual<T> operator -(const double scalar, const Dual<T> &d)
{
    return Dual<T>( T(scalar) ) - d;
}

/** Defines subtraction of a Dual and a double-precision scalar
 */
template<class T>
constexpr Dual<T> operator -(const Dual<T> &d, const double scalar)
{
    return d - Dual<T>( T(scalar) );
}
/// @}  {Subtraction}
/// @}  {DualAlgebra}
/// @}  {GlobalOperators}

/** @name Global Functions
 * 
 *  @relates Dual
 * 
 *  @{
 */
/** Calculates the dot-product of two Duals
 *  
 *  @return The dot-product of the two inputs
 *  
 *  @note This treats the Dual number as a pair of numbers,
 *        or 2D vector, and calculates the dot product as
 *        as expected of that.
 *
 *  @relates Dual
 */
template<class T>
constexpr T dot(const Dual<T> &left, const Dual<T> &right)
{
    return left.real * right.real +
           left.dual * right.dual;
}

/** Calculates the square root of a Dual
 *  
 *  This treats the input as a Dual scalar and
 *  calculates the square root based on that expectation.
 *  
 *  @return The Dual as a dual scalar
 *
 *  @relates Dual
 */
template<class T>
constexpr Dual<T> dualscalar_sqrt(const Dual<T> &input)
{
    // Expect that T is a scalar type (float, double, int, etc.)
    T root = std::sqrt(input.real);

    return Dual<T>{ root, input.dual / (T{2} * root)};
}

/** Calculates the square of the norm
 * 
 *  @relates Dual
 */
template<class T>
constexpr T dualscalar_normsquared(const Dual<T> &d)
{
    Dual<T> result = d * conjugate(d);

    assert( approximately_equal_to(result.dual, T{0}) );

    return result.real;
}

/** Accumulates the components of the input Dual
 *  
 *  @return A scalar that is the sum of the components
 * 
 *  @relates Dual
 */
template<class T>
constexpr T accumulate(const Dual<T> &input)
{
    return T{input.real + input.dual};
}
/// @}  {GlobalFunctions}

template <class T>
std::string format(const Dual<T> &input)
{
    return std::format("[real: {}, dual: {}]", input.real, input.dual);
}

/** @addtogroup Checks
 * 
 *  Compare two values for equality with a tolerance and prints debug information when false
 *  
 *  @param input     The first value to compare
 *  @param near_to   The second value to compare
 *  @param tolerance The minimum value for being considered equal
 * 
 *  @return @c true if the two are equal within @c tolerance , @c false otherwise
 */
template <class T>
bool check_if_equal(const Dual<T> &input, const Dual<T> &near_to, float tolerance = 0.0002f)
{
    if (!approximately_equal_to(input, near_to, tolerance))
    {
        auto diff{ near_to - input };

        std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {} .",
                                 Math::format(input),
                                 Math::format(near_to),
                                 tolerance,
                                 Math::format(near_to - input))
        << std::endl;
        return  false;
    }
    return true;
}

/** @addtogroup Checks
 * 
 *  Compare two values for inequality with a tolerance and prints debug information when false
 *  
 *  @param input     The first value to compare
 *  @param near_to   The second value to compare
 *  @param tolerance The minimum value for being considered equal
 * 
 *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
 */
template <class T>
bool check_if_not_equal(const Dual<T> &input, const Dual<T> &near_to, float tolerance = 0.0002f)
{
    if (approximately_equal_to(input, near_to, tolerance))
    {
        auto diff{ near_to - input };

        std::cout << std::format("input: {} is equal to near_to: {} within tolerance: {}.  Difference is {} .",
                                 Math::format(input),
                                 Math::format(near_to),
                                 tolerance,
                                 Math::format(near_to - input))
        << std::endl;
        return  false;
    }
    return true;
}

template <class T>
void CHECK_IF_EQUAL(const Dual<T> &input, const Dual<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_NOT_EQUAL(const Dual<T> &input, const Dual<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_ZERO(const Dual<T> &input, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, Dual<T>::zero(), tolerance));
}

/** @name Type Aliases
 * 
 *  @relates Dual
 * 
 *  @{
 */
using Dualf = Dual<float>;
using Duald = Dual<double>;
using Dualld = Dual<long double>;
/// @}

}