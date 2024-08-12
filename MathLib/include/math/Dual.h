#pragma once

#include "math/ApproximatelyEqualTo.h"
#include "math/Conjugate.h"
#include "math/types.h"
#include <cassert>


/** @file
 *  
 *  Contains the definition of the Dual class along with
 *  various helper functions.
 */

/** Class representing the concept of a dual number
 *  
 */
template<class T>
class Dual
{
public:
    using value_type = T;

    Dual() = default;
    explicit constexpr Dual(const value_type r) : real(r) { }
    explicit constexpr Dual(const value_type r, const value_type e) : real(r), dual(e) { }
    explicit constexpr Dual(const std::tuple<value_type, value_type> tuple) : real(std::get<0>(tuple)), dual(std::get<1>(tuple)) { }

    constexpr static Dual<T> identity() { return Dual{ T{1}, T{0} }; }
    constexpr static Dual<T> zero() { return Dual{}; }

    constexpr Dual<T> conjugate() const { return Dual{ real, ::conjugate(dual) }; }
    constexpr value_type magnitude() const { return real; }

    value_type real{};
    value_type dual{};
};

/** Compares two Dual inputs equal, component-wise, to within a tolerance
 *  
 *  @param value_to_test
 *  @param value_it_should_be 
 *  @param tolerance          How close they should be to be considered equal
 *  
 *  @return @c true if they are equal
 *  
 *  @see approximately_equal_to
 */
template<class T>
constexpr bool approximately_equal_to(Dual<T> value_to_test, Dual<T> value_it_should_be, float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.real, value_it_should_be.real, tolerance) &&
           approximately_equal_to(value_to_test.dual, value_it_should_be.dual, tolerance);
}

/** Defines equality of two Duals
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see approximately_equal_to
 */
template<class T>
constexpr bool operator ==(Dual<T> left, Dual<T> right)
{
    return approximately_equal_to(left, right);
}

/** Defines inequality of two Quaternions
 *  
 *  @note Uses operator ==()
 *  
 *  @see approximately_equal_to
 */
template<class T>
constexpr bool operator !=(Dual<T> left, Dual<T> right)
{
    return !(left == right);
}

/** Defines multiplication of two Dual objects
 *  
 */
template<class T>
constexpr Dual<T> operator *(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real * right.real,
                   left.real * right.dual + left.dual * right.real);
}

///@{
/** Defines scaling a Dual
 *  
 */
template<class T>
constexpr Dual<T> operator *(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) * d;
}

template<class T>
constexpr Dual<T> operator *(Dual<T> d, float scalar)
{
    return d * Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator *(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) * d;
}

template<class T>
constexpr Dual<T> operator *(Dual<T> d, double scalar)
{
    return d * Dual<T>( T(scalar) );
}
///@}

/** Defines division of Duals
 *  
 */
template<class T>
constexpr Dual<T> operator /(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real * right.real / (right.real * right.real),
        (left.dual * right.real - left.real * right.dual) / (right.real * right.real));
}

///@{
/** Defines dividing a Dual by a scalar
 */
template<class T>
constexpr Dual<T> operator /(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) / d;
}

template<class T>
constexpr Dual<T> operator /(Dual<T> d, float scalar)
{
    return d / Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator /(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) / d;
}

template<class T>
constexpr Dual<T> operator /(Dual<T> d, double scalar)
{
    return d / Dual<T>( T(scalar) );
}
///@}

///@{
/** Defines addition of Duals
 */
template<class T>
constexpr Dual<T> operator +(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real + right.real, left.dual + right.dual);
}

template<class T>
constexpr Dual<T> operator +(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) + d;
}

template<class T>
constexpr Dual<T> operator +(Dual<T> d, float scalar)
{
    return d + Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator +(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) + d;
}

template<class T>
constexpr Dual<T> operator +(Dual<T> d, double scalar)
{
    return d + Dual<T>( T(scalar) );
}
///@}

///@{
/** Defines subtraction of Duals
 */
template<class T>
constexpr Dual<T> operator -(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real - right.real, left.dual - right.dual);
}

template<class T>
constexpr Dual<T> operator -(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) - d;
}

template<class T>
constexpr Dual<T> operator -(Dual<T> d, float scalar)
{
    return d - Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator -(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) - d;
}

template<class T>
constexpr Dual<T> operator -(Dual<T> d, double scalar)
{
    return d - Dual<T>( T(scalar) );
}
///@}

/** Calculates the dot-product of two Duals
 *  
 *  @return The dot-product of the two inputs
 *  
 *  @note This treats the Dual number as a pair of numbers,
 *        or 2D vector, and calculates the dot product as
 *        as expected of that.
 */
template<class T>
constexpr T dot(Dual<T> left, Dual<T> right)
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
 */
template<class T>
constexpr Dual<T> dualscalar_sqrt(Dual<T> input)
{
    // Expect that T is a scalar type (float, double, int, etc.)
    T root = std::sqrt(input.real);

    return Dual<T>{ root, input.dual / (2 * root)};
}

template<class T>
constexpr T dualscalar_normsquared(Dual<T> d)
{
    Dual<T> result = d * conjugate(d);

    assert( approximately_equal_to(result.dual, 0) );

    return result.real;
}

/** Accumulates the components of the input Dual
 *  
 *  @return A scalar that is the sum of the components
 */
template<class T>
constexpr T accumulate(Dual<T> input)
{
    return T{input.real + input.dual};
}

/** Creates a pure Dual with @c input
 *  
 *  @param input
 *  
 *  @post output.real == 0
 *        output.dual == @c input
 *  
 *  @note A pure Dual is one which has the real component set to 0
 */
template<class T>
constexpr Dual<T> make_pure_dual(T input)
{
    return Dual<T>{ T{}, input };
}

///@{
using Dualf = Dual<float>;
using Duald = Dual<double>;
using Dualld = Dual<long double>;
///@}
