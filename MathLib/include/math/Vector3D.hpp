#pragma once

#include "math/Functions.hpp"
#include "math/Vector2D.hpp"

/** @file
 *  
 *  Contains the definition of 3D vector class
 *
 *  @hideincludegraph
 */

namespace Math
{

/** A simple 3D Vector class
 * 
 *  @headerfile "math/Vector3D.hpp"
 */
template <class Type>
struct Vector3D
{
    using value_type = Type;

    /** Class representing a reference to elements of a Vector3D object
     * 
     *  @note This class exists to support simple vector swizzle operations.
     * 
     *  @relates Vector3D
     */
    struct Ref
    {
        using value_type = Type;

        /** Explicitly force the user to create these
         * 
         */
        constexpr Ref(Type &x_in, Type &y_in, Type &z_in) : x{x_in}, y{y_in}, z{z_in} { }

        constexpr Ref operator =(const Ref &input)
        {
            return Ref{ x = input.x, y = input.y, z = input.z };
        }

        constexpr Ref operator =(const Vector3D<Type> &input)
        {
            return Ref{ x = input.x, y = input.y, z = input.z };
        }

        /** Vector3D conversion operator
         * 
         *  This allows Vector3DRef objects to automatically be converted to Vector3D objects
         *  for situations like passing to functions or constructors to Vector3D objects.
         */
        constexpr operator Vector3D<Type>() const { return { x, y, z }; }

        Type &x;
        Type &y;
        Type &z;
    };

    constexpr Vector3D() = default;
    constexpr Vector3D(const Type &x_in, const Type &y_in = 0, const Type &z_in = 0)
        :
        x{x_in},
        y{y_in},
        z{z_in}
    {
    }
    constexpr Vector3D(const Vector2D<Type> &other, const Type z_in = 0)
        :
        x{other.x},
        y{other.y},
        z{z_in}
    {
    }
    constexpr Vector3D(const Type x_in, const Vector2D<Type> &other)
        :
        x{x_in},
        y{other.x},
        z{other.y}
    {
    }

    /** @name Constants
     *  @{
     */
    constexpr static Vector3D<Type> unit_x() { return Vector3D{ Type{1}, Type{0}, Type{0} }; }
    constexpr static Vector3D<Type> unit_y() { return Vector3D{ Type{0}, Type{1}, Type{0} }; }
    constexpr static Vector3D<Type> unit_z() { return Vector3D{ Type{0}, Type{0}, Type{1} }; }

    constexpr static Vector3D<Type> zero() { return Vector3D{}; }
    /// @}

    constexpr value_type normSquared() const { return (x * x) + (y * y) + (z * z); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr Vector3D<Type> normalized() const
    {
        auto n = magnitude();

        return { x / n, y / n, z / n };
    }

    bool isNaN() const { return std::isnan(x) || std::isnan(y) || std::isnan(z); }
    bool isInf() const { return std::isinf(x) || std::isinf(y) || std::isinf(z); }

    /** @name Swizzle operations
     *  @{
     */
    constexpr const Vector2D<Type>::Ref xy() const { return { x, y }; }
    constexpr       Vector2D<Type>::Ref xy()       { return { x, y }; }

    constexpr const Vector2D<Type>::Ref xz() const { return { x, z }; }
    constexpr       Vector2D<Type>::Ref xz()       { return { x, z }; }

    constexpr const Vector2D<Type>::Ref yx() const { return { y, x }; }
    constexpr       Vector2D<Type>::Ref yx()       { return { y, x }; }

    constexpr const Vector2D<Type>::Ref yz() const { return { y, z }; }
    constexpr       Vector2D<Type>::Ref yz()       { return { y, z }; }

    constexpr const Vector2D<Type>::Ref zx() const { return { z, x }; }
    constexpr       Vector2D<Type>::Ref zx()       { return { z, x }; }

    constexpr const Ref xyz() const { return { x, y, z }; }
    constexpr       Ref xyz()       { return { x, y, z }; }

    constexpr const Ref xzy() const { return { x, z, y }; }
    constexpr       Ref xzy()       { return { x, z, y }; }

    constexpr const Ref zxy() const { return { z, x, y }; }
    constexpr       Ref zxy()       { return { z, x, y }; }

    constexpr const Ref zyx() const { return { z, y, x }; }
    constexpr       Ref zyx()       { return { z, y, x }; }
    /// @}

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

template <class Type>
bool operator ==(const Vector3D<Type> &left, const typename Vector3D<Type>::Ref &right)
{
    return approximately_equal_to(left, right);
}

template <class Type>
bool operator ==(const typename Vector3D<Type>::Ref &left, const Vector3D<Type> &right)
{
    return approximately_equal_to(left, right);
}

template <class Type>
bool operator ==(const typename Vector3D<Type>::Ref &left, const typename Vector3D<Type>::Ref &right)
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

template <class Type>
bool operator !=(const Vector3D<Type> &left, const typename Vector3D<Type>::Ref &right)
{
    return !(left == right);
}

template <class Type>
bool operator !=(const typename Vector3D<Type>::Ref &left, const Vector3D<Type> &right)
{
    return !(left == right);
}

template <class Type>
bool operator !=(const typename Vector3D<Type>::Ref &left, const typename Vector3D<Type>::Ref &right)
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

template <class Type>
constexpr Vector3D<Type> operator +(const Vector3D<Type> &left, const typename Vector3D<Type>::Ref &right)
{
    return Vector3D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z };
}

template <class Type>
constexpr Vector3D<Type> operator +(const typename Vector3D<Type>::Ref &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z };
}

template <class Type>
constexpr Vector3D<Type> operator +(const typename Vector3D<Type>::Ref &left, const typename Vector3D<Type>::Ref &right)
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

template <class Type>
constexpr Vector3D<Type> operator -(const Vector3D<Type> &left, const typename Vector3D<Type>::Ref &right)
{
    return Vector3D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z };
}

template <class Type>
constexpr Vector3D<Type> operator -(const typename Vector3D<Type>::Ref &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z };
}

template <class Type>
constexpr Vector3D<Type> operator -(const typename Vector3D<Type>::Ref &left, const typename Vector3D<Type>::Ref &right)
{
    return Vector3D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z };
}
/// @}  {Subtraction}

/** @name Multiplication
 *  @{
 */
/** Defines multiplication of two Vector3D objects
 */
template <class Type>
constexpr Vector3D<Type> operator *(const Vector3D<Type> left, const Vector3D<Type> right)
{
    return Vector3D<Type>{ left.x * right.x, left.y * right.y, left.z * right.z };
}

template <class Type>
constexpr Vector3D<Type> operator *(const Vector3D<Type> left, const Type right)
{
    return Vector3D<Type>{ left.x * right, left.y * right, left.z * right };
}

template <class Type>
constexpr Vector3D<Type> operator *(const Type left, const Vector3D<Type> right)
{
    return Vector3D<Type>{ left * right.x, left * right.y, left * right.z };
}
/// @}  {Multiplication}

/** @name Division
 *  @{
 */
/** Defines division of two Vector3D objects
 */
template <class Type>
constexpr Vector3D<Type> operator /(const Vector3D<Type> &left, const Vector3D<Type> &right)
{
    return Vector3D<Type>{ left.x / right.x, left.y / right.y, left.z / right.z };
}

template <class Type>
constexpr Vector3D<Type> operator /(const Vector3D<Type> &left, const Type right)
{
    return Vector3D<Type>{ left.x / right, left.y / right, left.z / right };
}
/// @}  {Division}
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
 *  
 *  @note This is only a strict dot product and thus a normalized
 *        result will depend on if the input vectors are both
 *        normalized!
 */
template <class T>
constexpr T dot(const Vector3D<T> &left, const Vector3D<T> &right)
{
    return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

/** Calculate the normalized dot product of two Vector3D objects
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
constexpr T dot_normalized(const Vector3D<T> &left, const Vector3D<T> &right)
{
    return dot(left, right) / (left.magnitude() * right.magnitude());
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
    return Vector3D<T>{ cross( left.yz(), right.yz() ),
                        cross( left.zx(), right.zx() ),
                        cross( left.xy(), right.xy() ) };
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

/** Calculate the absolute value of all components of a Vector3D
 *   
 *   @param input The Vector3D to operate on
 *
 *   @return The Vector3D with only positive values
 */
template <class T>
constexpr Vector3D<T> abs(const Vector3D<T> &input)
{
    return Vector3D<T>( std::abs(input.x), std::abs(input.y), std::abs(input.z) );
}

/** Calculate the fractional part of all components of a Vector3D
 *   
 *   @param input The Vector3D to operate on
 *
 *   @return The Vector3D with only fractional values
 */
template <class T>
constexpr Vector3D<T> fract(const Vector3D<T> &input)
{
    return Vector3D<T>( std::modf(input.x), std::modf(input.y), std::modf(input.z) );
}

template <class T>
constexpr Vector3D<T> saturate(const Vector3D<T> &input, const T lower_bound, const T upper_bound)
{
    return Vector3D<T>( Math::saturate(input.x, lower_bound, upper_bound),
                        Math::saturate(input.y, lower_bound, upper_bound),
                        Math::saturate(input.z, lower_bound, upper_bound) );
}
/// @}  {GlobalFunctions}

template <class T>
std::string format(const Vector3D<T> &input)
{
    return std::format("[x: {:.6}, y: {:.6}, z: {:.6}]", input.x, input.y, input.z);
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
bool check_if_equal(const Vector3D<T> &input, const Vector3D<T> &near_to, float tolerance = 0.0002f)
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
bool check_if_not_equal(const Vector3D<T> &input, const Vector3D<T> &near_to, float tolerance = 0.0002f)
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
void CHECK_IF_EQUAL(const Vector3D<T> &input, const Vector3D<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_NOT_EQUAL(const Vector3D<T> &input, const Vector3D<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_ZERO(const Vector3D<T> &input, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, Vector3D<T>::zero(), tolerance));
}

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

}