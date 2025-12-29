#include "AngleTests.hpp"
#include "math/Angle.hpp"
#include <cassert>
#include <iostream>
#include <numbers>


namespace AngleTests
{

using namespace Math;
using namespace Math::Literals;

constexpr double PI = std::numbers::pi;
constexpr double PI_2 = std::numbers::pi / 2.0;
constexpr double PI_4 = std::numbers::pi / 4.0;

void FunctionThatPrintsInput(Degreef input)
{

    std::cout << "You passed in a variable designating " << input.value() << " Degrees" << std::endl;
}

void TestFunctionTakingRadian(Radianf input)
{
    std::cout << "You passed in a variable designating " << input.value() << " Radians" << std::endl;
    FunctionThatPrintsInput(input);
}

void CommonUsage()
{
    std::cout << __func__ << std::endl;

    TestFunctionTakingRadian(90.0_deg_f);
    TestFunctionTakingRadian( Degreef(45.0f) );
    TestFunctionTakingRadian( Radianf{std::numbers::pi_v<float>} );
}

void UsingUserDefinedLiterals()
{
    // Float
    {
        Degreef a = 32.0_deg_f;
        Degreef b = 32.0_deg_F;
        Degreef c = 32.0_degf;
        Degreef d = 32.0_degF;

        assert( a == 32.0f );
        assert( b == 32.0f );
        assert( c == 32.0f );
        assert( d == 32.0f );
    }

    // Double
    {
        Degree a = 32.0_deg;
        Degreed b = 32.0_deg;

        assert( a == 32.0 );
        assert( b == 32.0 );
    }

    // Long Double
    {
        Degreel a = 32.0_deg_l;
        Degreel b = 32.0_deg_L;
        Degreel c = 32.0_degl;
        Degreel d = 32.0_degL;

        assert( a == 32.0l );
        assert( b == 32.0l );
        assert( c == 32.0l );
        assert( d == 32.0l );
    }
}

void RadianHasAllComparisonOperators()
{
    Radian a = 0.0_rad;
    Radian b = a;
    Radian c{ std::numbers::pi_v<double> / 2.0 };
    Radian d{ -(std::numbers::pi_v<double> / 2.0) };

    assert( a == b   );
    assert( a == 0.0 );
    assert( a == b.value() );
    assert( a != c );
    assert( a != (std::numbers::pi_v<double> / 2.0) );

    assert(   d < b   );
    assert(   d < 0.0 );
    assert( !(b < d) ); // check that the NOT of the operator holds

    assert( d <= d );
    assert( d <= -(std::numbers::pi_v<double> / 2.0) );

    assert(   c > b );
    assert(   c > 0.0 );
    assert( !(b > c) ); // check that the NOT of the operator holds

    assert( c >= c );
    assert( c >= (std::numbers::pi_v<double> / 2.0) );
    assert( c >= d );
}

void Run()
{
    std::cout << "Running Angle Tests..." << std::endl;

    CommonUsage();
    UsingUserDefinedLiterals();
    RadianHasAllComparisonOperators();

    std::cout << "PASSED!" << std::endl;
}
}
