#pragma once

#include <math/ApproximatelyEqualTo.hpp>
#include <math/Conversions.hpp>
#include <math/Trigonometric.hpp>
#include <math/Checks.hpp>
#include <math/Combinatorics.hpp>
#include <algorithm>

/** @file
 *  
 *  @hideincludegraph
 */


namespace Math
{

/** Linear interpolate a value from a lower bound to an upper bound
 * 
 *  @param input_lower_bound      The lower bound
 *  @param input_upper_bound      The upper bound
 *  @param percentage_zero_to_one The percentage along the interpolation
 */
template <class Type>
constexpr inline Type lerp(Type input_lower_bound, Type input_upper_bound, float percentage_zero_to_one)
{
    // C++ 20 has std::lerp() in <cmath>, so use that by default
    if constexpr (std::is_floating_point<Type>::value)
        return std::lerp(input_lower_bound, input_upper_bound, percentage_zero_to_one);
    else
        return (input_upper_bound - input_lower_bound) * percentage_zero_to_one + input_lower_bound;
}

/** Linear interpolate a value from a lower bound to an upper bound
 * 
 *  @param input_lower_bound      The lower bound
 *  @param input_upper_bound      The upper bound
 *  @param percentage_zero_to_one The percentage along the interpolation
 * 
 *  @note This is identical to the @c lerp function.
 * 
 *  @see lerp
 */
template <class Type>
constexpr inline Type mix(Type input_lower_bound, Type input_upper_bound, float percentage_zero_to_one)
{
    return Math::lerp(input_lower_bound, input_upper_bound, percentage_zero_to_one);
}

/** Produces the percentage of interpolation of a value within a range
 *   
 *  @param input_lower_bound  The lower bound
 *  @param input_upper_bound  The upper bound
 *   @param value_between     A value that you want to find the percentage interpolation of
 * 
 *   @return The percentage of @c value_between between @c input_lower_bound and @c input_upper_bound
 */
template <class Type>
constexpr inline Type inverse_lerp(Type input_lower_bound, Type input_upper_bound, Type value_between)
{
    return (value_between - input_lower_bound) / (input_upper_bound - input_lower_bound);
}

/** Map an input value within a range to a new range
 *   
 *  This will give you the @c input_value adjusted to within a
 *  new range of values, keeping the percentage of the @c input_value
 *  within the original range in the new range.
 *  
 *  @param input_value    The input value
 *  @param orig_range_min The original range's minimum value
 *  @param orig_range_max The original range's maximum value
 *  @param new_range_min  The new range's minimum value
 *  @param new_range_max  The new range's minimum value
 * 
 *  @return The @c input value mapped to a the new range
 */
template <class Type>
constexpr inline Type remap(Type input_value, Type orig_range_min, Type orig_range_max, Type new_range_min, Type new_range_max)
{
    return lerp(new_range_min, new_range_max, inverse_lerp(orig_range_min, orig_range_max, input_value));
}

/** Saturate a value to within a range
 * 
 *  @param value       The value to saturate
 *  @param lower_bound The minimum value to clamp to
 *  @param upper_bound The maximum value to clamp to
 * 
 *  @return The @c value clamped to within the given bounds
 */
template <class Type>
constexpr inline const Type &saturate(const Type &value, const Type &lower_bound, const Type &upper_bound)
{
    return std::clamp( value, lower_bound, upper_bound );
}

template <class Type>
constexpr inline Type step(Type y, Type x)
{
    return (x >= y) ? 1 : 0;
}

constexpr inline float smoothstep(float input_value, float left_edge = 0.0f, float right_edge = 1.0f)
{
    // Scale and clamp to 0..1 range
    input_value = std::clamp<float>((input_value - left_edge) / (right_edge - left_edge), 0.0f, 1.0f);

    return input_value * input_value * (3.0f - 2.0f * input_value);
}

// Second-order smoothstep function
template <class Type>
constexpr inline Type smootherstep(Type input_value, Type left_edge, Type right_edge)
{
    // Scale and clamp to 0..1 range
    input_value = std::clamp((input_value - left_edge) / (right_edge - left_edge), Type{0}, Type{1});
    if constexpr (std::is_same<Type, float>::value)
        return input_value * input_value * input_value * (input_value * (6.0f * input_value - 15.0f) + 10.0f);
    else
        return input_value * input_value * input_value * (input_value * (6.0 * input_value - 15.0) + 10.0);
}

template <class Type = float>
constexpr inline Type smoothstep_generalized(Type input_value, Type left_edge = 0, Type right_edge = 1, int Order = 1)
{
    // Scale and clamp to 0..1 range
    input_value = std::clamp<Type>((input_value - left_edge) / (right_edge - left_edge), Type{0}, Type{1});
    
    // Order of 0 mathematically works out to just the clamp
    if (Order == 0)
        return input_value;

    Type accumulation = 0;

    for (int n = 0; n <= Order; ++n)
    {
        Type part0 = std::pow( static_cast<Type>(-1), static_cast<Type>(n));
        int  part1 = Combinatorics::binomial_coefficient( Order + n, n );
        int  part2 = Combinatorics::binomial_coefficient( 2 * Order + 1, Order - n );
        Type part3 = std::pow( input_value, static_cast<Type>(Order + n + 1) );

        accumulation += part0 * static_cast<Type>(part1) * static_cast<Type>(part2) * part3;
    }
    return accumulation;
}

template <class Type = float>
constexpr inline Type inverse_smoothstep(Type input_value)
{
    return Type{0.5} - std::sin( std::asin(Type{1.0} - Type{2.0} * std::clamp<Type>(input_value, Type{0}, Type{1})) / Type{3.0} );
}

template <class Type>
Type fract(Type input)
{
    return std::modf(input);
}

}