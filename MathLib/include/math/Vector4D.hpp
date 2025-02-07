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
        constexpr operator Vector4D<Type>() const { return { x, y, z, w }; }

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
    constexpr Vector4D(const Vector2D<Type> &first2, const Vector2D<Type> &second2)
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


    /** @name Constants
     *  @{
     */
    constexpr static Vector4D<Type> unit_x() { return Vector4D{ Type{1}, Type{0}, Type{0}, Type{0} }; }
    constexpr static Vector4D<Type> unit_y() { return Vector4D{ Type{0}, Type{1}, Type{0}, Type{0} }; }
    constexpr static Vector4D<Type> unit_z() { return Vector4D{ Type{0}, Type{0}, Type{1}, Type{0} }; }
    constexpr static Vector4D<Type> unit_w() { return Vector4D{ Type{0}, Type{0}, Type{0}, Type{1} }; }

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

    constexpr const Vector3D<Type>::Ref xyz() const { return { x, y, z }; }
    constexpr       Vector3D<Type>::Ref xyz()       { return { x, y, z }; }

    constexpr const Vector3D<Type>::Ref xzy() const { return { x, z, y }; }
    constexpr       Vector3D<Type>::Ref xzy()       { return { x, z, y }; }

    constexpr const Vector3D<Type>::Ref zxy() const { return { z, x, y }; }
    constexpr       Vector3D<Type>::Ref zxy()       { return { z, x, y }; }

    constexpr const Vector3D<Type>::Ref zyx() const { return { z, y, x }; }
    constexpr       Vector3D<Type>::Ref zyx()       { return { z, y, x }; }

    constexpr const Vector3D<Type>::Ref xxx() const { return { x, x, x }; }
    constexpr       Vector3D<Type>::Ref xxx()       { return { x, x, x }; }

    constexpr const Vector3D<Type>::Ref yyy() const { return { y, y, y }; }
    constexpr       Vector3D<Type>::Ref yyy()       { return { y, y, y }; }

    constexpr const Vector3D<Type>::Ref zzz() const { return { z, z, z }; }
    constexpr       Vector3D<Type>::Ref zzz()       { return { z, z, z }; }

    constexpr const Vector3D<Type>::Ref www() const { return { w, w, w }; }
    constexpr       Vector3D<Type>::Ref www()       { return { w, w, w }; }
    /// @}

    /** Defines equality of two Vector4D objects
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @see Equality
     */
    friend constexpr Vector4D<Type> operator ==(const Vector4D<Type> &left, const Vector4D<Type> &right)
    {
        return approximately_equal_to(left, right);
    }

    /** @name Element Access
     *  @{
     */
    value_type x{};
    value_type y{};
    value_type z{};
    value_type w{};
    /// @}

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
    friend constexpr Vector4D<Type> operator +(const Vector4D<Type> &left, const Vector4D<Type> &right)
    {
        return Vector4D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
    }
    /// @}  {Addition}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two Vector4D objects
     */
    friend constexpr Vector4D<Type> operator -(const Vector4D<Type> &left, const Vector4D<Type> &right)
    {
        return Vector4D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
    }
    /// @}  {Subtraction}

    /** @name Multiplication
     *  @{
     */
    /** Defines multiplication of two Vector4D objects
     */
    friend constexpr Vector4D<Type> operator *(const Vector4D<Type> &left, const Vector4D<Type> &right)
    {
        return Vector4D<Type>{ left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w };
    }

    friend constexpr Vector4D<Type> operator *(const Vector4D<Type> &left, const Type right)
    {
        return Vector4D<Type>{ left.x * right, left.y * right, left.z * right, left.w * right };
    }

    friend constexpr Vector4D<Type> operator *(const Type left, const Vector4D<Type> right)
    {
        return Vector4D<Type>{ left * right.x, left * right.y, left * right.z, left * right.w };
    }
    /// @}  {Multiplication}

    /** @name Division
     *  @{
     */
    /** Defines division of two Vector4D objects
     */
    friend constexpr Vector4D<Type> operator /(const Vector4D<Type> &left, const Vector4D<Type> &right)
    {
        return Vector4D<Type>{ left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w };
    }

    friend constexpr Vector4D<Type> operator /(const Vector4D<Type> &left, const Type right)
    {
        return Vector4D<Type>{ left.x / right, left.y / right, left.z / right, left.w / right };
    }
    /// @}  {Division}
    /// @}  {Vector4DAlgebra}

    /** @name Global Functions
     * 
     *  @relates Vector4D
     * 
     *  @{
     */

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
    friend constexpr bool approximately_equal_to(const Vector4D<Type> &value_to_test, const Vector4D<Type> &value_it_should_be, const float tolerance = 0.0002f)
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
            approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
            approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance) &&
            approximately_equal_to(value_to_test.w, value_it_should_be.w, tolerance);
    }
    /// @}

    /** Sums up the components of @p input
     *  
     *  @param input The Vector4D to operate on
     * 
     *  @return The sum of all the components
     */
    friend constexpr Type accumulate(const Vector4D<Type> &input)
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
    friend constexpr Type dot(const Vector4D<Type> &left, const Vector4D<Type> &right)
    {
        return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);
    }

    /** Creates the normalized form of a Vector4D
     *  
     *  @param input The Vector4D to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr Vector4D<Type> normalized(const Vector4D<Type> &input)
    {
        return input.normalized();
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
    friend constexpr Type dot_normalized(const Vector4D<Type> &left, const Vector4D<Type> &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }

    /** Calculate the absolute value of all components of a Vector4D
     *   
     *   @param input The Vector4D to operate on
     *
     *   @return The Vector4D with only positive values
     */
    friend constexpr Vector4D<Type> abs(const Vector4D<Type> &input)
    {
        return Vector4D<Type>( std::abs(input.x), std::abs(input.y), std::abs(input.z), std::abs(input.w) );
    }

    /** Calculate the fractional part of all components of a Vector4D
     *   
     *   @param input The Vector4D to operate on
     *
     *   @return The Vector4D with only fractional values
     */
    friend constexpr Vector4D<Type> fract(const Vector4D<Type> &input)
    {
        return Vector4D<Type>( std::modf(input.x), std::modf(input.y), std::modf(input.z), std::modf(input.w) );
    }

    friend constexpr Vector4D<Type> saturate(const Vector4D<Type> &input, const Type lower_bound, const Type upper_bound)
    {
        return Vector4D<Type>( saturate(input.x, lower_bound, upper_bound),
                            saturate(input.y, lower_bound, upper_bound),
                            saturate(input.z, lower_bound, upper_bound),
                            saturate(input.w, lower_bound, upper_bound) );
    }

    friend std::string format(const Vector4D<Type> &input)
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
    friend bool check_if_equal(const Vector4D<Type> &input, const Vector4D<Type> &near_to, float tolerance = 0.0002f)
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
    friend bool check_if_not_equal(const Vector4D<Type> &input, const Vector4D<Type> &near_to, float tolerance = 0.0002f)
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

    friend void CHECK_IF_EQUAL(const Vector4D<Type> &input, const Vector4D<Type> &near_to, const float tolerance = 0.0002f)
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    friend void CHECK_IF_NOT_EQUAL(const Vector4D<Type> &input, const Vector4D<Type> &near_to, const float tolerance = 0.0002f)
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    friend void CHECK_IF_ZERO(const Vector4D<Type> &input, const float tolerance = 0.0002f)
    {
        assert( check_if_equal(input, Vector4D<Type>::zero(), tolerance));
    }
    /// @}  {GlobalFunctions}
};


/** @name Vector4D::Ref Type Aliases
 *  
 *  @relates Vector4D
 * 
 *  @{
 */
template <class T>
using Vector4DRef = typename Vector4D<T>::Ref;

using Vector4DfRef = Vector4DRef<float>;
using Vector4DdRef = Vector4DRef<double>;
using Vector4DldRef = Vector4DRef<long double>;
///@}  {Vector4D::Ref Type Aliases}

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