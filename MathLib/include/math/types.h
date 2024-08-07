#pragma once

#include <tuple>

template <class T>
using triple = std::tuple<T, T, T>;


template <class T>
constexpr triple<T> make_triple(T x, T y, T z)
{
    return std::make_tuple(x, y, z);
}
