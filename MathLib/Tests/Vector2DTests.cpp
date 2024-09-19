#include "Vector2DTests.hpp"
#include "math/Vector2D.hpp"
#include "math/Checks.hpp"
#include <iostream>
#include <format>


namespace Vector2DTests
{

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

void LRef()
{
    std::cout << __func__ << std::endl;

    {
        Vector2Df one{ 1.0f, 2.0f };
        Vector2Df two{ 2.1f, 2.3f };

        one.xy() = two.yx();

        CHECK_IF_EQUAL( one.x, two.y );
        CHECK_IF_EQUAL( one.y, two.x );
    }
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
    LRef();
    Swizzle();

    std::cout << "PASSED!" << std::endl;
}
}