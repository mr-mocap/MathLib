#pragma once

#include "math/Functions.hpp"

/** @file
 *  
 *  Contains the definition of 4D vector class
 *
 *  @hideincludegraph
 */

namespace Math
{

/** A simple 4D Vector class
 * 
 *  @headerfile "math/Vector4D.hpp"
 */
template <class Type>
struct Vector4D
{
    using value_type = Type;

    /** Class representing a reference to elements of a Vector4D object
     * 
     *  @note This class exists to support simple vector swizzle operations.
     * 
     *  @relates Vector4D
     */
    struct Ref
    {
        using value_type = Type;

        /** Explicitly force the user to create these
         * 
         */
        constexpr Ref(Type &x_in, Type &y_in, Type &z_in, Type &w_in) : x{x_in}, y{y_in}, z{z_in}, w{w_in} { }

        constexpr Ref operator =(const Ref &input)
        {
            return Ref{ x = input.x, y = input.y, z = input.z, w = input.w };
        }

        constexpr Ref operator =(const Vector4D<Type> &input)
        {
            return Ref{ x = input.x, y = input.y, z = input.z, w = input.w };
        }

        /** Vector4D conversion operator
         * 
         *  This allows Vector4DRef objects to automatically be converted to Vector4D objects
         *  for situations like passing to functions or constructors to Vector4D objects.
         */
        operator Vector4D<Type>() const { return { x, y, z, w }; }

        Type &x;
        Type &y;
        Type &z;
        Type &w;
    };

    constexpr Vector4D() = default;
    constexpr Vector4D(const Type &x_in, const Type &y_in = 0, const Type &z_in = 0, const Type &w_in = 0)
        :
        x{x_in},
        y{y_in},
        z{z_in},
        w{w_in}
        {
        }
    constexpr Vector4D(const Vector3D<Type> &first3, const Type &w_in = 0)
        :
        x{first3.x},
        y{first3.y},
        z{first3.z},
        w{w_in}
    {
    }
    constexpr Vector4D(const Vector3D<Type>::Ref &first3, const Type &w_in = 0)
        :
        x{first3.x},
        y{first3.y},
        z{first3.z},
        w{w_in}
    {
    }
    constexpr Vector4D(const Vector2D<Type> &first2, const Vector2D<Type> &second2)
        :
        x{first2.x},
        y{first2.y},
        z{second2.x},
        w{second2.y}
    {
    }
    constexpr Vector4D(const Vector2D<Type>::Ref &first2, const Vector2D<Type> &second2)
        :
        x{first2.x},
        y{first2.y},
        z{second2.x},
        w{second2.y}
    {
    }
    constexpr Vector4D(const Vector2D<Type> &first2, const Vector2D<Type>::Ref &second2)
        :
        x{first2.x},
        y{first2.y},
        z{second2.x},
        w{second2.y}
    {
    }
    constexpr Vector4D(const Vector2D<Type>::Ref &first2, const Vector2D<Type>::Ref &second2)
        :
        x{first2.x},
        y{first2.y},
        z{second2.x},
        w{second2.y}
    {
    }
    constexpr Vector4D(const Type &x_in, const Vector3D<Type> &last3)
        :
        x{x_in},
        y{last3.x},
        z{last3.y},
        w{last3.z}
    {
    }
    constexpr Vector4D(const Type &x_in, const Vector3D<Type>::Ref &last3)
        :
        x{x_in},
        y{last3.x},
        z{last3.y},
        w{last3.z}
    {
    }


    /** @name Constants
     *  @{
     */
    static constexpr Vector4D<Type> unit_x() { return Vector4D{ Type{1}, Type{0}, Type{0}, Type{0} }; }
    static constexpr Vector4D<Type> unit_y() { return Vector4D{ Type{0}, Type{1}, Type{0}, Type{0} }; }
    static constexpr Vector4D<Type> unit_z() { return Vector4D{ Type{0}, Type{0}, Type{1}, Type{0} }; }
    static constexpr Vector4D<Type> unit_w() { return Vector4D{ Type{0}, Type{0}, Type{0}, Type{1} }; }

    constexpr static Vector4D<Type> zero() { return Vector4D{}; }
    /// @}

    constexpr value_type normSquared() const { return (x * x) + (y * y) + (z * z) + (w * w); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr Vector4D<Type> normalized() const
    {
        auto n = magnitude();

        return { x / n, y / n, z / n, w / n };
    }

    bool isNaN() const { return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w); }
    bool isInf() const { return std::isinf(x) || std::isinf(y) || std::isinf(z) || std::isinf(w); }

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

    constexpr const Ref xyz() const { return Ref{ x, y, z }; }
    constexpr       Ref xyz()       { return Ref{ x, y, z }; }

    constexpr const Ref xzy() const { return Ref{ x, z, y }; }
    constexpr       Ref xzy()       { return Ref{ x, z, y }; }

    constexpr const Ref zxy() const { return Ref{ z, x, y }; }
    constexpr       Ref zxy()       { return Ref{ z, x, y }; }

    constexpr const Ref zyx() const { return Ref{ z, y, x }; }
    constexpr       Ref zyx()       { return Ref{ z, y, x }; }
    /// @}

    operator Ref() { return Ref{ x, y, z, w }; }

    /** @name Element Access
     *  @{
     */
    value_type x{};
    value_type y{};
    value_type z{};
    value_type w{};
    /// @}
};

/** @addtogroup Equality
 * 
 *  @relates Vector4D
 * 
 *  @{
 * 
 *  Compares two Vector4D inputs equal, component-wise, to within a tolerance
 *  
 *  @param value_to_test
 *  @param value_it_should_be 
 *  @param tolerance          How close they should be to be considered equal
 *  
 *  @return @c true if they are equal
 */
template <class T>
constexpr bool approximately_equal_to(const Vector4D<T> &value_to_test, const Vector4D<T> &value_it_should_be, const float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
           approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
           approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance) &&
           approximately_equal_to(value_to_test.w, value_it_should_be.w, tolerance);
}
/// @}

/** @name Global Operators
 * 
 *  @relates Vector4D
 * 
 *  @{
 */
/** Defines equality of two Vector4D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 */
template <class Type>
bool operator ==(const Vector4D<Type> &left, const Vector4D<Type> &right)
{
    return approximately_equal_to(left, right);
}

/** Defines inequality of two Vector4D objects
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see Equality
 */
template <class Type>
bool operator !=(const Vector4D<Type> &left, const Vector4D<Type> &right)
{
    return !(left == right);
}

/** @addtogroup Vector4DAlgebra 4D Vector Algebra
 * 
 *  Four Dimensional Vector Algrbra
 * 
 *  @{
 */

/** @name Addition
 *  @{
 */
/** Defines addition of two Vector4D objects
 */
template <class Type>
constexpr Vector4D<Type> operator +(const Vector4D<Type> &left, const Vector4D<Type> &right)
{
    return Vector4D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
}
/// @}  {Addition}

/** @name Subtraction
 *  @{
 */
/** Defines subtraction of two Vector4D objects
 */
template <class Type>
constexpr Vector4D<Type> operator -(const Vector4D<Type> &left, const Vector4D<Type> &right)
{
    return Vector4D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
}
/// @}  {Subtraction}
/// @}  {Vector4DAlgebra}
/// @}  {GlobalOperators}

/** @name Global Functions
 * 
 *  @relates Vector4D
 * 
 *  @{
 */
/** Sums up the components of @p input
 *  
 *  @param input The Vector4D to operate on
 * 
 *  @return The sum of all the components
 */
template <class T>
constexpr T accumulate(const Vector4D<T> &input)
{
    return input.x + input.y + input.z + input.w;
}

/** Calculate the dot product of two Vector4D objects
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
constexpr T dot(const Vector4D<T> &left, const Vector4D<T> &right)
{
    return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);
}

/** Calculate the normalized dot product of two Vector4D objects
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
constexpr T dot_normalized(const Vector4D<T> &left, const Vector4D<T> &right)
{
    return dot(left, right) / (left.magnitude() * right.magnitude());
}
/// @}  {GlobalFunctions}

template <class T>
std::string format(const Vector4D<T> &input)
{
    return std::format("[x: {:.6}, y: {:.6}, z: {:.6}, w: {:.6}]", input.x, input.y, input.z, input.w);
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
bool check_if_equal(const Vector4D<T> &input, const Vector4D<T> &near_to, float tolerance = 0.0002f)
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
bool check_if_not_equal(const Vector4D<T> &input, const Vector4D<T> &near_to, float tolerance = 0.0002f)
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
void CHECK_IF_EQUAL(const Vector4D<T> &input, const Vector4D<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_NOT_EQUAL(const Vector4D<T> &input, const Vector4D<T> &near_to, const float tolerance = 0.0002f)
{
    assert( check_if_not_equal(input, near_to, tolerance) );
}

template <class T>
void CHECK_IF_ZERO(const Vector4D<T> &input, const float tolerance = 0.0002f)
{
    assert( check_if_equal(input, Vector4D<T>::zero(), tolerance));
}

/** @name Vector4D Type Aliases
 *  
 *  @relates Vector4D
 * 
 *  @{
 */
using Vector4Df = Vector4D<float>;
using Vector4Dd = Vector4D<double>;
using Vector4Dld = Vector4D<long double>;
///@}  {Vector4D Type Aliases}

}