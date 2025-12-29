#pragma once

#include "math/Functions.hpp"
#include <cassert>
#include <concepts>
#include <type_traits>


/** @file
 *  
 *  Contains the definition of the BasicDual class along with
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
class BasicDual
{
public:
    using value_type = T;

    BasicDual() = default;
    explicit constexpr BasicDual(const T &r) : real(r) { }
    explicit constexpr BasicDual(const T &r, const T &e) : real(r), dual(e) { }

    /** @name Constants
     *  @{
     */
    constexpr static BasicDual<T> identity() { return BasicDual{ T{1}, T{0} }; }
    constexpr static BasicDual<T> zero() { return BasicDual{}; }
    /// @}

    constexpr BasicDual<T> conjugate() const
    {
        if constexpr (std::is_floating_point_v<T>)
            return BasicDual{ real, -dual };
        else
            return BasicDual{ real, conjugate(dual) };
    }

    constexpr T       magnitude() const { return real; }

    /** @name Convenience Creation Functions
     *  @{
     */
    /** Creates a pure BasicDual with @c input
     *  
     *  @param input
     *  
     *  @post output.real == 0
     *        output.dual == @c input
     *  
     *  @note A pure BasicDual is one which has the real component set to 0
     */
    constexpr static BasicDual<T> make_pure(const T &input)
    {
        return BasicDual<T>{ T{}, input };
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
    friend constexpr bool operator ==(const BasicDual<T> &left, const BasicDual<T> &right)
    {
        return approximately_equal_to(left, right);
    }

    /** @addtogroup DualAlgebra BasicDual Number Algebra
     *  @{
     */

    /** @name Multiplication
     *  @{
     */
    /** Defines multiplication of two Duals
     */
    friend constexpr BasicDual<T> operator *(const BasicDual<T> &left, const BasicDual<T> &right)
    {
        return BasicDual<T>(left.real * right.real,
                       left.real * right.dual + right.real * left.dual);
    }

    /** Defines multiplication of a single-precision scalar and a BasicDual
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator *(OT scalar, const BasicDual<T> &d)
    {
        return BasicDual<T>( T(scalar) ) * d;
    }

    /** Defines multiplication of a BasicDual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator *(const BasicDual<T> &left, OT scalar)
    {
        return left * BasicDual<T>( T(scalar) );
    }
    /// @}

    /** @name Division
     *  @{
     */
    /** Defines division of two Duals
     */
    friend constexpr BasicDual<T> operator /(const BasicDual<T> &left, const BasicDual<T> &right)
    {
        return BasicDual<T>(left.real * right.real / (right.real * right.real),
                       (left.dual * right.real - left.real * right.dual) / (right.real * right.real));
    }

    /** Defines division of a single-precision scalar and a BasicDual
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator /(OT scalar, const BasicDual<T> &d)
    {
        return BasicDual<T>( T(scalar) ) / d;
    }

    /** Defines division of a BasicDual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator /(const BasicDual<T> &left, OT scalar)
    {
        return left / BasicDual<T>( T(scalar) );
    }
    /// @}

    /** @name Addition
     *  @{
     */
    /** Defines addition of two Duals
     */
    friend constexpr BasicDual<T> operator +(const BasicDual<T> &left, const BasicDual<T> &right)
    {
        return BasicDual<T>(left.real + right.real, left.dual + right.dual);
    }

    /** Defines addition of a single-precision scalar and a BasicDual
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator +(OT scalar, const BasicDual<T> &d)
    {
        return BasicDual<T>( T(scalar) ) + d;
    }

    /** Defines addition of a BasicDual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator +(const BasicDual<T> &left, OT scalar)
    {
        return left + BasicDual<T>( T(scalar) );
    }
    /// @}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two Duals
     */
    friend constexpr BasicDual<T> operator -(const BasicDual<T> &left, const BasicDual<T> &right)
    {
        return BasicDual<T>(left.real - right.real, left.dual - right.dual);
    }

    /** Defines subtraction of a single-precision scalar and a BasicDual
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator -(OT scalar, const BasicDual<T> &d)
    {
        return BasicDual<T>( T(scalar) ) - d;
    }

    /** Defines subtraction of a BasicDual and a single-precision scalar
     */
    template <std::floating_point OT = double>
    friend constexpr BasicDual<T> operator -(const BasicDual<T> &left, OT scalar)
    {
        return left - BasicDual<T>( T(scalar) );
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
     *  @relates BasicDual
     */
    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicDual<T> &value_to_test, const BasicDual<T> &value_it_should_be, OT tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.real, value_it_should_be.real, tolerance) &&
               approximately_equal_to(value_to_test.dual, value_it_should_be.dual, tolerance);
    }
    /// @}  {Equality}

    /** Calculates the dot-product of two Duals
     *  
     *  @return The dot-product of the two inputs
     *  
     *  @note This treats the BasicDual number as a pair of numbers,
     *        or 2D vector, and calculates the dot product as
     *        as expected of that.
     *
     *  @relates BasicDual
     */
    friend constexpr T dot(const BasicDual<T> &left, const BasicDual<T> &right)
    {
        return left.real * right.real +
               left.dual * right.dual;
    }

    /** Calculates the square root of a BasicDual
     *  
     *  This treats the input as a BasicDual scalar and
     *  calculates the square root based on that expectation.
     *  
     *  @return The BasicDual as a dual scalar
     *
     *  @relates BasicDual
     */
    friend constexpr BasicDual<T> dualscalar_sqrt(const BasicDual<T> &input)
    {
        // Expect that T is a scalar type (float, double, int, etc.)
        T root = std::sqrt(input.real);

        return BasicDual<T>{ root, input.dual / (T{2} * root)};
    }

    /** Calculates the square of the norm
     * 
     *  @relates BasicDual
     */
    friend constexpr T dualscalar_normsquared(const BasicDual<T> &d)
    {
        BasicDual<T> result = d * d.conjugate();

        assert( approximately_equal_to(result.dual, T{0}) );

        return result.real;
    }

    /** Accumulates the components of the input BasicDual
     *  
     *  @return A scalar that is the sum of the components
     * 
     *  @relates BasicDual
     */
    friend constexpr T accumulate(const BasicDual<T> &input)
    {
        return T{input.real + input.dual};
    }

    /**  Computes the conjugate of the input
     * 
     *   @note This will just call @c input.conjugate()
     */
    friend constexpr BasicDual<T> conjugate(const BasicDual<T> &input)
    {
        return input.conjugate();
    }

    friend std::string format(const BasicDual<T> &input)
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
    friend bool check_if_equal(const BasicDual<T> &input, const BasicDual<T> &near_to, OT tolerance = OT{0.0002})
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
    friend bool check_if_not_equal(const BasicDual<T> &input, const BasicDual<T> &near_to, OT tolerance = OT{0.0002})
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
    friend void CHECK_IF_EQUAL(const BasicDual<T> &input, const BasicDual<T> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_NOT_EQUAL(const BasicDual<T> &input, const BasicDual<T> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_ZERO(const BasicDual<T> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicDual<T>::zero(), tolerance));
    }
    /// @} {Hidden Friend Functions}
};


/** @name Type Aliases
 * 
 *  @relates BasicDual
 * 
 *  @{
 */
using Dualf = BasicDual<float>;
using Duald = BasicDual<double>;
using Dual  = BasicDual<double>;
using Dualld = BasicDual<long double>;
/// @}

}