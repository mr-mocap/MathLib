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
 *  @headerfile "math/Vector2D.hpp"
 * 
 */
template <class Type>
struct Vector2D
{
    using value_type = Type;

    /** Class representing a reference to elements of a Vector2D object
     * 
     *  @note This class exists to support simple vector swizzle operations.
     * 
     *  @relates Vector2D
     */
    struct Ref
    {
        /** Explicitly force the user to create these
         * 
         */
        constexpr Ref(Type &x_in, Type &y_in) : x{x_in}, y{y_in} { }
        constexpr Ref(const Ref &) = default;
        constexpr Ref(const Vector2D<Type> &other) : x{other.x}, y{other.y} { }

        constexpr Ref &operator =(const Ref &input)
        {
            x = input.x;
            y = input.y;
            return *this;
        }

        constexpr Ref &operator =(const Vector2D<Type> &input)
        {
            x = input.x;
            y = input.y;
            return *this;
        }

        /** Defines equality of two Vector2D::Ref objects
         *  
         *  @note Uses approximately_equal_to under-the-hood
         *  
         *  @note We take advantage of the new C++20 rule where if there
         *        is not an appropriate operator ==(const Vector2D<Type> &) defined
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

        /** @addtogroup Vector2DAlgebra 2D Vector Algebra
         * 
         *  Two Dimensional Vector Algebra
         * 
         *  @{
         */

        /** @name Addition
         *  @{
         */
        /** Defines addition of two Vector2D::Ref objects
         */
        friend constexpr Vector2D<Type> operator +(const Ref &left, const Ref &right)
        {
            return { left.x + right.x, left.y + right.y };
        }
        /// @} {Addition}

        /** @name Subtraction
         *  @{
         */
        /** Defines subtraction of two Vector2D::Ref objects
         */
        friend constexpr Vector2D<Type> operator -(const Ref &left, const Ref &right)
        {
            return { left.x - right.x, left.y - right.y };
        }
        friend constexpr Vector2D<Type> operator -(const Ref &left, const Vector2D<Type> &right)
        {
            return { left.x - right.x, left.y - right.y };
        }
        /// @}  {Subtraction}

        /** @name Multiplication
         *  @{
         */
        /** Defines multiplication of two Vector2D::Ref objects
         */
        friend constexpr Vector2D<Type> operator *(const Ref &left, const Vector2D<Type> &right)
        {
            return Vector2D<Type>{ left.x * right.x, left.y * right.y };
        }

        friend constexpr Vector2D<Type> operator *(const Ref &left, const Ref &right)
        {
            return Vector2D<Type>{ left.x * right.x, left.y * right.y };
        }

        /** Defines multiplication of a Vector2D::Ref object by a scalar
         */
        friend constexpr Vector2D<Type> operator *(const Ref &left, Type scalar)
        {
            return Vector2D<Type>{ left.x * scalar, left.y * scalar };
        }
        /** Defines multiplication of a scalar by a Vector2D::Ref object
         */
        friend constexpr Vector2D<Type> operator *(Type scalar, const Ref &right)
        {
            return Vector2D<Type>{ scalar * right.x, scalar * right.y };
        }
        /// @}  {Multiplication}

        /** @name Division
         *  @{
         */
        /** Defines division of two Vector2D::Ref objects
         */
        friend constexpr Vector2D<Type> operator /(const Ref &left, const Ref &right)
        {
            return Vector2D<Type>{ left.x / right.x, left.y / right.y };
        }

        friend constexpr Vector2D<Type> operator /(const Ref &left, const Vector2D<Type> &right)
        {
            return Vector2D<Type>{ left.x / right.x, left.y / right.y };
        }

        /** Defines division of a Vector2D::Ref object by a scalar
         */
        friend constexpr Vector2D<Type> operator /(const Ref &left, Type scalar)
        {
            return Vector2D<Type>{ left.x / scalar, left.y / scalar };
        }
        /** Defines division of a scalar by a Vector2D::Ref object
         */
        friend constexpr Vector2D<Type> operator /(Type scalar, const Ref &right)
        {
            return Vector2D<Type>{ scalar / right.x, scalar / right.y };
        }
        /// @} {Division}
        /// @} {Vector2DAlgebra}

        /** Vector2D conversion operator
         * 
         *  This allows Ref objects to automatically be converted to Vector2D objects
         *  for situations like passing to functions or constructors to Vector2D objects.
         */
        constexpr operator Vector2D<Type>() const { return Vector2D<Type>{ x, y }; }

        Type &x;
        Type &y;


        /** @name Private Friend Functions
         *  @{
         */

        /** Compares two Vector2D inputs equal, component-wise, to within a tolerance
         * 
         *  @addtogroup Equality
         * 
         *  @relates Vector2D
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

        friend constexpr Type accumulate(const Ref &input)
        {
            return input.x + input.y;
        }

        friend constexpr Type dot(const Ref &left, const Ref &right)
        {
            return (left.x * right.x) + (left.y * right.y);
        }
        friend constexpr Type dot(const Ref &left, const Vector2D<Type> &right)
        {
            return (left.x * right.x) + (left.y * right.y);
        }

        friend constexpr Type dot_normalized(const Ref &left, const Ref &right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }
        friend constexpr Type dot_normalized(const Ref &left, const Vector2D<Type> &right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }

        friend constexpr Type cross(const Ref &left, const Ref &right)
        {
            return (left.x * right.y) - (left.y * right.x);
        }
        friend constexpr Type cross(const Ref &left, const Vector2D<Type> &right)
        {
            return (left.x * right.y) - (left.y * right.x);
        }

        friend constexpr Vector2D<Type> abs(const Ref &input)
        {
            return Vector2D<Type>( std::abs(input.x), std::abs(input.y) );
        }

        friend constexpr Vector2D<Type> fract(const Ref &input)
        {
            return Vector2D<Type>( std::modf(input.x), std::modf(input.y) );
        }

        constexpr Vector2D<Type> saturate(const Ref &input, Type lower_bound, Type upper_bound)
        {
            return Vector2D<Type>( Math::saturate(input.x, lower_bound, upper_bound),
                                   Math::saturate(input.y, lower_bound, upper_bound) );
        }

        friend std::string format(const Ref &input)
        {
            return std::format("[x: {:.6}, y: {:.6}]", input.x, input.y);
        }
        /// @} {Private Friend Functions}
    };

    constexpr Vector2D() = default;
    constexpr Vector2D(const Type &x_in, const Type &y_in = 0)
        :
        x{x_in},
        y{y_in}
    {
    }
    constexpr Vector2D<Type> &operator =(const Vector2D<Type> &other) = default;
    constexpr Vector2D<Type> &operator =(const Vector2D<Type>::Ref &other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    /** Defines equality of two Vector2D objects
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note We take advantage of new C++20 rules that can automatically
     *        generate the operator !=() from the operator ==().
     * 
     *  @see Equality
     */
    constexpr bool operator ==(const Vector2D<Type> &right) const
    {
        return approximately_equal_to(*this, right);
    }

    /** Defines equality of a Vector2D and Vector2D<Type>::Ref objects
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note We take advantage of new C++20 rules that can automatically
     *        generate the operator !=() from the operator ==().
     * 
     *  @see Equality
     */
    constexpr bool operator ==(const Vector2D<Type>::Ref &right) const
    {
        return approximately_equal_to(*this, Vector2D<Type>{right});
    }

    /** @addtogroup Vector2DAlgebra 2D Vector Algebra
     * 
     *  Two Dimensional Vector Algebra
     * 
     *  @{
     */

    /** @name Addition
     *  @{
     */
    /** Defines addition of two Vector2D objects
     */
    constexpr Vector2D<Type> operator +(const Vector2D<Type> &other) const
    {
        return Vector2D<Type>{ x + other.x, y + other.y };
    }
    constexpr Vector2D<Type> operator +(const Ref &other) const
    {
        return Vector2D<Type>{ x + other.x, y + other.y };
    }
    /// @} {Addition}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two Vector2D objects
     */
    constexpr Vector2D<Type> operator -(const Vector2D<Type> &other) const
    {
        return { x - other.x, y - other.y };
    }
    constexpr Vector2D<Type> operator -(const Ref &other) const
    {
        return { x - other.x, y - other.y };
    }
    /// @}  {Subtraction}

    /** @name Multiplication
     *  @{
     */
    /** Defines multiplication of two Vector2D objects
     */
    constexpr Vector2D<Type> operator *(const Vector2D<Type> &right) const
    {
        return Vector2D<Type>{ x * right.x, y * right.y };
    }

    constexpr Vector2D<Type> operator *(const Ref &right) const
    {
        return Vector2D<Type>{ x * right.x, y * right.y };
    }

    constexpr Vector2D<Type> operator *(Type scalar) const
    {
        return Vector2D<Type>{ x * scalar, y * scalar };
    }

    friend constexpr Vector2D<Type> operator *(Type scalar, const Vector2D<Type> &right)
    {
        return Vector2D<Type>{ scalar * right.x, scalar * right.y };
    }
    /// @}  {Multiplication}

    /** @name Division
     *  @{
     */
    /** Defines division of two Vector2D objects
     */
    constexpr Vector2D<Type> operator /(const Vector2D<Type> &right) const
    {
        return Vector2D<Type>{ x / right.x, y / right.y };
    }

    constexpr Vector2D<Type> operator /(const Ref &right) const
    {
        return Vector2D<Type>{ x / right.x, y / right.y };
    }

    /** Defines division of a Vector2D object by a scalar
     */
    constexpr Vector2D<Type> operator /(Type scalar) const
    {
        return Vector2D<Type>{ x / scalar, y / scalar };
    }

    /** Defines division of a scalar by a Vector2D object
     */
    friend constexpr Vector2D<Type> operator /(Type scalar, const Vector2D<Type> &right)
    {
        return Vector2D<Type>{ scalar / right.x, scalar / right.y };
    }
    /// @}  {Division}
    /// @}  {Vector2DAlgebra}

    /** @name Constants
     *  @{
     */
    constexpr static Vector2D<Type> unit_x() { return Vector2D{ Type{1}, Type{0} }; }
    constexpr static Vector2D<Type> unit_y() { return Vector2D{ Type{0}, Type{1} }; }

    constexpr static Vector2D<Type> zero() { return Vector2D{}; }
    /// @}

    constexpr value_type normSquared() const { return (x * x) + (y * y); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr Vector2D<Type> normalized() const
    {
        auto n = norm();

        return { x / n, y / n };
    }

    bool isNaN() const { return std::isnan(x) || std::isnan(y); }

    bool isInf() const { return std::isinf(x) || std::isinf(y); }

    /** @name Swizzle operations
     *  @{
     */
    constexpr Vector2D<Type> xx() const { return { x, x }; }
    constexpr Vector2D<Type> xx()       { return { x, x }; }

    constexpr Vector2D<Type> yy() const { return { y, y }; }
    constexpr Vector2D<Type> yy()       { return { y, y }; }

    constexpr const Ref      xy() const &  { return { x, y }; }
    constexpr       Ref      xy()       &  { return { x, y }; }
    constexpr Vector2D<Type> xy()       && { return { x, y }; }

    constexpr const Ref      yx() const &  { return { y, x }; }
    constexpr       Ref      yx()       &  { return { y, x }; }
    constexpr Vector2D<Type> yx()       && { return { y, x }; }
    /// @} {Swizzle operations}


    /** @name Element Access
     *  @{
     */
    Type x{};
    Type y{};
    /// @}

    /** @name Hidden Friend Functions
     *  @{
     */

    /** Compares two Vector2D inputs equal, component-wise, to within a tolerance
     * 
     *  @addtogroup Equality
     * 
     *  @relates Vector2D
     * 
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     */
    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const Vector2D<Type> &value_to_test, const Vector2D<Type> &value_it_should_be, OT tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
    }

    /** Sums up the components of @p input
     *  
     *  @input The Vector2D to operate on
     */
    friend constexpr Type accumulate(const Vector2D<Type> &input)
    {
        return input.x + input.y;
    }

    /** Calculate the dot product of two Vector2D objects
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
    friend constexpr Type dot(const Vector2D<Type> &left, const Vector2D<Type> &right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }
    friend constexpr Type dot(const Vector2D<Type> &left, const Ref &right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }

    /** Creates the normalized form of a Vector2D
     *  
     *  @param input The Vector2D to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr Vector2D<Type> normalized(const Vector2D<Type> &input)
    {
        return input.normalized();
    }

    /** Calculate the normalized dot product of two Vector2D objects
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
    friend constexpr Type dot_normalized(const Vector2D<Type> &left, const Vector2D<Type> &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }
    friend constexpr Type dot_normalized(const Vector2D<Type> &left, const Ref &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }
    /// @} {dot_normalized}

    /** Calculates a pseudo cross product between two Vector2D objects
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
    friend constexpr Type cross(const Vector2D<Type> &left, const Vector2D<Type> &right)
    {
        return (left.x * right.y) - (left.y * right.x);
    }
    friend constexpr Type cross(const Vector2D<Type> &left, const Ref &right)
    {
        return (left.x * right.y) - (left.y * right.x);
    }
    /// @} {cross}

    /** Calculate the absolute value of all components of a Vector2D
     *   
     *   @param input The Vector2D to operate on
     *
     *   @return The Vector2D with only positive values
     */
    friend constexpr Vector2D<Type> abs(const Vector2D<Type> &input)
    {
        return Vector2D<Type>( std::abs(input.x), std::abs(input.y) );
    }

    /** Calculate the fractional part of all components of a Vector2D
     *   
     *   @param input The Vector2D to operate on
     *
     *   @return The Vector2D with only fractional values
     */
    friend constexpr Vector2D<Type> fract(const Vector2D<Type> &input)
    {
        return Vector2D<Type>( std::modf(input.x), std::modf(input.y) );
    }

    friend constexpr Vector2D<Type> saturate(const Vector2D<Type> &input, const Type lower_bound, Type upper_bound)
    {
        return Vector2D<Type>( Math::saturate(input.x, lower_bound, upper_bound),
                               Math::saturate(input.y, lower_bound, upper_bound) );
    }

    friend std::string format(const Vector2D<Type> &input)
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
    friend bool check_if_equal(const Vector2D<Type> &input, const Vector2D<Type> &near_to, OT tolerance = OT{0.0002})
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
    friend bool check_if_not_equal(const Vector2D<Type> &input, const Vector2D<Type> &near_to, OT tolerance = OT{0.0002})
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
    friend void CHECK_IF_EQUAL(const Vector2D<Type> &input, const Vector2D<Type> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_NOT_EQUAL(const Vector2D<Type> &input, const Vector2D<Type> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_ZERO(const Vector2D<Type> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, Vector2D<Type>::zero(), tolerance));
    }
    /// @} {Hidden Friend Functions}
};

/** @name Vector2D::Ref Type Aliases
 *  
 *  @relates Vector2D
 * 
 *  @{
 */
template <class T>
using Vector2DRef = typename Vector2D<T>::Ref;

using Vector2DfRef = Vector2DRef<float>;
using Vector2DdRef = Vector2DRef<double>;
using Vector2DldRef = Vector2DRef<long double>;
///@}  {Vector2D::Ref Type Aliases}


/** @name Vector2D Type Aliases
 *  
 *  @relates Vector2D
 * 
 *  @{
 */
using Vector2Df = Vector2D<float>;
using Vector2Dd = Vector2D<double>;
using Vector2Dld = Vector2D<long double>;
///@}  {Vector2D Type Aliases}

}