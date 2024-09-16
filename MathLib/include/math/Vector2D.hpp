#pragma once

#include "math/Functions.hpp"

/** @file
 *  
 *  Contains the definition of 2D and 3D vector classes
 *
 *  @hideincludegraph
 */

template <class T>
struct Vector2DRef;

/** A simple 2D vector class
 *
 *  @headerfile "math/Vector2D.hpp"
 * 
 */
template <class Type>
struct Vector2D
{
    using value_type = Type;

    constexpr Vector2D() = default;
    constexpr Vector2D(const Type &x_in, const Type &y_in = 0)
        :
        x{x_in},
        y{y_in}
        {
        }

    /** @name Constants
     *  @{
     */
    static constexpr Vector2D<Type> unit_x() { return Vector2D{ Type{1}, Type{0} }; }
    static constexpr Vector2D<Type> unit_y() { return Vector2D{ Type{0}, Type{1} }; }

    constexpr static Vector2D<Type> zero() { return Vector2D{}; }
    /// @}

    constexpr value_type normSquared() const { return (x * x) + (y * y); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr Vector2D<Type> normalized() const { return *this / norm(); }

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    bool isNaN() const { return std::isnan(x) || std::isnan(y); }

    bool isInf() const { return std::isinf(x) || std::isinf(y); }

    /** @name Swizzle operations
     *  @{
     */
    constexpr const Vector2DRef<Type> xy() const;
    constexpr       Vector2DRef<Type> xy();

    constexpr const Vector2DRef<Type> yx() const;
    constexpr       Vector2DRef<Type> yx();
    /// @}

    /** @name Element Access
     *  @{
     */
    Type x{};
    Type y{};
    /// @}
};

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
 */
template <class Type>
bool operator ==(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return approximately_equal_to(left.x, right.x) && approximately_equal_to(left.y, right.y);
}

/** Defines inequality of two Vector2D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 */
template <class Type>
bool operator !=(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return !(left == right);
}

/** @addtogroup Vector2DAlgebra 2D Vector Algebra
 * 
 *  Two Dimension Vector Algebra
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
 */
template <class T>
constexpr T dot(const Vector2D<T> &left, const Vector2D<T> &right)
{
    return (left.x * right.x) + (left.y * right.y);
}

/** Calculates a pseudo cross product between two Vector2D objects
 * 
 *  @param left  The first vector
 *  @param right The second vector
 * 
 *  @result A scalar value representing the 2D cross product
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

/** Creates the normalized form of a Vector2D
 *  
 *  @param input The Vector2D to normalize
 *  
 *  @return The normalized version of @p input
 */
template <class T>
constexpr Vector2D<T> normalized(const Vector2D<T> &input)
{
    return input.normalized();
}
/// @}  {GlobalFunctions}

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


/** Class representing a reference to elements of a Vector2D object
 * 
 *  @note This class exists to support simple vector swizzle operations.
 * 
 *  @relates Vector2D
 */
template <class Type>
struct Vector2DRef
{
    using value_type = Type;

    /** Explicitly force the user to create these
     * 
     */
    constexpr explicit Vector2DRef(Type &x_in, Type &y_in) : x{x_in}, y{y_in} { }

    constexpr Vector2DRef<Type> &operator =(const Vector2DRef<Type> &input)
    {
        // Early exit if we try to self-assign
        if (this == &input)
            return *this;

        x = input.x;
        y = input.y;
        return *this;
    }

    constexpr Vector2DRef<Type> &operator =(const Vector2D<Type> &input)
    {
        x = input.x;
        y = input.y;
        return *this;
    }

    /** Vector2D conversion operator
     * 
     *  This allows Vector2DRef objects to automatically be converted to Vector2D objects
     *  for situations like passing to functions or constructors to Vector2D objects.
     */
    operator Vector2D<Type>() const { return Vector2D<Type>{ x, y }; }

    Type &x;
    Type &y;
};

template <class Type>
constexpr const Vector2DRef<Type> Vector2D<Type>::xy() const
{
    return Vector2DRef{ x, y };
}

template <class Type>
constexpr Vector2DRef<Type> Vector2D<Type>::xy()
{
    return Vector2DRef{ x, y };
}

template <class Type>
constexpr const Vector2DRef<Type> Vector2D<Type>::yx() const
{
    return Vector2DRef{ y, x };
}

template <class Type>
constexpr Vector2DRef<Type> Vector2D<Type>::yx()
{
    return Vector2DRef{ y, x };
}