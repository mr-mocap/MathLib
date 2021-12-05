#pragma once
#include <cmath>


inline bool approximately_equal_to(float input, float near_to, float tolerance)
{
    return std::abs(near_to - input) <= tolerance;
}

inline bool approximately_equal_to(double input, double near_to, double tolerance)
{
    return std::abs(near_to - input) <= tolerance;
}

inline bool approximately_equal_to(long double input, long double near_to, long double tolerance)
{
    return std::abs(near_to - input) <= tolerance;
}
