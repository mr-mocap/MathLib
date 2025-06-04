#pragma once

#include "math/Functions.hpp"
#include <cassert>
#include <concepts>
#include <type_traits>


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

    constexpr Dual<T> conjugate() const
    {
        if constexpr (std::is_floating_point_v<T>)
            return Dual{ real, -dual };
        else
            return Dual{ real, conjugate(dual) };
    }

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
        if constexpr ( std::is_floating_point_v<T> )
            return std::isnan(real) || std::isnan(dual);
        else
            return real.isNaN() || dual.isNaN();
    }

    bool isInf() const
    {
        if constexpr ( std::is_floating_point_v<T> )
            return std::isinf(real) || std::isinf(dual);
        else
            return real.isInf() || dual.isInf();
    }

    /** @name Element Access
     *  @{
     */
    T real{};
    T dual{};
    /// @}

    /** @name Hidden Friend Functions
     *  @{
     */

    /** Defines equality of two Duals
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     */
    friend constexpr bool operator ==(const Dual<T> &left, const Dual<T> &right)
    {
        return approximately_equal_to(left, right);
    }

    /** @addtogroup DualAlgebra Dual Number Algebra
     *  @{
     */

    /** @name Multiplication
     *  @{
     */
    /** Defines multiplication of two Duals
     */
    friend constexpr Dual<T> operator *(const Dual<T> &left, const Dual<T> &right)
    {
        return Dual<T>(left.real * right.real,
                       left.real * right.dual + right.real * left.dual);
    }

    /** Defines multiplication of a single-precision scalar and a Dual
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator *(OT scalar, const Dual<T> &d)
    {
        return Dual<T>( T(scalar) ) * d;
    }

    /** Defines multiplication of a Dual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator *(const Dual<T> &left, OT scalar)
    {
        return left * Dual<T>( T(scalar) );
    }
    /// @}

    /** @name Division
     *  @{
     */
    /** Defines division of two Duals
     */
    friend constexpr Dual<T> operator /(const Dual<T> &left, const Dual<T> &right)
    {
        return Dual<T>(left.real * right.real / (right.real * right.real),
                       (left.dual * right.real - left.real * right.dual) / (right.real * right.real));
    }

    /** Defines division of a single-precision scalar and a Dual
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator /(OT scalar, const Dual<T> &d)
    {
        return Dual<T>( T(scalar) ) / d;
    }

    /** Defines division of a Dual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator /(const Dual<T> &left, OT scalar)
    {
        return left / Dual<T>( T(scalar) );
    }
    /// @}

    /** @name Addition
     *  @{
     */
    /** Defines addition of two Duals
     */
    friend constexpr Dual<T> operator +(const Dual<T> &left, const Dual<T> &right)
    {
        return Dual<T>(left.real + right.real, left.dual + right.dual);
    }

    /** Defines addition of a single-precision scalar and a Dual
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator +(OT scalar, const Dual<T> &d)
    {
        return Dual<T>( T(scalar) ) + d;
    }

    /** Defines addition of a Dual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator +(const Dual<T> &left, OT scalar)
    {
        return left + Dual<T>( T(scalar) );
    }
    /// @}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two Duals
     */
    friend constexpr Dual<T> operator -(const Dual<T> &left, const Dual<T> &right)
    {
        return Dual<T>(left.real - right.real, left.dual - right.dual);
    }

    /** Defines subtraction of a single-precision scalar and a Dual
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator -(OT scalar, const Dual<T> &d)
    {
        return Dual<T>( T(scalar) ) - d;
    }

    /** Defines subtraction of a Dual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr Dual<T> operator -(const Dual<T> &left, OT scalar)
    {
        return left - Dual<T>( T(scalar) );
    }
    /// @}  {Subtraction}
    /// @}  {DualAlgebra}

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
    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const Dual<T> &value_to_test, const Dual<T> &value_it_should_be, OT tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.real, value_it_should_be.real, tolerance) &&
               approximately_equal_to(value_to_test.dual, value_it_should_be.dual, tolerance);
    }
    /// @}  {Equality}

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
    friend constexpr T dot(const Dual<T> &left, const Dual<T> &right)
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
    friend constexpr Dual<T> dualscalar_sqrt(const Dual<T> &input)
    {
        // Expect that T is a scalar type (float, double, int, etc.)
        T root = std::sqrt(input.real);

        return Dual<T>{ root, input.dual / (T{2} * root)};
    }

    /** Calculates the square of the norm
     * 
     *  @relates Dual
     */
    friend constexpr T dualscalar_normsquared(const Dual<T> &d)
    {
        Dual<T> result = d * d.conjugate();

        assert( approximately_equal_to(result.dual, T{0}) );

        return result.real;
    }

    /** Accumulates the components of the input Dual
     *  
     *  @return A scalar that is the sum of the components
     * 
     *  @relates Dual
     */
    friend constexpr T accumulate(const Dual<T> &input)
    {
        return T{input.real + input.dual};
    }

    /**  Computes the conjugate of the input
     * 
     *   @note This will just call @c input.conjugate()
     */
    friend constexpr Dual<T> conjugate(const Dual<T> &input)
    {
        return input.conjugate();
    }

    friend std::string format(const Dual<T> &input)
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
    template <std::floating_point OT = float>
    friend bool check_if_equal(const Dual<T> &input, const Dual<T> &near_to, OT tolerance = OT{0.0002})
    {
        if (!approximately_equal_to(input, near_to, tolerance))
        {
            auto diff{ near_to - input };

            std::cout << std::format("input: {} is not equal to near_to: {} within tolerance: {}.  Difference is {} .",
                                     format(input),
                                     format(near_to),
                                     tolerance,
                                     format(near_to - input))
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
    template <std::floating_point OT = float>
    friend bool check_if_not_equal(const Dual<T> &input, const Dual<T> &near_to, OT tolerance = OT{0.0002})
    {
        if (approximately_equal_to(input, near_to, tolerance))
        {
            auto diff{ near_to - input };

            std::cout << std::format("input: {} is equal to near_to: {} within tolerance: {}.  Difference is {} .",
                                     format(input),
                                     format(near_to),
                                     tolerance,
                                     format(near_to - input))
            << std::endl;
            return  false;
        }
        return true;
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_EQUAL(const Dual<T> &input, const Dual<T> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_NOT_EQUAL(const Dual<T> &input, const Dual<T> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_ZERO(const Dual<T> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, Dual<T>::zero(), tolerance));
    }
    /// @} {Hidden Friend Functions}
};


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