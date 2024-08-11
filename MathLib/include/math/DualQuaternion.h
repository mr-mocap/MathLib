#pragma once

#include "math/Dual.h"
#include "math/Quaternion.h"
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
using DualQuaternion = Dual<Quaternion<T>>;


///@{
/** Creates a DualQuaternion containing a rotation only
 *  
 *  @param radians The amount of rotation
 *  @param axis_x  The X axis component of the rotation axis
 *  @param axis_y  The Y axis component of the rotation axis
 *  @param axis_z  The Z axis component of the rotation axis
 *
 *  @return A DualQuaternion representing a rotation only
 */
template <class T>
constexpr DualQuaternion<T> make_dualquaternion_rotation(T radians, T axis_x, T axis_y, T axis_z)
{
    // A pure rotation has the dual part set to zero.
    return DualQuaternion<T>{ make_quaternion_rotation(radians, axis_x, axis_y, axis_z), Quaternion<T>::zero() };
}

/** Creates a DualQuaternion containing a rotation only
 *  
 *  @param rotation The rotation to apply, expressed as a Quaternion
 *
 *  @return A DualQuaternion representing a rotation only
 */
template <class T>
constexpr DualQuaternion<T> make_dualquaternion_rotation(const Quaternion<T> &rotation)
{
    // A pure rotation has the dual part set to zero.
    return DualQuaternion<T>{ rotation, Quaternion<T>::zero() };
}
///@}

/** Create a DualQuaternion containing a translation only
 *  
 *  @param translation_x The X component of the translation vector
 *  @param translation_y The Y component of the translation vector
 *  @param translation_z The Z component of the translation vector
 *  
 *  @return A DualQuaternion representing a translation only
 */
template <class T>
constexpr DualQuaternion<T> make_dualquaternion_translation(T translation_x, T translation_y, T translation_z)
{
    // A pure translation has the real part set to identity.

    return DualQuaternion<T>{ Quaternion<T>::unit(),
                              make_pure_quaternion( translation_x / T(2),
                                                    translation_y / T(2),
                                                    translation_z / T(2) )
                            };
}

/** Create a DualQuaternion representing no rotation and no translation
 *  
 *  @return A DualQuaternion representing no rotation or translation
 */
template <class T>
constexpr DualQuaternion<T> make_unit_dualquaternion()
{
    return DualQuaternion<T>{ Quaternion<T>::unit(), Quaternion<T>::zero() };
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
template <class T>
constexpr DualQuaternion<T> make_coordinate_system(const Quaternion<T> &rotation, T translation_x, T translation_y, T translation_z)
{
    assert( rotation.isUnit() );

    return DualQuaternion<T>{ rotation, make_pure_quaternion(translation_x, translation_y, translation_z) / T(2) * rotation };
}

/** Create the conjugate of a DualQuaternion
 *  
 *  @param q The input DualQuaternion
 *  
 *  @return the conjugate of @p q
 */
template <class T>
constexpr DualQuaternion<T> dualquaternion_conjugate(DualQuaternion<T> q)
{
    return DualQuaternion<T>{ conjugate(q.real), conjugate(q.dual) };
}

/** Create the square of the norm of the input
 *  
 *  @param d The DualQuaternion to find the squared norm of
 *  
 *  @return A Dual that is the square of the norm of the input
 *
 *  @note The @c norm is also known as the @c magnitude
 */
template <class T>
constexpr Dual<T> dualquaternion_normsquared(DualQuaternion<T> d)
{
    DualQuaternion<T> normsquared = d * dualquaternion_conjugate(d);

    // We should have a dual scalar now
    // Make that assumption clear
    assert( approximately_equal_to(normsquared.real.i(), 0) );
    assert( approximately_equal_to(normsquared.real.j(), 0) );
    assert( approximately_equal_to(normsquared.real.k(), 0) );

    assert( approximately_equal_to(normsquared.dual.i(), 0) );
    assert( approximately_equal_to(normsquared.dual.j(), 0) );
    assert( approximately_equal_to(normsquared.dual.k(), 0) );

    return Dual<T>{ normsquared.real.real(), normsquared.dual.real() };
}

/** Defines multiplication of a DualQuaternion by a Dual
 *
 *  @param dual_quaternion The DualQuaternion to scale
 *  @param dual_scalar     The amount to scale by
 *  
 *  @return The scaled DualQuaternion
 */
template <class T>
constexpr DualQuaternion<T> operator *(DualQuaternion<T> dual_quaternion, Dual<T> dual_scalar)
{
    return dual_quaternion * DualQuaternion<T>{ Quaternion<T>{dual_scalar.real, 0, 0, 0}, Quaternion<T>{dual_scalar.dual, 0, 0, 0} };
}

/** Defines division of a DualQuaternion by a Dual
 *
 *  @param dual_quaternion The DualQuaternion to scale
 *  @param dual_scalar     The amount to scale by
 *  
 *  @return The scaled DualQuaternion
 */
template <class T>
constexpr DualQuaternion<T> operator /(DualQuaternion<T> dual_quaternion, Dual<T> dual_scalar)
{
    return DualQuaternion<T>{ (dual_quaternion * conjugate(dual_scalar)) / dualscalar_normsquared(dual_scalar) };
}

/** Create the norm of a DualQuaternion
 *  
 *  @param d The DualQuaternion to find the norm of
 *  
 *  @return A Dual that is the norm of the input
 *
 *  @note The @c norm is also known as the @c magnitude
 */
template <class T>
constexpr Dual<T> dualquaternion_norm(DualQuaternion<T> d)
{
    return dualscalar_sqrt( dualquaternion_normsquared(d) );
}

/** Create the magnitude of a DualQuaternion
 *  
 *  @param d The DualQuaternion to find the magnitude of
 *  
 *  @return A Dual that is the magnitude of the input
 *
 *  @see dualquaternion_norm
 */
template <class T>
constexpr Dual<T> dualquaternion_magnitude(DualQuaternion<T> d)
{
    return dualquaternion_norm(d);
}

/** Create the normalized version of a DualQuaternion
 *  
 *  @param d The input DualQuaternion
 *  
 *  @return A DualQuaternion that is the normalized version of the input
 *
 *  @see dualquaternion_norm
 */
template <class T>
constexpr DualQuaternion<T> normalized(DualQuaternion<T> d)
{
    return d / dualquaternion_norm(d);
}

/** Checks for a DualQuaternion's rotation component has a magnitude of one
 *  
 *  @param d The input
 *  
 *  @return @c true of the magnitude of the rotation is 1, @c false otherwise
 */
template <class T>
constexpr bool unit_dualquaternion_rotation_magnitude_is_one(DualQuaternion<T> d)
{
    return approximately_equal_to( dot(d.real, d.real), 1 );
}

/** Checks if a DualQuaternion has orthogonal rotation and translation axes
 *  
 *  @param d The input
 *  
 *  @return @c true if they are orthogonal, @c false otherwise
 */
template <class T>
constexpr bool unit_dualquaternion_rotation_and_translation_are_orthogonal(DualQuaternion<T> d)
{
    return approximately_equal_to( dot(d.real, d.dual), 0);
}

/** Checks if a DualQuaternion is a "unit" representation
 *  
 *  @param d The input
 *  
 *  @return @c true if it is in unit form, @c false otherwise
 */
template <class T>
constexpr bool is_unit(DualQuaternion<T> d)
{
    return unit_dualquaternion_rotation_magnitude_is_one(d) && unit_dualquaternion_rotation_and_translation_are_orthogonal(d);
}

/** Generates a linear blend between two DualQuaternion objects
 *  
 *  @param beginning  The start state
 *  @param end        The ending state
 *  @param percentage The percentage blend between the two (typically [0..1])
 */
template <class T>
constexpr DualQuaternion<T> blend(DualQuaternion<T> beginning, DualQuaternion<T> end, float percentage)
{
    auto blended =  beginning + (end - beginning) * percentage;

    return normalized(blended);
}

/// @{
using DualQuaternionf = DualQuaternion<float>;
using DualQuaterniond = DualQuaternion<double>;
using DualQuaternionld = DualQuaternion<long double>;
/// @}
