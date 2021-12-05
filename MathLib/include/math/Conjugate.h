#pragma once


template<class T>
constexpr T conjugate(T input)
{
    return input.conjugate();
}

// Base cases
template<>
constexpr float conjugate<float>(float input)
{
    return input;
}

template<>
constexpr double conjugate<double>(double input)
{
    return input;
}

template<>
constexpr long double conjugate<long double>(long double input)
{
    return input;
}

