#include "Vector3DTests.hpp"
#include "math/Vector3D.hpp"
#include "math/Checks.hpp"
#include <iostream>
#include <format>
#include <numbers>


namespace Vector3DTests
{

void TestFunction(const Vector3Df &input)
{
    std::cout << std::format("{}\t{} {} {}", __func__, input.x, input.y, input.z) << std::endl;
}

void DefaultInitialied()
{
    std::cout << __func__ << std::endl;

    Vector3Df default_initialized;

    CHECK_IF_EQUAL( default_initialized.x, 0.0f );
    CHECK_IF_EQUAL( default_initialized.y, 0.0f );
    CHECK_IF_EQUAL( default_initialized.z, 0.0f );
}

void OneInitializer()
{
    std::cout << __func__ << std::endl;

    Vector3Df one{ 2.2f };

    CHECK_IF_EQUAL( one.x, 2.2f );
    CHECK_IF_EQUAL( one.y, 0.0f );
    CHECK_IF_EQUAL( one.z, 0.0f );

}

void TwoInitializers()
{
    std::cout << __func__ << std::endl;

    Vector3Df one{ 2.2f, 3.3f };

    CHECK_IF_EQUAL( one.x, 2.2f );
    CHECK_IF_EQUAL( one.y, 3.3f );
    CHECK_IF_EQUAL( one.z, 0.0f );
}

void ThreeInitializers()
{
    std::cout << __func__ << std::endl;

    Vector3Df one{ 2.2f, 3.3f, 4.4f };

    CHECK_IF_EQUAL( one.x, 2.2f );
    CHECK_IF_EQUAL( one.y, 3.3f );
    CHECK_IF_EQUAL( one.z, 4.4f );
}

void PassedToFunction()
{
    std::cout << __func__ << std::endl;

    TestFunction( { } );
    TestFunction( { 1.0f } );
    TestFunction( { 66.0f, 33.3f } );
    TestFunction( { 66.0f, 33.3f, 99.9f } );

    Vector3Df t{ 1.1f, 2.2f, 3.3f };

    TestFunction( t.zyx() );
}

void OperatorEqualsAndNotEquals()
{
    Vector3Df one{ 1.0f, 2.0f, 3.0f };
    Vector3Df two{ 1.0f, 2.0f, 3.0f };
    Vector3Df three{ 9.16f, 32.7f, 128.0f };

    CHECK_IF_EQUAL( one, two );
    CHECK_IF_NOT_EQUAL( one, three );
}

void AssignVector3DToVector3DRef()
{
    std::cout << __func__ << std::endl;

    Vector3Df one{ 1.0f, 2.0f };
    Vector3Df two{ 2.1f, 2.3f, 12.0f };

    CHECK_IF_NOT_EQUAL( one.x, two.x );
    CHECK_IF_NOT_EQUAL( one.y, two.y );
    CHECK_IF_NOT_EQUAL( one.z, two.z );

    one.xyz() = two;

    CHECK_IF_EQUAL( one.x, two.x );
    CHECK_IF_EQUAL( one.y, two.y );
    CHECK_IF_EQUAL( one.z, two.z );
    
    one.zyx() = two;

    CHECK_IF_EQUAL( one.x, two.z );
    CHECK_IF_EQUAL( one.y, two.y );
    CHECK_IF_EQUAL( one.z, two.x );

    two.zyx() = { 5.5f, 6.6f, 7.7f };

    CHECK_IF_EQUAL( two.x, 7.7f );
    CHECK_IF_EQUAL( two.y, 6.6f );
    CHECK_IF_EQUAL( two.z, 5.5f );
}

void AssignVector3DRefToVector3DRef()
{
    std::cout << __func__ << std::endl;

    Vector3Df one{ 1.0f, 2.0f, 3.0f };
    Vector3Df two{ 2.1f, 2.3f, 2.4f };

    CHECK_IF_NOT_EQUAL( one.x, two.x );
    CHECK_IF_NOT_EQUAL( one.y, two.y );
    CHECK_IF_NOT_EQUAL( one.z, two.z );

    one.xyz() = two.xyz();

    CHECK_IF_EQUAL( one.x, two.x );
    CHECK_IF_EQUAL( one.y, two.y );
    CHECK_IF_EQUAL( one.z, two.z );
}

void AssignVector3DRefToVector3D()
{
    std::cout << __func__ << std::endl;

    Vector3Df one{ 1.0f, 2.0f, 3.0f };
    Vector3Df two{ 2.1f, 2.3f, 2.5f };

    CHECK_IF_NOT_EQUAL( one.x, two.y );
    CHECK_IF_NOT_EQUAL( one.y, two.y );
    CHECK_IF_NOT_EQUAL( one.z, two.z );

    one = two.zyx();

    CHECK_IF_EQUAL( one.x, two.z );
    CHECK_IF_EQUAL( one.y, two.y );
    CHECK_IF_EQUAL( one.z, two.x );
}

void AssignVector3DToVector3D()
{
    std::cout << __func__ << std::endl;

    Vector3Df one{ 1.0f, 2.0f, 3.0f };
    Vector3Df two{ 2.1f, 2.3f, 2.5f };

    CHECK_IF_NOT_EQUAL( one.x, two.x );
    CHECK_IF_NOT_EQUAL( one.y, two.y );
    CHECK_IF_NOT_EQUAL( one.z, two.z );

    one = two;

    CHECK_IF_EQUAL( one.x, two.x );
    CHECK_IF_EQUAL( one.y, two.y );
    CHECK_IF_EQUAL( one.z, two.z );
}

void Dot()
{
    std::cout << __func__ << std::endl;

    float sqrt2_over_2 = std::numbers::sqrt2_v<float> / 2.0f;
    // At first, let's use unit vectors...

    // Perpendicular vectors are 0
    CHECK_IF_ZERO( dot(Vector3Df::unit_x(), Vector3Df::unit_y()) );
    CHECK_IF_ZERO( dot(Vector3Df::unit_x(), Vector3Df::unit_z()) );

    // Parallel vectors are 1
    CHECK_IF_EQUAL( dot(Vector3Df::unit_x(), Vector3Df::unit_x()), 1.0f);
    CHECK_IF_EQUAL( dot(Vector3Df::unit_y(), Vector3Df::unit_y()), 1.0f);
    CHECK_IF_EQUAL( dot(Vector3Df::unit_z(), Vector3Df::unit_z()), 1.0f);

    // Misc Rotations
    CHECK_IF_EQUAL( dot(Vector3Df{sqrt2_over_2, sqrt2_over_2, 0.0f}, Vector3Df{sqrt2_over_2, sqrt2_over_2, 0.0f}), 1.0f ); // 45 deg rotation
}

void Run()
{
    std::cout << "Running Vector3D Tests..." << std::endl;

    DefaultInitialied();
    OneInitializer();
    TwoInitializers();
    ThreeInitializers();
    PassedToFunction();
    OperatorEqualsAndNotEquals();
    AssignVector3DToVector3DRef();
    AssignVector3DRefToVector3DRef();
    AssignVector3DRefToVector3D();
    AssignVector3DToVector3D();
    Dot();

    std::cout << "PASSED!" << std::endl;

}
}