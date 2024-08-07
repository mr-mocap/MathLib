#include "CoordinateSystemTests.hpp"
#include "math/CoordinateSystem.hpp"
#include <iostream>
#include <cassert>
#include <cmath>


namespace CoordinateSystemTests
{

void VerifyOriginRepresentation()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf origin = CoordinateSystemf::make_origin();

    // Rotation part
    assert( origin.real.isUnit() );
    assert( origin.real.w() == 1.0f );
    assert( origin.real.i() == 0.0f );
    assert( origin.real.j() == 0.0f );
    assert( origin.real.k() == 0.0f );

    // Translation Part
    assert( origin.dual.isZero() );
}

void VerifyZeroRotationRepresentation()
{
    std::cout << __func__ << std::endl;

    // Rotate 0 around X axis
    DualQuaternionf no_rotation = CoordinateSystemf::make_rotation(0.0f, CoordinateSystemf::unit_x_axis());

    // Rotation part is a unit quaternion
    assert( no_rotation.real.isUnit() );
    assert( no_rotation.real.w() == 1.0f );
    assert( no_rotation.real.i() == 0.0f );
    assert( no_rotation.real.j() == 0.0f );
    assert( no_rotation.real.k() == 0.0f );

    // Translation Part
    assert( no_rotation.dual.isZero() );

    // Rotate 0 around Y axis
    no_rotation = CoordinateSystemf::make_rotation(0.0f, CoordinateSystemf::unit_y_axis());

    // Rotation part is a unit quaternion
    assert( no_rotation.real.isUnit() );
    assert( no_rotation.real.w() == 1.0f );
    assert( no_rotation.real.i() == 0.0f );
    assert( no_rotation.real.j() == 0.0f );
    assert( no_rotation.real.k() == 0.0f );

    // Translation Part
    assert( no_rotation.dual.isZero() );

    // Rotate 0 around Z axis
    no_rotation = CoordinateSystemf::make_rotation(0.0f, CoordinateSystemf::unit_z_axis());

    // Rotation part is a unit quaternion
    assert( no_rotation.real.isUnit() );
    assert( no_rotation.real.w() == 1.0f );
    assert( no_rotation.real.i() == 0.0f );
    assert( no_rotation.real.j() == 0.0f );
    assert( no_rotation.real.k() == 0.0f );

    // Translation Part
    assert( no_rotation.dual.isZero() );
}

void TranslatingOriginOnlyAlongX()
{
    std::cout << __func__ << std::endl;

    Vector3Df       x_translation{ 5.0f, 0.0f, 0.0f };
    DualQuaternionf origin = CoordinateSystemf::make_origin();
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0f, x_translation.x, x_translation.y, x_translation.z} * Quaternionf::unit();

    DualQuaternionf result = CoordinateSystemf::translate(origin, x_translation);
    Vector3Df       output_translation = CoordinateSystemf::translation_of(result);

    // Rotation part should be a "1" as a quaternion
    assert( result.real.isUnit() );
    assert( result.real.w() == 1.0f );
    assert( result.real.i() == 0.0f );
    assert( result.real.j() == 0.0f );
    assert( result.real.k() == 0.0f );

    // Translation part
    assert( result.dual.w() == 0.0f ); // This should always be 0
    assert( result.dual == encoded_translation );

    assert( output_translation.x == x_translation.x );
    assert( output_translation.y == x_translation.y );
    assert( output_translation.z == x_translation.z );
}

void TranslatingOriginOnlyAlongY()
{
    std::cout << __func__ << std::endl;

    Vector3Df       y_translation{ 0.0f, 17.2f, 0.0f };
    DualQuaternionf origin = CoordinateSystemf::make_origin();
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0f, y_translation.x, y_translation.y, y_translation.z} * Quaternionf::unit();

    DualQuaternionf result = CoordinateSystemf::translate(origin, y_translation);
    Vector3Df       output_translation = CoordinateSystemf::translation_of(result);

    // Rotation part should be a "1" as a quaternion
    assert( result.real.isUnit() );
    assert( result.real.w() == 1.0f );
    assert( result.real.i() == 0.0f );
    assert( result.real.j() == 0.0f );
    assert( result.real.k() == 0.0f );

    // Translation part
    assert( result.dual.w() == 0.0f ); // This should always be 0
    assert( result.dual == encoded_translation );

    assert( output_translation.x == y_translation.x );
    assert( output_translation.y == y_translation.y );
    assert( output_translation.z == y_translation.z );
}

void TranslatingOriginOnlyAlongZ()
{
    std::cout << __func__ << std::endl;

    Vector3Df       z_translation{ 0.0f, 0.0f, -32.0f };
    DualQuaternionf origin = CoordinateSystemf::make_origin();
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0f, z_translation.x, z_translation.y, z_translation.z} * Quaternionf::unit();

    DualQuaternionf result = CoordinateSystemf::translate(origin, z_translation);
    Vector3Df       output_translation = CoordinateSystemf::translation_of(result);

    // Rotation part should be a "1" as a quaternion
    assert( result.real.isUnit() );
    assert( result.real.w() == 1.0f );
    assert( result.real.i() == 0.0f );
    assert( result.real.j() == 0.0f );
    assert( result.real.k() == 0.0f );

    // Translation part
    assert( result.dual.w() == 0.0f ); // This should always be 0
    assert( result.dual == encoded_translation );

    assert( output_translation.x == z_translation.x );
    assert( output_translation.y == z_translation.y );
    assert( output_translation.z == z_translation.z );

}

void TestTranslations()
{
    VerifyOriginRepresentation();
    VerifyZeroRotationRepresentation();
    TranslatingOriginOnlyAlongX();
    TranslatingOriginOnlyAlongY();
    TranslatingOriginOnlyAlongZ();
}

void Run()
{
    std::cout << "Running Coordinate System Tests..." << std::endl;

    TestTranslations();

    std::cout << "PASSED!" << std::endl;
}

};