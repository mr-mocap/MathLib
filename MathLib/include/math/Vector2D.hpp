#pragma once

#include "math/Functions.hpp"
#include <concepts>

/** @file
 *  
 *  Contains the definition of 2D vector class
 *
 *  @hideincludegraph
 */

namespace Math
{

/** A simple 2D vector class
 *
 *  @headerfile <> <math/Vector2D.hpp>
 */
template <class Type>
struct BasicVector2D
{
    /** @name Types
     *  @{
     */
    using value_type = Type; ///< The underlying implementation type
    /// @}

    /** Class representing a reference to elements of a BasicVector2D object
     * 
     *  @note This class exists to support simple vector swizzle operations.
     * 
     *  @relates BasicVector2D
     */
    struct Ref
    {
        /** @name Types
         *  @{
         */
        using value_type = Type; ///< The underlying implementation type
        /// @}

        /** @name Constructors
         * 
         *  @{
         */
        constexpr Ref(Type &x_in, Type &y_in) : x{x_in}, y{y_in} { }
        constexpr Ref(const Ref &) = default;
        constexpr Ref(const BasicVector2D<Type> &other) : x{other.x}, y{other.y} { }
        /// @}

        /** @name Assignment
         *  @{
         */
        constexpr Ref &operator =(const Ref &input)
        {
            x = input.x;
            y = input.y;
            return *this;
        }

        constexpr Ref &operator =(const BasicVector2D<Type> &input)
        {
            x = input.x;
            y = input.y;
            return *this;
        }
        /// @}

        /** @name Equality
         *  @{
         */
        /** Defines equality of two BasicVector2D::Ref objects
         *  
         *  @note Uses approximately_equal_to under-the-hood
         *  
         *  @note We take advantage of the new C++20 rule where if there
         *        is not an appropriate operator ==(const BasicVector2D<Type> &) defined
         *        for this class, then the compiler tries a swapped instantiation
         *        in its place.  This allows us to only define the typical operator ==() here
         *        and then define comparison of different types to the other class.
         * 
         *  @see Equality
         */
        friend constexpr bool operator ==(const Ref &left, const Ref &right)
        {
            return approximately_equal_to( left, right );
        }

        friend constexpr bool operator ==(const Ref &left, const BasicVector2D<Type> &right)
        {
            return approximately_equal_to( left, right );
        }
        /// @}

        /** @addtogroup Vector2DAlgebra 2D Vector Algebra
         * 
         *  Two Dimensional Vector Algebra
         * 
         *  @{
         */

        /** @name Operators
         * 
         *  @relates BasicVector2D
         * 
         *  @{
         */
        friend constexpr BasicVector2D<Type> operator +(const Ref &left, const Ref &right)
        {
            return { left.x + right.x, left.y + right.y };
        }
        friend constexpr BasicVector2D<Type> operator +(const Ref &left, const BasicVector2D<Type> &right)
        {
            return { left.x + right.x, left.y + right.y };
        }

        friend constexpr BasicVector2D<Type> operator -(const Ref &left, const Ref &right)
        {
            return { left.x - right.x, left.y - right.y };
        }
        friend constexpr BasicVector2D<Type> operator -(const Ref &left, const BasicVector2D<Type> &right)
        {
            return { left.x - right.x, left.y - right.y };
        }

        friend constexpr BasicVector2D<Type> operator *(const Ref &left, const Ref &right)
        {
            return { left.x * right.x, left.y * right.y };
        }
        friend constexpr BasicVector2D<Type> operator *(const Ref &left, const BasicVector2D<Type> &right)
        {
            return { left.x * right.x, left.y * right.y };
        }

        friend constexpr BasicVector2D<Type> operator *(const Ref &left, Type scalar)
        {
            return { left.x * scalar, left.y * scalar };
        }
        friend constexpr BasicVector2D<Type> operator *(Type scalar, const Ref &right)
        {
            return { scalar * right.x, scalar * right.y };
        }

        friend constexpr BasicVector2D<Type> operator /(const Ref &left, const Ref &right)
        {
            return { left.x / right.x, left.y / right.y };
        }
        friend constexpr BasicVector2D<Type> operator /(const Ref &left, const BasicVector2D<Type> &right)
        {
            return { left.x / right.x, left.y / right.y };
        }

        friend constexpr BasicVector2D<Type> operator /(const Ref &left, Type scalar)
        {
            return { left.x / scalar, left.y / scalar };
        }
        friend constexpr BasicVector2D<Type> operator /(Type scalar, const Ref &right)
        {
            return { scalar / right.x, scalar / right.y };
        }
        /// @} {Operators}
        /// @} {Vector2DAlgebra}

        /** @name Conversion Operators
         *  @{
         */
        /** BasicVector2D conversion operator
         * 
         *  This allows Ref objects to automatically be converted to BasicVector2D objects
         *  for situations like passing to functions or constructors to BasicVector2D objects.
         */
        constexpr operator BasicVector2D<Type>() const { return BasicVector2D<Type>{ x, y }; }
        /// @}

        /** @name Element Access
         *  
         *  @{
         */
        Type &x;
        Type &y;
        /// @}


        /** Compares two BasicVector2D inputs equal, component-wise, to within a tolerance
         * 
         *  @addtogroup Equality
         * 
         *  @relates BasicVector2D
         *  
         *  @param value_to_test
         *  @param value_it_should_be 
         *  @param tolerance          How close they should be to be considered equal
         *  
         *  @return @c true if they are equal
         */
        template <std::floating_point OT = float>
        friend constexpr bool approximately_equal_to(const Ref &value_to_test, const Ref &value_it_should_be, OT tolerance = OT{0.0002})
        {
            return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
                   approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
        }

        /** Compares a BasicVector2D::Ref and BasicVector2D inputs equal, component-wise, to within a tolerance
         * 
         *  @addtogroup Equality
         * 
         *  @relates BasicVector2D
         *  
         *  @param value_to_test
         *  @param value_it_should_be 
         *  @param tolerance          How close they should be to be considered equal
         *  
         *  @return @c true if they are equal
         */
        template <std::floating_point OT = float>
        friend constexpr bool approximately_equal_to(const Ref                 &value_to_test,
                                                     const BasicVector2D<Type> &value_it_should_be,
                                                           OT                   tolerance = OT{0.0002})
        {
            return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
                   approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
        }

        friend constexpr Type accumulate(const Ref &input)
        {
            return input.x + input.y;
        }

        friend constexpr Type dot(const Ref &left, const Ref &right)
        {
            return (left.x * right.x) + (left.y * right.y);
        }
        friend constexpr Type dot(const Ref &left, const BasicVector2D<Type> &right)
        {
            return (left.x * right.x) + (left.y * right.y);
        }

        friend constexpr Type dot_normalized(const Ref &left, const Ref &right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }
        friend constexpr Type dot_normalized(const Ref &left, const BasicVector2D<Type> &right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }

        friend constexpr Type cross(const Ref &left, const Ref &right)
        {
            return (left.x * right.y) - (left.y * right.x);
        }
        friend constexpr Type cross(const Ref &left, const BasicVector2D<Type> &right)
        {
            return (left.x * right.y) - (left.y * right.x);
        }

        friend constexpr BasicVector2D<Type> abs(const Ref &input)
        {
            return { std::abs(input.x), std::abs(input.y) };
        }

        friend constexpr BasicVector2D<Type> fract(const Ref &input)
        {
            return { std::modf(input.x), std::modf(input.y) };
        }

        constexpr BasicVector2D<Type> saturate(const Ref &input, Type lower_bound, Type upper_bound)
        {
            return { Math::saturate(input.x, lower_bound, upper_bound),
                     Math::saturate(input.y, lower_bound, upper_bound) };
        }

        friend std::string format(const Ref &input)
        {
            return std::format("[x: {:.6}, y: {:.6}]", input.x, input.y);
        }
    };

    /** @name Constructors
     * 
     *  @{
     */
    constexpr BasicVector2D() = default;
    constexpr BasicVector2D(const Type &x_in, const Type &y_in = 0)
        :
        x{x_in},
        y{y_in}
    {
    }
    /// @}

    /** @name Assignment
     *  @{
     */
    constexpr BasicVector2D<Type> &operator =(const BasicVector2D<Type> &other) = default;
    constexpr BasicVector2D<Type> &operator =(const BasicVector2D<Type>::Ref &other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
    /// @}

    /** @name Equality
     *  @{
     */
    /** Defines equality of two BasicVector2D objects
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note We take advantage of new C++20 rules that can automatically
     *        generate the operator !=() from the operator ==().
     * 
     *  @see Equality
     */
    friend constexpr bool operator ==(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return approximately_equal_to(left, right);
    }

    /** @name Constants
     *  @{
     */
    constexpr static BasicVector2D<Type> unit_x() { return { Type{1}, Type{0} }; }
    constexpr static BasicVector2D<Type> unit_y() { return { Type{0}, Type{1} }; }

    constexpr static BasicVector2D<Type> zero() { return {}; }
    /// @}
 
    /** @addtogroup Vector2DAlgebra 2D Vector Algebra
     * 
     *  Two Dimensional Vector Algebra
     * 
     *  @{
     */

    /** @name Operators
     *  
     *  @relates Vector2D
     *  @{
     */
    friend constexpr BasicVector2D<Type> operator +(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return { left.x + right.x, left.y + right.y };
    }
    friend constexpr BasicVector2D<Type> operator +(const BasicVector2D<Type> &left, const Ref &right)
    {
        return { left.x + right.x, left.y + right.y };
    }

    friend constexpr BasicVector2D<Type> operator -(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return { left.x - right.x, left.y - right.y };
    }
    friend constexpr BasicVector2D<Type> operator -(const BasicVector2D<Type> &left, const Ref &right)
    {
        return { left.x - right.x, left.y - right.y };
    }

    friend constexpr BasicVector2D<Type> operator *(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return { left.x * right.x, left.y * right.y };
    }

    friend constexpr BasicVector2D<Type> operator *(const BasicVector2D<Type> &left, const Ref &right)
    {
        return { left.x * right.x, left.y * right.y };
    }

    friend constexpr BasicVector2D<Type> operator *(const BasicVector2D<Type> &left, const Type &scalar)
    {
        return { left.x * scalar, left.y * scalar };
    }

    friend constexpr BasicVector2D<Type> operator *(const Type &scalar, const BasicVector2D<Type> &right)
    {
        return { scalar * right.x, scalar * right.y };
    }

    friend constexpr BasicVector2D<Type> operator /(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return { left.x / right.x, left.y / right.y };
    }

    friend constexpr BasicVector2D<Type> operator /(const BasicVector2D<Type> &left, const Ref &right)
    {
        return { left.x / right.x, left.y / right.y };
    }

    friend constexpr BasicVector2D<Type> operator /(const BasicVector2D<Type> &left, const Type &scalar)
    {
        return { left.x / scalar, left.y / scalar };
    }

    friend constexpr BasicVector2D<Type> operator /(const Type &scalar, const BasicVector2D<Type> &right)
    {
        return { scalar / right.x, scalar / right.y };
    }
    /// @}  {Operators}
    /// @}  {Vector2DAlgebra}

    constexpr value_type normSquared() const { return (x * x) + (y * y); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr BasicVector2D<Type> normalized() const
    {
        auto n = norm();

        return { x / n, y / n };
    }

    /** @name Invalid Value Check
     *  @{
     */
    bool isNaN() const { return std::isnan(x) || std::isnan(y); }
    bool isInf() const { return std::isinf(x) || std::isinf(y); }
    /// @}

    /** @name Swizzle operations
     *  @{
     */
    constexpr BasicVector2D<Type> xx() const { return { x, x }; }
    constexpr BasicVector2D<Type> xx()       { return { x, x }; }

    constexpr BasicVector2D<Type> yy() const { return { y, y }; }
    constexpr BasicVector2D<Type> yy()       { return { y, y }; }

    constexpr const Ref                 xy() const &  { return { x, y }; }
    constexpr       Ref                 xy()       &  { return { x, y }; }
    constexpr       BasicVector2D<Type> xy()       && { return { x, y }; }

    constexpr const Ref                 yx() const &  { return { y, x }; }
    constexpr       Ref                 yx()       &  { return { y, x }; }
    constexpr       BasicVector2D<Type> yx()       && { return { y, x }; }
    /// @} {Swizzle operations}


    /** @name Element Access
     *  @{
     */
    Type x{};
    Type y{};
    /// @}

    /** @addtogroup Equality
     * 
     *  @relates BasicVector2D
     * 
     *  @{
     * 
     *  Compares two BasicVector2D inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     * 
     *  @see Equality
     */
    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicVector2D<Type> &value_to_test,
                                                 const BasicVector2D<Type> &value_it_should_be,
                                                       OT                   tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
    }

    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicVector2D<Type>      &value_to_test,
                                                 const BasicVector2D<Type>::Ref &value_it_should_be,
                                                       OT                        tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
    }
    /// @}

    /** Sums up the components of @p input
     *  
     *  @input The BasicVector2D to operate on
     */
    friend constexpr Type accumulate(const BasicVector2D<Type> &input)
    {
        return input.x + input.y;
    }

    /** Calculate the dot product of two BasicVector2D objects
     *
     *  @param left  The first vector
     *  @param right The second vector
     * 
     *  @return The dot product of the two input vectors
     *  
     *  @note This is only a strict dot product and thus a normalized
     *        result will depend on if the input vectors are both
     *        normalized!
     *
     *  @{
     */
    friend constexpr Type dot(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }
    friend constexpr Type dot(const BasicVector2D<Type> &left, const Ref &right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }
    /// @}

    /** Creates the normalized form of a BasicVector2D
     *  
     *  @param input The BasicVector2D to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr BasicVector2D<Type> normalized(const BasicVector2D<Type> &input)
    {
        return input.normalized();
    }

    /** Calculate the normalized dot product of two BasicVector2D objects
     *
     *  The input vectors are not assumed to be normalized, so we go
     *  ahead and divide through by both the input vectors
     *  to arrive at a normalized output.
     * 
     *  @param left  The first vector
     *  @param right The second vector
     * 
     *  @return The dot product of the two input vectors
     *
     *  @{
     */
    friend constexpr Type dot_normalized(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }
    friend constexpr Type dot_normalized(const BasicVector2D<Type> &left, const Ref &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }
    /// @} {dot_normalized}

    /** Calculates a pseudo cross product between two BasicVector2D objects
     * 
     *  @param left  The first vector
     *  @param right The second vector
     * 
     *  @return A scalar value representing the 2D cross product
     * 
     *  @note Since the 3D version of cross product comes from the calculation
     *        of a determinant of a matrix, I define the same idea here but
     *        using a 2 x 2 matrix instead of the 3 x 3 3D for the version (also
     *        owing to the recursive nature of the calculation of a determinant).
     * 
     *  @{
     */
    friend constexpr Type cross(const BasicVector2D<Type> &left, const BasicVector2D<Type> &right)
    {
        return (left.x * right.y) - (left.y * right.x);
    }
    friend constexpr Type cross(const BasicVector2D<Type> &left, const Ref &right)
    {
        return (left.x * right.y) - (left.y * right.x);
    }
    /// @} {cross}

    /** Calculate the absolute value of all components of a BasicVector2D
     *   
     *   @param input The BasicVector2D to operate on
     *
     *   @return The BasicVector2D with only positive values
     */
    friend constexpr BasicVector2D<Type> abs(const BasicVector2D<Type> &input)
    {
        return { std::abs(input.x), std::abs(input.y) };
    }

    /** Calculate the fractional part of all components of a BasicVector2D
     *   
     *   @param input The BasicVector2D to operate on
     *
     *   @return The BasicVector2D with only fractional values
     */
    friend constexpr BasicVector2D<Type> fract(const BasicVector2D<Type> &input)
    {
        return { std::modf(input.x), std::modf(input.y) };
    }

    friend constexpr BasicVector2D<Type> saturate(const BasicVector2D<Type> &input, const Type lower_bound, Type upper_bound)
    {
        return { Math::saturate(input.x, lower_bound, upper_bound),
                 Math::saturate(input.y, lower_bound, upper_bound) };
    }

    friend std::string format(const BasicVector2D<Type> &input)
    {
        return std::format("[x: {:.6}, y: {:.6}]", input.x, input.y);
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
    friend bool check_if_equal(const BasicVector2D<Type> &input, const BasicVector2D<Type> &near_to, OT tolerance = OT{0.0002})
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
    friend bool check_if_not_equal(const BasicVector2D<Type> &input, const BasicVector2D<Type> &near_to, OT tolerance = OT{0.0002})
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

    /** @addtogroup Checks
     * 
     *  Compare two values for equality with a tolerance and causes an assertion when false
     *  
     *  @param input     The first value to compare
     *  @param near_to   The second value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if the two are equal within @c tolerance , @c false otherwise
     */
    template <std::floating_point OT = float>
    friend void CHECK_IF_EQUAL(const BasicVector2D<Type> &input, const BasicVector2D<Type> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    /** @addtogroup Checks
     * 
     *  Compare two values for inequality with a tolerance and causes an assertion when false
     *  
     *  @param input     The first value to compare
     *  @param near_to   The second value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
     */
    template <std::floating_point OT = float>
    friend void CHECK_IF_NOT_EQUAL(const BasicVector2D<Type> &input, const BasicVector2D<Type> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    /** @addtogroup Checks
     * 
     *  Compare a value to near zero
     *  
     *  @param input     The first value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if @c input is inside @c tolerance , @c false otherwise
     */
    template <std::floating_point OT = float>
    friend void CHECK_IF_ZERO(const BasicVector2D<Type> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicVector2D<Type>::zero(), tolerance));
    }
};

/** @defgroup BasicVector2DRefAliases Vector2DRef Types
 * 
 *  Here are the type aliases for BasicVector2D::Ref
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicVector2D::Ref
 *  @{
 */
using Vector2DfRef = BasicVector2D<float>::Ref;
using Vector2DdRef = BasicVector2D<double>::Ref;
using Vector2DRef  = BasicVector2D<double>::Ref;
using Vector2DlRef = BasicVector2D<long double>::Ref;
///@}  {BasicVector2D::Ref Type Aliases}


/** @defgroup BasicVector2DAliases Vector2D Types
 * 
 *  Here are the type aliases for BasicVector2D
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicVector2D
 *  @{
 */
using Vector2Df = BasicVector2D<float>;
using Vector2Dd = BasicVector2D<double>;
using Vector2D  = BasicVector2D<double>;
using Vector2Dl = BasicVector2D<long double>;
///@}  {BasicVector2D Type Aliases}

}