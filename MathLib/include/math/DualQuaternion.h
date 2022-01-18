#pragma once

#include "math/Dual.h"
#include "math/Quaternion.h"
#include <cassert>


template<class T>
using DualQuaternion = Dual<Quaternion<T>>;


template<class T>
constexpr DualQuaternion<T> make_dualquaternion_rotation(T radians, triple<T> axis)
{
    // A pure rotation has the dual part set to zero.
    return DualQuaternion<T>{ make_quaternion_rotation(radians, axis), Quaternion<T>::zero() };
}

template<class T>
constexpr DualQuaternion<T> make_dualquaternion_translation(triple<T> translation)
{
    // A pure translation has the real part set to identity.

    return DualQuaternion<T>{ Quaternion<T>::unit(),
                              make_pure_quaternion( std::tuple<T, T, T>{ std::get<0>(translation) / T(2),
                                                                         std::get<1>(translation) / T(2),
                                                                         std::get<2>(translation) / T(2) } )
                            };
}

template<class T>
constexpr DualQuaternion<T> make_coordinate_system(Quaternion<T> rotation, triple<T> translation)
{
    // assert( rotation.isUnit() );

    return DualQuaternion<T>{ rotation, make_pure_quaternion(translation) / T(2) * rotation };
}

template<class T>
constexpr DualQuaternion<T> dualquaternion_conjugate(DualQuaternion<T> q)
{
    return DualQuaternion<T>{ conjugate(q.real), conjugate(q.dual) };
}

template<class T>
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

template<class T>
constexpr DualQuaternion<T> operator *(DualQuaternion<T> dual_quaternion, Dual<T> dual_scalar)
{
    return dual_quaternion * DualQuaternion<T>{ Quaternion<T>{dual_scalar.real, 0, 0, 0}, Quaternion<T>{dual_scalar.dual, 0, 0, 0} };
}

template<class T>
constexpr DualQuaternion<T> operator /(DualQuaternion<T> dual_quaternion, Dual<T> dual_scalar)
{
    return DualQuaternion<T>{ (dual_quaternion * conjugate(dual_scalar)) / dualscalar_normsquared(dual_scalar) };
}

template<class T>
constexpr Dual<T> dualquaternion_norm(DualQuaternion<T> d)
{
    return dualscalar_sqrt( dualquaternion_normsquared(d) );
}

template<class T>
constexpr Dual<T> dualquaternion_magnitude(DualQuaternion<T> d)
{
    return dualquaternion_norm(d);
}

template<class T>
constexpr DualQuaternion<T> normalized(DualQuaternion<T> d)
{
    return d / dualquaternion_norm(d);
}

template<class T>
constexpr bool unit_dualquaternion_rotation_magnitude_is_one(DualQuaternion<T> d)
{
    return approximately_equal_to( dot(d.real, d.real), 1 );
}

template<class T>
constexpr bool unit_dualquaternion_rotation_and_translation_are_orthogonal(DualQuaternion<T> d)
{
    return approximately_equal_to( dot(d.real, d.dual), 0);
}

template<class T>
constexpr bool is_unit(DualQuaternion<T> d)
{
    return unit_dualquaternion_rotation_magnitude_is_one(d) && unit_dualquaternion_rotation_and_translation_are_orthogonal(d);
}

using DualQuaternionf = DualQuaternion<float>;
using DualQuaterniond = DualQuaternion<double>;
using DualQuaternionld = DualQuaternion<long double>;
