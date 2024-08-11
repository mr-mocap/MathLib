#pragma once

#include "math/ApproximatelyEqualTo.h"
#include "math/Conjugate.h"
#include "math/types.h"
#include <cassert>

/** @file
 *  
 *  Contains the definition of the Quaternion class along with
 *  various helper functions.
 */

/** A mathematical quaternion
 *  
 *  @note A quaternion is a 4-dimensional object that is an extension
 *        of the complex number system.
 *        Its main use is for encoding rotation in 3-dimensional space.
 */
template <class T>
class Quaternion
{
public:
    using value_type = T;

    Quaternion() = default;
    explicit constexpr Quaternion(value_type real_number) : _w(real_number) { }
    explicit constexpr Quaternion(value_type w, value_type i, value_type j, value_type k) : _w(w), _i(i), _j(j), _k(k) { }

    // Quaternion representation of the real number 1
    constexpr static Quaternion<T> unit() { return Quaternion{ T{1}, T{}, T{}, T{} }; }

    // Quaternion representation of the real number 0
    constexpr static Quaternion<T> zero() { return Quaternion{}; }
    constexpr static Quaternion<T> unit_real() { return unit(); }
    constexpr static Quaternion<T> unit_i() { return Quaternion{ T{}, T{1}, T{},  T{} }; }
    constexpr static Quaternion<T> unit_j() { return Quaternion{ T{}, T{},  T{1}, T{} }; }
    constexpr static Quaternion<T> unit_k() { return Quaternion{ T{}, T{},  T{},  T{1} }; }

    Quaternion<T> conjugate() const { return Quaternion<T>{ _w, -_i, -_j, -_k }; }

    value_type    normSquared() const { return accumulate(*this * conjugate()); }
    value_type    norm() const { return std::sqrt( normSquared() ); }

    value_type    magnitudeSquared() const { return normSquared(); }
    value_type    magnitude() const { return norm(); }

    Quaternion<T> inverse() const { return conjugate() / normSquared(); }

    const value_type w() const { return _w; }
    const value_type real() const { return _w; }

    const value_type i() const { return _i; }
    const value_type j() const { return _j; }
    const value_type k() const { return _k; }

    // Extracts the imaginary part of a Quaternion as a 3-tuple
    constexpr triple<value_type> imaginary() { return { _i, _j, _k }; }

    bool isUnit() const { return approximately_equal_to( magnitude(), T{1} ); }
    bool isUnit(value_type tolerance) const { return approximately_equal_to( magnitude(), T{1}, tolerance ); }

    bool isZero() const { return approximately_equal_to( magnitude(), T{0} ); }
    bool isZero(value_type tolerance) const { return approximately_equal_to( magnitude(), T{0}, tolerance ); }

    // Checks if the real() part is 0
    bool isPure() const { return approximately_equal_to(real(), T{0}); }
protected:
    value_type _w{};
    value_type _i{};
    value_type _j{};
    value_type _k{};
};

/** Compares two Quaternion inputs equal, component-wise, to within a tolerance
 *  
 *  @param value_to_test
 *  @param value_it_should_be 
 *  @param tolerance          How close they should be to be considered equal
 *  
 *  @return @c true if they are equal
 *  
 *  @see approximately_equal_to
 */
template <class T>
constexpr bool approximately_equal_to(Quaternion<T> value_to_test, Quaternion<T> value_it_should_be, float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.w(), value_it_should_be.w(), tolerance) &&
           approximately_equal_to(value_to_test.i(), value_it_should_be.i(), tolerance) &&
           approximately_equal_to(value_to_test.j(), value_it_should_be.j(), tolerance) &&
           approximately_equal_to(value_to_test.k(), value_it_should_be.k(), tolerance);
}

/** Defines multiplication of a Quaternion and a scalar
 *  
 */
template <class T>
constexpr Quaternion<T> operator *(Quaternion<T> quaternion, T scalar)
{
    return Quaternion<T>{ quaternion.w() * scalar, quaternion.i() * scalar, quaternion.j() * scalar, quaternion.k() * scalar };
}

/** Defines multiplication of a scalar and a Quaternion
 *  
 */
template <class T>
constexpr Quaternion<T> operator *(T scalar, Quaternion<T> quaternion)
{
    return Quaternion<T>{ scalar * quaternion.w(), scalar * quaternion.i(), scalar * quaternion.j(), scalar * quaternion.k()};
}

/** Defines division of a Quaternion by a scalar
 *  
 *  @return the new Quaternion
 */
template <class T>
constexpr Quaternion<T> operator /(Quaternion<T> quaternion, T scalar)
{
    return Quaternion<T>{ quaternion.w() / scalar, quaternion.i() / scalar, quaternion.j() / scalar, quaternion.k() / scalar };
}

/** Defines division of a scalar by a Quaternion
 *  
 *  @return the new Quaternion
 */
template <class T>
constexpr Quaternion<T> operator /(T scalar, Quaternion<T> quaternion)
{
    return Quaternion<T>{ scalar / quaternion.w(), scalar / quaternion.i(), scalar / quaternion.j(), scalar / quaternion.kapproximately_equal_to under-the-hood() };
}

/** Defines division of a Quaternion by a Quaternion
 *  
 *  @return the new Quaternion
 */
template <class T>
constexpr Quaternion<T> operator /(Quaternion<T> left, Quaternion<T> right)
{
    return left * right.inverse();
}

/** Defines addition of a Quaternion and a Quaternion
 *  
 *  @return the new Quaternion
 */
template <class T>
constexpr Quaternion<T> operator +(Quaternion<T> left, Quaternion<T> right)
{
    return Quaternion<T>{left.w() + right.w(),
                         left.i() + right.i(),
                         left.j() + right.j(),
                         left.k() + right.k()};
}

/** Defines subtraction of a Quaternion and a Quaternion
 *  
 *  @return the new Quaternion
 */
template <class T>
constexpr Quaternion<T> operator -(Quaternion<T> left, Quaternion<T> right)
{
    return Quaternion<T>{left.w() - right.w(),
                         left.i() - right.i(),
                         left.j() - right.j(),
                         left.k() - right.k()};
}

/** Defines multiplication of a Quaternion and a Quaternion
 *  
 *  @return the new Quaternion
 */
template <class T>
constexpr Quaternion<T> operator *(Quaternion<T> left, Quaternion<T> right)
{
    return Quaternion<T>{left.w() * right.w() - (left.i() * right.i() +
                                                 left.j() * right.j() +
                                                 left.k() * right.k()),
                         left.w() * right.i() +
                         left.i() * right.w() +
                         left.j() * right.k() -
                         left.k() * right.j(),
                         
                         left.w() * right.j() -
                         left.i() * right.k() +
                         left.j() * right.w() +
                         left.k() * right.i(),
                         
                         left.w() * right.k() +
                         left.i() * right.j() -
                         left.j() * right.i() +
                         left.k() * right.w()
    };
}

/** Defines equality of two Quaternions
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see approximately_equal_to
 */
template <class T>
constexpr bool operator ==(Quaternion<T> left, Quaternion<T> right)
{
    return approximately_equal_to(left, right);
}

/** Defines inequality of two Quaternions
 *  
 *  @note Uses operator ==()
 *  
 *  @see approximately_equal_to
 */
template <class T>
constexpr bool operator !=(Quaternion<T> left, Quaternion<T> right)
{
    return !(left == right);
}

/** Defines negation of a Quaternion
 *  
 *  Performs a component-wise negation of the input
 */
template <class T>
constexpr Quaternion<T> operator -(Quaternion<T> q)
{
    return Quaternion<T>{ -q.w(), -q.i(), -q.j(), -q.k() };
}

/** Calculates the dot product of two Quaternions
 *  
 *  @note In this case, the Quaternions are just treated as
 *        separate 4-tuples and the dot product of those are
 *        calculated.
 */
template <class T>
constexpr T dot(Quaternion<T> left, Quaternion<T> right)
{
    return left.w() * right.w() +
           left.i() * right.i() +
           left.j() * right.j() +
           left.k() * right.k();
}

/** Construct a pure Quaternion
 *  
 *  @post output.w() == 0
 *        output.real() == 0

 *  @note A pure Quaternion is one in which the w, or real, component
 *        is 0.
 */
template <class T>
constexpr Quaternion<T> make_pure_quaternion(T x, T y, T z)
{
    return Quaternion<T>{ T(), x, y, z };
}

/** Construct a pure Quaternion
 *  
 *  @post output.w() == 0
 *        output.real() == 0

 *  @note A pure Quaternion is one in which the w, or real, component
 *        is 0.
 */
template <class T>
constexpr Quaternion<T> make_pure_quaternion(const triple<T> &t)
{
    return Quaternion<T>{ T(), std::get<0>(t), std::get<1>(t), std::get<2>(t) };
}

/** Encode a 3D point as a pure Quaternion
 *  
 *  @post output.w() == 0
 *        output.real() == 0

 *  @note A pure Quaternion is one in which the w, or real, component
 *        is 0.
 *  
 *  @see make_pure_quaternion
 */
template <class T>
constexpr Quaternion<T> encode_point_as_quaternion(T x, T y, T z)
{
    return make_pure_quaternion(x, y, z);
}

/** Enocde a rotation into a Quaternion
 *  
 *  @param radians The amount of rotation to apply (in radians)
 *  @param axis_x  The X component of the vector to rotate around
 *  @param axis_y  The Y component of the vector to rotate around
 *  @param axis_z  The Z component of the vector to rotate around
 *  
 *  @post output.isUnit() == true
 */
template <class T>
constexpr Quaternion<T> make_quaternion_rotation(T radians, T axis_x, T axis_y, T axis_z)
{
    T cos_theta = cos(radians / T{2});
    T sin_theta = sin(radians / T{2});

    return normalized( Quaternion<T>{ cos_theta,
                                      sin_theta * axis_x,
                                      sin_theta * axis_y,
                                      sin_theta * axis_z }
                     );
}

/** Enocde a rotation into a Quaternion
 *  
 *  @param radians The amount of rotation to apply (in radians)
 *  @param axis    The axis to rotate around
 *  
 *  @post output.isUnit() == true
 */
template <class T>
constexpr Quaternion<T> make_quaternion_rotation(T radians, triple<T> axis)
{
    T cos_theta = cos(radians / T{2});
    T sin_theta = sin(radians / T{2});

    return normalized( Quaternion<T>{ cos_theta,
                                      sin_theta * std::get<0>(axis),
                                      sin_theta * std::get<1>(axis),
                                      sin_theta * std::get<2>(axis) }
                     );
}

/** Rotates the encoded point using the given rotation
 *  
 *  @param rotation      The input rotation
 *  @param encoded_point The input point to be rotated
 *  
 *  @return The passively rotated encoded point
 *  
 *  @pre  @p rotation is a unit Quaternion.
 *        @p encoded_point is a pure Auaternion.
 *  @post The output is a pure Quaternion
 *  
 *  @note This is a passive rotation, meaning that the coordinate system is
 *        rotated with respect to the point.
 *        This is also known as a local rotation.
 */
template <class T>
constexpr Quaternion<T> passively_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
{
    assert( rotation.isUnit() );
    assert( encoded_point.isPure() );

    return rotation * encoded_point * rotation.conjugate();
}

/**
 *  
 *  @see passively_rotate_encoded_point
 */
template <class T>
constexpr Quaternion<T> locally_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
{
    return passively_rotate_encoded_point(rotation, encoded_point);
}

/** Rotates the @p encoded_point using the given @p rotation
 *  
 *  @param rotation      The input rotation
 *  @param encoded_point The input point to be rotated
 *  
 *  @return The actively rotated encoded point
 *  
 *  @pre  @p rotation is a unit Quaternion.
 *        @p encoded_point is a pure Auaternion.
 *  @post The output is a pure Quaternion
 *  
 *  @note This is an active rotation, meaning that the point is rotated with
 *        respect to the coordinate system.
 *        This is also known as a global rotation.
 */
template <class T>
constexpr Quaternion<T> actively_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
{
    assert( rotation.isUnit() );
    assert( encoded_point.isPure() );

    return rotation.conjugate() * encoded_point * rotation;
}

/**
 *  
 *  @see actively_rotate_encoded_point
 */
template <class T>
constexpr Quaternion<T> globally_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
{
    return actively_rotate_encoded_point(rotation, encoded_point);
}

template <class T>
constexpr Quaternion<T> compose_rotations(const Quaternion<T> &rotation_1, const Quaternion<T> &rotation_2)
{
    return rotation_2 * rotation_1;
}

/** Creates the normalized form of a Quaternion
 *  
 *  @param input The Quaternion to normalize
 *  
 *  @return The normalized version of @p input
 */
template <class T>
constexpr Quaternion<T> normalized(Quaternion<T> input)
{
    return input / input.norm();
}

/** Sums up the components of @p input
 *  
 *  @input The Quaternion to operate on
 */
template <class T>
constexpr T accumulate(Quaternion<T> input)
{
    return T{input.real() + input.i() + input.j() + input.k()};
}

///@{
using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;
using Quaternionld = Quaternion<long double>;
///@}
