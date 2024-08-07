#pragma once


template <class Type>
struct Vector2D
{
    Type x{};
    Type y{};
};

template <class Type>
struct Vector3D
{
    Type x{};
    Type y{};
    Type z{};
};


using Vector2Df = Vector2D<float>;
using Vector2Dd = Vector2D<double>;
using Vector2Dld = Vector2D<long double>;

using Vector3Df = Vector3D<float>;
using Vector3Dd = Vector3D<double>;
using Vector3Dld = Vector3D<long double>;