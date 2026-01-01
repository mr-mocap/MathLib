#pragma once

#include "math/Functions.hpp"
#include "math/Vector2D.hpp"
#include <concepts>

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
 *  @headerfile <> <math/Vector3D.hpp>
 */
template <class Type>
struct BasicVector3D
{
    /** @name Types
     *  @{
     */
    using value_type = Type; ///< The underlying implementation type
    /// @}

    /** Class representing a reference to elements of a BasicVector3D object
     * 
     *  @note This class exists to support simple vector swizzle operations.
     * 
     *  @relates BasicVector3D
     */
    struct Ref
    {
        /** @name Types
         *  @{
         */
        using value_type = Type; ///< The underlying implementation type
        /// @}

        /** @name Constructors
         * 
         *  @{
         */
        constexpr Ref(Type &x_in, Type &y_in, Type &z_in) : x{x_in}, y{y_in}, z{z_in} { }
        constexpr Ref(const Ref &) = default;
        constexpr Ref(const BasicVector3D<Type> &other) : x{other.x}, y{other.y}, z{other.z} { }
        /// @}

        /** @name Assignment
         *  @{
         */
        constexpr Ref &operator =(const Ref &input)
        {
            x = input.x;
            y = input.y;
            z = input.z;
            return *this;
        }

        constexpr Ref &operator =(const BasicVector3D<Type> &input)
        {
            x = input.x;
            y = input.y;
            z = input.z;
            return *this;
        }
        /// @}

        /** @name Conversion Operators
         *  @{
         */
        /** BasicVector3D conversion operator
         * 
         *  This allows Vector3DRef objects to automatically be converted to BasicVector3D objects
         *  for situations like passing to functions or constructors to BasicVector3D objects.
         */
        constexpr operator BasicVector3D<Type>() const { return { x, y, z }; }
        /// @}

        /** @name Element Access
         *  @{
         */
        Type &x;
        Type &y;
        Type &z;
        /// @}

        /** @name Equality
         *  @{
         */
        /** Defines equality of two BasicVector3D::Ref objects
         *  
         *  @note Uses approximately_equal_to under-the-hood
         *  
         *  @note We take advantage of the new C++20 rule where if there
         *        is not an appropriate operator ==(const BasicVector3D<Type> &) defined
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

        friend constexpr bool operator ==(const Ref &left, const BasicVector3D<Type> &right)
        {
            return approximately_equal_to( left, right );
        }
        /// @} {Equality}

        /** @name Operators
         * 
         *  @relates BasicVector3D
         * 
         *  @{
         */
        friend constexpr BasicVector3D<Type> operator +(const Ref &left, const Ref &right)
        {
            return { left.x + right.x, left.y + right.y, left.z + right.z };
        }
        friend constexpr BasicVector3D<Type> operator +(const Ref &left, const BasicVector3D<Type> &right)
        {
            return { left.x + right.x, left.y + right.y, left.z + right.z };
        }
        friend constexpr BasicVector3D<Type> operator -(const Ref &left, const Ref &right)
        {
            return { left.x - right.x, left.y - right.y, left.z - right.z };
        }
        friend constexpr BasicVector3D<Type> operator -(const Ref &left, const BasicVector3D<Type> &right)
        {
            return { left.x - right.x, left.y - right.y, left.z - right.z };
        }
        friend constexpr BasicVector3D<Type> operator *(const Ref &left, const Ref &right)
        {
            return { left.x * right.x, left.y * right.y, left.z * right.z };
        }
        friend constexpr BasicVector3D<Type> operator *(const Ref &left, const BasicVector3D<Type> &right)
        {
            return { left.x * right.x, left.y * right.y, left.z * right.z };
        }
        friend constexpr BasicVector3D<Type> operator /(const Ref &left, const Ref &right)
        {
            return { left.x / right.x, left.y / right.y, left.z / right.z };
        }
        friend constexpr BasicVector3D<Type> operator /(const Ref &left, const BasicVector3D<Type> &right)
        {
            return { left.x / right.x, left.y / right.y, left.z / right.z };
        }
        /// @} {Operators}

        /** Compares two BasicVector3D::Ref inputs equal, component-wise, to within a tolerance
         * 
         *  @addtogroup Equality
         * 
         *  @relates BasicVector3D
         *  
         *  @param value_to_test
         *  @param value_it_should_be 
         *  @param tolerance          How close they should be to be considered equal
         *  
         *  @return @c true if they are equal
         * 
         *  @{
         */
        template <std::floating_point OT = float>
        friend constexpr bool approximately_equal_to(const Ref &value_to_test,
                                                     const Ref &value_it_should_be,
                                                           OT   tolerance = OT{0.0002})
        {
            return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
                   approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
                   approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance);
        }

        template <std::floating_point OT = float>
        friend constexpr bool approximately_equal_to(const Ref                 &value_to_test,
                                                     const BasicVector3D<Type> &value_it_should_be,
                                                           OT                   tolerance = OT{0.0002})
        {
            return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
                   approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
                   approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance);
        }
        /// @}

        /** Sums up the components of @p input
         *  
         *  @param input The BasicVector3D::Ref to operate on
         * 
         *  @return The sum of all the components
         */
        friend constexpr Type accumulate(const Ref &input)
        {
            return input.x + input.y + input.z;
        }

        /** Calculate the dot product of two BasicVector3D objects
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
        friend constexpr Type dot(const Ref &left, const Ref &right)
        {
            return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
        }
        friend constexpr Type dot(const Ref &left, const BasicVector3D<Type> &right)
        {
            return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
        }
        /// @}

        /** Calculate the normalized dot product of two BasicVector3D objects
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
        friend constexpr Type dot_normalized(const Ref &left, const Ref &right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }
        friend constexpr Type dot_normalized(const Ref &left, const BasicVector3D<Type> &right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }
        /// @}

        /** Calculates the cross product of two BasicVector3D::Ref objects
         * 
         *  @param left  The first vector
         *  @param right The second vector
         * 
         *  @return The cross product of the input vectors
         */
        friend constexpr BasicVector3D<Type> cross(const Ref &left, const Ref &right)
        {
            return cross( BasicVector3D<Type>(left), BasicVector3D<Type>(right) );
        }

        /** Creates the normalized form of a BasicVector3D::Ref
         *  
         *  @param input The BasicVector3D::Ref to normalize
         *  
         *  @return The normalized version of @p input
         */
        friend constexpr BasicVector3D<Type> normalized(const Ref &input)
        {
            return BasicVector3D<Type>( input ).normalized();
        }

        /** Calculate the absolute value of all components of a BasicVector3D
         *   
         *   @param input The BasicVector3D::Ref to operate on
         *
         *   @return The BasicVector3D with only positive values
         */
        friend constexpr BasicVector3D<Type> abs(const Ref &input)
        {
            return { std::abs(input.x), std::abs(input.y), std::abs(input.z) };
        }

        /** Calculate the fractional part of all components of a BasicVector3D
         *   
         *   @param input The BasicVector3D::Ref to operate on
         *
         *   @return The BasicVector3D with only fractional values
         */
        constexpr BasicVector3D<Type> fract(const Ref &input)
        {
            return { std::modf(input.x), std::modf(input.y), std::modf(input.z) };
        }

        constexpr BasicVector3D<Type> saturate(const Ref &input, Type lower_bound, Type upper_bound)
        {
            return { Math::saturate(input.x, lower_bound, upper_bound),
                     Math::saturate(input.y, lower_bound, upper_bound),
                     Math::saturate(input.z, lower_bound, upper_bound) };
        }

        friend std::string format(const Ref &input)
        {
            return std::format("[x: {:.6}, y: {:.6}, z: {:.6}]", input.x, input.y, input.z);
        }
    };

    /** @name Constructors
     *  @{
     */
    constexpr BasicVector3D() = default;
    constexpr BasicVector3D(const Type &x_in, const Type &y_in = 0, const Type &z_in = 0)
        :
        x{x_in},
        y{y_in},
        z{z_in}
    {
    }
    constexpr BasicVector3D(const BasicVector2D<Type> &other, Type z_in = 0)
        :
        x{other.x},
        y{other.y},
        z{z_in}
    {
    }
    constexpr BasicVector3D(Type x_in, const BasicVector2D<Type> &other)
        :
        x{x_in},
        y{other.x},
        z{other.y}
    {
    }
    /// @}

    /** @name Constants
     *  @{
     */
    constexpr static BasicVector3D<Type> unit_x() { return { Type{1}, Type{0}, Type{0} }; }
    constexpr static BasicVector3D<Type> unit_y() { return { Type{0}, Type{1}, Type{0} }; }
    constexpr static BasicVector3D<Type> unit_z() { return { Type{0}, Type{0}, Type{1} }; }

    constexpr static BasicVector3D<Type> zero() { return { }; }
    /// @}

    constexpr value_type normSquared() const { return (x * x) + (y * y) + (z * z); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr BasicVector3D<Type> normalized() const
    {
        auto n = magnitude();

        return { x / n, y / n, z / n };
    }

    /** @name Invalid Value Check
     *  @{
     */
    bool isNaN() const { return std::isnan(x) || std::isnan(y) || std::isnan(z); }
    bool isInf() const { return std::isinf(x) || std::isinf(y) || std::isinf(z); }
    /// @}

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

    constexpr const Ref                 xyz() const &  { return { x, y, z }; }
    constexpr       Ref                 xyz()       &  { return { x, y, z }; }
    constexpr       BasicVector3D<Type> xyz()       && { return { x, y, z }; }

    constexpr const Ref                 xzy() const &  { return { x, z, y }; }
    constexpr       Ref                 xzy()       &  { return { x, z, y }; }
    constexpr       BasicVector3D<Type> xzy()       && { return { x, z, y }; }

    constexpr const Ref                 zxy() const &  { return { z, x, y }; }
    constexpr       Ref                 zxy()       &  { return { z, x, y }; }
    constexpr       BasicVector3D<Type> zxy()       && { return { z, x, y }; }

    constexpr const Ref                 zyx() const &  { return { z, y, x }; }
    constexpr       Ref                 zyx()       &  { return { z, y, x }; }
    constexpr       BasicVector3D<Type> zyx()       && { return { z, y, x }; }
    /// @}

    /** Defines equality of two BasicVector3D objects
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @see Equality
     * 
     *  @{
     */
    friend constexpr bool operator ==(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return approximately_equal_to(left, right);
    }

    friend constexpr bool operator ==(const BasicVector3D<Type> &left, const Ref &right)
    {
        return approximately_equal_to(left, right);
    }
    /// @}

    /** @name Element Access
     *  @{
     */
    value_type x{};
    value_type y{};
    value_type z{};
    /// @}

    /** @addtogroup Equality
     * 
     *  @relates BasicVector3D
     * 
     *  @{
     * 
     *  Compares two BasicVector3D inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     */
    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicVector3D<Type> &value_to_test,
                                                 const BasicVector3D<Type> &value_it_should_be,
                                                       OT                   tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
               approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance);
    }

    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicVector3D<Type> &value_to_test,
                                                 const Ref                 &value_it_should_be,
                                                       OT                   tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance) &&
               approximately_equal_to(value_to_test.z, value_it_should_be.z, tolerance);
    }
    /// @}

    /** @addtogroup Vector3DAlgebra 3D Vector Algebra
     * 
     *  Three Dimensional Vector Algrbra
     * 
     *  @{
     */

    /** @name Operators
     *  
     *  @relates BasicVector3D
     *  @{
     */
    friend constexpr BasicVector3D<Type> operator +(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return { left.x + right.x, left.y + right.y, left.z + right.z };
    }

    friend constexpr BasicVector3D<Type> operator +(const BasicVector3D<Type> &left, const Ref &right)
    {
        return { left.x + right.x, left.y + right.y, left.z + right.z };
    }

    friend constexpr BasicVector3D<Type> operator -(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return { left.x - right.x, left.y - right.y, left.z - right.z };
    }

    friend constexpr BasicVector3D<Type> operator -(const BasicVector3D<Type> &left, const Ref &right)
    {
        return { left.x - right.x, left.y - right.y, left.z - right.z };
    }

    friend constexpr BasicVector3D<Type> operator *(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return { left.x * right.x, left.y * right.y, left.z * right.z };
    }

    friend constexpr BasicVector3D<Type> operator *(const BasicVector3D<Type> &left, Type right)
    {
        return { left.x * right, left.y * right, left.z * right };
    }

    friend constexpr BasicVector3D<Type> operator /(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return { left.x / right.x, left.y / right.y, left.z / right.z };
    }

    friend constexpr BasicVector3D<Type> operator /(const BasicVector3D<Type> &left, Type right)
    {
        return { left.x / right, left.y / right, left.z / right };
    }
    /// @}  {Operators}
    /// @}  {Vector3DAlgebra}

    /** Sums up the components of @p input
     *  
     *  @param input The BasicVector3D to operate on
     * 
     *  @return The sum of all the components
     */
    friend constexpr Type accumulate(const BasicVector3D<Type> &input)
    {
        return input.x + input.y + input.z;
    }

    /** Calculate the dot product of two BasicVector3D objects
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
    friend constexpr Type dot(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
    }

    /** Calculate the normalized dot product of two BasicVector3D objects
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
    friend constexpr Type dot_normalized(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }

    /** Calculates the cross product of two BasicVector3D objects
     * 
     *  @param left  The first vector
     *  @param right The second vector
     * 
     *  @return The cross product of the input vectors
     */
    friend constexpr BasicVector3D<Type> cross(const BasicVector3D<Type> &left, const BasicVector3D<Type> &right)
    {
        return { cross( left.yz(), right.yz() ),
                 cross( left.zx(), right.zx() ),
                 cross( left.xy(), right.xy() ) };
    }

    /** Creates the normalized form of a BasicVector3D
     *  
     *  @param input The BasicVector3D to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr BasicVector3D<Type> normalized(const BasicVector3D<Type> &input)
    {
        return input.normalized();
    }

    /** Calculate the absolute value of all components of a BasicVector3D
     *   
     *   @param input The BasicVector3D to operate on
     *
     *   @return The BasicVector3D with only positive values
     */
    friend constexpr BasicVector3D<Type> abs(const BasicVector3D<Type> &input)
    {
        return { std::abs(input.x), std::abs(input.y), std::abs(input.z) };
    }

    /** Calculate the fractional part of all components of a BasicVector3D
     *   
     *   @param input The BasicVector3D to operate on
     *
     *   @return The BasicVector3D with only fractional values
     */
    friend constexpr BasicVector3D<Type> fract(const BasicVector3D<Type> &input)
    {
        return { std::modf(input.x), std::modf(input.y), std::modf(input.z) };
    }

    friend constexpr BasicVector3D<Type> saturate(const BasicVector3D<Type> &input,
                                                        Type                 lower_bound,
                                                        Type                 upper_bound)
    {
        return { Math::saturate(input.x, lower_bound, upper_bound),
                 Math::saturate(input.y, lower_bound, upper_bound),
                 Math::saturate(input.z, lower_bound, upper_bound) };
    }

    friend std::string format(const BasicVector3D<Type> &input)
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
    template <std::floating_point OT = float>
    friend bool check_if_equal(const BasicVector3D<Type> &input,
                               const BasicVector3D<Type> &near_to,
                                     OT                   tolerance = OT{0.0002})
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
    friend bool check_if_not_equal(const BasicVector3D<Type> &input,
                                   const BasicVector3D<Type> &near_to,
                                         OT                   tolerance = OT{0.0002})
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

    /** @addtogroup Checks
     * 
     *  Compare two values for equality with a tolerance and causes an assertion when false
     *  
     *  @param input     The first value to compare
     *  @param near_to   The second value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if the two are equal within @c tolerance , @c false otherwise
     */
    template <std::floating_point OT = float>
    friend void CHECK_IF_EQUAL(const BasicVector3D<Type> &input,
                               const BasicVector3D<Type> &near_to,
                                     OT                   tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    /** @addtogroup Checks
     * 
     *  Compare two values for inequality with a tolerance and causes an assertion when false
     *  
     *  @param input     The first value to compare
     *  @param near_to   The second value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
     */
    template <std::floating_point OT = float>
    friend void CHECK_IF_NOT_EQUAL(const BasicVector3D<Type> &input,
                                   const BasicVector3D<Type> &near_to,
                                         OT                   tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    /** @addtogroup Checks
     * 
     *  Compare a value to near zero
     *  
     *  @param input     The first value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if @c input is inside @c tolerance , @c false otherwise
     */
    template <std::floating_point OT = float>
    friend void CHECK_IF_ZERO(const BasicVector3D<Type> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicVector3D<Type>::zero(), tolerance));
    }
};

/** @defgroup BasicVector3DRefAliases Vector3DRef Types
 * 
 *  Here are the type aliases for BasicVector3D::Ref
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicVector3D::Ref
 *  @{
 */
using Vector3DfRef = BasicVector3D<float>::Ref;
using Vector3DdRef = BasicVector3D<double>::Ref;
using Vector3DRef  = BasicVector3D<double>::Ref;
using Vector3DlRef = BasicVector3D<long double>::Ref;
///@}  {BasicVector3D::Ref Type Aliases}


/** @defgroup BasicVector3DAliases Vector3D Types
 * 
 *  Here are the type aliases for BasicVector3D
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicVector3D
 *  @{
 */
using Vector3Df = BasicVector3D<float>;
using Vector3Dd = BasicVector3D<double>;
using Vector3D  = BasicVector3D<double>;
using Vector3Dl = BasicVector3D<long double>;
///@}  {BasicVector3D Type Aliases}

}