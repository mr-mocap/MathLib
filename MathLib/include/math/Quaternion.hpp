#pragma once

#include "math/ApproximatelyEqualTo.hpp"
#include "math/Conjugate.hpp"
#include "math/Vector.hpp"
#include <cassert>
#include <cmath>

/** @file
 *  
 *  Contains the definition of the Quaternion class along with
 *  various helper functions
 *
 *  @hideincludegraph
 */

/** A mathematical quaternion
 *  
 *  @note A quaternion is a 4-dimensional object that is an extension
 *        of the complex number system.
 *        Its main use is for encoding rotation in 3-dimensional space.
 *
 *  @headerfile "math/Quaternion.hpp"
 */
template <class T = float>
class Quaternion
{
public:
    using value_type = T;

    Quaternion() = default;
    explicit constexpr Quaternion(T real_number) : _w(real_number) { }
    explicit constexpr Quaternion(T w, T i, T j, T k) : _w(w), _i(i), _j(j), _k(k) { }

    /** @name Constants
     *  @{
     */
    /// Quaternion representation of the real number 1
    constexpr static Quaternion<T> identity() { return Quaternion{ T{1}, T{}, T{}, T{} }; }

    /// Quaternion representation of the real number 0
    constexpr static Quaternion<T> zero() { return Quaternion{}; }
    constexpr static Quaternion<T> unit_real() { return identity(); }
    constexpr static Quaternion<T> unit_i() { return Quaternion{ T{}, T{1}, T{},  T{} }; }
    constexpr static Quaternion<T> unit_j() { return Quaternion{ T{}, T{},  T{1}, T{} }; }
    constexpr static Quaternion<T> unit_k() { return Quaternion{ T{}, T{},  T{},  T{1} }; }
    /// @}

    Quaternion<T> conjugate() const { return Quaternion<T>{ _w, -_i, -_j, -_k }; }
    Quaternion<T> pow(const T exponent) const
    {
        assert( isUnit() );

        T magnitude{ imaginary().magnitude() };

        // Are we a purely real number?
        if ( approximately_equal_to(magnitude, T{0}) )
            return Quaternion{ std::pow( w(), exponent ) }; // Yes, so only compute the real part

        // Calculate the angle
        T theta{ std::atan2(magnitude, w()) };
        T new_theta{ exponent * theta };
        T coefficient{ std::sin(new_theta) / magnitude };

        // NOW we can calculate to the power of "exponent"...
        T temp{ w() * w() + magnitude * magnitude };

        return Quaternion<T>{ std::cos(new_theta),
                              coefficient * i(),
                              coefficient * j(),
                              coefficient * k() } * std::pow(temp, exponent);
    }

    Quaternion<T> exp() const
    {
        T e_to_the_x{ std::exp( w() ) };
        T vector_part_magnitude{ imaginary().magnitude() };
        T cos_v{ std::cos(vector_part_magnitude) };
        T sin_v{ (vector_part_magnitude > T{0}) ? std::sin(vector_part_magnitude) / vector_part_magnitude : T{0} };

        return Quaternion{ cos_v,
                           sin_v * i(),
                           sin_v * j(),
                           sin_v * k() } * e_to_the_x;
    }

    Quaternion<T> log() const
    {
        T magnitude_of_imaginary_part{ imaginary().magnitude() };

        // Are we purely a real number?
        if ( magnitude_of_imaginary_part == T{0} )
            return Quaternion{ std::log( w() ) }; // YES, so just set the w() component (the others will be zero)

        T this_norm{ norm() };
        T theta{ std::acos( w() / this_norm ) };
        T coefficient{ theta / magnitude_of_imaginary_part };

        return Quaternion{ std::log(this_norm),
                           coefficient * i(),
                           coefficient * j(),
                           coefficient * k() };
    }

    T    normSquared() const { return accumulate(*this * conjugate()); }
    T    norm() const { return std::sqrt( normSquared() ); }

    T    magnitudeSquared() const { return normSquared(); }
    T    magnitude() const { return norm(); }

    Quaternion<T> inverse() const { return conjugate() / normSquared(); }

    /** @name Element Access
     *  @{
     */
    const T &w() const { return _w; }
    const T &real() const { return _w; }

    const T &i() const { return _i; }
    const T &j() const { return _j; }
    const T &k() const { return _k; }

    /// Extracts the imaginary part of a Quaternion as a Vector3D
    constexpr Vector3D<T> imaginary() const { return { _i, _j, _k }; }
    /// @}

    bool isUnit() const { return approximately_equal_to( magnitude(), T{1} ); }
    bool isUnit(T tolerance) const { return approximately_equal_to( magnitude(), T{1}, tolerance ); }

    bool isZero() const { return approximately_equal_to( magnitude(), T{} ); }
    bool isZero(T tolerance) const { return approximately_equal_to( magnitude(), T{}, tolerance ); }

    // Checks if the real() part is 0
    bool isPure() const { return approximately_equal_to(real(), T{}); }

    /** @name Convenience Creation Functions
     *  @{
     */
    /** Construct a pure Quaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure Quaternion is one in which the w, or real, component
     *        is 0.
     */
    constexpr static Quaternion<T> make_pure(T x, T y, T z) { return Quaternion<T>{ T{}, x, y, z }; }

    /** Construct a pure Quaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure Quaternion is one in which the w, or real, component
     *        is 0.
     */
    constexpr static Quaternion<T> make_pure(const Vector3D<T> &t) { return Quaternion<T>{ T{}, t.x, t.y, t.z }; }

    /** Encode a 3D point as a pure Quaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure Quaternion is one in which the w, or real, component
     *        is 0.
     *  
     *  @see make_pure
     */
    constexpr static Quaternion<T> encode_point(T x, T y, T z) { return make_pure(x, y, z); }

    /** Encode a 3D point as a pure Quaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure Quaternion is one in which the w, or real, component
     *        is 0.
     *  
     *  @see make_pure
     */
    constexpr static Quaternion<T> encode_point(const Vector3D<T> &point) { return make_pure(point); }

    /** Enocde a rotation into a Quaternion
     *  
     *  @param radians The amount of rotation to apply (in radians)
     *  @param axis_x  The X component of the vector to rotate around
     *  @param axis_y  The Y component of the vector to rotate around
     *  @param axis_z  The Z component of the vector to rotate around
     *  
     *  @post output.isUnit() == true
     */
    constexpr static Quaternion<T> make_rotation(T radians, T axis_x, T axis_y, T axis_z)
    {
        T half_angle = radians * T{0.5};
        T cos_theta = cos( half_angle );
        T sin_theta = sin( half_angle );

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
    constexpr static Quaternion<T> make_rotation(T radians, const Vector3D<T>& axis) { return make_rotation(radians, axis.x, axis.y, axis.z); }
    /// @}

private:
    T _w{};
    T _i{};
    T _j{};
    T _k{};
};

/** @addtogroup Equality
 * 
 *  @{
 * 
 *  Compares two Quaternion inputs equal, component-wise, to within a tolerance
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
constexpr bool approximately_equal_to(const Quaternion<T> &value_to_test, const Quaternion<T> &value_it_should_be, float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.w(), value_it_should_be.w(), tolerance) &&
           approximately_equal_to(value_to_test.i(), value_it_should_be.i(), tolerance) &&
           approximately_equal_to(value_to_test.j(), value_it_should_be.j(), tolerance) &&
           approximately_equal_to(value_to_test.k(), value_it_should_be.k(), tolerance);
}
/// @}

/** @name Operators
 *  @{
 */

/** Defines equality of two Quaternions
 *  
 *  @note Uses approximately_equal_to under-the-hood
 *  
 *  @see approximately_equal_to
 * 
 *  @relates Quaternion
 */
template<class T>
constexpr bool operator ==(Quaternion<T> left, Quaternion<T> right)
{
    return approximately_equal_to(left, right);
}

/** Defines inequality of two Quaternions
 *  
 *  @note Uses operator ==()
 *  
 *  @see approximately_equal_to
 * 
 *  @relates Quaternion
 */
template<class T>
constexpr bool operator !=(Quaternion<T> left, Quaternion<T> right)
{
    return !(left == right);
}

/** Defines multiplication of a Quaternion and a scalar
 *  
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> operator *(Quaternion<T> quaternion, T scalar)
{
    return Quaternion<T>{ quaternion.w() * scalar, quaternion.i() * scalar, quaternion.j() * scalar, quaternion.k() * scalar };
}

/** Defines multiplication of a scalar and a Quaternion
 *  
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> operator *(T scalar, Quaternion<T> quaternion)
{
    return Quaternion<T>{ scalar * quaternion.w(), scalar * quaternion.i(), scalar * quaternion.j(), scalar * quaternion.k()};
}

/** Defines division of a Quaternion by a scalar
 *  
 *  @return the new Quaternion
 *
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> operator /(Quaternion<T> quaternion, T scalar)
{
    return Quaternion<T>{ quaternion.w() / scalar, quaternion.i() / scalar, quaternion.j() / scalar, quaternion.k() / scalar };
}

/** Defines division of a scalar by a Quaternion
 *  
 *  @return the new Quaternion
 * 
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> operator /(T scalar, Quaternion<T> quaternion)
{
    return Quaternion<T>{ scalar / quaternion.w(), scalar / quaternion.i(), scalar / quaternion.j(), scalar / quaternion.k() };
}

/** Defines division of a Quaternion by a Quaternion
 *  
 *  @return the new Quaternion
 * 
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> operator /(Quaternion<T> left, Quaternion<T> right)
{
    return left * right.inverse();
}

/** Defines addition of a Quaternion and a Quaternion
 *  
 *  @return the new Quaternion
 * 
 *  @relates Quaternion
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
 * 
 *  @relates Quaternion
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
 * 
 *  @relates Quaternion
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

/** Defines negation of a Quaternion
 *  
 *  Performs a component-wise negation of the input
 * 
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> operator -(Quaternion<T> q)
{
    return Quaternion<T>{ -q.w(), -q.i(), -q.j(), -q.k() };
}
/// @}

/** Calculates the dot product of two Quaternions
 *  
 *  @note In this case, the Quaternions are just treated as
 *        separate 4-tuples and the dot product of those are
 *        calculated.
 * 
 *  @relates Quaternion
 */
template <class T>
constexpr T dot(Quaternion<T> left, Quaternion<T> right)
{
    return left.w() * right.w() +
           left.i() * right.i() +
           left.j() * right.j() +
           left.k() * right.k();
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
 * 
 *  @relates Quaternion
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
 * 
 *  @relates Quaternion
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
 *        @p encoded_point is a pure Quaternion.
 *  @post The output is a pure Quaternion
 *  
 *  @note This is an active rotation, meaning that the point is rotated with
 *        respect to the coordinate system.
 *        This is also known as a global rotation.
 * 
 *  @relates Quaternion
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
 * 
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> globally_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
{
    return actively_rotate_encoded_point(rotation, encoded_point);
}

/** Performs a concatenation of two rotations
 *  
 *  @param rotation_1 The first rotation to perform
 *  @param rotation_2 The second rotation to perform
 * 
 *  @relates Quaternion
 */
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
 * 
 *  @relates Quaternion
 */
template <class T>
constexpr Quaternion<T> normalized(Quaternion<T> input)
{
    assert( Quaternion<T>{input / input.norm()}.isUnit() );

    return input / input.norm();
}

/** Sums up the components of @p input
 *  
 *  @param input The Quaternion to operate on
 * 
 *  @return The sum of all the components
 * 
 *  @relates Quaternion
 */
template <class T>
constexpr T accumulate(Quaternion<T> input)
{
    return T{input.real() + input.i() + input.j() + input.k()};
}

template <class T>
constexpr Quaternion<T> slerp(const Quaternion<T> &begin, const Quaternion<T> &end, const T percent)
{
    Quaternion<T> combined{ begin.conjugate() * end };

    return begin * combined.pow(percent);
}

/** @name QuaternionTypeAliases
 *
 *  Type Aliases
 *  
 *  @{
 */
using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;
using Quaternionld = Quaternion<long double>;
/// @}
