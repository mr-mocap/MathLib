#include "QuaternionTests.hpp"
#include "math/Quaternion.hpp"
#include "math/Conversions.hpp"
#include "math/Exponential.hpp"
#include "math/Checks.hpp"
#include <cassert>
#include <iostream>

/** @file
 * 
 *  @hideincludegraph
 */

/** @defgroup QuaternionTests Quaternion Unit Tests
 * 
 *  Here are all the unit tests used to exercise the Quaternion class
 * 
 *  @ingroup UnitTests
 * 
 *  @{
 */


/** Contains the unit tests for Quaternion
 * 
 */
namespace QuaternionTests
{

void TestRotationAtRegularIntervals(Quaternionf begin, Degreef amount_of_rotation, Vector3Df rotation_axis, int num_equal_steps)
{
#if 0
    Degreef step_deg{ 10.0f };
    float step_percentage = 1.0f / 9.0f;

    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 0.0f), begin );

    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 0.0f), Quaternionf::make_rotation(step_deg * 0.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 1.0f), Quaternionf::make_rotation(step_deg * 1.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 2.0f), Quaternionf::make_rotation(step_deg * 2.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 3.0f), Quaternionf::make_rotation(step_deg * 3.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 4.0f), Quaternionf::make_rotation(step_deg * 4.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 5.0f), Quaternionf::make_rotation(step_deg * 5.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 6.0f), Quaternionf::make_rotation(step_deg * 6.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 7.0f), Quaternionf::make_rotation(step_deg * 7.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 8.0f), Quaternionf::make_rotation(step_deg * 8.0f, z) );
    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 9.0f), Quaternionf::make_rotation(step_deg * 9.0f, z) );

    CHECK_IF_EQUAL( slerp(begin, end, step_percentage * 9.0f), end );
#endif
    Quaternionf end_rotation{ Quaternionf::make_rotation(amount_of_rotation, rotation_axis) };
    float step_percentage = 1.0f / num_equal_steps;

    for (int iCurrentStep = 0; iCurrentStep < num_equal_steps; ++iCurrentStep)
    {
        float       current_percentage{ step_percentage * iCurrentStep };
        Degreef     current_rotation_amount{ amount_of_rotation * current_percentage };
        Quaternionf new_rotation{ Quaternionf::make_rotation(current_rotation_amount, rotation_axis) };

        CHECK_IF_EQUAL( slerp(begin, end_rotation, current_percentage), new_rotation);
    }
    CHECK_IF_EQUAL( slerp(begin, end_rotation, 1.0f), end_rotation);
}

/// @{
void UnitQuaternionIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Quaternionf unit = Quaternionf::identity();

    CHECK_IF_EQUAL(unit.w(), 1.0f);
    CHECK_IF_EQUAL(unit.i(), 0.0f);
    CHECK_IF_EQUAL(unit.j(), 0.0f);
    CHECK_IF_EQUAL(unit.k(), 0.0f);
}

void ZeroQuaternionIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Quaternionf zero = Quaternionf::zero();

    CHECK_IF_EQUAL(zero.w(), 0.0f);
    CHECK_IF_EQUAL(zero.i(), 0.0f);
    CHECK_IF_EQUAL(zero.j(), 0.0f);
    CHECK_IF_EQUAL(zero.k(), 0.0f);
}

void QuaternionIsConstructedAsExpected()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 1.0, 2.0, 3.0, 4.0 };

    CHECK_IF_EQUAL(q.w(), 1.0f);
    CHECK_IF_EQUAL(q.i(), 2.0f);
    CHECK_IF_EQUAL(q.j(), 3.0f);
    CHECK_IF_EQUAL(q.k(), 4.0f);
}

void QuaternionAddsPerComponent()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_left{ 1.0, 2.0, 3.0, 4.0 };
    Quaternionf q_right{ 5.0, 6.0, 7.0, 8.0 };
    Quaternionf q_result = q_left + q_right;

    CHECK_IF_EQUAL(q_result.w(), 6.0f);
    CHECK_IF_EQUAL(q_result.i(), 8.0f);
    CHECK_IF_EQUAL(q_result.j(), 10.0f);
    CHECK_IF_EQUAL(q_result.k(), 12.0f);
}

void OperatorEqualsComparesMatchingComponents()
{ 
    std::cout << __func__ << std::endl;

    Quaternionf q_original{ 1.0, 2.0, 3.0, 4.0 };
    Quaternionf q_tocompareagainst{ 1.0, 2.0, 3.0, 4.0 };

    CHECK_IF_EQUAL(q_original, q_tocompareagainst);
    CHECK_IF_EQUAL(q_original.w(), q_tocompareagainst.w());
    CHECK_IF_EQUAL(q_original.i(), q_tocompareagainst.i());
    CHECK_IF_EQUAL(q_original.j(), q_tocompareagainst.j());
    CHECK_IF_EQUAL(q_original.k(), q_tocompareagainst.k());
}

void OperatorNotEqualsIsOppositeOfEquals()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_original{ 1.0, 2.0, 3.0, 4.0 };
    Quaternionf q_tocompareagainst{ 1.0, 2.0, 3.0, 4.0 };
    Quaternionf q_different4{ 1.0, 2.0, 3.0, 5.0 };
    Quaternionf q_different3{ 1.0, 2.0, 9.0, 4.0 };
    Quaternionf q_different2{ 1.0, 12.0, 3.0, 4.0 };
    Quaternionf q_different1{ 100.0, 2.0, 3.0, 4.0 };

    CHECK_IF_EQUAL(q_original, q_tocompareagainst);

    assert( (q_original != q_tocompareagainst) == false );

    // Now test for each component individually
    CHECK_IF_NOT_EQUAL(q_original, q_different1);
    CHECK_IF_NOT_EQUAL(q_original, q_different2);
    CHECK_IF_NOT_EQUAL(q_original, q_different3);
    CHECK_IF_NOT_EQUAL(q_original, q_different4);
}

void CopyOperatorIsImplemented()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_original{ 2.0, 4.0, 6.0, 8.0 };
    Quaternionf q_copy{ q_original };

    CHECK_IF_EQUAL(q_original, q_copy);
}

void ConjugateInvertsTheImaginaryComponents()
{
    std::cout << __func__ << std::endl;

    Quaternionf arbitrary_value1{ 1.0, 2.0, 3.0, 4.0 };
    Quaternionf arbitrary_value2{ 1.0, -2.0, 3.0, 4.0 };
    Quaternionf arbitrary_value3{ 1.0, 2.0, -3.0, 4.0 };
    Quaternionf arbitrary_value4{ 1.0, 2.0, 3.0, -4.0 };

    Quaternionf expected_value1{ 1.0, -2.0, -3.0, -4.0 };
    Quaternionf expected_value2{ 1.0, 2.0, -3.0, -4.0 };
    Quaternionf expected_value3{ 1.0, -2.0, 3.0, -4.0 };
    Quaternionf expected_value4{ 1.0, -2.0, -3.0, 4.0 };

    CHECK_IF_EQUAL(arbitrary_value1.conjugate(), expected_value1);
    CHECK_IF_EQUAL(arbitrary_value2.conjugate(), expected_value2);
    CHECK_IF_EQUAL(arbitrary_value3.conjugate(), expected_value3);
    CHECK_IF_EQUAL(arbitrary_value4.conjugate(), expected_value4);
}

void ConjugateIsItsOwnInverse()
{
    std::cout << __func__ << std::endl;

    Quaternionf arbitrary_value1{ 6.0, 7.0, 8.0, 9.0 };

    CHECK_IF_EQUAL(arbitrary_value1.conjugate().conjugate(), arbitrary_value1);
}

void RotatingA3DPointByUnitRotationLeavesPointUnchanged()
{
    std::cout << __func__ << std::endl;

    // The rotation must be of unit length
    Quaternionf unit_rotation = Quaternionf::identity();
    const float point[3] = { 1.0, 3.0, 7.0 };

    // Place 3D point in the imaginary part, leaving the real part as 0.0
    Quaternionf value_to_rotate{ 0.0f, point[0], point[1], point[2] };

    CHECK_IF_EQUAL((unit_rotation * value_to_rotate * unit_rotation.conjugate()), value_to_rotate);
}

void IJKUnitQuaternionsAreDefined()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf::unit_i(), Quaternionf{ 0.0, 1.0, 0.0, 0.0 } );
    CHECK_IF_EQUAL( Quaternionf::unit_j(), Quaternionf{ 0.0, 0.0, 1.0, 0.0 } );
    CHECK_IF_EQUAL( Quaternionf::unit_k(), Quaternionf{ 0.0, 0.0, 0.0, 1.0 } );
}

void ISquaredIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
    Quaternionf i = Quaternionf::unit_i();

    CHECK_IF_EQUAL( i * i, negative_1 );
}

void JSquaredIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
    Quaternionf j = Quaternionf::unit_j();

    CHECK_IF_EQUAL( j * j, negative_1 );
}

void KSquaredIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
    Quaternionf k = Quaternionf::unit_k();

    CHECK_IF_EQUAL( k * k, negative_1 );
}

void IJKIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };

    CHECK_IF_EQUAL( Quaternionf::unit_i() * Quaternionf::unit_j() * Quaternionf::unit_k(), negative_1 );
}

void IJEqualsK()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf::unit_i() * Quaternionf::unit_j(), Quaternionf::unit_k() );
}

void JIEqualsNegativeK()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_k{ 0.0, 0.0, 0.0, -1.0 };

    CHECK_IF_EQUAL( Quaternionf::unit_j() * Quaternionf::unit_i(), negative_k );
}
void JKEqualsI()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf::unit_j() * Quaternionf::unit_k(), Quaternionf::unit_i() );
}

void KJEqualsNegativeI()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_i{ 0.0, -1.0, 0.0, 0.0 };

    CHECK_IF_EQUAL( Quaternionf::unit_k() * Quaternionf::unit_j(), negative_i );
}

void KIEqualsJ()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf::unit_k() * Quaternionf::unit_i(), Quaternionf::unit_j() );
}

void IKEqualsNegativeJ()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_j{ 0.0, 0.0, -1.0, 0.0 };

    CHECK_IF_EQUAL( Quaternionf::unit_i() * Quaternionf::unit_k(), negative_j );
}

void HasOperatorNegate()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( -Quaternionf::identity(), Quaternionf{ -1.0,  0.0,  0.0,  0.0 } );
    CHECK_IF_EQUAL( -Quaternionf::unit_i(),   Quaternionf{  0.0, -1.0,  0.0,  0.0 } );
    CHECK_IF_EQUAL( -Quaternionf::unit_j(),   Quaternionf{  0.0,  0.0, -1.0,  0.0 } );
    CHECK_IF_EQUAL( -Quaternionf::unit_k(),   Quaternionf{  0.0,  0.0,  0.0, -1.0 } );

    CHECK_IF_EQUAL( -Quaternionf(1.0f, -2.2f, 3.0f, -4.0f), Quaternionf(-1.0f, 2.2f, -3.0f, 4.0f) );
}

void OperatorPlusAndMinusAreInverses()
{
    std::cout << __func__ << std::endl;

    Quaternionf::value_type starting_value = 0;
    Quaternionf::value_type value = 6;
    Quaternionf::value_type added_value = starting_value + value;
    Quaternionf::value_type subtracted_value = starting_value - value;

    CHECK_IF_EQUAL( added_value - value, starting_value );
    CHECK_IF_EQUAL( subtracted_value + value, starting_value );
}

void NormIsEquivalentToDistance()
{
    std::cout << __func__ << std::endl;

    // Show that sqrt(4) == 2.
    // i.e. qrt) of a^2 + b^2 + c^2 + d^2 == 2
    // i.e. a^2 + b^2 + c^2 + d^2 == 4
    CHECK_IF_EQUAL( Quaternionf{ 1.0, 1.0, 1.0, 1.0 }.norm(), 2.0f );

    CHECK_IF_EQUAL( Quaternionf{ 2.0, 2.0, 2.0, 2.0 }.norm(), 4.0f );
    CHECK_IF_EQUAL( Quaternionf{ 1.0, 2.0, 3.0, 4.0 }.norm(), std::sqrt(30.0f) ); // 1^2 + 2^2 + 3^2 + 4^2
}

void UnitQuaternionHasNormOfOne()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf::identity().norm(), 1.0f );
    CHECK_IF_EQUAL( Quaternionf::unit_i().norm(), 1.0f );
    CHECK_IF_EQUAL( Quaternionf::unit_j().norm(), 1.0f );
    CHECK_IF_EQUAL( Quaternionf::unit_k().norm(), 1.0f );
}

void DividingByAScalarDividesEachComponent()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf{1.0f, 2.0f, 3.0f, 4.0f} / 2.0f, Quaternionf{1.0f / 2.0f, 2.0f / 2.0f, 3.0f / 2.0f, 4.0f / 2.0f} );
    CHECK_IF_EQUAL( Quaternionf{1.0f, 2.0f, 3.0f, 4.0f} / 3.0f, Quaternionf{1.0f / 3.0f, 2.0f / 3.0f, 3.0f / 3.0f, 4.0f / 3.0f} );
}

void MultiplyingByItsOwnInverseProducesUnity()
{
    std::cout << __func__ << std::endl;

    Quaternionf q1{ 6.3f, 2.2f, 1.1f, 0.0f };
    Quaternionf q1_inverse = q1.inverse();
    Quaternionf q1_product = q1_inverse * q1;
    Quaternionf q1_product_reversed = q1 * q1_inverse;

    CHECK_IF_EQUAL( q1_product, Quaternionf::identity() );
    CHECK_IF_EQUAL( q1_product_reversed, Quaternionf::identity() );
    CHECK_IF_EQUAL( q1_product_reversed, q1_product );
}

void InverseOfAUnitQuaternionIsItsConjugate()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL(Quaternionf::unit_real().inverse(), Quaternionf::unit_real().conjugate());
    CHECK_IF_EQUAL(Quaternionf::unit_i().inverse(), Quaternionf::unit_i().conjugate());
    CHECK_IF_EQUAL(Quaternionf::unit_j().inverse(), Quaternionf::unit_j().conjugate());
    CHECK_IF_EQUAL(Quaternionf::unit_k().inverse(), Quaternionf::unit_k().conjugate());
}

void UnitQuaternionIsNear1()
{
    std::cout << __func__ << std::endl;

    assert( Quaternionf::identity().isUnit() );
    CHECK_IF_EQUAL( Quaternionf::identity().norm(), 1.0f );
}

void MakePureQuaternionSetsRealComponentToZero()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf::make_pure( { 1.0f, 2.0f, 3.0f } ).real(), 0.0f );
}

void MakePureQuaternionSetsImaginaryVectorToInputParameters()
{
    std::cout << __func__ << std::endl;

    Quaternionf pure_q = Quaternionf::make_pure( {1.0f, 2.0f, 3.0f} );

    CHECK_IF_EQUAL( pure_q.i(), 1.0f );
    CHECK_IF_EQUAL( pure_q.j(), 2.0f );
    CHECK_IF_EQUAL( pure_q.k(), 3.0f );
}

void ImaginaryReturnsIJK()
{
    std::cout << __func__ << std::endl;

    Quaternionf pure_q = Quaternionf::make_pure( {1.0f, 2.0f, 3.0f} );

    CHECK_IF_EQUAL( pure_q.imaginary().x, 1.0f );
    CHECK_IF_EQUAL( pure_q.imaginary().y, 2.0f );
    CHECK_IF_EQUAL( pure_q.imaginary().z, 3.0f );
}

void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
{
    std::cout << __func__ << std::endl;

    Quaternionf q1{ 1.0f, 2.0f,  3.0f,  4.0f };
    Quaternionf q2{ 9.0f, 10.0f, 11.0f, 12.0f };

    CHECK_IF_EQUAL( dot( q1, q2 ), 110.0f );
}

void MultiplyingAQuaternionByItsConjugateProducesAPureRealNumber()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf product = q * q.conjugate();

    CHECK_IF_EQUAL( product.i(), 0.0f );
    CHECK_IF_EQUAL( product.j(), 0.0f );
    CHECK_IF_EQUAL( product.k(), 0.0f );
}

void MagnitudeSquaredIsValueOfRealPartOfProductOfAQuaternionAndItsConjugate()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf product = q * q.conjugate();
    float       m_squared = q.magnitudeSquared();

    CHECK_IF_EQUAL( m_squared, std::abs(product.real()) );
}

void MagnitudeIsAbsoluteValueOfRealPartOfProductOfAQuaternionAndItsConjugate()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf product = q * q.conjugate();
    float       magnitude = q.magnitude();

    CHECK_IF_EQUAL(magnitude, std::abs(product.real()) );
}

void DivisionIsJustMultiplyingByTheInverse()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 9.0f, 10.0f, 11.0f, 12.0f };
    Quaternionf q2{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf q_dividedby_q2 = q / q2;
    Quaternionf q_times_inverse_of_q2 = q * q2.inverse();

    CHECK_IF_EQUAL( q_dividedby_q2, q_times_inverse_of_q2 );
}

void ARotationIsStoredAsTheHalfAngle()
{
    std::cout << __func__ << std::endl;

    // 90 deg rotation around X axis
    {
        float       degrees_of_rotation = 90.0f;
        float       half_angle = degrees_of_rotation / 2.0f;
        Quaternionf rotation = Quaternionf::make_rotation( Degree(degrees_of_rotation), 1.0f, 0.0f, 0.0f );

        CHECK_IF_EQUAL( rotation.norm(), 1.0f );
        CHECK_IF_EQUAL( rotation.w(), std::cos( DegreesToRadians(half_angle) ) );
        CHECK_IF_EQUAL( rotation.i(), std::sin( DegreesToRadians(half_angle) ) );
        CHECK_IF_EQUAL( rotation.j(), 0.0f );
        CHECK_IF_EQUAL( rotation.k(), 0.0f );
    }

    // 60 deg rotation around X axis
    {
        float       degrees_of_rotation = 60.0f;
        float       half_angle = degrees_of_rotation / 2.0f;
        Quaternionf rotation = Quaternionf::make_rotation( Degree(degrees_of_rotation), 1.0f, 0.0f, 0.0f );

        CHECK_IF_EQUAL( rotation.norm(), 1.0f );
        CHECK_IF_EQUAL( rotation.w(), std::cos( DegreesToRadians(half_angle) ) );
        CHECK_IF_EQUAL( rotation.i(), std::sin( DegreesToRadians(half_angle) ) );
        CHECK_IF_EQUAL( rotation.j(), 0.0f );
        CHECK_IF_EQUAL( rotation.k(), 0.0f );
    }
}

void MakingARotationIsAccurate()
{
    std::cout << __func__ << std::endl;

    // Rotate 90 deg around X axis.
    // A unit in Y becomes a unit in Z.
    {
        Quaternionf rotation = Quaternionf::make_rotation( Degree(90.0f), 1.0f, 0.0f, 0.0f );
        Quaternionf encoded_point = Quaternionf::encode_point(0.0f, 1.0f, 0.0f);
        Quaternionf transformed_point = rotation * encoded_point * rotation.conjugate();

        CHECK_IF_EQUAL( transformed_point.w(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.i(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.j(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.k(), 1.0f );
    }

    // Rotate 90 deg around Y axis.
    // A unit in X becomes a unit in -Z.
    {
        Quaternionf rotation = Quaternionf::make_rotation( Degree(90.0f), 0.0f, 1.0f, 0.0f );
        Quaternionf encoded_point = Quaternionf::encode_point(1.0f, 0.0f, 0.0f);
        Quaternionf transformed_point = rotation * encoded_point * rotation.conjugate();

        CHECK_IF_EQUAL( transformed_point.w(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.i(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.j(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.k(), -1.0f );
    }
}

void PerformTwoConsecutiveRotations()
{
    std::cout << __func__ << std::endl;

    {
        Quaternionf rotation_90_x = Quaternionf::make_rotation( Degree(90.0f), 1.0f, 0.0f, 0.0f );
        Quaternionf rotation_90_y = Quaternionf::make_rotation( Degree(90.0f), 0.0f, 1.0f, 0.0f );
        Quaternionf encoded_point = Quaternionf::encode_point(0.0f, 1.0f, 0.0f);
        Quaternionf transformed_point = passively_rotate_encoded_point(rotation_90_x, encoded_point);

        transformed_point = passively_rotate_encoded_point(rotation_90_y, transformed_point);

        CHECK_IF_EQUAL( transformed_point.w(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.i(), 1.0f );
        CHECK_IF_EQUAL( transformed_point.j(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.k(), 0.0f );
    }

    // Same thing, but compose the rotations first
    {
        Quaternionf rotation_90_x = Quaternionf::make_rotation( Degree(90.0f), 1.0f, 0.0f, 0.0f );
        Quaternionf rotation_90_y = Quaternionf::make_rotation( Degree(90.0f), 0.0f, 1.0f, 0.0f );
        Quaternionf composed_rotation = compose_rotations( rotation_90_x, rotation_90_y );
        Quaternionf encoded_point = Quaternionf::encode_point(0.0f, 1.0f, 0.0f);
        Quaternionf transformed_point = passively_rotate_encoded_point(composed_rotation, encoded_point);

        CHECK_IF_EQUAL( transformed_point.w(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.i(), 1.0f );
        CHECK_IF_EQUAL( transformed_point.j(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.k(), 0.0f );
    }
}

void TestPow()
{
    std::cout << __func__ << std::endl;

    auto angle = 90.0_deg_f;
    Quaternionf rotation = Quaternionf::make_rotation( angle, Vector3Df::unit_z() );
    Quaternionf exp0 = rotation.pow(0.0f);
    Quaternionf exp_0_5 = rotation.pow(0.5f);
    Quaternionf exp1 = rotation.pow(1.0f);
    Quaternionf exp_2_0 = rotation.pow(2.0f);
    Quaternionf exp_3_0 = rotation.pow(3.0f);
    Quaternionf two_rotations_multiplied{ rotation * rotation };
    Quaternionf three_rotations_multiplied{ rotation * rotation * rotation };

    CHECK_IF_EQUAL( exp0, Quaternionf::identity() );
    CHECK_IF_EQUAL( exp_0_5, Quaternionf::make_rotation( angle * 0.5f, Vector3Df::unit_z()) );
    CHECK_IF_EQUAL( exp1, rotation );
    CHECK_IF_EQUAL( exp_2_0, Quaternionf::make_rotation(angle * 2.0f, Vector3Df::unit_z()) );

    // Check that a quaternion squared via pow() is identical to multiplying by itself
    CHECK_IF_EQUAL( exp_2_0, two_rotations_multiplied );

    CHECK_IF_EQUAL( exp_3_0, three_rotations_multiplied );
}

void TestExp()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Quaternionf{1.0f}.exp().w(), std::exp(1.0f) );
    CHECK_IF_EQUAL( Quaternionf{1.0f}.exp().imaginary(), Vector3Df::zero() );

    CHECK_IF_EQUAL( Quaternionf{2.0f}.exp().w(), std::exp(2.0f) );
    CHECK_IF_EQUAL( Quaternionf{2.0f}.exp().imaginary(), Vector3Df::zero() );

    CHECK_IF_EQUAL( Quaternionf{3.2f}.exp().w(), std::exp(3.2f) );
    CHECK_IF_EQUAL( Quaternionf{3.2f}.exp().imaginary(), Vector3Df::zero() );
}

void ExpAndLogAreInversesOfEachOther()
{
    std::cout << __func__ << std::endl;

    auto a{ Quaternionf::identity() };
    auto b{ Quaternionf::make_rotation(36.3_deg_f, Vector3Df::unit_y()) };
    auto c{ Quaternionf::make_rotation(90.0_deg_f, Vector3Df{1.0f, 1.0f, 1.0f}) };

    CHECK_IF_EQUAL( log( exp(a) ), a );
    CHECK_IF_EQUAL( exp( log(a) ), a );

    CHECK_IF_EQUAL( log( exp(b) ), b );
    CHECK_IF_EQUAL( exp( log(b) ), b );

    CHECK_IF_EQUAL( log( exp(c) ), c );
    CHECK_IF_EQUAL( exp( log(c) ), c );
}

void TestSlerp()
{
    std::cout << __func__ << std::endl;

    Vector3Df   z{ Vector3Df::unit_z() };
    Quaternionf begin = Quaternionf::identity();
    Quaternionf end = Quaternionf::make_rotation( 90.0_deg_f, z );

    // with only the endpoints
    {
        Quaternionf slerp_begin = slerp(begin, end, 0.0f);
        Quaternionf slerp_end = slerp(begin, end, 1.0f);

        CHECK_IF_EQUAL( slerp_begin, begin );
        CHECK_IF_EQUAL( slerp_end, end );
    }

    // 0 to 90 in 10 deg increments
    TestRotationAtRegularIntervals(begin, 90.0_deg_f, z, 9);

    // 0 to 180 in 10 deg increments
    TestRotationAtRegularIntervals(begin, 180.0_deg_f, z, 18);
}

void IsNaNIsTrueWhenAtLeastOneMemberIsNaN()
{
    std::cout << __func__ << std::endl;

    assert( Quaternionf(NAN).isNaN() );
    assert( Quaternionf(NAN, 0.0f, 0.0f, 0.0f).isNaN() );
    assert( Quaternionf(3.2f, NAN, 0.0f, 0.0f).isNaN() );
    assert( Quaternionf(3.2f, 0.0f, NAN, 0.0f).isNaN() );
    assert( Quaternionf(3.2f, 0.0f, 0.0f, NAN).isNaN() );
    assert( !Quaternionf(3.2f, 4.6f, 0.0f, 1.1f).isNaN() );
}

void IsInfIsTrueWhenAtLeastOneMemberIsInf()
{
    std::cout << __func__ << std::endl;

    assert( Quaternionf(INFINITY).isInf() );
    assert( Quaternionf(INFINITY, 0.0f, 0.0f, 0.0f).isInf() );
    assert( Quaternionf(3.2f, INFINITY, 0.0f, 0.0f).isInf() );
    assert( Quaternionf(3.2f, 0.0f, INFINITY, 0.0f).isInf() );
    assert( Quaternionf(3.2f, 0.0f, 0.0f, INFINITY).isInf() );
    assert( !Quaternionf(3.2f, 4.6f, 0.0f, 1.1f).isInf() );
}

void DivideByZeroProducesInf()
{
    std::cout << __func__ << std::endl;

    Quaternionf result{ Quaternionf::identity() / 0.0f };

    assert( result.isInf() );
}
/// @}

/** Run all of the unit tests in this namespace
 * 
 */
void Run()
{
    std::cout << "Running Quaternion Tests..." << std::endl;

    UnitQuaternionIsAsExpected();
    ZeroQuaternionIsAsExpected();
    QuaternionIsConstructedAsExpected();
    QuaternionAddsPerComponent();
    OperatorEqualsComparesMatchingComponents();
    OperatorNotEqualsIsOppositeOfEquals();
    CopyOperatorIsImplemented();
    ConjugateInvertsTheImaginaryComponents();
    ConjugateIsItsOwnInverse();
    RotatingA3DPointByUnitRotationLeavesPointUnchanged();
    ISquaredIsNegativeOne();
    JSquaredIsNegativeOne();
    KSquaredIsNegativeOne();
    IJKIsNegativeOne();
    IJEqualsK();
    JIEqualsNegativeK();
    JKEqualsI();
    KJEqualsNegativeI();
    KIEqualsJ();
    IKEqualsNegativeJ();
    HasOperatorNegate();
    OperatorPlusAndMinusAreInverses();
    NormIsEquivalentToDistance();
    UnitQuaternionHasNormOfOne();
    DividingByAScalarDividesEachComponent();
    MultiplyingByItsOwnInverseProducesUnity();
    InverseOfAUnitQuaternionIsItsConjugate();
    UnitQuaternionIsNear1();
    MakePureQuaternionSetsRealComponentToZero();
    MakePureQuaternionSetsImaginaryVectorToInputParameters();
    ImaginaryReturnsIJK();
    DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues();
    MultiplyingAQuaternionByItsConjugateProducesAPureRealNumber();
    MagnitudeSquaredIsValueOfRealPartOfProductOfAQuaternionAndItsConjugate();
    ARotationIsStoredAsTheHalfAngle();
    MakingARotationIsAccurate();
    PerformTwoConsecutiveRotations();
    TestPow();
    TestExp();
    ExpAndLogAreInversesOfEachOther();
    TestSlerp();
    IsNaNIsTrueWhenAtLeastOneMemberIsNaN();
    IsInfIsTrueWhenAtLeastOneMemberIsInf();
    DivideByZeroProducesInf();

    std::cout << "PASSED!" << std::endl;
}

}
/// @}