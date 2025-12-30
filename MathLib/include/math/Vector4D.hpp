#pragma once

#include "math/Functions.hpp"
#include <concepts>

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
struct BasicVector4D
{
    using value_type = Type;

    /** Class representing a reference to elements of a BasicVector4D object
     * 
     *  @note This class exists to support simple vector swizzle operations.
     * 
     *  @relates BasicVector4D
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

        constexpr Ref operator =(const BasicVector4D<Type> &input)
        {
            return Ref{ x = input.x, y = input.y, z = input.z, w = input.w };
        }

        /** BasicVector4D conversion operator
         * 
         *  This allows Vector4DRef objects to automatically be converted to BasicVector4D objects
         *  for situations like passing to functions or constructors to BasicVector4D objects.
         */
        constexpr operator BasicVector4D<Type>() const { return { x, y, z, w }; }

        Type &x;
        Type &y;
        Type &z;
        Type &w;
    };

    constexpr BasicVector4D() = default;
    constexpr BasicVector4D(const Type &x_in, const Type &y_in = 0, const Type &z_in = 0, const Type &w_in = 0)
        :
        x{x_in},
        y{y_in},
        z{z_in},
        w{w_in}
        {
        }
    constexpr BasicVector4D(const BasicVector3D<Type> &first3, const Type &w_in = 0)
        :
        x{first3.x},
        y{first3.y},
        z{first3.z},
        w{w_in}
    {
    }
    constexpr BasicVector4D(const BasicVector2D<Type> &first2, const BasicVector2D<Type> &second2)
        :
        x{first2.x},
        y{first2.y},
        z{second2.x},
        w{second2.y}
    {
    }
    constexpr BasicVector4D(const Type &x_in, const BasicVector3D<Type> &last3)
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
    constexpr static BasicVector4D<Type> unit_x() { return BasicVector4D{ Type{1}, Type{0}, Type{0}, Type{0} }; }
    constexpr static BasicVector4D<Type> unit_y() { return BasicVector4D{ Type{0}, Type{1}, Type{0}, Type{0} }; }
    constexpr static BasicVector4D<Type> unit_z() { return BasicVector4D{ Type{0}, Type{0}, Type{1}, Type{0} }; }
    constexpr static BasicVector4D<Type> unit_w() { return BasicVector4D{ Type{0}, Type{0}, Type{0}, Type{1} }; }

    constexpr static BasicVector4D<Type> zero() { return BasicVector4D{}; }
    /// @}

    constexpr value_type normSquared() const { return (x * x) + (y * y) + (z * z) + (w * w); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr BasicVector4D<Type> normalized() const
    {
        auto n = magnitude();

        return { x / n, y / n, z / n, w / n };
    }

    bool isNaN() const { return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w); }
    bool isInf() const { return std::isinf(x) || std::isinf(y) || std::isinf(z) || std::isinf(w); }

    /** @name Swizzle operations
     *  @{
     */
    constexpr const BasicVector2D<Type>::Ref xy() const &  { return { x, y }; }
    constexpr       BasicVector2D<Type>::Ref xy()       &  { return { x, y }; }
    constexpr       BasicVector2D<Type>      xy()       && { return { x, y }; }

    constexpr const BasicVector2D<Type>::Ref xz() const &  { return { x, z }; }
    constexpr       BasicVector2D<Type>::Ref xz()       &  { return { x, z }; }
    constexpr       BasicVector2D<Type>      xz()       && { return { x, z }; }

    constexpr const BasicVector2D<Type>::Ref yx() const &  { return { y, x }; }
    constexpr       BasicVector2D<Type>::Ref yx()       &  { return { y, x }; }
    constexpr       BasicVector2D<Type>      yx()       && { return { y, x }; }

    constexpr const BasicVector2D<Type>::Ref yz() const &  { return { y, z }; }
    constexpr       BasicVector2D<Type>::Ref yz()       &  { return { y, z }; }
    constexpr       BasicVector2D<Type>      yz()       && { return { y, z }; }

    constexpr const BasicVector2D<Type>::Ref zx() const &  { return { z, x }; }
    constexpr       BasicVector2D<Type>::Ref zx()       &  { return { z, x }; }
    constexpr       BasicVector2D<Type>      zx()       && { return { z, x }; }

    constexpr const BasicVector3D<Type>::Ref xyz() const &  { return { x, y, z }; }
    constexpr       BasicVector3D<Type>::Ref xyz()       &  { return { x, y, z }; }
    constexpr       BasicVector3D<Type>      xyz()       && { return { x, y, z }; }

    constexpr const BasicVector3D<Type>::Ref xzy() const &  { return { x, z, y }; }
    constexpr       BasicVector3D<Type>::Ref xzy()       &  { return { x, z, y }; }
    constexpr       BasicVector3D<Type>      xzy()       && { return { x, z, y }; }

    constexpr const BasicVector3D<Type>::Ref zxy() const &  { return { z, x, y }; }
    constexpr       BasicVector3D<Type>::Ref zxy()       &  { return { z, x, y }; }
    constexpr       BasicVector3D<Type>      zxy()       && { return { z, x, y }; }

    constexpr const BasicVector3D<Type>::Ref zyx() const &  { return { z, y, x }; }
    constexpr       BasicVector3D<Type>::Ref zyx()       &  { return { z, y, x }; }
    constexpr       BasicVector3D<Type>      zyx()       && { return { z, y, x }; }

    constexpr const BasicVector3D<Type>::Ref xxx() const &  { return { x, x, x }; }
    constexpr       BasicVector3D<Type>::Ref xxx()       &  { return { x, x, x }; }
    constexpr       BasicVector3D<Type>      xxx()       && { return { x, x, x }; }

    constexpr const BasicVector3D<Type>::Ref yyy() const &  { return { y, y, y }; }
    constexpr       BasicVector3D<Type>::Ref yyy()       &  { return { y, y, y }; }
    constexpr       BasicVector3D<Type>      yyy()       && { return { y, y, y }; }

    constexpr const BasicVector3D<Type>::Ref zzz() const &  { return { z, z, z }; }
    constexpr       BasicVector3D<Type>::Ref zzz()       &  { return { z, z, z }; }
    constexpr       BasicVector3D<Type>      zzz()       && { return { z, z, z }; }

    constexpr const BasicVector3D<Type>::Ref www() const &  { return { w, w, w }; }
    constexpr       BasicVector3D<Type>::Ref www()       &  { return { w, w, w }; }
    constexpr       BasicVector3D<Type>      www()       && { return { w, w, w }; }
    /// @}

    /** Defines equality of two BasicVector4D objects
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @see Equality
     */
    friend constexpr bool operator ==(const BasicVector4D<Type> &left, const BasicVector4D<Type> &right)
    {
        return approximately_equal_to(left, right);
    }

    friend constexpr bool operator ==(const BasicVector4D<Type> &left, const Ref &right)
    {
        return approximately_equal_to(left, BasicVector4D<Type>{right});
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
    /** Defines addition of two BasicVector4D objects
     */
    friend constexpr BasicVector4D<Type> operator +(const BasicVector4D<Type> &left, const BasicVector4D<Type> &right)
    {
        return BasicVector4D<Type>{ left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
    }
    /// @}  {Addition}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two BasicVector4D objects
     */
    friend constexpr BasicVector4D<Type> operator -(const BasicVector4D<Type> &left, const BasicVector4D<Type> &right)
    {
        return BasicVector4D<Type>{ left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
    }
    /// @}  {Subtraction}

    /** @name Multiplication
     *  @{
     */
    /** Defines multiplication of two BasicVector4D objects
     */
    friend constexpr BasicVector4D<Type> operator *(const BasicVector4D<Type> &left, const BasicVector4D<Type> &right)
    {
        return BasicVector4D<Type>{ left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w };
    }

    friend constexpr BasicVector4D<Type> operator *(const BasicVector4D<Type> &left, Type right)
    {
        return BasicVector4D<Type>{ left.x * right, left.y * right, left.z * right, left.w * right };
    }

    friend constexpr BasicVector4D<Type> operator *(Type left, const BasicVector4D<Type> right)
    {
        return BasicVector4D<Type>{ left * right.x, left * right.y, left * right.z, left * right.w };
    }
    /// @}  {Multiplication}

    /** @name Division
     *  @{
     */
    /** Defines division of two BasicVector4D objects
     */
    friend constexpr BasicVector4D<Type> operator /(const BasicVector4D<Type> &left, const BasicVector4D<Type> &right)
    {
        return BasicVector4D<Type>{ left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w };
    }

    friend constexpr BasicVector4D<Type> operator /(const BasicVector4D<Type> &left, Type right)
    {
        return BasicVector4D<Type>{ left.x / right, left.y / right, left.z / right, left.w / right };
    }
    /// @}  {Division}
    /// @}  {Vector4DAlgebra}

    /** @name Global Functions
     * 
     *  @relates BasicVector4D
     * 
     *  @{
     */

    /** @addtogroup Equality
     * 
     *  @relates BasicVector4D
     * 
     *  @{
     * 
     *  Compares two BasicVector4D inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     */
    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicVector4D<Type> &value_to_test, const BasicVector4D<Type> &value_it_should_be, OT tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
               approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance) &&
               approximately_equal_to(value_to_test.w, value_it_should_be.w, tolerance);
    }
    /// @}

    /** Sums up the components of @p input
     *  
     *  @param input The BasicVector4D to operate on
     * 
     *  @return The sum of all the components
     */
    friend constexpr Type accumulate(const BasicVector4D<Type> &input)
    {
        return input.x + input.y + input.z + input.w;
    }

    /** Calculate the dot product of two BasicVector4D objects
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
    friend constexpr Type dot(const BasicVector4D<Type> &left, const BasicVector4D<Type> &right)
    {
        return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);
    }

    /** Creates the normalized form of a BasicVector4D
     *  
     *  @param input The BasicVector4D to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr BasicVector4D<Type> normalized(const BasicVector4D<Type> &input)
    {
        return input.normalized();
    }

    /** Calculate the normalized dot product of two BasicVector4D objects
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
    friend constexpr Type dot_normalized(const BasicVector4D<Type> &left, const BasicVector4D<Type> &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }

    /** Calculate the absolute value of all components of a BasicVector4D
     *   
     *   @param input The BasicVector4D to operate on
     *
     *   @return The BasicVector4D with only positive values
     */
    friend constexpr BasicVector4D<Type> abs(const BasicVector4D<Type> &input)
    {
        return BasicVector4D<Type>( std::abs(input.x), std::abs(input.y), std::abs(input.z), std::abs(input.w) );
    }

    /** Calculate the fractional part of all components of a BasicVector4D
     *   
     *   @param input The BasicVector4D to operate on
     *
     *   @return The BasicVector4D with only fractional values
     */
    friend constexpr BasicVector4D<Type> fract(const BasicVector4D<Type> &input)
    {
        return BasicVector4D<Type>( std::modf(input.x), std::modf(input.y), std::modf(input.z), std::modf(input.w) );
    }

    friend constexpr BasicVector4D<Type> saturate(const BasicVector4D<Type> &input, Type lower_bound, Type upper_bound)
    {
        return BasicVector4D<Type>( saturate(input.x, lower_bound, upper_bound),
                            saturate(input.y, lower_bound, upper_bound),
                            saturate(input.z, lower_bound, upper_bound),
                            saturate(input.w, lower_bound, upper_bound) );
    }

    friend std::string format(const BasicVector4D<Type> &input)
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
    template <std::floating_point OT = float>
    friend bool check_if_equal(const BasicVector4D<Type> &input, const BasicVector4D<Type> &near_to, OT tolerance = OT{0.0002})
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
    friend bool check_if_not_equal(const BasicVector4D<Type> &input, const BasicVector4D<Type> &near_to, OT tolerance = OT{0.0002})
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
    friend void CHECK_IF_EQUAL(const BasicVector4D<Type> &input, const BasicVector4D<Type> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_NOT_EQUAL(const BasicVector4D<Type> &input, const BasicVector4D<Type> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_ZERO(const BasicVector4D<Type> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicVector4D<Type>::zero(), tolerance));
    }
    /// @}  {GlobalFunctions}
};


/** @name BasicVector4D::Ref Type Aliases
 *  
 *  @relates BasicVector4D
 * 
 *  @{
 */
using Vector4DfRef = BasicVector4D<float>::Ref;
using Vector4DdRef = BasicVector4D<double>::Ref;
using Vector4DRef  = BasicVector4D<double>::Ref;
using Vector4DlRef = BasicVector4D<long double>::Ref;
///@}  {BasicVector4D::Ref Type Aliases}

/** @name BasicVector4D Type Aliases
 *  
 *  @relates BasicVector4D
 * 
 *  @{
 */
using Vector4Df = BasicVector4D<float>;
using Vector4Dd = BasicVector4D<double>;
using Vector4D  = BasicVector4D<double>;
using Vector4Dl = BasicVector4D<long double>;
///@}  {BasicVector4D Type Aliases}

}