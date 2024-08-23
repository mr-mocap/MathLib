#include "DualNumberTests.hpp"
#include "math/DualQuaternion.hpp"
#include "math/Conversions.hpp"
#include <tuple>
#include <cassert>
#include <iostream>

#define _USE_MATH_DEFINES 1
#include <math.h>


namespace DualQuaternionTests
{

static bool IsNear(float value_to_test, float value_it_should_be, float epsilon = 0.0002f)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}


/** @addtogroup DualQuaternionTests
 *   
 *  @ingroup Tests
 */
/// @{
void PureRotationHasZeroTranslation()
{
    std::cout << __func__ << std::endl;

    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(0.0_deg_f, 0.0f, 1.0f, 0.0f) ).dual() == Quaternionf::zero() );
    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(45.0_deg_f, 0.0f, 0.0f, 1.0f) ).dual() == Quaternionf::zero() );
    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(90.0_deg_f, 1.0f, 0.0f, 0.0f) ).dual() == Quaternionf::zero() );

    // Same thing, but use a better named method.
    // NOTE: They are not the same thing for the general case!
    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(0.0_deg_f, 0.0f, 1.0f, 0.0f) ).translation() == Vector3Df::zero() );
    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(45.0_deg_f, 0.0f, 0.0f, 1.0f) ).translation() == Vector3Df::zero() );
    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(90.0_deg_f, 1.0f, 0.0f, 0.0f) ).translation() == Vector3Df::zero() );
}

void PureTranslationHasIdentityRotation()
{
    std::cout << __func__ << std::endl;

    assert( DualQuaternionf::make_translation(1.0f, 2.0f, 3.0f).real() == Quaternionf::identity());
    assert( DualQuaternionf::make_translation(1.0f, 2.0f, 3.0f).rotation() == Quaternionf::identity());
}

void MagnitudeOfNormalizedDualQuaternionIsOne()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf a{ Quaternionf::make_rotation(45.0_deg_f, 0.0f, 0.0f, 1.0f), {-43.1113f, -6.0f, 0.0f} };

    a = a * 3.3f;
    DualQuaternionf normalized_a = a.normalized();

    assert( normalized_a.norm() == Dualf::identity() );
    assert( normalized_a.magnitude() == Dualf::identity() );
    assert( !a.is_unit() );
}

void MagnitudeIsTheNumberMultipliedByItsConjugate()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf a{ Quaternionf::make_rotation( 45.0_deg_f, 1.0f, 0.0f, 0.0f ),
                       10.0f, 10.0f, 10.0f
                     };
    DualQuaternionf a_times_conjugate{ a * a.conjugate() };
    Dualf mag_a = a.magnitude();
    Dualf mag_a_times_conjugate = a_times_conjugate.magnitude();

    assert( mag_a == mag_a_times_conjugate );
}

void UnitCondition()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_rotation{ Quaternionf::make_rotation( 45.0_deg_f, 1.0f, 0.0f, 0.0f ) };
    DualQuaternionf a{ DualQuaternionf::make_coordinate_system( q_rotation, 10.0f, 10.0f, 10.0f ) };
    Quaternionf conjugate_real{ a.real().conjugate() * a.dual()};
    Quaternionf conjugate_dual{ a.dual().conjugate() * a.real()};
    Quaternionf sum = conjugate_real + conjugate_dual;


    assert( a.magnitude() == Dualf{ 1.0f } );
    assert( a.is_unit() );
    assert( sum == Quaternionf::zero() );
}

void HowToCombineASeparateRotationAndTranslation()
{
    Quaternionf q_rotation{ Quaternionf::make_rotation( 45.0_deg_f, 1.0f, 0.0f, 0.0f ) };
    Vector3Df   translation{ 10.0f, 0.0f, 0.0f };
    DualQuaternionf pure_rotation{ DualQuaternionf::make_rotation( q_rotation ) };
    DualQuaternionf pure_translation{ DualQuaternionf::make_translation( translation ) };
    DualQuaternionf combination = pure_translation * pure_rotation;

    assert( combination.rotation() == q_rotation );
    assert( combination.translation() == translation );
}

void CreateRotationAndTestXAxis(float degrees_of_rotation)
{
    float half_angle = degrees_of_rotation / 2.0f;
    DualQuaternionf rotation = DualQuaternionf::make_rotation( Quaternionf::make_rotation( DegreesToRadians(degrees_of_rotation), Vector3Df::unit_x() ) );

    // Rotation is 45 deg angle in right-hand coordinate system
    assert( IsNear(rotation.real().w(), std::cos( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real().i(), std::sin( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real().j(), 0.0f) );
    assert( IsNear(rotation.real().k(), 0.0f) );

    // Translation is 0
    assert( rotation.dual().isZero());
}

void CreateRotationAndTestYAxis(float degrees_of_rotation)
{
    float half_angle = degrees_of_rotation / 2.0f;
    DualQuaternionf rotation = DualQuaternionf::make_rotation( Quaternionf::make_rotation( DegreesToRadians(degrees_of_rotation), Vector3Df::unit_y() ) );

    // Rotation is 45 deg angle in right-hand coordinate system
    assert( IsNear(rotation.real().w(), std::cos( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real().i(), 0.0f) );
    assert( IsNear(rotation.real().j(), std::sin( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real().k(), 0.0f) );

    // Translation is 0
    assert( rotation.dual().isZero() );
}

void CreateRotationAndTestZAxis(float degrees_of_rotation)
{
    float half_angle = degrees_of_rotation / 2.0f;
    DualQuaternionf rotation = DualQuaternionf::make_rotation( Quaternionf::make_rotation( DegreesToRadians(degrees_of_rotation), Vector3Df::unit_z() ) );

    // Rotation is 45 deg angle in right-hand coordinate system
    assert( IsNear(rotation.real().w(), std::cos( DegreesToRadians(half_angle) )) );
    assert( IsNear(rotation.real().i(), 0.0f) );
    assert( IsNear(rotation.real().j(), 0.0f) );
    assert( IsNear(rotation.real().k(), std::sin( DegreesToRadians(half_angle) )) );

    // Translation is 0
    assert( rotation.dual().isZero() );
}

void VerifyOriginRepresentation()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf origin;

    // Rotation part
    assert( IsNear(origin.real().norm(), 1.0f));
    assert( IsNear(origin.real().w(), 1.0f) );
    assert( IsNear(origin.real().i(), 0.0f) );
    assert( IsNear(origin.real().j(), 0.0f) );
    assert( IsNear(origin.real().k(), 0.0f) );

    // Translation Part
    assert( origin.dual().isZero());
}

void VerifyZeroRotationRepresentation()
{
    std::cout << __func__ << std::endl;

    // Rotate 0 around X axis
    DualQuaternionf no_rotation = DualQuaternionf::make_rotation( Quaternionf::make_rotation(0.0_deg_f, Vector3Df::unit_x()) );

    // Rotation part is a unit quaternion
    assert( IsNear(no_rotation.real().norm(), 1.0f) );
    assert( IsNear(no_rotation.real().w(), 1.0f) );
    assert( IsNear(no_rotation.real().i(), 0.0f) );
    assert( IsNear(no_rotation.real().j(), 0.0f) );
    assert( IsNear(no_rotation.real().k(), 0.0f) );

    // Translation Part
    assert( no_rotation.dual().isZero() );

    // Rotate 0 around Y axis
    no_rotation = DualQuaternionf::make_rotation( Quaternionf::make_rotation(0.0_deg_f, Vector3Df::unit_y()) );

    // Rotation part is a unit quaternion
    assert( IsNear(no_rotation.real().norm(), 1.0f) );
    assert( IsNear(no_rotation.real().w(), 1.0f) );
    assert( IsNear(no_rotation.real().i(), 0.0f) );
    assert( IsNear(no_rotation.real().j(), 0.0f) );
    assert( IsNear(no_rotation.real().k(), 0.0f) );

    // Translation Part
    assert( no_rotation.dual().isZero() );

    // Rotate 0 around Z axis
    no_rotation = DualQuaternionf::make_rotation( Quaternionf::make_rotation(0.0_deg_f, Vector3Df::unit_z()) );

    // Rotation part is a unit quaternion
    assert( IsNear(no_rotation.real().norm(), 1.0f) );
    assert( IsNear(no_rotation.real().w(), 1.0f) );
    assert( IsNear(no_rotation.real().i(), 0.0f) );
    assert( IsNear(no_rotation.real().j(), 0.0f) );
    assert( IsNear(no_rotation.real().k(), 0.0f) );

    // Translation Part
    assert( no_rotation.dual().isZero() );
}

void TranslatingOriginOnlyAlongX()
{
    std::cout << __func__ << std::endl;

    Vector3Df       x_translation{ 5.0f, 0.0f, 0.0f };
    DualQuaternionf origin;
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0_deg_f, x_translation.x, x_translation.y, x_translation.z} * Quaternionf::identity();

    DualQuaternionf result = origin * DualQuaternionf::make_translation(x_translation);
    Vector3Df       output_translation = result.translation();

    // Rotation part should be a "1" as a quaternion
    assert( result.real().isUnit());
    assert( IsNear(result.real().w(), 1.0f) );
    assert( IsNear(result.real().i(), 0.0f) );
    assert( IsNear(result.real().j(), 0.0f) );
    assert( IsNear(result.real().k(), 0.0f) );

    // Translation part
    assert( result.dual().w() == 0.0f ); // This should always be 0
    assert( result.dual() == encoded_translation );

    assert( IsNear(output_translation.x, x_translation.x) );
    assert( IsNear(output_translation.y, x_translation.y) );
    assert( IsNear(output_translation.z, x_translation.z) );
}

void TranslatingOriginOnlyAlongY()
{
    std::cout << __func__ << std::endl;

    Vector3Df       y_translation{ 0.0f, 17.2f, 0.0f };
    DualQuaternionf origin;
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0_deg_f, y_translation.x, y_translation.y, y_translation.z} * Quaternionf::identity();

    DualQuaternionf result = origin * DualQuaternionf::make_translation(y_translation);
    Vector3Df       output_translation = result.translation();

    // Rotation part should be a "1" as a quaternion
    assert( result.real().isUnit() );
    assert( IsNear(result.real().w(), 1.0f) );
    assert( IsNear(result.real().i(), 0.0f) );
    assert( IsNear(result.real().j(), 0.0f) );
    assert( IsNear(result.real().k(), 0.0f) );

    // Translation part
    assert( IsNear(result.dual().w(), 0.0f) ); // This should always be 0
    assert( result.dual() == encoded_translation );

    assert( IsNear(output_translation.x, y_translation.x) );
    assert( IsNear(output_translation.y, y_translation.y) );
    assert( IsNear(output_translation.z, y_translation.z) );
}

void TranslatingOriginOnlyAlongZ()
{
    std::cout << __func__ << std::endl;

    Vector3Df       z_translation{ 0.0f, 0.0f, -32.0f };
    DualQuaternionf origin;
    Quaternionf     encoded_translation = 0.5f * Quaternionf{0.0_deg_f, z_translation.x, z_translation.y, z_translation.z} * Quaternionf::identity();

    DualQuaternionf result = origin * DualQuaternionf::make_translation(z_translation);
    Vector3Df       output_translation = result.translation();

    // Rotation part should be a "1" as a quaternion
    assert( result.real().isUnit());
    assert( IsNear(result.real().w(), 1.0f) );
    assert( IsNear(result.real().i(), 0.0f) );
    assert( IsNear(result.real().j(), 0.0f) );
    assert( IsNear(result.real().k(), 0.0f) );

    // Translation part
    assert( IsNear(result.dual().w(), 0.0f) ); // This should always be 0
    assert( result.dual() == encoded_translation );

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

void TranslationIsTheInverseOfMakeTranslation()
{
    std::cout << __func__ << std::endl;

    Vector3Df vector{ 42.0f, 3.14f, -723.0f };
    
    assert( DualQuaternionf::make_translation(vector).translation() == vector);
}
/// @}

void TestTranslations()
{
    TranslatingOriginOnlyAlongX();
    TranslatingOriginOnlyAlongY();
    TranslatingOriginOnlyAlongZ();
    TranslationIsTheInverseOfMakeTranslation();
}

void TestRotations()
{
    VerifyZeroRotationRepresentation();
    RotateOnlyAroundAMainAxis();
}

/// @}

void Run()
{
    std::cout << "Running Dual Quaternion Tests..." << std::endl;

    PureRotationHasZeroTranslation();
    PureTranslationHasIdentityRotation();
    MagnitudeOfNormalizedDualQuaternionIsOne();
    MagnitudeIsTheNumberMultipliedByItsConjugate();
    UnitCondition();
    HowToCombineASeparateRotationAndTranslation();
    VerifyOriginRepresentation();
    TestTranslations();
    TestRotations();

    std::cout << "PASSED!" << std::endl;
}
}