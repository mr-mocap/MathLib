#pragma once

#include "math/Dual.h"
#include "math/Quaternion.h"


template<class T>
using DualQuaternion = Dual<Quaternion<T>>;


template<class T>
constexpr DualQuaternion<T> make_dualquaternion_rotation(T radians, std::tuple<T, T, T> axis)
{
    // A pure rotation has the dual part set to zero.
    return DualQuaternion<T>{ make_quaternion_rotation(radians, axis), Quaternion<T>::zero() };
}

template<class T>
constexpr DualQuaternion<T> make_dualquaternion_translation(std::tuple<T, T, T> translation)
{
    // A pure translation has the real part set to identity.

    return DualQuaternion<T>{ Quaternion<T>::unit(),
                              make_pure_quaternion( std::tuple<T, T, T>{ std::get<0>(translation) / T{2},
                                                                         std::get<1>(translation) / T{2},
                                                                         std::get<2>(translation) / T{2} } )
                            };
}

template<class T>
constexpr DualQuaternion<T> make_coordinate_system(Quaternion<T> rotation, std::tuple<T, T, T> translation)
{
    // assert( rotation.isUnit() );

    return DualQuaternion<T>{ rotation, make_pure_quaternion( std::get<0>(translation) / T{2},
                                                              std::get<1>(translation) / T{2},
                                                              std::get<2>(translation) / T{2} ) * rotation };
}

using DualQuaternionf = DualQuaternion<float>;
using DualQuaterniond = DualQuaternion<double>;
using DualQuaternionld = DualQuaternion<long double>;
