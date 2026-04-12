#pragma once

#include <Math/math/Functions.hpp>
#include <Math/math/Vector2D.hpp>
#include <Math/math/Angle.hpp>
#include <cassert>
#include <cmath>
#include <concepts>
#include <type_traits>

/** @file
 *  
 *  Contains the definition of the BasicComplex class along with
 *  various helper functions
 *
 *  @hideincludegraph
 */

namespace Math
{

/** A mathematical complex number
 *  
 *  @note A complex number is a 2-dimensional object that extends the real number system.
 *        It is commonly used in various fields of mathematics and engineering.
 *
 *  @headerfile <> <math/Complex.hpp>
 */
template <class T>
class BasicComplex
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
    constexpr BasicComplex() = default;
    constexpr BasicComplex(T real_number) : _real(real_number) { } ///< Constructs a BasicComplex equivalent to the given real number
    constexpr BasicComplex(T real_part, T imaginary_part) : _real(real_part), _imaginary(imaginary_part) { }
    /// @}

    /** @name Constants
     *  @{
     */
    /// BasicComplex representation of the real number 1
    constexpr static BasicComplex<T> identity() { return BasicComplex{ T{1}, T{} }; }

    /// BasicComplex representation of the real number 0
    constexpr static BasicComplex<T> zero() { return BasicComplex{}; }
    constexpr static BasicComplex<T> unit_real() { return identity(); }
    constexpr static BasicComplex<T> unit_i() { return BasicComplex{ T{}, T{1} }; }
    /// @}

    constexpr BasicComplex<T> conjugate() const
    {
        if constexpr (std::is_floating_point_v<T>)
            return BasicComplex<T>{ _real, -_imaginary };
        else
            return BasicComplex<T>{ _real, conjugate(_imaginary) };
    }

    /// Computes this BasicComplex raised to a real power
    BasicComplex<T> pow(T exponent) const
    {
        assert( isUnit() );

        T magnitude{ imaginary() };

        // Are we a purely real number?
        if ( approximately_equal_to(magnitude, T{0.0}) )
        {
            // It is an error for real() to be finite & negative when the exponent is not an integer!
            return BasicComplex{ std::pow( real(), exponent ) }; // Yes, so only compute the real part
        }

        // Calculate the angle
        T theta{ std::atan2(magnitude, real()) };
        T new_theta{ exponent * theta };
        T coefficient{ std::sin(new_theta) / magnitude };

        // NOW we can calculate to the power of "exponent"...
        T temp{ real() * real() + magnitude * magnitude };

        return BasicComplex<T>{ std::cos(new_theta), coefficient * i() } * std::pow(temp, exponent);
    }

    /** Computes the exponential form of this BasicComplex
     *
     *  @note It is possible for this routine to output a non-unit BasicComplex
     *        when given a unit BasicComplex as input.  It is for this reason that
     *        the implementation of log() has been adjusted to automatically handle
     *        non-unit Quaternions.
     */
    BasicComplex<T> exp() const
    {
        T e_to_the_w{ std::exp( real() ) };
        T vector_part_magnitude{ imaginary() };
        T cos_v{ std::cos(vector_part_magnitude) };
        T sin_v{ (vector_part_magnitude > T{0.0}) ? std::sin(vector_part_magnitude) / vector_part_magnitude : T{0.0} };

        return BasicComplex{ cos_v, sin_v * i() } * e_to_the_w;
    }

    /** Computes the log base e of this BasicComplex
     *  
     *  @note We handle non-unit Quaternions in this version so that we can satisfy the relationship:
     *        log( exp( x ) ) == x
     */
    BasicComplex<T> log() const
    {
        T magnitude_of_imaginary_part{ imaginary() };

        // Are we purely a real number?
        if ( approximately_equal_to(magnitude_of_imaginary_part, T{0.0}) )
            return BasicComplex{ std::log( real() ) }; // YES, so just set the real() component (the others will be zero)

        T this_norm{ norm() };
        T theta{ std::acos( real() / this_norm ) };
        T coefficient{ theta / magnitude_of_imaginary_part };

        return BasicComplex{ std::log(this_norm), coefficient * i() };
    }

    T    normSquared() const { return accumulate(*this * conjugate()); }
    T    norm() const { return std::sqrt( normSquared() ); }

    T    magnitudeSquared() const { return normSquared(); }
    T    magnitude() const { return norm(); }

    constexpr BasicComplex<T> normalized() const
    {
        assert( BasicComplex<T>{*this / magnitude()}.isUnit() ); // Verify that we actually return a unit-length BasicComplex

        return *this / this->magnitude();
    }

    BasicComplex<T> inverse() const { return conjugate() / normSquared(); }

    BasicRadian<T> angle() const
    {
        return T( std::atan2( imaginary().magnitude(), real() ) );
    }

    /** @name Element Access
     *  @{
     */
    constexpr const T &real() const { return _real; }

    constexpr const T &i() const { return _imaginary; }

    /// Extracts the imaginary part of a BasicComplex
    constexpr const T &imaginary() const { return _imaginary; }
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
            return std::isnan(_real) || std::isnan(_imaginary);
        else
            return _real.isNaN() || _imaginary.isNaN();
    }
    bool isInf() const
    {
        if constexpr ( std::is_floating_point_v<T> )
            return std::isinf(_real) || std::isinf(_imaginary);
        else
            return _real.isInf() || _imaginary.isInf();
    }
    /// @}

    /** @name Convenience Creation Functions
     *  @{
     */
    /** Construct a pure BasicComplex
     *  
     *  @param i The value to set the imaginary component to
     * 
     *  @post output.real() == 0
     *  @post output.imaginary() == @p i
     *
     *  @note A pure BasicComplex is one in which the real component
     *        is 0.
     */
    constexpr static BasicComplex<T> make_pure(T i) { return BasicComplex<T>{ T{}, i }; }

    constexpr static BasicComplex<T> encode_point(T x, T y) { return BasicComplex<T>{ x, y }; }

    /** Enocde a rotation into a BasicComplex
     *  
     *  @param radians The amount of rotation to apply (in radians)
     * 
     *  @note This ends up being like polar(), but we assume the magnitude is 1,
     *        so we don't take that as an input and we don't compute it in the output.
     */
    constexpr static BasicComplex<T> make_rotation(BasicRadian<T> radians)
    {
        return { std::cos( radians.value() ), std::sin( radians.value() ) };
    }
    /// @}

private:
    T _real{};
    T _imaginary{};

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
    friend constexpr bool operator ==(const BasicComplex<T> &left, const BasicComplex<T> &right)
    {
        return approximately_equal_to(left, right);
    }
    /// @}

    /** @addtogroup Equality
     * 
     *  @relates BasicComplex
     * 
     *  @{
     * 
     *  Compares two BasicComplex inputs equal, component-wise, to within a tolerance
     *  
     *  @param value_to_test
     *  @param value_it_should_be 
     *  @param tolerance          How close they should be to be considered equal
     *  
     *  @return @c true if they are equal
     * 
     *  @see Equality
     */
    template <std::floating_point OT = T>
        requires std::is_floating_point_v<T>
    friend constexpr bool approximately_equal_to(const BasicComplex<T> &value_to_test,
                                                 const BasicComplex<T> &value_it_should_be,
                                                       OT               tolerance = OT{0.0002})
    {
        return approximately_equal_to(value_to_test.real(),      value_it_should_be.real(),      tolerance) &&
               approximately_equal_to(value_to_test.imaginary(), value_it_should_be.imaginary(), tolerance);
    }
    /// @}  {Equality}

    /** @addtogroup ComplexAlgebra Complex Algebra
     *  @{
     */

    /** @name Operators
     * 
     *  @relates BasicComplex
     * 
     *  @{
     */
    friend constexpr BasicComplex<T> operator *(const BasicComplex<T> &left, const BasicComplex<T> &right)
    {
        return { left.real() * right.real() - left.imaginary() * right.imaginary(),
                 left.real() * right.imaginary() + left.imaginary() * right.real() };
    }

    template <std::floating_point OT>
    friend constexpr BasicComplex<T> operator *(const BasicComplex<T> &complex, OT scalar)
    {
        return { complex.real() * T(scalar), complex.imaginary() * T(scalar) };
    }

    friend constexpr BasicComplex<T> operator /(const BasicComplex<T> &left, const BasicComplex<T> &right)
    {
        return left * right.inverse();
    }

    template <std::floating_point OT>
    friend constexpr BasicComplex<T> operator /(const BasicComplex<T> &complex, OT scalar)
    {
        return { complex.real()      / T(scalar),
                 complex.imaginary() / T(scalar) };
    }

    friend constexpr BasicComplex<T> operator +(const BasicComplex<T> &left, const BasicComplex<T> &right)
    {
        return { left.real()      + right.real(),
                 left.imaginary() + right.imaginary() };
    }

    template <std::floating_point OT>
    friend constexpr BasicComplex<T> operator +(const BasicComplex<T> &complex, OT scalar)
    {
        return { complex.real() + scalar, complex.imaginary() };
    }

    friend constexpr BasicComplex<T> operator -(const BasicComplex<T> &left, const BasicComplex<T> &right)
    {
        return { left.real()      - right.real(),
                 left.imaginary() - right.imaginary() };
    }

    template <std::floating_point OT>
    friend constexpr BasicComplex<T> operator -(const BasicComplex<T> &complex, OT scalar)
    {
        return { complex.real() - scalar, complex.imaginary() };
    }

    friend constexpr BasicComplex<T> operator -(const BasicComplex<T> &q)
    {
        return { -q.real(), -q.imaginary() };
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
    template <std::floating_point OT = T>
        requires std::is_floating_point_v<T>
    friend bool check_if_equal(const BasicComplex<T> &input,
                               const BasicComplex<T> &near_to,
                                     OT               tolerance = OT{0.0002})
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
    template <std::floating_point OT = T>
        requires std::is_floating_point_v<T>
    friend bool check_if_not_equal(const BasicComplex<T> &input,
                                   const BasicComplex<T> &near_to,
                                         OT               tolerance = OT{0.0002})
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
    template <std::floating_point OT = T>
        requires std::is_floating_point_v<T>
    friend void CHECK_IF_EQUAL(const BasicComplex<T> &input,
                               const BasicComplex<T> &near_to,
                                     OT               tolerance = OT{0.0002})
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
    template <std::floating_point OT = T>
        requires std::is_floating_point_v<T>
    friend void CHECK_IF_NOT_EQUAL(const BasicComplex<T> &input,
                                   const BasicComplex<T> &near_to,
                                         OT               tolerance = OT{0.0002})
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
    template <std::floating_point OT = T>
        requires std::is_floating_point_v<T>
    friend void CHECK_IF_ZERO(const BasicComplex<T> &input, OT tolerance = OT{0.0002})
    {
        assert( check_if_equal(input, BasicComplex<T>::zero(), tolerance));
    }

    /** @name Global Functions
     * 
     *  @relates BasicComplex
     * 
     *  @{
     */
    /** Calculates the dot product of two Quaternions
     *  
     *  @note In this case, the Quaternions are just treated as
     *        separate 4-tuples and the dot product of those are
     *        calculated.
     */
    friend constexpr T dot(const BasicComplex<T> &left, const BasicComplex<T> &right)
    {
        return left.real()      * right.real() +
               left.imaginary() * right.imaginary();
    }

    friend constexpr T dot_normalized(const BasicComplex<T> &left, const BasicComplex<T> &right)
    {
        return ( left.real()      * right.real() +
                 left.imaginary() * right.imaginary() ) / (left.magnitude() * right.magnitude());
    }

    /** Rotates the encoded point using the given rotation
     *  
     *  @param rotation      The input rotation
     *  @param encoded_point The input point to be rotated
     *  
     *  @return The passively rotated encoded point
     *  
     *  @pre  @p rotation is a unit BasicComplex.
     *        @p encoded_point is an encoded_point
     *  @post The output is a pure BasicComplex
     *  
     *  @note This is a passive rotation, meaning that the coordinate system is
     *        rotated with respect to the point.
     *        This is also known as a local rotation.
     */
    friend constexpr BasicComplex<T> passively_rotate_encoded_point(const BasicComplex<T> &rotation,
                                                                    const BasicComplex<T> &encoded_point)
    {
        assert( rotation.isUnit() );

        return rotation * encoded_point;
    }

    /** Performs a concatenation of two rotations
     *  
     *  @param rotation_1 The first rotation to perform
     *  @param rotation_2 The second rotation to perform
     */
    friend constexpr BasicComplex<T> compose_rotations(const BasicComplex<T> &rotation_1,
                                                       const BasicComplex<T> &rotation_2)
    {
        return rotation_2 * rotation_1;
    }

    /** Creates the normalized form of a Quaternion
     *  
     *  @param input The Quaternion to normalize
     *  
     *  @return The normalized version of @p input
     */
    friend constexpr BasicComplex<T> normalized(const BasicComplex<T> &input)
    {
        return input.normalized();
    }

    /** Computes the phase-angle (in radians of a Complex)
     *
     *  @note This is meant to mirror the behavior of std::arg( std::complex )
     */
    friend constexpr T arg(const BasicComplex<T> &input)
    {
        return input.angle().value();
    }

    /** Constructs a unit Complex from the given axis and angle
     *
     *  @param r     The magnitude of the Complex to create
     *  @param angle The amount of rotation to apply (in radians)
     * 
     *  @note This is meant to mirror the behavior of the std::complex version of std::polar()
     */
    friend constexpr BasicComplex<T> polar(T r, BasicRadian<T> angle = BasicRadian<T>{})
    {
        return r * BasicComplex<T>::make_rotation( angle );
    }

    /** Sums up the components of @p input
     *  
     *  @param input The BasicComplex to operate on
     * 
     *  @return The sum of all the components
     */
    friend constexpr T accumulate(const BasicComplex<T> &input)
    {
        return T{input.real() + input.i()};
    }

    /** Calculates the Spherical Linear Interpolation betwee two Complex numbers
     * 
     *  @param begin   Origin value
     *  @param end     Destination value
     *  @param percent [0..1] Represents the percentage to interpolate
     */
    friend constexpr BasicComplex<T> slerp(const BasicComplex<T> &begin,
                                           const BasicComplex<T> &end,
                                                 T                percent)
    {
        BasicComplex<T> combined{ begin.conjugate() * end };
        BasicComplex<T> powered{ combined.pow(percent) };
        BasicComplex<T> result{ begin * powered };

        return result;
    }

    friend std::string format(const BasicComplex<T> &input)
    {
        return std::format("[real: {}, i: {}]", input.real(), input.i() );
    }

    /**  Computes the conjugate of the input
     * 
     *   @note This will just call @c input.conjugate()
     */
    friend constexpr BasicComplex<T> conjugate(const BasicComplex<T> &input)
    {
        return input.conjugate();
    }

    /**  Computes the log of the input
     * 
     *   @note This will just call @c input.log()
     */
    friend constexpr BasicComplex<T> log(const BasicComplex<T> &input)
    {
        return input.log();
    }

    /**  Computes the exponential of the input
     * 
     *   @note This will just call @c input.exp()
     */
    friend BasicComplex<T> exp(const BasicComplex<T> &input)
    {
        return input.exp();
    }
    /// @} {GlobalFunctions}
};

/** @defgroup ComplexAliases Complex Types
 * 
 *  Here are the type aliases for Complex
 * 
 *  @ingroup TypeAliases
 *  @{
 */
/** @name Type Aliases
 * 
 *  @relates BasicComplex
 *  @{
 */
using Complexf = BasicComplex<float>;
using Complexd = BasicComplex<double>;
using Complex  = BasicComplex<double>;
using Complexl = BasicComplex<long double>;
/// @}
/// @}  {ComplexAliases}

}