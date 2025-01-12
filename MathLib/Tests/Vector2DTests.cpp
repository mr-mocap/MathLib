#include "Vector2DTests.hpp"
#include "math/Vector2D.hpp"
#include "math/Checks.hpp"
#include <iostream>
#include <format>
#include <numbers>


namespace Vector2DTests
{

using namespace Math;

void TestFunction(const Vector2Df &input)
{
    std::cout << std::format("{}\t{} {}", __func__, input.x, input.y) << std::endl;
}

void DefaultInitialied()
{
    std::cout << __func__ << std::endl;

    Vector2Df default_initialized;

    CHECK_IF_EQUAL( default_initialized.x, 0.0f );
    CHECK_IF_EQUAL( default_initialized.y, 0.0f );
}

void OneInitializer()
{
    std::cout << __func__ << std::endl;

    Vector2Df one{ 2.2f };

    CHECK_IF_EQUAL( one.x, 2.2f );
    CHECK_IF_EQUAL( one.y, 0.0f );
}

void TwoInitializers()
{
    std::cout << __func__ << std::endl;

    Vector2Df one{ 2.2f, 3.3f };

    CHECK_IF_EQUAL( one.x, 2.2f );
    CHECK_IF_EQUAL( one.y, 3.3f );
}

void PassedToFunction()
{
    std::cout << __func__ << std::endl;

    TestFunction( { } );
    TestFunction( { 1.0f } );
    TestFunction( { 66.0f, 33.3f } );

    Vector2Df t{ 1.1f, 2.2f };

    TestFunction( t.yx() );
}

void OperatorEqualsAndNotEquals()
{
    Vector2Df one{ 1.0f, 2.0f };
    Vector2Df two{ 1.0f, 2.0f };
    Vector2Df three{ 9.16f, 32.7f };

    CHECK_IF_EQUAL( one, two );
    CHECK_IF_NOT_EQUAL( one, three );
}

void AssignVector2DToVector2DRef()
{
    std::cout << __func__ << std::endl;

    Vector2Df one{ 1.0f, 2.0f };
    Vector2Df two{ 2.1f, 2.3f };

    CHECK_IF_NOT_EQUAL( one.x, two.x );
    CHECK_IF_NOT_EQUAL( one.y, two.y );

    one.xy() = two;

    CHECK_IF_EQUAL( one.x, two.x );
    CHECK_IF_EQUAL( one.y, two.y );
    
    one.yx() = two;

    CHECK_IF_EQUAL( one.x, two.y );
    CHECK_IF_EQUAL( one.y, two.x );

    two.yx() = { 5.5f, 6.6f };

    CHECK_IF_EQUAL( two.x, 6.6f );
    CHECK_IF_EQUAL( two.y, 5.5f );
}

void AssignVector2DRefToVector2DRef()
{
    std::cout << __func__ << std::endl;

    Vector2Df one{ 1.0f, 2.0f };
    Vector2Df two{ 2.1f, 2.3f };

    CHECK_IF_NOT_EQUAL( one.x, two.x );
    CHECK_IF_NOT_EQUAL( one.y, two.y );

    one.xy() = two.xy();

    CHECK_IF_EQUAL( one.x, two.x );
    CHECK_IF_EQUAL( one.y, two.y );
}

void AssignVector2DRefToVector2D()
{
    std::cout << __func__ << std::endl;

    Vector2Df one{ 1.0f, 2.0f };
    Vector2Df two{ 2.1f, 2.3f };

    CHECK_IF_NOT_EQUAL( one.x, two.y );
    CHECK_IF_NOT_EQUAL( one.y, two.y );

    one = two.yx();

    CHECK_IF_EQUAL( one.x, two.y );
    CHECK_IF_EQUAL( one.y, two.x );
}

void AssignVector2DToVector2D()
{
    std::cout << __func__ << std::endl;

    Vector2Df one{ 1.0f, 2.0f };
    Vector2Df two{ 2.1f, 2.3f };

    CHECK_IF_NOT_EQUAL( one.x, two.x );
    CHECK_IF_NOT_EQUAL( one.y, two.y );

    one = two;

    CHECK_IF_EQUAL( one.x, two.x );
    CHECK_IF_EQUAL( one.y, two.y );
}

void Swizzle()
{
    std::cout << __func__ << std::endl;

    {
        Vector2Df one{ 1.0f, 2.0f };
        Vector2Df two{ one.yx() };

        CHECK_IF_EQUAL( two.x, 2.0f );
        CHECK_IF_EQUAL( two.y, 1.0f );
    }
}

void Dot()
{
    std::cout << __func__ << std::endl;

    float sqrt2_over_2 = std::numbers::sqrt2_v<float> / 2.0f;
    // At first, let's use unit vectors...

    // Perpendicular vectors are 0
    CHECK_IF_ZERO( dot(Vector2Df::unit_x(), Vector2Df::unit_y()) );

    // Parallel vectors are 1
    CHECK_IF_EQUAL( dot(Vector2Df::unit_x(), Vector2Df::unit_x()), 1.0f);
    CHECK_IF_EQUAL( dot(Vector2Df::unit_y(), Vector2Df::unit_y()), 1.0f);

    // Misc Rotations
    CHECK_IF_EQUAL( dot(Vector2Df{sqrt2_over_2, sqrt2_over_2}, Vector2Df{sqrt2_over_2, sqrt2_over_2}), 1.0f ); // 45 deg rotation
}

void Run()
{
    std::cout << "Running Vector2D Tests..." << std::endl;

    DefaultInitialied();
    OneInitializer();
    TwoInitializers();
    PassedToFunction();
    OperatorEqualsAndNotEquals();
    AssignVector2DToVector2DRef();
    AssignVector2DRefToVector2DRef();
    AssignVector2DRefToVector2D();
    AssignVector2DToVector2D();
    Swizzle();
    Dot();

    std::cout << "PASSED!" << std::endl;
}
}