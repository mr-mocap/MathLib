#pragma once

#include "math/Functions.hpp"

/** A simple 3D vector class
 *
 *  @headerfile "math/Vector3D.hpp"
 * 
 */
template <class Type>
struct Vector3D
{
    using value_type = Type;

    /** @name Constants
     *  @{
     */
    static constexpr Vector3D<Type> unit_x() { return Vector3D{ Type{1}, Type{0}, Type{0} }; }
    static constexpr Vector3D<Type> unit_y() { return Vector3D{ Type{0}, Type{1}, Type{0} }; }
    static constexpr Vector3D<Type> unit_z() { return Vector3D{ Type{0}, Type{0}, Type{1} }; }

    constexpr static Vector3D<Type> zero() { return Vector3D{}; }
    /// @}

    constexpr value_type normSquared() const { return (x * x) + (y * y) + (z * z); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr Vector3D<Type> normalized() const { return *this / magnitude(); }

    bool isNaN() const { return std::isnan(x) || std::isnan(y) || std::isnan(z); }
    bool isInf() const { return std::isinf(x) || std::isinf(y) || std::isinf(z); }

    /** @name Element Access
     *  @{
     */
    value_type x{};
    value_type y{};
    value_type z{};
    /// @}
};

/** @addtogroup Equality
 * 
 *  @relates Vector3D
 * 
 *  @{
 * 
 *  Compares two Vector3D inputs equal, component-wise, to within a tolerance
 *  
 *  @param value_to_test
 *  @param value_it_should_be 
 *  @param tolerance          How close they should be to be considered equal
 *  
 *  @return @c true if they are equal
 */
template <class T>
constexpr bool approximately_equal_to(const Vector3D<T> &value_to_test, const Vector3D<T> &value_it_should_be, const float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
           approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
           approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance);
}
/// @}

/** @name Global Operators
 * 
 *  @relates Vector3D
 * 
 *  @{
 */
/** Defines equality of two Vector3D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 */
template <class Type>
bool operator ==(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return approximately_equal_to(left, right);
}

/** Defines inequality of two Vector3D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 */
template <class Type>
bool operator !=(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return !(left == right);
}

/** @addtogroup Vector3DAlgebra 3D Vector Algebra
 * 
 *  Three Dimensional Vector Algrbra
 * 
 *  @{
 */

/** @name Addition
 *  @{
 */
/** Defines addition of two Vector3D objects
 */
template <class Type>
constexpr Vector3D<Type> operator +(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z };
}
/// @}  {Addition}

/** @name Subtraction
 *  @{
 */
/** Defines subtraction of two Vector3D objects
 */
template <class Type>
constexpr Vector3D<Type> operator -(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z };
}
/// @}  {Subtraction}
/// @}  {Vector3DAlgebra}
/// @}  {GlobalOperators}


/** @name Global Functions
 * 
 *  @relates Vector3D
 * 
 *  @{
 */
/** Sums up the components of @p input
 *  
 *  @param input The Vector3D to operate on
 * 
 *  @return The sum of all the components
 */
template <class T>
constexpr T accumulate(const Vector3D<T> &input)
{
    return input.x + input.y + input.z;
}

/** Calculate the dot product of two Vector3D objects
 *
 *  @param left  The first vector
 *  @param right The second vector
 * 
 *  @return The dot product of the two input vectors
 */
template <class T>
constexpr T dot(const Vector3D<T> &left, const Vector3D<T> &right)
{
    return (left.x * right.x) + (left.y + right.y) + (left.z * right.z);
}

/** Calculates the cross product of two Vector3D objects
 * 
 *  @param left  The first vector
 *  @param right The second vector
 * 
 *  @return The cross product of the input vectors
 */
template <class T>
constexpr Vector3D<T> cross(const Vector3D<T> &left, const Vector3D<T> &right)
{
    return Vector3D<T>{ (left.y * right.z) - (left.z * right.y),
                        (left.z * right.x) - (left.x * right.z),
                        (left.x * right.y) - (left.y * right.x)
                      };
}

/** Creates the normalized form of a Vector3D
 *  
 *  @param input The Vector3D to normalize
 *  
 *  @return The normalized version of @p input
 */
template <class T>
constexpr Vector3D<T> normalized(const Vector3D<T> &input)
{
    return input.normalized();
}
/// @}  {GlobalFunctions}

/** @name Vector3D Type Aliases
 *  
 *  @relates Vector3D
 * 
 *  @{
 */
using Vector3Df = Vector3D<float>;
using Vector3Dd = Vector3D<double>;
using Vector3Dld = Vector3D<long double>;
///@}  {Vector3D Type Aliases}