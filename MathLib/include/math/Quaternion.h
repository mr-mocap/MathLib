#pragma once

#include "math/ApproximatelyEqualTo.h"
#include "math/Conjugate.h"
#include "math/types.h"


template<class T>
class Quaternion
{
public:
    using value_type = T;

    Quaternion() = default;
    explicit constexpr Quaternion(value_type real_number) : _w(real_number) { }
    explicit constexpr Quaternion(value_type w, value_type i, value_type j, value_type k) : _w(w), _i(i), _j(j), _k(k) { }

    constexpr static Quaternion<T> unit() { return Quaternion{ T{1}, T{}, T{}, T{} }; }
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

    constexpr triple<value_type> imaginary() { return { _i, _j, _k }; }

    bool isUnit() const { return approximately_equal_to( accumulate(*this), accumulate(unit()) ); }
    bool isZero() const { return approximately_equal_to( accumulate(*this), accumulate(zero()) ); }

protected:
    value_type _w{};
    value_type _i{};
    value_type _j{};
    value_type _k{};
};

template<class T>
constexpr bool approximately_equal_to(Quaternion<T> value_to_test, Quaternion<T> value_it_should_be, float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.w(), value_it_should_be.w(), tolerance) &&
           approximately_equal_to(value_to_test.i(), value_it_should_be.i(), tolerance) &&
           approximately_equal_to(value_to_test.j(), value_it_should_be.j(), tolerance) &&
           approximately_equal_to(value_to_test.k(), value_it_should_be.k(), tolerance);
}

template<class T>
constexpr Quaternion<T> operator *(Quaternion<T> quaternion, T scalar)
{
    return Quaternion<T>{ quaternion.w() * scalar, quaternion.i() * scalar, quaternion.j() * scalar, quaternion.k() * scalar };
}

template<class T>
constexpr Quaternion<T> operator *(T scalar, Quaternion<T> quaternion)
{
    return Quaternion<T>{ scalar * quaternion.w(), scalar * quaternion.i(), scalar * quaternion.j(), scalar * quaternion.k()};
}

template<class T>
constexpr Quaternion<T> operator /(Quaternion<T> quaternion, T scalar)
{
    return Quaternion<T>{ quaternion.w() / scalar, quaternion.i() / scalar, quaternion.j() / scalar, quaternion.k() / scalar };
}

template<class T>
constexpr Quaternion<T> operator /(T scalar, Quaternion<T> quaternion)
{
    return Quaternion<T>{ scalar / quaternion.w(), scalar / quaternion.i(), scalar / quaternion.j(), scalar / quaternion.k() };
}

template<class T>
constexpr Quaternion<T> operator /(Quaternion<T> left, Quaternion<T> right)
{
    return left * right.inverse();
}

template<class T>
constexpr Quaternion<T> operator +(Quaternion<T> left, Quaternion<T> right)
{
    return Quaternion<T>{left.w() + right.w(),
                         left.i() + right.i(),
                         left.j() + right.j(),
                         left.k() + right.k()};
}

template<class T>
constexpr Quaternion<T> operator -(Quaternion<T> left, Quaternion<T> right)
{
    return Quaternion<T>{left.w() - right.w(),
                         left.i() - right.i(),
                         left.j() - right.j(),
                         left.k() - right.k()};
}

template<class T>
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

template<class T>
constexpr bool operator ==(Quaternion<T> left, Quaternion<T> right)
{
    return approximately_equal_to(left, right);
}

template<class T>
constexpr bool operator !=(Quaternion<T> left, Quaternion<T> right)
{
    return !(left == right);
}

template<class T>
constexpr Quaternion<T> operator -(Quaternion<T> q)
{
    return Quaternion<T>{ -q.w(), -q.i(), -q.j(), -q.k() };
}

template<class T>
constexpr T dot(Quaternion<T> left, Quaternion<T> right)
{
    return left.w() * right.w() +
           left.i() * right.i() +
           left.j() * right.j() +
           left.k() * right.k();
}

template<class T>
constexpr Quaternion<T> make_pure_quaternion(triple<T> t)
{
    return Quaternion<T>{ T(), std::get<0>(t), std::get<1>(t), std::get<2>(t) };
}


template<class T>
constexpr Quaternion<T> make_quaternion_rotation(T radians, triple<T> axis)
{
    return Quaternion<T>{ T(cos(radians / T{2})),
                          T(sin(radians / T{2}) * std::get<0>(axis)),
                          T(sin(radians / T{2}) * std::get<1>(axis)),
                          T(sin(radians / T{2}) * std::get<2>(axis)) };

    // assert( output.isUnit() )
}

template<class T>
constexpr Quaternion<T> normalized(Quaternion<T> input)
{
    return input / input.norm();
}

template<class T>
constexpr T accumulate(Quaternion<T> input)
{
    return T{input.real() + input.i() + input.j() + input.k()};
}

using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;
using Quaternionld = Quaternion<long double>;
