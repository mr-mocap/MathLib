#pragma once

#include <tuple>
#include <array>


namespace Generic
{

template <typename T, std::size_t Count>
struct VecArray : public std::array<T, Count>
{
};

template <typename T>
struct XY
{
    T x;
    T y;
};

template <typename T>
struct XYZ
{
    T x;
    T y;
    T z;
};

template <typename T>
struct RGB
{
    T r;
    T g;
    T b;
};

template <typename T>
struct RGBA
{
    T r;
    T g;
    T b;
    T a;
};

template <typename T>
struct UV
{
    T u;
    T v;
};

template <typename T, std::size_t Count, std::size_t ... Indices>
VecArray<T, Count> swizzle(const VecArray<T, Count> &input)
{
    return VecArray<T, Count>( { input[Indices]... } );
}

}