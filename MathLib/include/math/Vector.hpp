#pragma once

#include "math/ApproximatelyEqualTo.hpp"

/** @file
 *  
 *  Contains the definition of 2D and 3D vector classes
 *
 *  @hideincludegraph
 */


/** A simple 2D vector class
 *
 *  @headerfile "math/Vector.hpp"
 * 
 */
template <class Type = float>
struct Vector2D
{
    /** @name Constants
     *  @{
     */
    static constexpr Vector2D<Type> unit_x() { return Vector2D{ Type{1}, Type{0} }; }
    static constexpr Vector2D<Type> unit_y() { return Vector2D{ Type{0}, Type{1} }; }

    constexpr static Vector2D<Type> zero() { return Vector2D{}; }
    /// @}

    Type x{};
    Type y{};
};

/** @name Operators
 *  @{
 */
/** Defines equality of two Vector2D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see approximately_equal_to
 * 
 *  @relates Vector2D
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
 *  @see approximately_equal_to
 * 
 *  @relates Vector2D
 */
template <class Type>
bool operator !=(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return !(left == right);
}

/** Defines addition of two Vector2D objects
 * 
 *  @relates Vector2D
 */
template <class Type>
Vector2D<Type> operator +(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return Vector2D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z };
}

/** Defines subtraction of two Vector2D objects
 * 
 *  @relates Vector2D
 */
template <class Type>
Vector2D<Type> operator -(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return Vector2D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z };
}

/** Defines multiplication of two Vector2D objects
 * 
 *  @relates Vector2D
 */
template <class Type>
Vector2D<Type> operator *(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return Vector2D<Type>{ left.x * right.x, left.y * right.y, left.z * right.z };
}

/** Defines division of two Vector2D objects
 * 
 *  @relates Vector2D
 */
template <class Type>
Vector2D<Type> operator /(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return Vector2D<Type>{ left.x / right.x, left.y / right.y, left.z / right.z };
}
/// @}

/** A simple 3D vector class
 *
 *  @headerfile "math/Vector.hpp"
 * 
 */
template <class Type = float>
struct Vector3D
{
    /** @name Constants
     *  @{
     */
    static constexpr Vector3D<Type> unit_x() { return Vector3D{ Type{1}, Type{0}, Type{0} }; }
    static constexpr Vector3D<Type> unit_y() { return Vector3D{ Type{0}, Type{1}, Type{0} }; }
    static constexpr Vector3D<Type> unit_z() { return Vector3D{ Type{0}, Type{0}, Type{1} }; }

    constexpr static Vector3D<Type> zero() { return Vector3D{}; }
    /// @}

    Type x{};
    Type y{};
    Type z{};
};

/** @name Operators
 *  @{
 */
/** Defines equality of two Vector3D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see approximately_equal_to
 * 
 *  @relates Vector3D
 */
template <class Type>
bool operator ==(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return approximately_equal_to(left.x, right.x) &&
           approximately_equal_to(left.y, right.y) &&
           approximately_equal_to(left.z, right.z);
}

/** Defines inequality of two Vector3D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see approximately_equal_to
 * 
 *  @relates Vector3D
 */
template <class Type>
bool operator !=(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return !(left == right);
}

/** Defines addition of two Vector3D objects
 * 
 *  @relates Vector3D
 */
template <class Type>
Vector3D<Type> operator +(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z };
}

/** Defines subtraction of two Vector3D objects
 * 
 *  @relates Vector3D
 */
template <class Type>
Vector3D<Type> operator -(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z };
}

/** Defines multiplication of two Vector3D objects
 * 
 *  @relates Vector3D
 */
template <class Type>
Vector3D<Type> operator *(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x * right.x, left.y * right.y, left.z * right.z };
}

/** Defines division of two Vector3D objects
 * 
 *  @relates Vector3D
 */
template <class Type>
Vector3D<Type> operator /(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x / right.x, left.y / right.y, left.z / right.z };
}
/// @}


/** @name Vector2D Type Aliases
 *  @{
 */
using Vector2Df = Vector2D<float>;
using Vector2Dd = Vector2D<double>;
using Vector2Dld = Vector2D<long double>;
///@}

/** @name Vector3D Type Aliases
 *  @{
 */
using Vector3Df = Vector3D<float>;
using Vector3Dd = Vector3D<double>;
using Vector3Dld = Vector3D<long double>;
///@}