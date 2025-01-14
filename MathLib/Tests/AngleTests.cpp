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
    TestFunctionTakingRadian( Radian{std::numbers::pi_v<float>} );
}

void Run()
{
    std::cout << "Running Angle Tests..." << std::endl;

    CommonUsage();

    std::cout << "PASSED!" << std::endl;
}
}
