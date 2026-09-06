#include <Math/math/Dual.hpp>
#include <Math/math/Checks.hpp>
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace Math;

namespace ForwardDifferentiationTests
{

Dualf SingleVariableFunction(Dualf input)
{
    // Model x^2
    return input * input; // x^2, so derivative is 2x (in dual part)
}

Dualf TwoVariableFunction(Dualf input_x, Dualf input_y)
{
    // Model x^2 * y
    Dualf tmp = input_x * input_x;

    return tmp * input_y;
}

void SingleVariable()
{
    float input = 3.0f;
    Dualf output = SingleVariableFunction( {input, 1.0f} );

    CHECK_IF_EQUAL(output.real, 9.0f);
    CHECK_IF_EQUAL(output.dual, 6.0f);

    CHECK_IF_EQUAL(input * input,  9.0f); // 3^2 is 9
    CHECK_IF_EQUAL(input * 2.0f, 6.0f); // 3 * 2 is 6
}

void TwoVariables()
{
    float input_x = 2.0f;
    float input_y = 3.0f;
    Dualf derivative_wrt_x = TwoVariableFunction( {input_x, 1.0f}, {input_y, 0.0f} );
    Dualf derivative_wrt_y = TwoVariableFunction( {input_x, 0.0f}, {input_y, 1.0f} );

    CHECK_IF_EQUAL(derivative_wrt_x.real, 9.0f);
    CHECK_IF_EQUAL(derivative_wrt_x.dual, 6.0f);
}

void Run()
{
    std::cout << "Running ForwardDifferentiation Tests..." << std::endl;

    SingleVariable();
    TwoVariables();

    std::cout << "PASSED!" << std::endl;
}

}

int main(void)
{
    ForwardDifferentiationTests::Run();
    return EXIT_SUCCESS;
}