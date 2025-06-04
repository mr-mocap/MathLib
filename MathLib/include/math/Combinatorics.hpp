#pragma once

#include <vector>

namespace Math
{

namespace Combinatorics
{

inline float factorial_f(float input)
{
    return std::tgammaf(input);
}

inline double factorial_d(double input)
{
    return std::tgamma(input);
}

inline long double factorial_ld(long double input)
{
    return std::tgammal(input);
}

constexpr inline int factorial_i(int input)
{
    assert( input >= 0 );

    if ((input == 0) || (input == 1))
        return 1;
    return input * factorial_i( input - 1 );
}

constexpr inline long factorial_l(long input)
{
    assert( input >= 0 );

    if ((input == 0) || (input == 1))
        return 1;
    return input * factorial_l( input - 1 );
}

constexpr inline long long factorial_ll(long long input)
{
    assert( input >= 0 );

    if ((input == 0) || (input == 1))
        return 1;
    return input * factorial_ll( input - 1 );
}

template <class Type>
constexpr inline Type factorial(Type input)
{
    if constexpr (std::is_integral<Type>::value)
    {
        if constexpr (std::is_same<Type, long long>::value)
            return factorial_ll(input);
        else if constexpr (std::is_same<Type, long>::value)
            return factorial_l(input);
        else if constexpr (std::is_same<Type, int>::value)
            return factorial_i(input);
        else
            return factorial_i(input);
    }
    else if constexpr (std::is_floating_point<Type>::value)
    {
        if constexpr (std::is_same<Type, long double>::value)
            return factorial_ld(input);
        if constexpr (std::is_same<Type, double>::value)
            return factorial_d(input);
        if constexpr (std::is_same<Type, float>::value)
            return factorial_f(input);
        else
            return factorial_f(input);
    }
    else
        static_assert(false);
}

template <class Type>
constexpr inline Type n_choose_k(Type n, Type k)
{
    assert(k >= 0);
    assert(k <= n);

    return factorial(n) / (factorial(k) * factorial(n - k));
}

constexpr inline int binomial_coefficient(int row, int column)
{
    if (column == 0) // Top of triangle AND left side
        return 1;
    else if (row == column) // Right side of triangle
        return 1;
    else
        return n_choose_k(row, column);
}

constexpr inline std::vector<int> pascal_triangle_row(int row)
{
    assert(row >= 0);

    std::vector<int> values;

    values.reserve( static_cast<size_t>(row + 1 ) );
    for (int iCurrentColumn = 0; iCurrentColumn <= row; ++iCurrentColumn)
        values.push_back( binomial_coefficient(row, iCurrentColumn) );

    return values;
}

} // Combinatorics
} // Math