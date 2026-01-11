#pragma once

#include <Math/math/Functions.hpp>
#include <Math/Concepts.hpp>

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
 *  @headerfile <> <math/Vector2D.hpp>
 */
template <class Type>
struct BasicVector2D
{
    /** @name Types
     *  @{
     */
    using value_type = Type; ///< The underlying implementation type
    /// @}

    /** Class representing a reference to elements of a BasicVector2D object
     * 
     *  @note This class exists to support simple vector swizzle operations.
     * 
     *  @relates BasicVector2D
     */
    template <class RType>
    struct BasicRef
    {
        /** @name Types
         *  @{
         */
        using value_type = RType; ///< The underlying implementation type
        /// @}

        /** @name Constructors
         * 
         *  @{
         */
        constexpr BasicRef(RType &x_in, RType &y_in) : x{x_in}, y{y_in} { }
        constexpr BasicRef(const BasicRef &) = default;
        constexpr BasicRef(const BasicVector2D<RType> &other) : x{other.x}, y{other.y} { }
        /// @}

        /** @name Assignment
         *  @{
         */
        constexpr BasicRef &operator =(BasicRef input)
        {
            x = input.x;
            y = input.y;
            return *this;
        }

        constexpr BasicRef &operator =(const BasicVector2D<RType> &input)
        {
            x = input.x;
            y = input.y;
            return *this;
        }
        /// @}

        /** @name Equality
         *  @{
         */
        /** Defines equality of two BasicVector2D::Ref objects
         *  
         *  @note Uses approximately_equal_to under-the-hood
         *  
         *  @note We take advantage of the new C++20 rule where if there
         *        is not an appropriate operator ==(const BasicVector2D<Type> &) defined
         *        for this class, then the compiler tries a swapped instantiation
         *        in its place.  This allows us to only define the typical operator ==() here
         *        and then define comparison of different types to the other class.
         * 
         *  @see Equality
         */
        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr bool operator ==(BasicRef left, BasicRef<U> right)
        {
            return approximately_equal_to( left, right );
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr bool operator ==(BasicRef left, const BasicVector2D<U> &right)
        {
            return approximately_equal_to( left, right );
        }
        /// @}

        /** @addtogroup Vector2DAlgebra 2D Vector Algebra
         * 
         *  Two Dimensional Vector Algebra
         * 
         *  @{
         */

        /** @name Operators
         * 
         *  @relates BasicVector2D
         * 
         *  @{
         */
        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator +(BasicRef left, BasicRef<U> right)
        {
            return { left.x + right.x, left.y + right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator +(BasicRef left, const BasicVector2D<U> &right)
        {
            return { left.x + right.x, left.y + right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator -(BasicRef left, BasicRef<U> right)
        {
            return { left.x - right.x, left.y - right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator -(BasicRef left, const BasicVector2D<U> &right)
        {
            return { left.x - right.x, left.y - right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator *(BasicRef left, BasicRef<U> right)
        {
            return { left.x * right.x, left.y * right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator *(BasicRef left, const BasicVector2D<U> &right)
        {
            return { left.x * right.x, left.y * right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator *(BasicRef left, const U &scalar)
        {
            return { left.x * scalar, left.y * scalar };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator *(const U &scalar, BasicRef right)
        {
            return { scalar * right.x, scalar * right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator /(BasicRef left, BasicRef<U> right)
        {
            return { left.x / right.x, left.y / right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator /(BasicRef left, const BasicVector2D<U> &right)
        {
            return { left.x / right.x, left.y / right.y };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> operator /(BasicRef left, U scalar)
        {
            return { left.x / scalar, left.y / scalar };
        }
        /// @} {Operators}
        /// @} {Vector2DAlgebra}

        /** @name Conversion Operators
         *  @{
         */
        /** BasicVector2D conversion operator
         * 
         *  This allows Ref objects to automatically be converted to BasicVector2D objects
         *  for situations like passing to functions or constructors to BasicVector2D objects.
         */
        constexpr operator BasicVector2D<RType>() const { return { x, y }; }

        constexpr operator std::tuple<RType, RType>() const { return std::make_tuple( x, y ); }
        /// @}

        /** @name Element Access
         *  
         *  @{
         */
        RType &x;
        RType &y;
        /// @}


        /** Compares two BasicVector2D inputs equal, component-wise, to within a tolerance
         * 
         *  @addtogroup Equality
         * 
         *  @relates BasicVector2D
         *  
         *  @param value_to_test
         *  @param value_it_should_be 
         *  @param tolerance          How close they should be to be considered equal
         *  
         *  @return @c true if they are equal
         */
        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr bool approximately_equal_to(BasicRef    value_to_test,
                                                     BasicRef<U> value_it_should_be,
                                                           OT    tolerance = OT{0.0002})
        {
            return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
                   approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
        }

        /** Compares a BasicVector2D::Ref and BasicVector2D inputs equal, component-wise, to within a tolerance
         * 
         *  @addtogroup Equality
         * 
         *  @relates BasicVector2D
         *  
         *  @param value_to_test
         *  @param value_it_should_be 
         *  @param tolerance          How close they should be to be considered equal
         *  
         *  @return @c true if they are equal
         */
        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr bool approximately_equal_to(      BasicRef          value_to_test,
                                                     const BasicVector2D<U> &value_it_should_be,
                                                           OT                tolerance = OT{0.0002})
        {
            return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
                   approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
        }

        friend constexpr RType accumulate(BasicRef input)
        {
            return input.x + input.y;
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr RType dot(BasicRef left, BasicRef<U> right)
        {
            return (left.x * right.x) + (left.y * right.y);
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr RType dot(BasicRef left, const BasicVector2D<U> &right)
        {
            return (left.x * right.x) + (left.y * right.y);
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr RType dot_normalized(BasicRef left, BasicRef<U> right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr RType dot_normalized(BasicRef left, const BasicVector2D<U> &right)
        {
            return dot(left, right) / (left.magnitude() * right.magnitude());
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr RType cross(BasicRef left, BasicRef<U> right)
        {
            return (left.x * right.y) - (left.y * right.x);
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr RType cross(BasicRef left, const BasicVector2D<U> &right)
        {
            return (left.x * right.y) - (left.y * right.x);
        }

        friend constexpr BasicVector2D<RType> normalized(BasicRef input)
        {
            return BasicVector2D<RType>( input ).normalized();
        }

        friend constexpr BasicVector2D<RType> abs(BasicRef input)
        {
            return { std::abs(input.x), std::abs(input.y) };
        }

        friend constexpr BasicVector2D<RType> fract(BasicRef input)
        {
            Type dummy;

            return { std::modf(input.x, &dummy), std::modf(input.y, &dummy) };
        }

        friend constexpr BasicVector2D<RType> saturate(BasicRef input, RType lower_bound, RType upper_bound)
        {
            return { Math::saturate(input.x, lower_bound, upper_bound),
                     Math::saturate(input.y, lower_bound, upper_bound) };
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> lerp(BasicRef    input_lower_bound,
                                                   BasicRef<U> input_upper_bound,
                                                   float       percentage_zero_to_one)
        {
            return (input_upper_bound - input_lower_bound) * percentage_zero_to_one + input_lower_bound;
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> lerp(      BasicRef          input_lower_bound,
                                                   const BasicVector2D<U> &input_upper_bound,
                                                         float             percentage_zero_to_one)
        {
            return (input_upper_bound - input_lower_bound) * percentage_zero_to_one + input_lower_bound;
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> mix(BasicRef    input_lower_bound,
                                                  BasicRef<U> input_upper_bound,
                                                  float       percentage_zero_to_one)
        {
            return lerp( input_lower_bound, input_upper_bound, percentage_zero_to_one );
        }

        template <class U>
            requires Concept::SameUnqualified<RType, U>
        friend constexpr BasicVector2D<RType> mix(      BasicRef          input_lower_bound,
                                                  const BasicVector2D<U> &input_upper_bound,
                                                        float             percentage_zero_to_one)
        {
            return lerp( input_lower_bound, input_upper_bound, percentage_zero_to_one );
        }

        friend std::string format(BasicRef input)
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
         * 
         *  @{
         */
        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend bool check_if_equal(BasicRef    input,
                                   BasicRef<U> near_to,
                                   OT          tolerance = OT{0.0002})
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

        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend bool check_if_equal(      BasicRef          input,
                                   const BasicVector2D<U> &near_to,
                                         OT                tolerance = OT{0.0002})
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
        /// @}

        /** @addtogroup Checks
         * 
         *  Compare two values for inequality with a tolerance and prints debug information when false
         *  
         *  @param input     The first value to compare
         *  @param near_to   The second value to compare
         *  @param tolerance The minimum value for being considered equal
         * 
         *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
         * 
         *  @{
         */
        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend bool check_if_not_equal(BasicRef input,
                                       BasicRef near_to,
                                       OT       tolerance = OT{0.0002})
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

        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend bool check_if_not_equal(      BasicRef          input,
                                       const BasicVector2D<U> &near_to,
                                             OT                tolerance = OT{0.0002})
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
        /// @}

        /** @addtogroup Checks
         * 
         *  Compare two values for equality with a tolerance and causes an assertion when false
         *  
         *  @param input     The first value to compare
         *  @param near_to   The second value to compare
         *  @param tolerance The minimum value for being considered equal
         * 
         *  @return @c true if the two are equal within @c tolerance , @c false otherwise
         * 
         *  @{
         */
        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend void CHECK_IF_EQUAL(BasicRef    input,
                                   BasicRef<U> near_to,
                                   OT          tolerance = OT{0.0002})
        {
            assert( check_if_equal(input, near_to, tolerance) );
        }

        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend void CHECK_IF_EQUAL(      BasicRef          input,
                                   const BasicVector2D<U> &near_to,
                                         OT                tolerance = OT{0.0002})
        {
            assert( check_if_equal(input, near_to, tolerance) );
        }
        /// @}

        /** @addtogroup Checks
         * 
         *  Compare two values for inequality with a tolerance and causes an assertion when false
         *  
         *  @param input     The first value to compare
         *  @param near_to   The second value to compare
         *  @param tolerance The minimum value for being considered equal
         * 
         *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
         * 
         *  @{
         */
        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend void CHECK_IF_NOT_EQUAL(BasicRef    input,
                                       BasicRef<U> near_to,
                                       OT          tolerance = OT{0.0002})
        {
            assert( check_if_not_equal(input, near_to, tolerance) );
        }

        template <class U, std::floating_point OT = float>
            requires Concept::SameUnqualified<RType, U>
        friend void CHECK_IF_NOT_EQUAL(      BasicRef          input,
                                       const BasicVector2D<U> &near_to,
                                             OT                tolerance = OT{0.0002})
        {
            assert( check_if_not_equal(input, near_to, tolerance) );
        }
        /// @}

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
        friend void CHECK_IF_ZERO(BasicRef input, OT tolerance = OT{0.0002})
        {
            assert( check_if_equal(input, BasicVector2D<RType>::zero(), tolerance));
        }
    };

    using Ref      = BasicRef<Type>;
    using ConstRef = BasicRef<const Type>;

    /** @name Constructors
     * 
     *  @{
     */
    constexpr BasicVector2D() = default;
    constexpr BasicVector2D(const Type &x_in, const Type &y_in = 0)
        :
        x{x_in},
        y{y_in}
    {
    }
    constexpr BasicVector2D(const std::tuple<Type, Type> &t)
        :
        x{ std::get<0>( t ) },
        y{ std::get<1>( t ) }
    {
    }
    /// @}

    /** @name Assignment
     *  @{
     */
    constexpr BasicVector2D<Type> &operator =(const BasicVector2D &other) = default;
    constexpr BasicVector2D<Type> &operator =(Ref other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
    /// @}

    /** @name Conversion Operators
     *  @{
     */
    constexpr operator std::tuple<Type, Type>() const { return std::make_tuple( x, y ); }
    /// @}

    /** @name Equality
     *  @{
     */
    /** Defines equality of two BasicVector2D objects
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note We take advantage of new C++20 rules that can automatically
     *        generate the operator !=() from the operator ==().
     * 
     *  @see Equality
     */
    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr bool operator ==(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return approximately_equal_to(left, right);
    }
    /// @}

    /** @name Constants
     *  @{
     */
    constexpr static BasicVector2D<Type> unit_x() { return { Type{1}, Type{0} }; }
    constexpr static BasicVector2D<Type> unit_y() { return { Type{0}, Type{1} }; }

    constexpr static BasicVector2D<Type> zero() { return {}; }
    /// @}
 
    /** @addtogroup Vector2DAlgebra 2D Vector Algebra
     * 
     *  Two Dimensional Vector Algebra
     * 
     *  @{
     */

    /** @name Operators
     *  
     *  @relates Vector2D
     *  @{
     */
    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator +(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return { left.x + right.x, left.y + right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator +(const BasicVector2D &left, BasicRef<U> right)
    {
        return { left.x + right.x, left.y + right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator -(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return { left.x - right.x, left.y - right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator -(const BasicVector2D &left, BasicRef<U> right)
    {
        return { left.x - right.x, left.y - right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator *(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return { left.x * right.x, left.y * right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator *(const BasicVector2D &left, BasicRef<U> right)
    {
        return { left.x * right.x, left.y * right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator *(const BasicVector2D &left, const U &scalar)
    {
        return { left.x * scalar, left.y * scalar };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator *(const U &scalar, const BasicVector2D<U> &right)
    {
        return { scalar * right.x, scalar * right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator /(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return { left.x / right.x, left.y / right.y };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> operator /(const BasicVector2D &left, BasicRef<U> right)
    {
        return { left.x / right.x, left.y / right.y };
    }

    friend constexpr BasicVector2D<Type> operator /(const BasicVector2D &left, const Type &scalar)
    {
        return { left.x / scalar, left.y / scalar };
    }
    /// @}  {Operators}
    /// @}  {Vector2DAlgebra}

    constexpr value_type normSquared() const { return (x * x) + (y * y); }
    constexpr value_type norm() const { return std::sqrt( normSquared() ); } ///< @todo See if we need to use std::hypot()

    constexpr value_type magnitudeSquared() const { return normSquared(); }
    constexpr value_type magnitude() const { return norm(); }

    constexpr BasicVector2D<Type> normalized() const
    {
        auto n = norm();

        return { x / n, y / n };
    }

    /** @name Invalid Value Check
     *  @{
     */
    bool isNaN() const { return std::isnan(x) || std::isnan(y); }
    bool isInf() const { return std::isinf(x) || std::isinf(y); }
    /// @}

    /** @name Swizzle operations
     *  @{
     */
    constexpr BasicVector2D xx() const { return { x, x }; }
    constexpr BasicVector2D xx()       { return { x, x }; }

    constexpr BasicVector2D yy() const { return { y, y }; }
    constexpr BasicVector2D yy()       { return { y, y }; }

    constexpr ConstRef      xy() const &  { return { x, y }; }
    constexpr Ref           xy()       &  { return { x, y }; }
    constexpr BasicVector2D xy()       && { return { x, y }; }

    constexpr ConstRef      yx() const &  { return { y, x }; }
    constexpr Ref           yx()       &  { return { y, x }; }
    constexpr BasicVector2D yx()       && { return { y, x }; }
    /// @} {Swizzle operations}


    /** @name Element Access
     *  @{
     */
    Type x{};
    Type y{};
    /// @}

    /** @addtogroup Equality
     * 
     *  @relates BasicVector2D
     * 
     *  @{
     * 
     *  Compares two BasicVector2D inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     * 
     *  @see Equality
     */
    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr bool approximately_equal_to(const BasicVector2D    &value_to_test,
                                                 const BasicVector2D<U> &value_it_should_be,
                                                       OT                tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
    }

    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr bool approximately_equal_to(const BasicVector2D &value_to_test,
                                                       BasicRef<U>    value_it_should_be,
                                                       OT             tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.x, value_it_should_be.x, tolerance) &&
               approximately_equal_to(value_to_test.y, value_it_should_be.y, tolerance);
    }
    /// @}

    /** Sums up the components of @p input
     *  
     *  @input The BasicVector2D to operate on
     */
    friend constexpr Type accumulate(const BasicVector2D<Type> &input)
    {
        return input.x + input.y;
    }

    /** Calculate the dot product of two BasicVector2D objects
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
    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr Type dot(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr Type dot(const BasicVector2D &left, BasicRef<U> right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }
    /// @}

    /** Calculate the normalized dot product of two BasicVector2D objects
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
    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr Type dot_normalized(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr Type dot_normalized(const BasicVector2D &left, BasicRef<U> right)
    {
        return dot(left, right) / (left.magnitude() * right.magnitude());
    }
    /// @} {dot_normalized}

    /** Creates the normalized form of a BasicVector2D
     *  
     *  @param input The BasicVector2D to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr BasicVector2D<Type> normalized(const BasicVector2D &input)
    {
        return input.normalized();
    }

    /** Calculates a pseudo cross product between two BasicVector2D objects
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
     * 
     *  @{
     */
    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr Type cross(const BasicVector2D &left, const BasicVector2D<U> &right)
    {
        return (left.x * right.y) - (left.y * right.x);
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr Type cross(const BasicVector2D<Type> &left, BasicRef<U> right)
    {
        return (left.x * right.y) - (left.y * right.x);
    }
    /// @} {cross}

    /** Calculate the absolute value of all components of a BasicVector2D
     *   
     *   @param input The BasicVector2D to operate on
     *
     *   @return The BasicVector2D with only positive values
     */
    friend constexpr BasicVector2D<Type> abs(const BasicVector2D &input)
    {
        return { std::abs(input.x), std::abs(input.y) };
    }

    /** Calculate the fractional part of all components of a BasicVector2D
     *   
     *   @param input The BasicVector2D to operate on
     *
     *   @return The BasicVector2D with only fractional values
     */
    friend constexpr BasicVector2D<Type> fract(const BasicVector2D &input)
    {
        return { std::modf(input.x), std::modf(input.y) };
    }

    friend constexpr BasicVector2D<Type> saturate(const BasicVector2D &input, const Type lower_bound, Type upper_bound)
    {
        return { Math::saturate(input.x, lower_bound, upper_bound),
                 Math::saturate(input.y, lower_bound, upper_bound) };
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> lerp(const BasicVector2D    &input_lower_bound,
                                              const BasicVector2D<U> &input_upper_bound,
                                                    float             percentage_zero_to_one)
    {
        return (input_upper_bound - input_lower_bound) * percentage_zero_to_one + input_lower_bound;
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> lerp(const BasicVector2D &input_lower_bound,
                                                    BasicRef<U>    input_upper_bound,
                                                    float          percentage_zero_to_one)
    {
        return (input_upper_bound - input_lower_bound) * percentage_zero_to_one + input_lower_bound;
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> mix(const BasicVector2D    &input_lower_bound,
                                             const BasicVector2D<U> &input_upper_bound,
                                                   float             percentage_zero_to_one)
    {
        return lerp( input_lower_bound, input_upper_bound, percentage_zero_to_one );
    }

    template <class U>
        requires Concept::SameUnqualified<Type, U>
    friend constexpr BasicVector2D<Type> mix(const BasicVector2D &input_lower_bound,
                                                   BasicRef<U>    input_upper_bound,
                                                   float          percentage_zero_to_one)
    {
        return lerp( input_lower_bound, input_upper_bound, percentage_zero_to_one );
    }

    friend std::string format(const BasicVector2D &input)
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
     * 
     *  @{
     */
    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend bool check_if_equal(const BasicVector2D    &input,
                               const BasicVector2D<U> &near_to,
                                     OT                tolerance = OT{0.0002})
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

    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend bool check_if_equal(const BasicVector2D &input,
                                     BasicRef<U>    near_to,
                                     OT             tolerance = OT{0.0002})
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
    /// @}

    /** @addtogroup Checks
     * 
     *  Compare two values for inequality with a tolerance and prints debug information when false
     *  
     *  @param input     The first value to compare
     *  @param near_to   The second value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
     * 
     *  @{
     */
    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend bool check_if_not_equal(const BasicVector2D    &input,
                                   const BasicVector2D<U> &near_to,
                                         OT                tolerance = OT{0.0002})
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

    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend bool check_if_not_equal(const BasicVector2D &input,
                                         BasicRef<U>    near_to,
                                         OT             tolerance = OT{0.0002})
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
    /// @}

    /** @addtogroup Checks
     * 
     *  Compare two values for equality with a tolerance and causes an assertion when false
     *  
     *  @param input     The first value to compare
     *  @param near_to   The second value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if the two are equal within @c tolerance , @c false otherwise
     * 
     *  @{
     */
    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend void CHECK_IF_EQUAL(const BasicVector2D    &input,
                               const BasicVector2D<U> &near_to,
                                     OT                tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend void CHECK_IF_EQUAL(const BasicVector2D &input,
                                     BasicRef<U>    near_to,
                                     OT             tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }
    /// @}

    /** @addtogroup Checks
     * 
     *  Compare two values for inequality with a tolerance and causes an assertion when false
     *  
     *  @param input     The first value to compare
     *  @param near_to   The second value to compare
     *  @param tolerance The minimum value for being considered equal
     * 
     *  @return @c true if the two are not equal outside @c tolerance , @c false otherwise
     * 
     *  @{
     */
    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend void CHECK_IF_NOT_EQUAL(const BasicVector2D    &input,
                                   const BasicVector2D<U> &near_to,
                                         OT                tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    template <class U, std::floating_point OT = float>
        requires Concept::SameUnqualified<Type, U>
    friend void CHECK_IF_NOT_EQUAL(const BasicVector2D &input,
                                         BasicRef<U>    near_to,
                                         OT             tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }
    /// @}

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
    friend void CHECK_IF_ZERO(const BasicVector2D &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicVector2D<Type>::zero(), tolerance));
    }
};

/** @defgroup BasicVector2DRefAliases Vector2DRef Types
 * 
 *  Here are the type aliases for BasicVector2D::Ref
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicVector2D::Ref
 *  @{
 */
using Vector2DfRef = BasicVector2D<float>::Ref;
using Vector2DdRef = BasicVector2D<double>::Ref;
using Vector2DRef  = BasicVector2D<double>::Ref;
using Vector2DlRef = BasicVector2D<long double>::Ref;

using Vector2DfConstRef = BasicVector2D<float>::ConstRef;
using Vector2DdConstRef = BasicVector2D<double>::ConstRef;
using Vector2DConstRef  = BasicVector2D<double>::ConstRef;
using Vector2DlConstRef = BasicVector2D<long double>::ConstRef;
///@}  {BasicVector2D::Ref Type Aliases}


/** @defgroup BasicVector2DAliases Vector2D Types
 * 
 *  Here are the type aliases for BasicVector2D
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicVector2D
 *  @{
 */
using Vector2Df = BasicVector2D<float>;
using Vector2Dd = BasicVector2D<double>;
using Vector2D  = BasicVector2D<double>;
using Vector2Dl = BasicVector2D<long double>;
///@}  {BasicVector2D Type Aliases}

}
