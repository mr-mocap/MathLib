#pragma once

#include "math/ApproximatelyEqualTo.h"
#include "math/Conjugate.h"
#include <tuple>


template<class T>
class Dual
{
public:
    using value_type = T;

    Dual() = default;
    explicit constexpr Dual(const value_type r) : real(r) { }
    explicit constexpr Dual(const value_type r, const value_type e) : real(r), dual(e) { }
    explicit constexpr Dual(const std::tuple<value_type, value_type> tuple) : real(std::get<0>(tuple)), dual(std::get<1>(tuple)) { }

    constexpr static Dual<T> unit() { return Dual{ T{1}, T{} }; }
    constexpr static Dual<T> zero() { return Dual{}; }

    constexpr Dual<T> conjugate(Dual<T> d) { return Dual{ conjugate(d.real), conjugate(d.dual) }; }

    friend constexpr bool approximately_equal_to(Dual<T> value_to_test, Dual<T> value_it_should_be, T tolerance)
    {
        return approximately_equal_to(value_to_test.real, value_it_should_be.real, tolerance) &&
               approximately_equal_to(value_to_test.dual, value_it_should_be.dual, tolerance);
    }

    value_type real{};
    value_type dual{};
};

template<class T>
constexpr Dual<T> operator *(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real * right.real,
                   left.real * right.dual + left.dual * right.real);
}

template<class T>
constexpr Dual<T> operator *(float scalar, Dual<T> d)
{
    return Dual<T>(scalar * d.real, scalar * d.dual);
}

template<class T>
constexpr Dual<T> operator *(double scalar, Dual<T> d)
{
    return Dual<T>(scalar * d.real, scalar * d.dual);
}

template<class T>
constexpr Dual<T> operator /(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real * right.real / (right.real * right.real),
                  (right.real * left.dual - left.real * right.dual) / (right.real * right.real));
}

template<class T>
constexpr Dual<T> operator /(float scalar, Dual<T> d)
{
    return Dual<T>(scalar / d.real, scalar / d.dual);
}

template<class T>
constexpr Dual<T> operator /(double scalar, Dual<T> d)
{
    return Dual<T>(scalar / d.real, scalar / d.dual);
}

template<class T>
constexpr Dual<T> operator +(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real + right.real, left.dual + right.dual);
}

template<class T>
constexpr Dual<T> operator +(float scalar, Dual<T> d)
{
    return Dual<T>(scalar + d.real, scalar + d.dual);
}

template<class T>
constexpr Dual<T> operator +(double scalar, Dual<T> d)
{
    return Dual<T>(scalar + d.real, scalar + d.dual);
}

template<class T>
constexpr Dual<T> operator -(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real - right.real, left.dual - right.dual);
}

template<class T>
constexpr Dual<T> operator -(float scalar, Dual<T> d)
{
    return Dual<T>(scalar - d.real, scalar - d.dual);
}

template<class T>
constexpr Dual<T> operator -(double scalar, Dual<T> d)
{
    return Dual<T>(scalar - d.real, scalar - d.dual);
}

template<class T>
constexpr T dot(Dual<T> left, Dual<T> right)
{
    return left.real * right.real +
           left.dual * right.dual;
}

template<class T>
constexpr Dual<T> make_pure_dual(T input)
{
    return Dual<T>{ T{}, input };
}

using Dualf = Dual<float>;
using Duald = Dual<double>;
using Dualld = Dual<long double>;
