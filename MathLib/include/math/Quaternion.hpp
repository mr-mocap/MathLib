#pragma once

#include "math/Functions.hpp"
#include "math/Vector3D.hpp"
#include "math/Angle.hpp"
#include <cassert>
#include <cmath>
#include <concepts>
#include <type_traits>

/** @file
 *  
 *  Contains the definition of the BasicQuaternion class along with
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
class BasicQuaternion
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
    BasicQuaternion() = default;
    constexpr BasicQuaternion(T real_number) : _w(real_number) { } ///< Constructs a BasicQuaternion equivalent to the given real number
    explicit constexpr BasicQuaternion(T w, T i, T j, T k) : _w(w), _i(i), _j(j), _k(k) { }
    /// @}

    /** @name Constants
     *  @{
     */
    /// BasicQuaternion representation of the real number 1
    constexpr static BasicQuaternion<T> identity() { return BasicQuaternion{ T{1}, T{}, T{}, T{} }; }

    /// BasicQuaternion representation of the real number 0
    constexpr static BasicQuaternion<T> zero() { return BasicQuaternion{}; }
    constexpr static BasicQuaternion<T> unit_real() { return identity(); }
    constexpr static BasicQuaternion<T> unit_i() { return BasicQuaternion{ T{}, T{1}, T{},  T{} }; }
    constexpr static BasicQuaternion<T> unit_j() { return BasicQuaternion{ T{}, T{},  T{1}, T{} }; }
    constexpr static BasicQuaternion<T> unit_k() { return BasicQuaternion{ T{}, T{},  T{},  T{1} }; }
    /// @}

    constexpr BasicQuaternion<T> conjugate() const
    {
        if constexpr (std::is_floating_point_v<T>)
            return BasicQuaternion<T>{ _w, -_i, -_j, -_k };
        else
            return BasicQuaternion<T>{ _w, conjugate(_i), conjugate(_j), conjugate(_k) };
    }

    /// Computes this BasicQuaternion raised to a real power
    BasicQuaternion<T> pow(T exponent) const
    {
        assert( isUnit() );

        T magnitude{ imaginary().magnitude() };

        // Are we a purely real number?
        if ( approximately_equal_to(magnitude, T{0.0}) )
            return BasicQuaternion{ std::pow( w(), exponent ) }; // Yes, so only compute the real part

        // Calculate the angle
        T theta{ std::atan2(magnitude, w()) };
        T new_theta{ exponent * theta };
        T coefficient{ std::sin(new_theta) / magnitude };

        // NOW we can calculate to the power of "exponent"...
        T temp{ w() * w() + magnitude * magnitude };

        return BasicQuaternion<T>{ std::cos(new_theta),
                              coefficient * i(),
                              coefficient * j(),
                              coefficient * k() } * std::pow(temp, exponent);
    }

    /** Computes the exponential form of this BasicQuaternion
     *
     *  @note It is possible for this routine to output a non-unit BasicQuaternion
     *        when given a unit BasicQuaternion as input.  It is for this reason that
     *        the implementation of log() has been adjusted to automatically handle
     *        non-unit Quaternions.
     */
    BasicQuaternion<T> exp() const
    {
        T e_to_the_w{ std::exp( w() ) };
        T vector_part_magnitude{ imaginary().magnitude() };
        T cos_v{ std::cos(vector_part_magnitude) };
        T sin_v{ (vector_part_magnitude > T{0.0}) ? std::sin(vector_part_magnitude) / vector_part_magnitude : T{0.0} };

        return BasicQuaternion{ cos_v,
                           sin_v * i(),
                           sin_v * j(),
                           sin_v * k() } * e_to_the_w;
    }

    /** Computes the log base e of this BasicQuaternion
     *  
     *  @note We handle non-unit Quaternions in this version so that we can satisfy the relationship:
     *        log( exp( x ) ) == x
     */
    BasicQuaternion<T> log() const
    {
        T magnitude_of_imaginary_part{ imaginary().magnitude() };

        // Are we purely a real number?
        if ( approximately_equal_to(magnitude_of_imaginary_part, T{0.0}) )
            return BasicQuaternion{ std::log( w() ) }; // YES, so just set the w() component (the others will be zero)

        T this_norm{ norm() };
        T theta{ std::acos( w() / this_norm ) };
        T coefficient{ theta / magnitude_of_imaginary_part };

        return BasicQuaternion{ std::log(this_norm),
                           coefficient * i(),
                           coefficient * j(),
                           coefficient * k() };
    }

    T    normSquared() const { return accumulate(*this * conjugate()); }
    T    norm() const { return std::sqrt( normSquared() ); }

    T    magnitudeSquared() const { return normSquared(); }
    T    magnitude() const { return norm(); }

    constexpr BasicQuaternion<T> normalized() const
    {
        assert( BasicQuaternion<T>{*this / magnitude()}.isUnit() ); // Verify that we actually return a unit-length BasicQuaternion

        return *this / this->magnitude();
    }

    BasicQuaternion<T> inverse() const { return conjugate() / normSquared(); }

    BasicRadian<T> angle() const
    {
        return T{2.0} * std::atan2( imaginary().magnitude(), w() );
    }

    constexpr BasicVector3D<T> axis() const
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

    /// Extracts the imaginary part of a BasicQuaternion as a BasicVector3D
    constexpr BasicVector3D<T> imaginary() const { return { _i, _j, _k }; }
    /// @}

    bool isUnit() const { return approximately_equal_to( magnitude(), T{1} ); }
    bool isUnit(T tolerance) const { return approximately_equal_to( magnitude(), T{1}, tolerance ); }

    bool isZero() const { return approximately_equal_to( magnitude(), T{} ); }
    bool isZero(T tolerance) const { return approximately_equal_to( magnitude(), T{}, tolerance ); }

    // Checks if the real() part is 0
    bool isPure() const { return approximately_equal_to(real(), T{}); }

    /** @name Invalid Value Check
     *  @{
     */
    bool isNaN() const
    {
        if constexpr ( std::is_floating_point_v<T> )
            return std::isnan(_w) || std::isnan(_i) || std::isnan(_j) || std::isnan(_k);
        else
            return _w.isNaN() || _i.isNaN() || _j.isNaN() || _k.isNaN();
    }
    bool isInf() const
    {
        if constexpr ( std::is_floating_point_v<T> )
            return std::isinf(_w) || std::isinf(_i) || std::isinf(_j) || std::isinf(_k);
        else
            return _w.isInf() || _i.isInf() || _j.isInf() || _k.isInf();
    }
    /// @}

    /** @name Convenience Creation Functions
     *  @{
     */
    /** Construct a pure BasicQuaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure BasicQuaternion is one in which the w, or real, component
     *        is 0.
     */
    constexpr static BasicQuaternion<T> make_pure(T x, T y, T z) { return BasicQuaternion<T>{ T{}, x, y, z }; }

    /** Construct a pure BasicQuaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure BasicQuaternion is one in which the w, or real, component
     *        is 0.
     */
    constexpr static BasicQuaternion<T> make_pure(const BasicVector3D<T> &t) { return BasicQuaternion<T>{ T{}, t.x, t.y, t.z }; }

    /** Encode a 3D point as a pure BasicQuaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure BasicQuaternion is one in which the w, or real, component
     *        is 0.
     *  
     *  @see make_pure
     */
    constexpr static BasicQuaternion<T> encode_point(T x, T y, T z) { return make_pure(x, y, z); }

    /** Encode a 3D point as a pure BasicQuaternion
     *  
     *  @post output.w() == 0
     *        output.real() == 0

     *  @note A pure BasicQuaternion is one in which the w, or real, component
     *        is 0.
     *  
     *  @see make_pure
     */
    constexpr static BasicQuaternion<T> encode_point(const BasicVector3D<T> &point) { return make_pure(point); }

    /** Enocde a rotation into a BasicQuaternion
     *  
     *  @param radians The amount of rotation to apply (in radians)
     *  @param axis_x  The X component of the vector to rotate around
     *  @param axis_y  The Y component of the vector to rotate around
     *  @param axis_z  The Z component of the vector to rotate around
     *  
     *  @post output.isUnit() == true
     */
    constexpr static BasicQuaternion<T> make_rotation(const BasicRadian<T> &radians, T axis_x, T axis_y, T axis_z)
    {
        return make_rotation(radians, { axis_x, axis_y, axis_z });
    }

    /** Enocde a rotation into a BasicQuaternion
     *  
     *  @param radians The amount of rotation to apply (in radians)
     *  @param axis    The axis to rotate around
     *  
     *  @post output.isUnit() == true
     */
    constexpr static BasicQuaternion<T> make_rotation(const BasicRadian<T> &radians, const BasicVector3D<T> &axis)
    {
        T half_angle = radians.value() * T{0.5};
        T cos_theta = cos( half_angle );
        T sin_theta = sin( half_angle );
        BasicVector3D<T> n{ axis.normalized() };

        return BasicQuaternion<T>{ cos_theta,
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

    /** @name Equality
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
    friend constexpr bool operator ==(const BasicQuaternion<T> &left, const BasicQuaternion<T> &right)
    {
        return approximately_equal_to(left, right);
    }
    /// @}

    /** @addtogroup Equality
     * 
     *  @relates BasicQuaternion
     * 
     *  @{
     * 
     *  Compares two BasicQuaternion inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     * 
     *  @see Equality
     */
    template <std::floating_point OT = float>
    friend constexpr bool approximately_equal_to(const BasicQuaternion<T> &value_to_test, const BasicQuaternion<T> &value_it_should_be, OT tolerance = OT{0.0002})
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

    /** @name Operators
     * 
     *  @relates BasicQuaternion
     * 
     *  @{
     */
    template <std::floating_point OT>
    friend constexpr BasicQuaternion<T> operator *(const BasicQuaternion<T> &quaternion, OT scalar)
    {
        return BasicQuaternion<T>{ quaternion.w() * scalar, quaternion.i() * scalar, quaternion.j() * scalar, quaternion.k() * scalar };
    }

    friend constexpr BasicQuaternion<T> operator *(const BasicQuaternion<T> &left, const BasicQuaternion<T> &right)
    {
        return BasicQuaternion<T>{left.w() * right.w() - (left.i() * right.i() +
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

    friend constexpr BasicQuaternion<T> operator /(const BasicQuaternion<T> &left, const BasicQuaternion<T> &right)
    {
        return left * right.inverse();
    }

    template <std::floating_point OT>
    friend constexpr BasicQuaternion<T> operator /(const BasicQuaternion<T> &quaternion, OT scalar)
    {
        return BasicQuaternion<T>( quaternion.w() / T(scalar),
                                   quaternion.i() / T(scalar),
                                   quaternion.j() / T(scalar),
                                   quaternion.k() / T(scalar) );
    }

    friend constexpr BasicQuaternion<T> operator +(const BasicQuaternion<T> &left, const BasicQuaternion<T> &right)
    {
        return BasicQuaternion<T>( left.w() + right.w(),
                                   left.i() + right.i(),
                                   left.j() + right.j(),
                                   left.k() + right.k() );
    }

    friend constexpr BasicQuaternion<T> operator -(const BasicQuaternion<T> &left, const BasicQuaternion<T> &right)
    {
        return BasicQuaternion<T>{ left.w() - right.w(),
                                   left.i() - right.i(),
                                   left.j() - right.j(),
                                   left.k() - right.k()
                            };
    }

    friend constexpr BasicQuaternion<T> operator -(const BasicQuaternion<T> &q)
    {
        return BasicQuaternion<T>{ -q.w(), -q.i(), -q.j(), -q.k() };
    }
    /// @}  {Operators}
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
    template <std::floating_point OT = float>
    friend bool check_if_equal(const BasicQuaternion<T> &input, const BasicQuaternion<T> &near_to, OT tolerance = OT{0.0002})
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
    friend bool check_if_not_equal(const BasicQuaternion<T> &input, const BasicQuaternion<T> &near_to, OT tolerance = OT{0.0002})
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
    friend void CHECK_IF_EQUAL(const BasicQuaternion<T> &input, const BasicQuaternion<T> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_NOT_EQUAL(const BasicQuaternion<T> &input, const BasicQuaternion<T> &near_to, OT tolerance = OT{0.0002})
    {
        assert( check_if_not_equal(input, near_to, tolerance) );
    }

    template <std::floating_point OT = float>
    friend void CHECK_IF_ZERO(const BasicQuaternion<T> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicQuaternion<T>::zero(), tolerance));
    }

    /** @name Global Functions
     * 
     *  @relates BasicQuaternion
     * 
     *  @{
     */
    /** Calculates the dot product of two Quaternions
     *  
     *  @note In this case, the Quaternions are just treated as
     *        separate 4-tuples and the dot product of those are
     *        calculated.
     */
    friend constexpr T dot(const BasicQuaternion<T> &left, const BasicQuaternion<T> &right)
    {
        return left.w() * right.w() +
               left.i() * right.i() +
               left.j() * right.j() +
               left.k() * right.k();
    }

    friend constexpr T dot_normalized(const BasicQuaternion<T> &left, const BasicQuaternion<T> &right)
    {
        return ( left.w() * right.w() +
                 left.i() * right.i() +
                 left.j() * right.j() +
                 left.k() * right.k()) / (left.magnitude() * right.magnitude()
               );
    }

    /** Rotates the encoded point using the given rotation
     *  
     *  @param rotation      The input rotation
     *  @param encoded_point The input point to be rotated
     *  
     *  @return The passively rotated encoded point
     *  
     *  @pre  @p rotation is a unit BasicQuaternion.
     *        @p encoded_point is a pure Auaternion.
     *  @post The output is a pure BasicQuaternion
     *  
     *  @note This is a passive rotation, meaning that the coordinate system is
     *        rotated with respect to the point.
     *        This is also known as a local rotation.
     */
    friend constexpr BasicQuaternion<T> passively_rotate_encoded_point(const BasicQuaternion<T> &rotation, const BasicQuaternion<T> &encoded_point)
    {
        assert( rotation.isUnit() );
        assert( encoded_point.isPure() );

        return rotation * encoded_point * rotation.conjugate();
    }

    /**
     *  
     *  @see passively_rotate_encoded_point
     */
    friend constexpr BasicQuaternion<T> locally_rotate_encoded_point(const BasicQuaternion<T> &rotation, const BasicQuaternion<T> &encoded_point)
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
     *  @pre  @p rotation is a unit BasicQuaternion.
     *        @p encoded_point is a pure BasicQuaternion.
     *  @post The output is a pure BasicQuaternion
     *  
     *  @note This is an active rotation, meaning that the point is rotated with
     *        respect to the coordinate system.
     *        This is also known as a global rotation.
     */
    friend constexpr BasicQuaternion<T> actively_rotate_encoded_point(const BasicQuaternion<T> &rotation, const BasicQuaternion<T> &encoded_point)
    {
        assert( rotation.isUnit() );
        assert( encoded_point.isPure() );

        return rotation.conjugate() * encoded_point * rotation;
    }

    /**
     *  
     *  @see actively_rotate_encoded_point
     */
    friend constexpr BasicQuaternion<T> globally_rotate_encoded_point(const BasicQuaternion<T> &rotation, const BasicQuaternion<T> &encoded_point)
    {
        return actively_rotate_encoded_point(rotation, encoded_point);
    }

    /** Performs a concatenation of two rotations
     *  
     *  @param rotation_1 The first rotation to perform
     *  @param rotation_2 The second rotation to perform
     */
    friend constexpr BasicQuaternion<T> compose_rotations(const BasicQuaternion<T> &rotation_1, const BasicQuaternion<T> &rotation_2)
    {
        return rotation_2 * rotation_1;
    }

    /** Creates the normalized form of a Quaternion
     *  
     *  @param input The Quaternion to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr BasicQuaternion<T> normalized(const BasicQuaternion<T> &input)
    {
        return input.normalized();
    }

    /** Computes the phase-angle (in radians of a Quaternion)
     *
     *  @note This is meant to mirror the behavior of std::arg( std::complex )
     */
    friend constexpr T arg(const BasicQuaternion<T> &input)
    {
        return input.angle().value();
    }

    /** Constructs a unit Quaternion from the given axis and angle
     *
     *  @note This is meant to mirror the behavior of the std::complex version of std::polar()
     */
    friend constexpr BasicQuaternion<T> polar(const BasicVector3D<T> &axis, const BasicRadian<T> angle = BasicRadian<T>{})
    {
        assert( axis.magnitude() == T{1} );

        return BasicQuaternion<T>::make_rotation( angle, axis );
    }

    /** Sums up the components of @p input
     *  
     *  @param input The BasicQuaternion to operate on
     * 
     *  @return The sum of all the components
     */
    friend constexpr T accumulate(const BasicQuaternion<T> &input)
    {
        return T{input.real() + input.i() + input.j() + input.k()};
    }

    /** Calculates the Spherical Linear Interpolation betwee two Quaternions
     * 
     *  @param begin   Origin value
     *  @param end     Destination value
     *  @param percent [0..1] Represents the percentage to interpolate
     */
    friend constexpr BasicQuaternion<T> slerp(const BasicQuaternion<T> &begin, const BasicQuaternion<T> &end, T percent)
    {
        BasicQuaternion<T> combined{ begin.conjugate() * end };

        return begin * combined.pow(percent);
    }

    friend std::string format(const BasicQuaternion<T> &input)
    {
        return std::format("[w: {}, i: {}, j: {}, k: {}]", input.w(), input.i(), input.j(), input.k());
    }

    /**  Computes the conjugate of the input
     * 
     *   @note This will just call @c input.conjugate()
     */
    friend constexpr BasicQuaternion<T> conjugate(const BasicQuaternion<T> &input)
    {
        return input.conjugate();
    }

    /**  Computes the log of the input
     * 
     *   @note This will just call @c input.log()
     */
    friend constexpr BasicQuaternion<T> log(const BasicQuaternion<T> &input)
    {
        return input.log();
    }

    /**  Computes the exponential of the input
     * 
     *   @note This will just call @c input.exp()
     */
    friend BasicQuaternion<T> exp(const BasicQuaternion<T> &input)
    {
        return input.exp();
    }
    /// @} {GlobalFunctions}
};


/** @defgroup QuaternionAliases Quaternion Types
 * 
 *  Here are the type aliases for Quaternions
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicQuaternion
 *  @{
 */
using Quaternionf  = BasicQuaternion<float>;
using Quaterniond  = BasicQuaternion<double>;
using Quaternion   = BasicQuaternion<double>;
using Quaternionld = BasicQuaternion<long double>;
/// @}
/// @}  {QuaternionAliases}

}