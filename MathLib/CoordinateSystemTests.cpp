#include "CoordinateSystemTests.hpp"
#include "math/CoordinateSystem.hpp"
#include "math/ApproximatelyEqualTo.hpp"
#include "math/Conversions.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <numbers>


static bool IsNear(float value_to_test, float value_it_should_be, float epsilon = 0.0002f)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}


namespace
{

void CreateRotationAndTestXAxis(float degrees_of_rotation)
{
    float half_angle = degrees_of_rotation / 2.0f;
    DualQuaternionf rotation = CoordinateSystemf::make_rotation( DegreesToRadians(degrees_of_rotation), CoordinateSystemf::unit_x_axis() );

    // Rotation is 45 deg angle in right-hand coordinate system
    assert( IsNear(rotation.real.w(), std::cos( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real.i(), std::sin( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real.j(), 0.0f) );
    assert( IsNear(rotation.real.k(), 0.0f) );

    // Translation is 0
    assert( rotation.dual.isZero() );
}

void CreateRotationAndTestYAxis(float degrees_of_rotation)
{
    float half_angle = degrees_of_rotation / 2.0f;
    DualQuaternionf rotation = CoordinateSystemf::make_rotation( DegreesToRadians(degrees_of_rotation), CoordinateSystemf::unit_y_axis() );

    // Rotation is 45 deg angle in right-hand coordinate system
    assert( IsNear(rotation.real.w(), std::cos( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real.i(), 0.0f) );
    assert( IsNear(rotation.real.j(), std::sin( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real.k(), 0.0f) );

    // Translation is 0
    assert( rotation.dual.isZero() );
}

void CreateRotationAndTestZAxis(float degrees_of_rotation)
{
    float half_angle = degrees_of_rotation / 2.0f;
    DualQuaternionf rotation = CoordinateSystemf::make_rotation( DegreesToRadians(degrees_of_rotation), CoordinateSystemf::unit_z_axis() );

    // Rotation is 45 deg angle in right-hand coordinate system
    assert( IsNear(rotation.real.w(), std::cos( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real.i(), 0.0f) );
    assert( IsNear(rotation.real.j(), 0.0f) );
    assert( IsNear(rotation.real.k(), std::sin( DegreesToRadians(half_angle) )) );

    // Translation is 0
    assert( rotation.dual.isZero() );
}

}

namespace CoordinateSystemTests
{

void VerifyOriginRepresentation()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf origin = CoordinateSystemf::make_origin();

    // Rotation part
    assert( IsNear(origin.real.norm(), 1.0f) );
    assert( IsNear(origin.real.w(), 1.0f) );
    assert( IsNear(origin.real.i(), 0.0f) );
    assert( IsNear(origin.real.j(), 0.0f) );
    assert( IsNear(origin.real.k(), 0.0f) );

    // Translation Part
    assert( origin.dual.isZero() );
}

void VerifyZeroRotationRepresentation()
{
    std::cout << __func__ << std::endl;

    // Rotate 0 around X axis
    DualQuaternionf no_rotation = CoordinateSystemf::make_rotation(0.0f, CoordinateSystemf::unit_x_axis());

    // Rotation part is a unit quaternion
    assert( IsNear(no_rotation.real.norm(), 1.0f) );
    assert( IsNear(no_rotation.real.w(), 1.0f) );
    assert( IsNear(no_rotation.real.i(), 0.0f) );
    assert( IsNear(no_rotation.real.j(), 0.0f) );
    assert( IsNear(no_rotation.real.k(), 0.0f) );

    // Translation Part
    assert( no_rotation.dual.isZero() );

    // Rotate 0 around Y axis
    no_rotation = CoordinateSystemf::make_rotation(0.0f, CoordinateSystemf::unit_y_axis());

    // Rotation part is a unit quaternion
    assert( IsNear(no_rotation.real.norm(), 1.0f) );
    assert( IsNear(no_rotation.real.w(), 1.0f) );
    assert( IsNear(no_rotation.real.i(), 0.0f) );
    assert( IsNear(no_rotation.real.j(), 0.0f) );
    assert( IsNear(no_rotation.real.k(), 0.0f) );

    // Translation Part
    assert( no_rotation.dual.isZero() );

    // Rotate 0 around Z axis
    no_rotation = CoordinateSystemf::make_rotation(0.0f, CoordinateSystemf::unit_z_axis());

    // Rotation part is a unit quaternion
    assert( IsNear(no_rotation.real.norm(), 1.0f) );
    assert( IsNear(no_rotation.real.w(), 1.0f) );
    assert( IsNear(no_rotation.real.i(), 0.0f) );
    assert( IsNear(no_rotation.real.j(), 0.0f) );
    assert( IsNear(no_rotation.real.k(), 0.0f) );

    // Translation Part
    assert( no_rotation.dual.isZero() );
}

void TranslatingOriginOnlyAlongX()
{
    std::cout << __func__ << std::endl;

    Vector3Df       x_translation{ 5.0f, 0.0f, 0.0f };
    DualQuaternionf origin = CoordinateSystemf::make_origin();
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0f, x_translation.x, x_translation.y, x_translation.z} * Quaternionf::identity();

    DualQuaternionf result = CoordinateSystemf::translate(origin, x_translation);
    Vector3Df       output_translation = CoordinateSystemf::translation_of(result);

    // Rotation part should be a "1" as a quaternion
    assert( result.real.isUnit() );
    assert( IsNear(result.real.w(), 1.0f) );
    assert( IsNear(result.real.i(), 0.0f) );
    assert( IsNear(result.real.j(), 0.0f) );
    assert( IsNear(result.real.k(), 0.0f) );

    // Translation part
    assert( result.dual.w() == 0.0f ); // This should always be 0
    assert( result.dual == encoded_translation );

    assert( IsNear(output_translation.x, x_translation.x) );
    assert( IsNear(output_translation.y, x_translation.y) );
    assert( IsNear(output_translation.z, x_translation.z) );
}

void TranslatingOriginOnlyAlongY()
{
    std::cout << __func__ << std::endl;

    Vector3Df       y_translation{ 0.0f, 17.2f, 0.0f };
    DualQuaternionf origin = CoordinateSystemf::make_origin();
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0f, y_translation.x, y_translation.y, y_translation.z} * Quaternionf::identity();

    DualQuaternionf result = CoordinateSystemf::translate(origin, y_translation);
    Vector3Df       output_translation = CoordinateSystemf::translation_of(result);

    // Rotation part should be a "1" as a quaternion
    assert( result.real.isUnit() );
    assert( IsNear(result.real.w(), 1.0f) );
    assert( IsNear(result.real.i(), 0.0f) );
    assert( IsNear(result.real.j(), 0.0f) );
    assert( IsNear(result.real.k(), 0.0f) );

    // Translation part
    assert( IsNear(result.dual.w(), 0.0f) ); // This should always be 0
    assert( result.dual == encoded_translation );

    assert( IsNear(output_translation.x, y_translation.x) );
    assert( IsNear(output_translation.y, y_translation.y) );
    assert( IsNear(output_translation.z, y_translation.z) );
}

void TranslatingOriginOnlyAlongZ()
{
    std::cout << __func__ << std::endl;

    Vector3Df       z_translation{ 0.0f, 0.0f, -32.0f };
    DualQuaternionf origin = CoordinateSystemf::make_origin();
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0f, z_translation.x, z_translation.y, z_translation.z} * Quaternionf::identity();

    DualQuaternionf result = CoordinateSystemf::translate(origin, z_translation);
    Vector3Df       output_translation = CoordinateSystemf::translation_of(result);

    // Rotation part should be a "1" as a quaternion
    assert( result.real.isUnit() );
    assert( IsNear(result.real.w(), 1.0f) );
    assert( IsNear(result.real.i(), 0.0f) );
    assert( IsNear(result.real.j(), 0.0f) );
    assert( IsNear(result.real.k(), 0.0f) );

    // Translation part
    assert( IsNear(result.dual.w(), 0.0f) ); // This should always be 0
    assert( result.dual == encoded_translation );

    assert( IsNear(output_translation.x, z_translation.x) );
    assert( IsNear(output_translation.y, z_translation.y) );
    assert( IsNear(output_translation.z, z_translation.z) );
}

void RotateOnlyAroundAMainAxis()
{
    std::cout << __func__ << std::endl;

    float input_rotations[] = { 90.0f, 60.0f, 45.0f, 30.0f, -90.0f, -60.0f, -45.0f, -30.0f };

    // X axis
    for (float degrees : input_rotations)
        CreateRotationAndTestXAxis(90.0f);

    // Y axis
    for (float degrees : input_rotations)
        CreateRotationAndTestYAxis(90.0f);

    // Z axis
    for (float degrees : input_rotations)
        CreateRotationAndTestZAxis(90.0f);
}

void TranslationOfIsTheInverseOfMakeTranslation()
{
    std::cout << __func__ << std::endl;

    Vector3Df vector{ 42.0f, 3.14f, -723.0f };
    
    assert( CoordinateSystemf::translation_of( CoordinateSystemf::make_translation(vector) ) == vector );
}

void TestTranslations()
{
    TranslatingOriginOnlyAlongX();
    TranslatingOriginOnlyAlongY();
    TranslatingOriginOnlyAlongZ();
    TranslationOfIsTheInverseOfMakeTranslation();
}

void TestRotations()
{
    VerifyZeroRotationRepresentation();
    RotateOnlyAroundAMainAxis();
}

void Run()
{
    std::cout << "Running Coordinate System Tests..." << std::endl;

    VerifyOriginRepresentation();
    TestTranslations();
    TestRotations();

    std::cout << "PASSED!" << std::endl;
}

};