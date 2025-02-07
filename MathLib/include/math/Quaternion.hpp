#pragma once

#include "math/Functions.hpp"
#include "math/Vector3D.hpp"
#include "math/Angle.hpp"
#include <cassert>
#include <cmath>

/** @file
 *  
 *  Contains the definition of the Quaternion class along with
 *  various helper functions
 *
 *  @hideincludegraph
 */

namespace Math
{

/** A mathematical quaternion
 *  
 *  @note A quaternion is a 4-dimensional object that is an extension
 *        of the complex number system.
 *        Its main use is for encoding rotation in 3-dimensional space.
 *
 *  @headerfile "math/Quaternion.hpp"
 */
template <class T>
class Quaternion
{
public:
    using value_type = T;

    Quaternion() = default;
    explicit constexpr Quaternion(const T real_number) : _w(real_number) { } ///< Constructs a Quaternion equivalent to the given real number
    explicit constexpr Quaternion(const T w, const T i, const T j, const T k) : _w(w), _i(i), _j(j), _k(k) { }

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

    constexpr Quaternion<T> conjugate() const
    {
        if constexpr (std::is_floating_point_v<T>)
            return Quaternion<T>{ _w, -_i, -_j, -_k };
        else
            return Quaternion<T>{ _w, conjugate(_i), conjugate(_j), conjugate(_k) };
    }

    /// Computes this Quaternion raised to a real power
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

    /** Computes the exponential form of this Quaternion
     *
     *  @note It is possible for this routine to output a non-unit Quaternion
     *        when given a unit Quaternion as input.  It is for this reason that
     *        the implementation of log() has been adjusted to automatically handle
     *        non-unit Quaternions.
     */
    Quaternion<T> exp() const
    {
        T e_to_the_w{ std::exp( w() ) };
        T vector_part_magnitude{ imaginary().magnitude() };
        T cos_v{ std::cos(vector_part_magnitude) };
        T sin_v{ (vector_part_magnitude > T{0}) ? std::sin(vector_part_magnitude) / vector_part_magnitude : T{0} };

        return Quaternion{ cos_v,
                           sin_v * i(),
                           sin_v * j(),
                           sin_v * k() } * e_to_the_w;
    }

    /** Computes the log base e of this Quaternion
     *  
     *  @note We handle non-unit Quaternions in this version so that we can satisfy the relationship:
     *        log( exp( x ) ) == x
     */
    Quaternion<T> log() const
    {
        T magnitude_of_imaginary_part{ imaginary().magnitude() };

        // Are we purely a real number?
        if ( approximately_equal_to(magnitude_of_imaginary_part, T{0}) )
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

    constexpr Quaternion<T> normalized() const
    {
        assert( Quaternion<T>{*this / magnitude()}.isUnit() ); // Verify that we actually return a unit-length Quaternion

        return *this / this->magnitude();
    }

    Quaternion<T> inverse() const { return conjugate() / normSquared(); }

    Radian<T> angle() const
    {
        return T{2} * std::atan2( imaginary().magnitude(), w() );
    }

    constexpr Vector3D<T> axis() const
    {
        return imaginary().normalized();
    }

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
    bool isUnit(const T tolerance) const { return approximately_equal_to( magnitude(), T{1}, tolerance ); }

    bool isZero() const { return approximately_equal_to( magnitude(), T{} ); }
    bool isZero(const T tolerance) const { return approximately_equal_to( magnitude(), T{}, tolerance ); }

    // Checks if the real() part is 0
    bool isPure() const { return approximately_equal_to(real(), T{}); }

    bool isNaN() const { return std::isnan(_w) || std::isnan(_i) || std::isnan(_j) || std::isnan(_k); }
    bool isInf() const { return std::isinf(_w) || std::isinf(_i) || std::isinf(_j) || std::isinf(_k); }

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
    constexpr static Quaternion<T> make_pure(const T x, const T y, const T z) { return Quaternion<T>{ T{}, x, y, z }; }

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
    constexpr static Quaternion<T> encode_point(const T x, const T y, const T z) { return make_pure(x, y, z); }

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
    constexpr static Quaternion<T> make_rotation(const Radian<T> radians, const T axis_x, const T axis_y, const T axis_z)
    {
        return make_rotation(radians, { axis_x, axis_y, axis_z });
    }

    /** Enocde a rotation into a Quaternion
     *  
     *  @param radians The amount of rotation to apply (in radians)
     *  @param axis    The axis to rotate around
     *  
     *  @post output.isUnit() == true
     */
    constexpr static Quaternion<T> make_rotation(const Radian<T> radians, const Vector3D<T> &axis)
    {
        T half_angle = radians.value() * T{0.5};
        T cos_theta = cos( half_angle );
        T sin_theta = sin( half_angle );
        Vector3D<T> n{ axis.normalized() };

        return Quaternion<T>{ cos_theta,
                              sin_theta * n.x,
                              sin_theta * n.y,
                              sin_theta * n.z };
    }
    /// @}

private:
    T _w{};
    T _i{};
    T _j{};
    T _k{};

    /** @name Hidden Friend Functions
     *  @{
     */

    /** Defines equality of two Quaternions
     *  
     *  @note Uses approximately_equal_to under-the-hood
     *  
     *  @note Use C++20's ability to generate the operator !=() from operator ==()
     * 
     *  @see Equality
     */
    friend constexpr bool operator ==(const Quaternion<T> &left, const Quaternion<T> &right)
    {
        return approximately_equal_to(left, right);
    }

    /** @addtogroup Equality
     * 
     *  @relates Quaternion
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
     */
    friend constexpr bool approximately_equal_to(const Quaternion<T> &value_to_test, const Quaternion<T> &value_it_should_be, const float tolerance = 0.0002f)
    {
        return approximately_equal_to(value_to_test.w(), value_it_should_be.w(), tolerance) &&
               approximately_equal_to(value_to_test.i(), value_it_should_be.i(), tolerance) &&
               approximately_equal_to(value_to_test.j(), value_it_should_be.j(), tolerance) &&
               approximately_equal_to(value_to_test.k(), value_it_should_be.k(), tolerance);
    }
    /// @}  {Equality}

    /** @addtogroup QuaternionAlgebra Quaternion Algebra
     *  @{
     */

    /** @name Multiplication
     *  @{
     */
    /** Implements multiplication of a Quaternion by a scalar
     */
    friend constexpr Quaternion<T> operator *(const Quaternion<T> &quaternion, const T scalar)
    {
        return Quaternion<T>{ quaternion.w() * scalar, quaternion.i() * scalar, quaternion.j() * scalar, quaternion.k() * scalar };
    }

    /** Implements multiplication of a scalar by a Quaternion
     */
    friend constexpr Quaternion<T> operator *(const T scalar, const Quaternion<T> &quaternion)
    {
        return Quaternion<T>{ scalar * quaternion.w(), scalar * quaternion.i(), scalar * quaternion.j(), scalar * quaternion.k()};
    }

    /** Defines multiplication of two Quaternions
     *  
     *  @return the new Quaternion
     */
    friend constexpr Quaternion<T> operator *(const Quaternion<T> &left, const Quaternion<T> &right)
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
    /// @}

    /** @name Division
     *  @{
     */
    /** Defines division of a Quaternion by a scalar
     *  
     *  @return the new Quaternion
     */
    friend constexpr Quaternion<T> operator /(const Quaternion<T> &quaternion, const T scalar)
    {
        return Quaternion<T>{ quaternion.w() / scalar, quaternion.i() / scalar, quaternion.j() / scalar, quaternion.k() / scalar };
    }

    /** Defines division of a scalar by a Quaternion
     *  
     *  @return the new Quaternion
     */
    friend constexpr Quaternion<T> operator /(const T scalar, const Quaternion<T> &quaternion)
    {
        return Quaternion<T>{ scalar / quaternion.w(), scalar / quaternion.i(), scalar / quaternion.j(), scalar / quaternion.k() };
    }

    /** Defines division of two Quaternions
     *  
     *  @return the new Quaternion
     */
    friend constexpr Quaternion<T> operator /(const Quaternion<T> &left, const Quaternion<T> &right)
    {
        return left * right.inverse();
    }
    /// @}

    /** @name Addition
     *  @{
     */
    /** Defines addition of two Quaternions
     *  
     *  @return the new Quaternion
     */
    friend constexpr Quaternion<T> operator +(const Quaternion<T> &left, const Quaternion<T> &right)
    {
        return Quaternion<T>{left.w() + right.w(),
                            left.i() + right.i(),
                            left.j() + right.j(),
                            left.k() + right.k()};
    }
    /// @}

    /** @name Subtraction
     *  @{
     */
    /** Defines subtraction of two Quaternions
     *  
     *  @return the new Quaternion
     */
    friend constexpr Quaternion<T> operator -(const Quaternion<T> &left, const Quaternion<T> &right)
    {
        return Quaternion<T>{left.w() - right.w(),
                            left.i() - right.i(),
                            left.j() - right.j(),
                            left.k() - right.k()};
    }
    /// @}

    /** Defines negation of a Quaternion
     *  
     *  @return the new Quaternion
     * 
     *  @name Negation
     */
    friend constexpr Quaternion<T> operator -(const Quaternion<T> &q)
    {
        return Quaternion<T>{ -q.w(), -q.i(), -q.j(), -q.k() };
    }
    /// @}  {QuaternionAlgebra}

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
    friend bool check_if_equal(const Quaternion<T> &input, const Quaternion<T> &near_to, float tolerance = 0.0002f)
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
    friend bool check_if_not_equal(const Quaternion<T> &input, const Quaternion<T> &near_to, float tolerance = 0.0002f)
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

    friend void CHECK_IF_EQUAL(const Quaternion<T> &input, const Quaternion<T> &near_to, const float tolerance = 0.0002f)
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    friend void CHECK_IF_NOT_EQUAL(const Quaternion<T> &input, const Quaternion<T> &near_to, const float tolerance = 0.0002f)
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    friend void CHECK_IF_ZERO(const Quaternion<T> &input, const float tolerance = 0.0002f)
    {
        assert( check_if_equal(input, Quaternion<T>::zero(), tolerance));
    }

    /** @name Global Functions
     * 
     *  @relates Quaternion
     * 
     *  @{
     */
    /** Calculates the dot product of two Quaternions
     *  
     *  @note In this case, the Quaternions are just treated as
     *        separate 4-tuples and the dot product of those are
     *        calculated.
     */
    friend constexpr T dot(const Quaternion<T> &left, const Quaternion<T> &right)
    {
        return left.w() * right.w() +
            left.i() * right.i() +
            left.j() * right.j() +
            left.k() * right.k();
    }

    friend constexpr T dot_normalized(const Quaternion<T> &left, const Quaternion<T> &right)
    {
        return (left.w() * right.w() +
                left.i() * right.i() +
                left.j() * right.j() +
                left.k() * right.k()) / (left.magnitude() * right.magnitude());
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
    friend constexpr Quaternion<T> passively_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
    {
        assert( rotation.isUnit() );
        assert( encoded_point.isPure() );

        return rotation * encoded_point * rotation.conjugate();
    }

    /**
     *  
     *  @see passively_rotate_encoded_point
     */
    friend constexpr Quaternion<T> locally_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
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
     */
    friend constexpr Quaternion<T> actively_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
    {
        assert( rotation.isUnit() );
        assert( encoded_point.isPure() );

        return rotation.conjugate() * encoded_point * rotation;
    }

    /**
     *  
     *  @see actively_rotate_encoded_point
     */
    friend constexpr Quaternion<T> globally_rotate_encoded_point(const Quaternion<T> &rotation, const Quaternion<T> &encoded_point)
    {
        return actively_rotate_encoded_point(rotation, encoded_point);
    }

    /** Performs a concatenation of two rotations
     *  
     *  @param rotation_1 The first rotation to perform
     *  @param rotation_2 The second rotation to perform
     */
    friend constexpr Quaternion<T> compose_rotations(const Quaternion<T> &rotation_1, const Quaternion<T> &rotation_2)
    {
        return rotation_2 * rotation_1;
    }

    /** Creates the normalized form of a Quaternion
     *  
     *  @param input The Quaternion to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr Quaternion<T> normalized(const Quaternion<T> &input)
    {
        return input.normalized();
    }

    /** Computes the phase-angle (in radians of a Quaternion)
     *
     *  @note This is meant to mirror the behavior of std::arg( std::complex )
     */
    friend constexpr T arg(const Quaternion<T> &input)
    {
        return input.angle().value();
    }

    /** Constructs a unit Quaternion from the given axis and angle
     *
     *  @note This is meant to mirror the behavior of the std::complex version of std::polar()
     */
    friend constexpr Quaternion<T> polar(const Vector3D<T> &axis, const Radian<T> angle = Radian<T>{})
    {
        assert( axis.magnitude() == T{1} );

        return Quaternion<T>::make_rotation( angle, axis );
    }

    /** Sums up the components of @p input
     *  
     *  @param input The Quaternion to operate on
     * 
     *  @return The sum of all the components
     */
    friend constexpr T accumulate(const Quaternion<T> &input)
    {
        return T{input.real() + input.i() + input.j() + input.k()};
    }

    /** Calculates the Spherical Linear Interpolation betwee two Quaternions
     * 
     *  @param begin   Origin value
     *  @param end     Destination value
     *  @param percent [0..1] Represents the percentage to interpolate
     */
    friend constexpr Quaternion<T> slerp(const Quaternion<T> &begin, const Quaternion<T> &end, const T percent)
    {
        Quaternion<T> combined{ begin.conjugate() * end };

        return begin * combined.pow(percent);
    }

    friend std::string format(const Quaternion<T> &input)
    {
        return std::format("[w: {}, i: {}, j: {}, k: {}]", input.w(), input.i(), input.j(), input.k());
    }

    /**  Computes the conjugate of the input
     * 
     *   @note This will just call @c input.conjugate()
     */
    friend constexpr Quaternion<T> conjugate(const Quaternion<T> &input)
    {
        return input.conjugate();
    }

    /**  Computes the log of the input
     * 
     *   @note This will just call @c input.log()
     */
    friend constexpr Quaternion<T> log(const Quaternion<T> &input)
    {
        return input.log();
    }

    /**  Computes the exponential of the input
     * 
     *   @note This will just call @c input.exp()
     */
    friend Quaternion<T> exp(const Quaternion<T> &input)
    {
        return input.exp();
    }
    /// @} {GlobalFunctions}
    /// @} {HiddenFriendFunctions}
};


/** @name Type Aliases
 *
 *  @relates Quaternion
 * 
 *  @{
 */
using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;
using Quaternionld = Quaternion<long double>;
/// @}

}