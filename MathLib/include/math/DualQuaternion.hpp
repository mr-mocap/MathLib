#pragma once

#include "math/Dual.hpp"
#include "math/Quaternion.hpp"
#include "math/Vector3D.hpp"
#include "math/Functions.hpp"
#include <cassert>
#include <concepts>

/** @file
 *  
 *  Defines a DualQuaternion and contains functions for manipulating them
 *
 *  @hideincludegraph
 */

namespace Math
{

/** The definition of a DualQuaternion
 *  
 *  Here, we just compose the ideas of the BasicDual and BasicQuaternion classes
 *  together to create a DualQuaternion class.
 * 
 *  @headerfile <> <math/DualQuaternion.hpp>
 * 
 *  @see BasicDual
 *  @see BasicQuaternion
 */
template <class T>
class BasicDualQuaternion
{
public:
    /** @name Types
     *  @{
     */
    using value_type = T; ///< The underlying implementation type
    /// @}

    /** @name Constructors
     *  @{
     */
    BasicDualQuaternion() = default;

    /** Constructs a DualQuaternion directly from the two given quaternions
     *
     *  @param rotation    The Quaternion to place into the real() part
     *  @param translation The Quaternion to place into the dual() part
     *  
     *  @note The user takes full responsibility for the input.  This could possibly be used
     *        to construct a non-unit DualQuaternion!
     */
    constexpr BasicDualQuaternion(const BasicQuaternion<T> &rotation,
                                  const BasicQuaternion<T> &translation)
        :
        _frame_of_reference{rotation, translation}
    {
    }

    /** Constructs a DualQuaternion from a unit Quaternion (rotation) and a translation
     *  
     *  @note This is the proper way to construct a unit DualQuaternion.
     */
    constexpr BasicDualQuaternion(const BasicQuaternion<T> &rotation,
                                                        T   translation_x,
                                                        T   translation_y,
                                                        T   translation_z)
        :
        _frame_of_reference{ rotation,
                             T{0.5} * BasicQuaternion<T>::encode_point(translation_x, translation_y, translation_z) * rotation }
    {
        assert( real().isUnit() );
    }
    constexpr BasicDualQuaternion(const BasicQuaternion<T> &rotation,
                                  const BasicVector3D<T>   &translation)
        :
        _frame_of_reference{ rotation,
                             T{0.5} * BasicQuaternion<T>::encode_point(translation) * rotation }
    {
        assert( real().isUnit() );
    }

    /** Constructs a DualQuaternion directly from a BasicDual<BasicQuaternion>
     *  
     *  @param underlying_representation The BasicDual number that will ultimately be used as the internal representation
     */
    explicit constexpr BasicDualQuaternion(const BasicDual<BasicQuaternion<T>> &underlying_representation)
        :
        _frame_of_reference(underlying_representation)
    {
    }
    /// @}

    /** @name Constants
     *  @{
     */

    /** Create a DualQuaternion representing no rotation and no translation
     *  
     *  @return A DualQuaternion representing no rotation or translation
     */
    constexpr static BasicDualQuaternion<T> identity()
    {
        return { BasicQuaternion<T>(1.0),
                 BasicQuaternion<T>::zero() };
    }

    /** Create a DualQuaternion that is all zeros
     */
    constexpr static BasicDualQuaternion<T> zero()
    {
        return { BasicQuaternion<T>::zero(), BasicQuaternion<T>::zero() };
    }
    /// @}

    /** @name Convenience Creation Functions
     *  @{
     */
    /** Creates a DualQuaternion containing a rotation only
     *  
     *  @param rotation The rotation to apply, expressed as a Quaternion
     *
     *  @return A DualQuaternion representing a rotation only
     *  
     *  @pre @p rotation is a unit Quaternion
     *  @post result.real == @p rotation.
     *        result.dual == BasicQuaternion::zero()
     */
    constexpr static BasicDualQuaternion<T> make_rotation(const BasicQuaternion<T> &rotation)
    {
        // A pure rotation has the dual part set to zero.
        return { rotation, BasicQuaternion<T>::zero() };
    }

    /** Create a DualQuaternion containing a translation only
     *  
     *  @param translation_x The X component of the translation vector
     *  @param translation_y The Y component of the translation vector
     *  @param translation_z The Z component of the translation vector
     *  
     *  @return A DualQuaternion representing a translation only
     *  
     *  @post result.real == BasicQuaternion::identity()
     *        result.dual.isPure()
     */
    constexpr static BasicDualQuaternion<T> make_translation(T translation_x, T translation_y, T translation_z)
    {
        // No need to make the translation "0.5 * t * r" because "r" is an identity Quaterion,
        // so we just use "0.5 * t".
        return { BasicQuaternion<T>::identity(),
                 T{0.5} * BasicQuaternion<T>::encode_point(translation_x, translation_y, translation_z)
               };
    }

    /** Create a DualQuaternion containing a translation only
     * 
     *  @param translation The translation to apply
     *  
     *  @return A DualQuaternion representing a translation only
     *  
     *  @post result.real == BasicQuaternion::identity()
     *        result.dual.isPure()
     */
    constexpr static BasicDualQuaternion<T> make_translation(const BasicVector3D<T> &translation)
    {
        // No need to make the translation "0.5 * t * r" because "r" is an identity Quaterion,
        // so we just use "0.5 * t".
        return BasicDualQuaternion<T>{ BasicQuaternion<T>::identity(),
                                  T{0.5} * BasicQuaternion<T>::encode_point(translation)
                                };
    }

    /** Encode both the @p rotation and translation together
     *
     *  @param rotation The rotation to inject
     *  @param translation_x The X component of the translation vector
     *  @param translation_y The Y component of the translation vector
     *  @param translation_z The Z component of the translation vector
     *  
     *  @return A DualQuaternion containing both the rotation and translation
     *  
     *  @pre @p rotation is a unit BasicQuaternion
     *  @post result.real == @p rotation.
     *        result.dual.isPure()
     */
    constexpr static BasicDualQuaternion<T> make_coordinate_system(const BasicQuaternion<T> &rotation,
                                                                                         T   translation_x,
                                                                                         T   translation_y,
                                                                                         T   translation_z)
    {
        assert( rotation.isUnit() );

        return BasicDualQuaternion<T>{ rotation, translation_x, translation_y, translation_z };
    }

    constexpr static BasicDualQuaternion<T> encode_point(const BasicVector3D<T> &point)
    {
        return BasicDualQuaternion<T>{ BasicQuaternion<T>::identity(), point };
    }
    /// @}

    constexpr static BasicVector3D<T> decode_point(const BasicDualQuaternion<T>& encoded_point)
    {
        return encoded_point.translation();
    }

    /** Create the conjugate of a DualQuaternion
     *  
     *  @return the conjugate of this object
     *  
     *  @note This is a bit different from the definition of a conjugate for
     *        a Dual, in that the conjugate of a Dual is just { real, dual.conjugate() },
     *        while for a DualQuaternion the operation needs to be
     *        { real.conjugate(), dual.conjugate() }.
     */
    constexpr BasicDualQuaternion<T> conjugate() const
    {
        return BasicDualQuaternion<T>{ real().conjugate(), dual().conjugate() };
    }

    /** Create the square of the norm of the input
     *  
     *  @return A Dual that is the square of the norm of this object
     *
     *  @note The @c norm is also known as the @c magnitude
     */
    constexpr BasicDual<T> normsquared() const
    {
        BasicDualQuaternion<T> normsquared{ *this * this->conjugate() };

        // We should have a dual scalar now
        // Make that assumption clear
        assert( approximately_equal_to(normsquared.real().i(), T{0.0}) );
        assert( approximately_equal_to(normsquared.real().j(), T{0.0}) );
        assert( approximately_equal_to(normsquared.real().k(), T{0.0}) );

#if 0
        assert( approximately_equal_to(normsquared.dual().i(), T{0}) );
        assert( approximately_equal_to(normsquared.dual().j(), T{0}) );
        assert( approximately_equal_to(normsquared.dual().k(), T{0}) );
#endif

        return BasicDual<T>{ normsquared.real().real(), normsquared.dual().real() };
    }

    /** Create the norm of a DualQuaternion
     *  
     *  @return A Dual that is the norm of the object
     *
     *  @note The @c norm is also known as the @c magnitude
     */
    constexpr BasicDual<T> norm() const
    {
        return dualscalar_sqrt( normsquared() );
    }

    /** Creates the magnitude of a DualQuaternion
     *  
     *  @return A Dual that is the magnitude of the object
     *  
     *  @see norm
     */
    constexpr BasicDual<T> magnitude() const { return norm(); }

    /** @name Element Access
     *  @{
     */
    const BasicQuaternion<T> &real() const { return _frame_of_reference.real; }
    const BasicQuaternion<T> &dual() const { return _frame_of_reference.dual; }
    /// @}

    const BasicQuaternion<T> &rotation()    const { return real(); }
          BasicVector3D<T>    translation() const
    {
        return BasicQuaternion<T>(T{2.0} * dual() * rotation().conjugate()).imaginary();
    }

    /** Create the normalized version of a DualQuaternion
     *  
     *  @return A DualQuaternion that is the normalized version of the object
     *
     *  @see norm
     */
    constexpr BasicDualQuaternion<T> normalized() const
    {
        return *this / norm();
    }

    /** Checks for a DualQuaternion's rotation component has a magnitude of one
     *  
     *  @return @c true of the magnitude of the rotation is 1, @c false otherwise
     *  
     *  @note This is part of the definition of a unit DualQuaternion
     */
    constexpr bool rotation_magnitude_is_one() const
    {
        return approximately_equal_to( dot(real(), real()), T{1.0} );
    }

    /** Checks if a DualQuaternion has orthogonal rotation and translation axes
     *  
     *  @return @c true if they are orthogonal, @c false otherwise
     *  
     *  @note This is part of the definition of a unit DualQuaternion
     */
    constexpr bool rotation_and_translation_are_orthogonal() const
    {
        return approximately_equal_to( dot(real(), dual()), T{0.0} );
    }

    /** Checks if a DualQuaternion is a "unit" representation
     *  
     *  @return @c true if it is in unit form, @c false otherwise
     */
    constexpr bool is_unit() const
    {
        return rotation_magnitude_is_one() && rotation_and_translation_are_orthogonal();
    }

    /** @name Invalid Value Check
     *  @{
     */
    bool isNaN() const { return _frame_of_reference.real.isNaN() || _frame_of_reference.dual.isNaN(); }
    bool isInf() const { return _frame_of_reference.real.isInf() || _frame_of_reference.dual.isInf(); }
    /// @}

private:
    BasicDual<BasicQuaternion<T>> _frame_of_reference{ BasicQuaternion<T>::identity(), BasicQuaternion<T>::zero() }; // The default value is an identity transformation

    /** @name Equality
     *  @{
     */
    /** Defines equality of two DualQuaternions
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     */
    friend constexpr bool operator ==(const BasicDualQuaternion<T> &left,
                                      const BasicDualQuaternion<T> &right)
    {
        return approximately_equal_to(left, right);
    }
    /// @}

    /** @addtogroup DualQuaternionAlgebra Dual Quaternion Algebra
     *  @{
     */

    /** @name Operators
     * 
     *  @relates BasicDualQuaternion
     * 
     *  @{
     */
    friend constexpr BasicDualQuaternion<T> operator +(const BasicDualQuaternion<T> &left_side,
                                                       const BasicDualQuaternion<T> &right_side)
    {
        return BasicDualQuaternion<T>{ left_side._frame_of_reference + right_side._frame_of_reference };
    }

    /** Defines scaling a DualQuaternion
     *
     *  @param dual_quaternion The BasicDualQuaternion to scale
     *  @param dual_scalar     The amount to scale by
     *  
     *  @return The scaled BasicDualQuaternion
     *  
     *  @see DualQuaternionAlgebra
     */
    friend constexpr BasicDualQuaternion<T> operator *(T scalar, const BasicDualQuaternion<T> &dual_quaternion)
    {
        return BasicDualQuaternion<T>{ scalar * dual_quaternion._frame_of_reference };
    }

    /** Defines scaling a DualQuaternion
     *
     *  @param dual_scalar     The amount to scale by
     *  @param dual_quaternion The DualQuaternion to scale
     *  
     *  @return The scaled DualQuaternion
     *  
     *  @see DualQuaternionAlgebra
     */
    friend constexpr BasicDualQuaternion<T> operator *(const BasicDualQuaternion<T> &dual_quaternion, T scalar)
    {
        return BasicDualQuaternion<T>{ dual_quaternion._frame_of_reference * scalar };
    }

    /** Defines multiplication of a BasicDualQuaternion by a BasicDual
     *
     *  @param dual_quaternion The BasicDualQuaternion to scale
     *  @param dual_scalar     The amount to scale by
     *  
     *  @return The scaled BasicDualQuaternion
     *  
     *  @see BasicDualQuaternion Algebra
     */
    friend constexpr BasicDualQuaternion<T> operator *(const BasicDualQuaternion<T> &dual_quaternion,
                                                       const BasicDual<T>           &dual_scalar)
    {
        return dual_quaternion * BasicDualQuaternion<T>( BasicQuaternion<T>(dual_scalar.real),
                                                         BasicQuaternion<T>(dual_scalar.dual) );
    }

    /** Defines multiplication of two DualQuaternions
     *
     *  @return The resulting BasicDualQuaternion
     *  
     *  @see BasicDualQuaternion Algebra
     */
    friend constexpr BasicDualQuaternion<T> operator *(const BasicDualQuaternion<T> &left_side,
                                                       const BasicDualQuaternion<T> &right_side)
    {
        return BasicDualQuaternion<T>( left_side._frame_of_reference * right_side._frame_of_reference );
    }

    /** Defines division of a DualQuaternion by a Dual
     *
     *  @param dual_quaternion The DualQuaternion to scale
     *  @param dual_scalar     The amount to scale by
     *  
     *  @return The scaled DualQuaternion
     *  
     *  @see BasicDualQuaternion Algebra
     */
    friend constexpr BasicDualQuaternion<T> operator /(const BasicDualQuaternion<T> &dual_quaternion,
                                                       const BasicDual<T>           &dual_scalar)
    {
        return BasicDualQuaternion<T>( BasicDualQuaternion<T>(dual_quaternion *
                                                              dual_scalar.conjugate())._frame_of_reference /
                                       dualscalar_normsquared(dual_scalar) );
    }
    /// @}  {DualQuaternionAlgebra}
    /// @}  {Operators}

    /** @addtogroup Equality
     * 
     *  @relates BasicDualQuaternion
     * 
     *  @{
     * 
     *  Compares two BasicDualQuaternion inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     *  
     *  @see Equality
     */
    //template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicDualQuaternion<T> &value_to_test,
                                                 const BasicDualQuaternion<T> &value_it_should_be,
                                                                           T  tolerance = T{0.0002})
    {
        // Just use the underlying BasicDual number's version of the same function...
        return approximately_equal_to( value_to_test._frame_of_reference, value_it_should_be._frame_of_reference, tolerance );
    }
    /// @}  {Equality}

    /** Creates the normalized form of a BasicDualQuaternion
     *  
     *  @param input The BasicDualQuaternion to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr BasicDualQuaternion<T> normalized(const BasicDualQuaternion<T> &input)
    {
        return input.normalized();
    }

    /** Generates a linear blend between two BasicDualQuaternion objects
     *  
     *  @param beginning  The start state
     *  @param end        The ending state
     *  @param percentage The percentage blend between the two (typically [0..1])
     */
    template <std::floating_point OT = float>
    friend constexpr BasicDualQuaternion<T> blend(const BasicDualQuaternion<T> &beginning,
                                                  const BasicDualQuaternion<T> &end,
                                                        OT                      percentage)
    {
        auto blended = beginning + (end - beginning) * percentage;

        return blended.normalized();
    }

    friend std::string format(const BasicDualQuaternion<T> &input)
    {
        return std::format("[real: {}, dual: {}]", input.real(), input.dual());
    }

    /**  Computes the conjugate of the input
     * 
     *   @note This will just call @c input.conjugate()
     */
    friend constexpr BasicDualQuaternion<T> conjugate(const BasicDualQuaternion<T> &input)
    {
        return input.conjugate();
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
    friend bool check_if_equal(const BasicDualQuaternion<T> &input,
                               const BasicDualQuaternion<T> &near_to,
                                     OT                      tolerance = OT{0.0002})
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
    friend bool check_if_not_equal(const BasicDualQuaternion<T> &input,
                                   const BasicDualQuaternion<T> &near_to,
                                         OT                      tolerance = OT{0.0002})
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
    friend void CHECK_IF_EQUAL(const BasicDualQuaternion<T> &input,
                               const BasicDualQuaternion<T> &near_to,
                                     OT                      tolerance = OT{0.0002})
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
    friend void CHECK_IF_NOT_EQUAL(const BasicDualQuaternion<T> &input,
                                   const BasicDualQuaternion<T> &near_to,
                                         OT                      tolerance = OT{0.0002})
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
    friend void CHECK_IF_ZERO(const BasicDualQuaternion<T> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicDualQuaternion<T>::zero(), tolerance));
    }
};


/** @defgroup DualQuaternionAliases DualQuaternion Types
 * 
 *  Here are the type aliases for DualQuaternions
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicDualQuaternion
 *  @{
 */
using DualQuaternionf = BasicDualQuaternion<float>;
using DualQuaterniond = BasicDualQuaternion<double>;
using DualQuaternion  = BasicDualQuaternion<double>;
using DualQuaternionl = BasicDualQuaternion<long double>;
/// @}
/// @}  {DualQuaternionAliases}

}