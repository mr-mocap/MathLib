#pragma once

#include "math/ApproximatelyEqualTo.hpp"

/** @file
 *  
 */


/** A simple 2D vector class
 */
template <class Type>
struct Vector2D
{
    static constexpr Vector2D<Type> unit_x() { return Vector2D{ Type{1}, Type{0} }; }
    static constexpr Vector2D<Type> unit_y() { return Vector2D{ Type{0}, Type{1} }; }

    Type x{};
    Type y{};
};

template <class Type>
bool operator ==(const Vector2D<Type> &left, const Vector2D<Type> &right)
{
    return approximately_equal_to(left.x, right.x) && approximately_equal_to(left.y, right.y);
}

/** A simple 3D vector class
 */
template <class Type>
struct Vector3D
{
    static constexpr Vector3D<Type> unit_x() { return Vector3D{ Type{1}, Type{0}, Type{0} }; }
    static constexpr Vector3D<Type> unit_y() { return Vector3D{ Type{0}, Type{1}, Type{0} }; }
    static constexpr Vector3D<Type> unit_z() { return Vector3D{ Type{0}, Type{0}, Type{1} }; }

    Type x{};
    Type y{};
    Type z{};
};

template <class Type>
bool operator ==(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return approximately_equal_to(left.x, right.x) &&
           approximately_equal_to(left.y, right.y) &&
           approximately_equal_to(left.z, right.z);
}


///@{
/** Specialized types of the Vector2D class
 */
using Vector2Df = Vector2D<float>;
using Vector2Dd = Vector2D<double>;
using Vector2Dld = Vector2D<long double>;
///@}

///@{
/** Specialized types of the Vector3D class
 */
using Vector3Df = Vector3D<float>;
using Vector3Dd = Vector3D<double>;
using Vector3Dld = Vector3D<long double>;
///@}