#pragma once

#include "math/Dual.hpp"
#include "math/Quaternion.hpp"
#include "math/Conjugate.hpp"
#include "math/Vector.hpp"
#include <cassert>

/** @file
 *  
 *  Defines a DualQuaternion and contains functions for manipulating them.
 */


/** The definition of a DualQuaternion
 *  
 *  Here, we just compose the ideas of the Dual and Quaternion classes
 *  together to create a DualQuaternion class.
 *
 *  @see Dual
 *  @see Quaternion
 */
template <class T>
class DualQuaternion
{
public:
    DualQuaternion() = default;

    /** Constructs a DualQuaternion directly from the two given quaternions
     *
     *  @param rotation    The Quaternion to place into the real() part
     *  @param translation The Quaternion to place into the dual() part
     */
    explicit constexpr DualQuaternion(const Quaternion<T> &rotation, const Quaternion<T> &translation) : _frame_of_reference{rotation, translation} { }
    explicit constexpr DualQuaternion(const Quaternion<T> &rotation,
                                      const T translation_x,
                                      const T translation_y,
                                      const T translation_z)
        :
        _frame_of_reference{ rotation, T{0.5} * Quaternion<T>::encode_point(translation_x, translation_y, translation_z) * rotation }
    {
        assert( real().isUnit() );
    }

    /** Constructs a DualQuaternion directly from a Dual<Quaternion>
     *  
     *  @param underlying_representation The Dual number that will ultimately be used as the internal representation
     */
    explicit constexpr DualQuaternion(const Dual<Quaternion<T>> &underlying_representation) : _frame_of_reference(underlying_representation) { }

    /** Create a DualQuaternion representing no rotation and no translation
     *  
     *  @return A DualQuaternion representing no rotation or translation
     */
    constexpr static DualQuaternion<T> identity() { return DualQuaternion{}; }

    /** Create a DualQuaternion that is all zeros
     */
    constexpr static DualQuaternion<T> zero() { return DualQuaternion{ Quaternion<T>::zero(), Quaternion<T>::zero() }; }

    /** Creates a DualQuaternion containing a rotation only
     *  
     *  @param rotation The rotation to apply, expressed as a Quaternion
     *
     *  @return A DualQuaternion representing a rotation only
     *  
     *  @pre @p rotation is a unit Quaternion
     *  @post result.real == @p rotation.
     *        result.dual == Quaternion::zero()
     */
    constexpr static DualQuaternion<T> make_rotation(const Quaternion<T> &rotation)
    {
        // A pure rotation has the dual part set to zero.
        return DualQuaternion<T>{ rotation, Quaternion<T>::zero() };
    }

    /** Create a DualQuaternion containing a translation only
     *  
     *  @param translation_x The X component of the translation vector
     *  @param translation_y The Y component of the translation vector
     *  @param translation_z The Z component of the translation vector
     *  
     *  @return A DualQuaternion representing a translation only
     *  
     *  @post result.real == Quaternion::identity()
     *        result.dual.isPure()
     */
    constexpr static DualQuaternion<T> make_translation(T translation_x, T translation_y, T translation_z)
    {
        // No need to make the translation "0.5 * t * r" because "r" is an identity Quaterion,
        // so we just use "0.5 * t".
        return DualQuaternion<T>{ Quaternion<T>::identity(),
                                  T{0.5} * Quaternion<T>::encode_point(translation_x, translation_y, translation_z)
                                };
    }

    constexpr static DualQuaternion<T> make_translation(const Vector3D<T> &translation)
    {
        // No need to make the translation "0.5 * t * r" because "r" is an identity Quaterion,
        // so we just use "0.5 * t".
        return DualQuaternion<T>{ Quaternion<T>::identity(),
                                  T{0.5} * Quaternion<T>::encode_point(translation)
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
     *  @pre @p rotation is a unit Quaternion
     *  @post result.real == @p rotation.
     *        result.dual.isPure()
     */
    constexpr static DualQuaternion<T> make_coordinate_system(const Quaternion<T> &rotation, T translation_x, T translation_y, T translation_z)
    {
        assert( rotation.isUnit() );

        return DualQuaternion<T>{ rotation, translation_x, translation_y, translation_z };
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
    constexpr DualQuaternion<T> conjugate() const
    {
        return DualQuaternion<T>{ real().conjugate(), dual().conjugate() };
    }

    /** Create the square of the norm of the input
     *  
     *  @return A Dual that is the square of the norm of this object
     *
     *  @note The @c norm is also known as the @c magnitude
     */
    constexpr Dual<T> normsquared() const
    {
        DualQuaternion<T> normsquared = *this * this->conjugate();

        // We should have a dual scalar now
        // Make that assumption clear
        assert( approximately_equal_to(normsquared.real().i(), 0) );
        assert( approximately_equal_to(normsquared.real().j(), 0) );
        assert( approximately_equal_to(normsquared.real().k(), 0) );

        assert( approximately_equal_to(normsquared.dual().i(), 0) );
        assert( approximately_equal_to(normsquared.dual().j(), 0) );
        assert( approximately_equal_to(normsquared.dual().k(), 0) );

        return Dual<T>{ normsquared.real().real(), normsquared.dual().real() };
    }

    /** Create the norm of a DualQuaternion
     *  
     *  @return A Dual that is the norm of the object
     *
     *  @note The @c norm is also known as the @c magnitude
     */
    constexpr Dual<T> norm() const
    {
        return dualscalar_sqrt( normsquared() );
    }

    /** Creates the magnitude of a DualQuaternion
     *  
     *  @return A Dual that is the magnitude of the object
     *  
     *  @see norm
     */
    constexpr Dual<T> magnitude() const { return norm(); }

    const Quaternion<T> &real() const { return _frame_of_reference.real; }
    const Quaternion<T> &dual() const { return _frame_of_reference.dual; }

    const Quaternion<T> &rotation()    const { return real(); }
          Vector3D<T>    translation() const { return Quaternion<T>{T{2} * dual() * rotation().conjugate()}.imaginary(); }

    template <class T>
    friend constexpr DualQuaternion<T> operator +(const DualQuaternion<T> &left, const DualQuaternion<T> &right);

    template <class T>
    friend constexpr DualQuaternion<T> operator *(const DualQuaternion<T> &left, const DualQuaternion<T> &right);

    template <class T>
    friend constexpr DualQuaternion<T> operator *(const T scalar, const DualQuaternion<T> &dual_quaternion);

    template <class T>
    friend constexpr DualQuaternion<T> operator /(const DualQuaternion<T> &dual_quaternion, const Dual<T> &dual_scalar);

    /** Create the normalized version of a DualQuaternion
     *  
     *  @return A DualQuaternion that is the normalized version of the object
     *
     *  @see norm
     */
    constexpr DualQuaternion<T> normalized() const
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
        return approximately_equal_to( dot(real(), real()), T{1} );
    }

    /** Checks if a DualQuaternion has orthogonal rotation and translation axes
     *  
     *  @return @c true if they are orthogonal, @c false otherwise
     *  
     *  @note This is part of the definition of a unit DualQuaternion
     */
    constexpr bool rotation_and_translation_are_orthogonal() const
    {
        return approximately_equal_to( dot(real(), dual()), T{0} );
    }

    /** Checks if a DualQuaternion is a "unit" representation
     *  
     *  @return @c true if it is in unit form, @c false otherwise
     */
    constexpr bool is_unit() const
    {
        return rotation_magnitude_is_one() && rotation_and_translation_are_orthogonal();
    }

    template<class T>
    friend constexpr bool approximately_equal_to(const DualQuaternion<T> &value_to_test, const DualQuaternion<T> &value_it_should_be, float tolerance);

protected:
    Dual<Quaternion<T>> _frame_of_reference{ Quaternion<T>::identity(), Quaternion<T>::zero() }; // The default value is an identity transformation
};

/** Compares two DualQuaternion inputs equal, component-wise, to within a tolerance
 *  
 *  @param value_to_test
 *  @param value_it_should_be 
 *  @param tolerance          How close they should be to be considered equal
 *  
 *  @return @c true if they are equal
 *  
 *  @see approximately_equal_to
 */
template<class T>
constexpr bool approximately_equal_to(const DualQuaternion<T> &value_to_test, const DualQuaternion<T> &value_it_should_be, float tolerance = 0.0002f)
{
    // Just use the underlying Dual number's version of the same function...
    return approximately_equal_to( value_to_test._frame_of_reference, value_it_should_be._frame_of_reference, tolerance );
}

/** Defines equality of two DualQuaternions
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see approximately_equal_to
 */
template<class T>
constexpr bool operator ==(const DualQuaternion<T> &left, const DualQuaternion<T> &right)
{
    return approximately_equal_to(left, right);
}

/** Defines inequality of two DualQuaternions
 *  
 *  @note Uses operator ==()
 *  
 *  @see approximately_equal_to
 */
template<class T>
constexpr bool operator !=(const Dual<T> &left, const Dual<T> &right)
{
    return !(left == right);
}

/** Defines addition
 *  
 *  We basically just add the underlying Dual numbers
 */
template <class T>
constexpr DualQuaternion<T> operator +(const DualQuaternion<T> &left_side, const DualQuaternion<T> &right_side)
{
    return DualQuaternion<T>{ left_side._frame_of_reference + right_side._frame_of_reference };
}

/** Defines scaling a DualQuaternion
 *
 *  @param dual_quaternion The DualQuaternion to scale
 *  @param dual_scalar     The amount to scale by
 *  
 *  @return The scaled DualQuaternion
 */
template <class T>
constexpr DualQuaternion<T> operator *(const T scalar, const DualQuaternion<T> &dual_quaternion)
{
    return DualQuaternion<T>{ scalar * dual_quaternion._frame_of_reference };
}

/** Defines scaling a DualQuaternion
 *
 *  @param dual_scalar     The amount to scale by
 *  @param dual_quaternion The DualQuaternion to scale
 *  
 *  @return The scaled DualQuaternion
 */
template <class T>
constexpr DualQuaternion<T> operator *(const DualQuaternion<T> &dual_quaternion, const T scalar)
{
    return DualQuaternion<T>{ dual_quaternion._frame_of_reference * scalar };
}

/** Defines multiplication of a DualQuaternion by a Dual
 *
 *  @param dual_quaternion The DualQuaternion to scale
 *  @param dual_scalar     The amount to scale by
 *  
 *  @return The scaled DualQuaternion
 */
template <class T>
constexpr DualQuaternion<T> operator *(const DualQuaternion<T> &dual_quaternion, const Dual<T> &dual_scalar)
{
    return dual_quaternion * DualQuaternion<T>{ Quaternion<T>{dual_scalar.real}, Quaternion<T>{dual_scalar.dual} };
}

/** Defines multiplication of two DualQuaternions
 *
 *  @return The resulting DualQuaternion
 */
template <class T>
constexpr DualQuaternion<T> operator *(const DualQuaternion<T> &left_side, const DualQuaternion<T> &right_side)
{
    return DualQuaternion<T>{ left_side._frame_of_reference * right_side._frame_of_reference };
}

/** Defines division of a DualQuaternion by a Dual
 *
 *  @param dual_scalar The amount to scale by
 *  
 *  @return The scaled DualQuaternion
 */
template <class T>
constexpr DualQuaternion<T> operator /(const DualQuaternion<T> &dual_quaternion, const Dual<T> &dual_scalar)
{
    return DualQuaternion<T>{ (dual_quaternion * dual_scalar.conjugate())._frame_of_reference / dualscalar_normsquared(dual_scalar) };
}

/** Generates a linear blend between two DualQuaternion objects
 *  
 *  @param beginning  The start state
 *  @param end        The ending state
 *  @param percentage The percentage blend between the two (typically [0..1])
 */
template <class T>
constexpr DualQuaternion<T> blend(const DualQuaternion<T> &beginning, const DualQuaternion<T> &end, float percentage)
{
    auto blended =  beginning + (end - beginning) * percentage;

    return normalized(blended);
}


/// @{
using DualQuaternionf = DualQuaternion<float>;
using DualQuaterniond = DualQuaternion<double>;
using DualQuaternionld = DualQuaternion<long double>;
/// @}
