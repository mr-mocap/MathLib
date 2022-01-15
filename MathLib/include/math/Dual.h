#pragma once

#include "math/ApproximatelyEqualTo.h"
#include "math/Conjugate.h"
#include "math/types.h"
#include <cassert>


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

    constexpr Dual<T> conjugate() const { return Dual{ real, ::conjugate(dual) }; }
    constexpr value_type magnitude() const { return real; }

    value_type real{};
    value_type dual{};
};

template<class T>
constexpr bool approximately_equal_to(Dual<T> value_to_test, Dual<T> value_it_should_be, float tolerance = 0.0002f)
{
    return approximately_equal_to(value_to_test.real, value_it_should_be.real, tolerance) &&
           approximately_equal_to(value_to_test.dual, value_it_should_be.dual, tolerance);
}

template<class T>
constexpr bool operator ==(Dual<T> left, Dual<T> right)
{
    return approximately_equal_to(left, right);
}

template<class T>
constexpr bool operator !=(Dual<T> left, Dual<T> right)
{
    return !(left == right);
}

template<class T>
constexpr Dual<T> operator *(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real * right.real,
                   left.real * right.dual + left.dual * right.real);
}

template<class T>
constexpr Dual<T> operator *(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) * d;
}

template<class T>
constexpr Dual<T> operator *(Dual<T> d, float scalar)
{
    return d * Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator *(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) * d;
}

template<class T>
constexpr Dual<T> operator *(Dual<T> d, double scalar)
{
    return d * Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator /(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real * right.real / (right.real * right.real),
        (left.dual * right.real - left.real * right.dual) / (right.real * right.real));
}

template<class T>
constexpr Dual<T> operator /(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) / d;
}

template<class T>
constexpr Dual<T> operator /(Dual<T> d, float scalar)
{
    return d / Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator /(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) / d;
}

template<class T>
constexpr Dual<T> operator /(Dual<T> d, double scalar)
{
    return d / Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator +(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real + right.real, left.dual + right.dual);
}

template<class T>
constexpr Dual<T> operator +(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) + d;
}

template<class T>
constexpr Dual<T> operator +(Dual<T> d, float scalar)
{
    return d + Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator +(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) + d;
}

template<class T>
constexpr Dual<T> operator +(Dual<T> d, double scalar)
{
    return d + Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator -(Dual<T> left, Dual<T> right)
{
    return Dual<T>(left.real - right.real, left.dual - right.dual);
}

template<class T>
constexpr Dual<T> operator -(float scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) - d;
}

template<class T>
constexpr Dual<T> operator -(Dual<T> d, float scalar)
{
    return d - Dual<T>( T(scalar) );
}

template<class T>
constexpr Dual<T> operator -(double scalar, Dual<T> d)
{
    return Dual<T>( T(scalar) ) - d;
}

template<class T>
constexpr Dual<T> operator -(Dual<T> d, double scalar)
{
    return d - Dual<T>( T(scalar) );
}

template<class T>
constexpr T dot(Dual<T> left, Dual<T> right)
{
    return left.real * right.real +
           left.dual * right.dual;
}

template<class T>
constexpr Dual<T> dualscalar_sqrt(Dual<T> input)
{
    // Expect that T is a scalar type (float, double, int, etc.)
    T root = std::sqrt(input.real);

    return Dual<T>{ root, input.dual / (2 * root)};
}

template<class T>
constexpr T dualscalar_normsquared(Dual<T> d)
{
    Dual<T> result = d * conjugate(d);

    assert( approximately_equal_to(result.dual, 0) );

    return result.dual;
}

template<class T>
constexpr T accumulate(Dual<T> input)
{
    return T{input.real + input.dual};
}

template<class T>
constexpr Dual<T> make_pure_dual(T input)
{
    return Dual<T>{ T{}, input };
}

using Dualf = Dual<float>;
using Duald = Dual<double>;
using Dualld = Dual<long double>;
