#pragma once

#include "math/Functions.hpp"

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
            //return Ref{ x = input.x, y = input.y };
            x = input.x;
            y = input.y;
            return *this;
        }

        constexpr Ref operator =(const Vector2D<Type> &input)
        {
            //return Ref{ x = input.x, y = input.y };
            x = input.x;
            y = input.y;
            return *this;
        }

        /** Vector2D conversion operator
         * 
         *  This allows Ref objects to automatically be converted to Vector2D objects
         *  for situations like passing to functions or constructors to Vector2D objects.
         */
        constexpr operator Vector2D<Type>() const { return Vector2D<Type>{ x, y }; }

        Type &x;
        Type &y;
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
    constexpr const Ref xy() const { return { x, y }; }
    constexpr       Ref xy()       { return { x, y }; }

    constexpr const Ref yx() const { return { y, x }; }
    constexpr       Ref yx()       { return { y, x }; }
    /// @}


    /** @name Element Access
     *  @{
     */
    Type x{};
    Type y{};
    /// @}
};

template <class T>
using Vector2DRef = typename Vector2D<T>::Ref;

/** @addtogroup Equality
 * 
 *  @relates Vector2D
 * 
 *  @{
 * 
 *  Compares two Vector2D inputs equal, component-wise, to within a tolerance
 *  
 *  @param value_to_test
 *  @param value_it_should_be 
 *  @param tolerance          How close they should be to be considered equal
 *  
 *  @return @c true if they are equal
 */
template <class T>
constexpr bool approximately_equal_to(const Vector2D<T> &value_to_test, const Vector2D<T> &value_it_should_be, const float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
           approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
}

template <class T>
constexpr bool approximately_equal_to(const Vector2DRef<T> &value_to_test, const Vector2DRef<T> &value_it_should_be, const float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
           approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
}

/// @}

/** @name Global Operators
 * 
 *  @relates Vector2D
 * 
 *  @{
 */
/** Defines equality of two Vector2D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 * 
 *  @{
 */
template <class T>
constexpr bool operator ==(const Vector2D<T> left, const Vector2D<T> right)
{
    return approximately_equal_to(left, right);
}

template <class T>
constexpr bool operator ==(const Vector2DRef<T> left, const Vector2DRef<T> right)
{
    return approximately_equal_to(left, right);
}
/// @}

/** Defines inequality of two Vector2D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 * 
 *  @{
 */
template <class Type>
constexpr bool operator !=(const Vector2D<Type> left, const Vector2D<Type> right)
{
    return !(left == right);
}

template <class Type>
constexpr bool operator !=(const Vector2DRef<Type> left, const Vector2DRef<Type> right)
{
    return !(left == right);
}
/// @}

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
template <class Type>
constexpr Vector2D<Type> operator +(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return Vector2D<Type>{ left.x + right.x, left.y + right.y };
}
/// @}  {Addition}

/** @name Subtraction
 *  @{
 */
/** Defines subtraction of two Vector2D objects
 */
template <class Type>
constexpr Vector2D<Type> operator -(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return Vector2D<Type>{ left.x - right.x, left.y - right.y };
}
/// @}  {Subtraction}

/** @name Multiplication
 *  @{
 */
/** Defines multiplication of two Vector2D objects
 */
template <class Type>
constexpr Vector2D<Type> operator *(const Vector2D<Type> left, const Vector2D<Type> right)
{
    return Vector2D<Type>{ left.x * right.x, left.y * right.y };
}

template <class Type>
constexpr Vector2D<Type> operator *(const Vector2D<Type> left, const Type right)
{
    return Vector2D<Type>{ left.x * right, left.y * right };
}

template <class Type>
constexpr Vector2D<Type> operator *(const Type left, const Vector2D<Type> right)
{
    return Vector2D<Type>{ left * right.x, left * right.y };
}
/// @}  {Multiplication}

/** @name Division
 *  @{
 */
/** Defines division of two Vector2D objects
 */
template <class Type>
constexpr Vector2D<Type> operator /(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return Vector2D<Type>{ left.x / right.x, left.y / right.y };
}

template <class Type>
constexpr Vector2D<Type> operator /(const Vector2D<Type> &left, const Type right)
{
    return Vector2D<Type>{ left.x / right, left.y / right };
}
/// @}  {Division}
/// @}  {Vector2DAlgebra}
/// @}  {GlobalOperators}

/** @name Global Functions
 * 
 *  @relates Vector2D
 * 
 *  @{
 */
/** Sums up the components of @p input
 *  
 *  @input The Vector2D to operate on
 */
template <class T>
constexpr T accumulate(const Vector2D<T> &input)
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
 */
template <class T>
constexpr T dot(const Vector2D<T> &left, const Vector2D<T> &right)
{
    return (left.x * right.x) + (left.y * right.y);
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
 */
template <class T>
constexpr T dot_normalized(const Vector2D<T> &left, const Vector2D<T> &right)
{
    return dot(left, right) / (left.magnitude() * right.magnitude());
}

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
 */
template <class T>
constexpr T cross(const Vector2D<T> &left, const Vector2D<T> &right)
{
    return (left.x * right.y) - (left.y * right.x);
}

/** Calculate the absolute value of all components of a Vector2D
 *   
 *   @param input The Vector2D to operate on
 *
 *   @return The Vector2D with only positive values
 */
template <class T>
constexpr Vector2D<T> abs(const Vector2D<T> &input)
{
    return Vector2D<T>( std::abs(input.x), std::abs(input.y) );
}

/** Calculate the fractional part of all components of a Vector2D
 *   
 *   @param input The Vector2D to operate on
 *
 *   @return The Vector2D with only fractional values
 */
template <class T>
constexpr Vector2D<T> fract(const Vector2D<T> &input)
{
    return Vector2D<T>( std::modf(input.x), std::modf(input.y) );
}

template <class T>
constexpr Vector2D<T> saturate(const Vector2D<T> &input, const T lower_bound, const T upper_bound)
{
    return Vector2D<T>( Math::saturate(input.x, lower_bound, upper_bound),
                        Math::saturate(input.y, lower_bound, upper_bound) );
}
/// @}  {GlobalFunctions}

template <class T>
std::string format(const Vector2D<T> &input)
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
template <class T>
bool check_if_equal(const Vector2D<T> &input, const Vector2D<T> &near_to, float tolerance = 0.0002f)
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
bool check_if_not_equal(const Vector2D<T> &input, const Vector2D<T> &near_to, float tolerance = 0.0002f)
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
void CHECK_IF_EQUAL(const Vector2D<T> &input, const Vector2D<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_NOT_EQUAL(const Vector2D<T> &input, const Vector2D<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_ZERO(const Vector2D<T> &input, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, Vector2D<T>::zero(), tolerance));
}

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