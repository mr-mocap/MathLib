#include "QuaternionTests.hpp"
#include "math/Quaternion.hpp"
#include "math/Conversions.hpp"
#include "math/Exponential.hpp"
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


static bool IsNear(float value_to_test, float value_it_should_be, float epsilon = 0.0002f)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}

static bool IsNear(Quaternionf value_to_test, Quaternionf value_it_should_be, float epsilon = 0.0002f)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}

/** Contains the unit tests for Quaternion
 * 
 */
namespace QuaternionTests
{

/// @{
void UnitQuaternionIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Quaternionf unit = Quaternionf::identity();

    assert(unit.w() == 1.0);
    assert(unit.i() == 0.0);
    assert(unit.j() == 0.0);
    assert(unit.k() == 0.0);
}

void ZeroQuaternionIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Quaternionf zero = Quaternionf::zero();

    assert(zero.w() == 0.0);
    assert(zero.i() == 0.0);
    assert(zero.j() == 0.0);
    assert(zero.k() == 0.0);
}

void QuaternionIsConstructedAsExpected()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 1.0, 2.0, 3.0, 4.0 };

    assert(q.w() == 1.0);
    assert(q.i() == 2.0);
    assert(q.j() == 3.0);
    assert(q.k() == 4.0);
}

void QuaternionAddsPerComponent()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_left{ 1.0, 2.0, 3.0, 4.0 };
    Quaternionf q_right{ 5.0, 6.0, 7.0, 8.0 };
    Quaternionf q_result = q_left + q_right;

    assert(q_result.w() == 6.0);
    assert(q_result.i() == 8.0);
    assert(q_result.j() == 10.0);
    assert(q_result.k() == 12.0);
}

void OperatorEqualsComparesMatchingComponents()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_original{ 1.0, 2.0, 3.0, 4.0 };
    Quaternionf q_tocompareagainst{ 1.0, 2.0, 3.0, 4.0 };

    assert(q_original == q_tocompareagainst);
    assert(q_original.w() == q_tocompareagainst.w());
    assert(q_original.i() == q_tocompareagainst.i());
    assert(q_original.j() == q_tocompareagainst.j());
    assert(q_original.k() == q_tocompareagainst.k());
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

    assert(q_original == q_tocompareagainst);

    assert( (q_original != q_tocompareagainst) == false );

    // Now test for each component individually
    assert(q_original != q_different1);
    assert(q_original != q_different2);
    assert(q_original != q_different3);
    assert(q_original != q_different4);
}

void CopyOperatorIsImplemented()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_original{ 2.0, 4.0, 6.0, 8.0 };
    Quaternionf q_copy{ q_original };

    assert(q_original == q_copy);
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

    assert(arbitrary_value1.conjugate() == expected_value1);
    assert(arbitrary_value2.conjugate() == expected_value2);
    assert(arbitrary_value3.conjugate() == expected_value3);
    assert(arbitrary_value4.conjugate() == expected_value4);
}

void ConjugateIsItsOwnInverse()
{
    std::cout << __func__ << std::endl;

    Quaternionf arbitrary_value1{ 6.0, 7.0, 8.0, 9.0 };

    assert(arbitrary_value1.conjugate().conjugate() == arbitrary_value1);
}

void RotatingA3DPointByUnitRotationLeavesPointUnchanged()
{
    std::cout << __func__ << std::endl;

    // The rotation must be of unit length
    Quaternionf unit_rotation = Quaternionf::identity();
    const float point[3] = { 1.0, 3.0, 7.0 };

    // Place 3D point in the imaginary part, leaving the real part as 0.0
    Quaternionf value_to_rotate{ 0.0, point[0], point[1], point[2] };

    assert((unit_rotation * value_to_rotate * unit_rotation.conjugate()) == value_to_rotate);
}

void IJKUnitQuaternionsAreDefined()
{
    std::cout << __func__ << std::endl;

    assert( (Quaternionf::unit_i() == Quaternionf{ 0.0, 1.0, 0.0, 0.0 }) );
    assert( (Quaternionf::unit_j() == Quaternionf{ 0.0, 0.0, 1.0, 0.0 }) );
    assert( (Quaternionf::unit_k() == Quaternionf{ 0.0, 0.0, 0.0, 1.0 }) );
}

void ISquaredIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
    Quaternionf i = Quaternionf::unit_i();

    assert( (i * i) == negative_1 );
}

void JSquaredIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
    Quaternionf j = Quaternionf::unit_j();

    assert( (j * j) == negative_1 );
}

void KSquaredIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
    Quaternionf k = Quaternionf::unit_k();

    assert( (k * k) == negative_1 );
}

void IJKIsNegativeOne()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };

    assert( (Quaternionf::unit_i() * Quaternionf::unit_j() * Quaternionf::unit_k()) == negative_1 );
}

void IJEqualsK()
{
    std::cout << __func__ << std::endl;

    assert( (Quaternionf::unit_i() * Quaternionf::unit_j()) == Quaternionf::unit_k() );
}

void JIEqualsNegativeK()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_k{ 0.0, 0.0, 0.0, -1.0 };

    assert( (Quaternionf::unit_j() * Quaternionf::unit_i()) == negative_k );
}
void JKEqualsI()
{
    std::cout << __func__ << std::endl;

    assert( (Quaternionf::unit_j() * Quaternionf::unit_k()) == Quaternionf::unit_i() );
}

void KJEqualsNegativeI()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_i{ 0.0, -1.0, 0.0, 0.0 };

    assert( (Quaternionf::unit_k() * Quaternionf::unit_j()) == negative_i );
}

void KIEqualsJ()
{
    std::cout << __func__ << std::endl;

    assert( (Quaternionf::unit_k() * Quaternionf::unit_i()) == Quaternionf::unit_j() );
}

void IKEqualsNegativeJ()
{
    std::cout << __func__ << std::endl;

    Quaternionf negative_j{ 0.0, 0.0, -1.0, 0.0 };

    assert( (Quaternionf::unit_i() * Quaternionf::unit_k()) == negative_j );
}

void HasOperatorNegate()
{
    std::cout << __func__ << std::endl;

    assert( (-Quaternionf::identity()   == Quaternionf{ -1.0,  0.0,  0.0,  0.0 }) );
    assert( (-Quaternionf::unit_i() == Quaternionf{  0.0, -1.0,  0.0,  0.0 }) );
    assert( (-Quaternionf::unit_j() == Quaternionf{  0.0,  0.0, -1.0,  0.0 }) );
    assert( (-Quaternionf::unit_k() == Quaternionf{  0.0,  0.0,  0.0, -1.0 }) );

    assert( (-Quaternionf(1.0f, -2.2f, 3.0f, -4.0f) == Quaternionf(-1.0f, 2.2f, -3.0f, 4.0f)) );
}

void OperatorPlusAndMinusAreInverses()
{
    std::cout << __func__ << std::endl;

    Quaternionf::value_type starting_value = 0;
    Quaternionf::value_type value = 6;
    Quaternionf::value_type added_value = starting_value + value;
    Quaternionf::value_type subtracted_value = starting_value - value;

    assert( (added_value - value) == starting_value );
    assert( (subtracted_value + value) == starting_value );
}

void NormIsEquivalentToDistance()
{
    std::cout << __func__ << std::endl;

    // Show that sqrt(4) == 2.
    // i.e. qrt) of a^2 + b^2 + c^2 + d^2 == 2
    // i.e. a^2 + b^2 + c^2 + d^2 == 4
    assert( (Quaternionf{ 1.0, 1.0, 1.0, 1.0 }.norm() == 2.0f) );

    assert( (Quaternionf{ 2.0, 2.0, 2.0, 2.0 }.norm() == 4.0f) );
    assert( (Quaternionf{ 1.0, 2.0, 3.0, 4.0 }.norm() == std::sqrt(30.0f)) ); // 1^2 + 2^2 + 3^2 + 4^2
}

void UnitQuaternionHasNormOfOne()
{
    std::cout << __func__ << std::endl;

    assert( Quaternionf::identity().norm() == 1.0f );
    assert( Quaternionf::unit_i().norm() == 1.0f );
    assert( Quaternionf::unit_j().norm() == 1.0f );
    assert( Quaternionf::unit_k().norm() == 1.0f );
}

void DividingByAScalarDividesEachComponent()
{
    std::cout << __func__ << std::endl;

    assert( ((Quaternionf{1.0f, 2.0f, 3.0f, 4.0f} / 2.0f) == Quaternionf{1.0f / 2.0f, 2.0f / 2.0f, 3.0f / 2.0f, 4.0f / 2.0f}) );
    assert( ((Quaternionf{1.0f, 2.0f, 3.0f, 4.0f} / 3.0f) == Quaternionf{1.0f / 3.0f, 2.0f / 3.0f, 3.0f / 3.0f, 4.0f / 3.0f}) );
}

void MultiplyingByItsOwnInverseProducesUnity()
{
    std::cout << __func__ << std::endl;

    Quaternionf q1{ 6.3f, 2.2f, 1.1f, 0.0f };
    Quaternionf q1_inverse = q1.inverse();
    Quaternionf q1_product = q1_inverse * q1;
    Quaternionf q1_product_reversed = q1 * q1_inverse;

    assert( IsNear(q1_product, Quaternionf::identity()) );
    assert( IsNear(q1_product_reversed, Quaternionf::identity()) );
    assert( IsNear(q1_product_reversed, q1_product) );
}

void InverseOfAUnitQuaternionIsItsConjugate()
{
    std::cout << __func__ << std::endl;

    assert(Quaternionf::unit_real().inverse() == Quaternionf::unit_real().conjugate());
    assert(Quaternionf::unit_i().inverse() == Quaternionf::unit_i().conjugate());
    assert(Quaternionf::unit_j().inverse() == Quaternionf::unit_j().conjugate());
    assert(Quaternionf::unit_k().inverse() == Quaternionf::unit_k().conjugate());
}

void UnitQuaternionIsNear1()
{
    std::cout << __func__ << std::endl;

    assert( Quaternionf::identity().isUnit() );
    assert( IsNear(Quaternionf::identity().norm(), 1.0f) );
}

void MakePureQuaternionSetsRealComponentToZero()
{
    std::cout << __func__ << std::endl;

    assert( Quaternionf::make_pure( { 1.0f, 2.0f, 3.0f } ).real() == 0.0f );
}

void MakePureQuaternionSetsImaginaryVectorToInputParameters()
{
    std::cout << __func__ << std::endl;

    Quaternionf pure_q = Quaternionf::make_pure( {1.0f, 2.0f, 3.0f} );

    assert( pure_q.i() == 1.0f );
    assert( pure_q.j() == 2.0f );
    assert( pure_q.k() == 3.0f );
}

void ImaginaryReturnsIJK()
{
    std::cout << __func__ << std::endl;

    Quaternionf pure_q = Quaternionf::make_pure( {1.0f, 2.0f, 3.0f} );

    assert( pure_q.imaginary().x == 1.0f );
    assert( pure_q.imaginary().y == 2.0f );
    assert( pure_q.imaginary().z == 3.0f );
}

void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
{
    std::cout << __func__ << std::endl;

    Quaternionf q1{ 1.0f, 2.0f,  3.0f,  4.0f };
    Quaternionf q2{ 9.0f, 10.0f, 11.0f, 12.0f };

    assert( dot( q1, q2 ) == 110.0f );
}

void MultiplyingAQuaternionByItsConjugateProducesAPureRealNumber()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf product = q * q.conjugate();

    assert( IsNear(product.i(), 0.0f ) );
    assert( IsNear(product.j(), 0.0f ) );
    assert( IsNear(product.k(), 0.0f ) );
}

void MagnitudeSquaredIsValueOfRealPartOfProductOfAQuaternionAndItsConjugate()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf product = q * q.conjugate();
    float       m_squared = q.magnitudeSquared();

    assert(IsNear( m_squared, std::abs(product.real()) ));
}

void MagnitudeIsAbsoluteValueOfRealPartOfProductOfAQuaternionAndItsConjugate()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf product = q * q.conjugate();
    float       magnitude = q.magnitude();

    assert(IsNear( magnitude, std::abs(product.real()) ));
}

void DivisionIsJustMultiplyingByTheInverse()
{
    std::cout << __func__ << std::endl;

    Quaternionf q{ 9.0f, 10.0f, 11.0f, 12.0f };
    Quaternionf q2{ 3.5f, -45.668f, 113.443f, 6.332f};
    Quaternionf q_dividedby_q2 = q / q2;
    Quaternionf q_times_inverse_of_q2 = q * q2.inverse();

    assert( q_dividedby_q2 == q_times_inverse_of_q2 );
}

void ARotationIsStoredAsTheHalfAngle()
{
    std::cout << __func__ << std::endl;

    // 90 deg rotation around X axis
    {
        float       degrees_of_rotation = 90.0f;
        float       half_angle = degrees_of_rotation / 2.0f;
        Quaternionf rotation = Quaternionf::make_rotation( DegreesToRadians(degrees_of_rotation), 1.0f, 0.0f, 0.0f );

        assert( IsNear(rotation.norm(), 1.0f) );
        assert( IsNear(rotation.w(), std::cos( DegreesToRadians(half_angle) )) );
        assert( IsNear(rotation.i(), std::sin( DegreesToRadians(half_angle) )) );
        assert( IsNear(rotation.j(), 0.0f) );
        assert( IsNear(rotation.k(), 0.0f) );
    }

    // 60 deg rotation around X axis
    {
        float       degrees_of_rotation = 60.0f;
        float       half_angle = degrees_of_rotation / 2.0f;
        Quaternionf rotation = Quaternionf::make_rotation( DegreesToRadians(degrees_of_rotation), 1.0f, 0.0f, 0.0f );

        assert( IsNear(rotation.norm(), 1.0f) );
        assert( IsNear(rotation.w(), std::cos( DegreesToRadians(half_angle) )) );
        assert( IsNear(rotation.i(), std::sin( DegreesToRadians(half_angle) )) );
        assert( IsNear(rotation.j(), 0.0f) );
        assert( IsNear(rotation.k(), 0.0f) );
    }
}

void MakingARotationIsAccurate()
{
    std::cout << __func__ << std::endl;

    // Rotate 90 deg around X axis.
    // A unit in Y becomes a unit in Z.
    {
        Quaternionf rotation = Quaternionf::make_rotation( DegreesToRadians(90.0f), 1.0f, 0.0f, 0.0f );
        Quaternionf encoded_point = Quaternionf::encode_point(0.0f, 1.0f, 0.0f);
        Quaternionf transformed_point = rotation * encoded_point * rotation.conjugate();

        assert( IsNear(transformed_point.w(), 0.0f) );
        assert( IsNear(transformed_point.i(), 0.0f) );
        assert( IsNear(transformed_point.j(), 0.0f) );
        assert( IsNear(transformed_point.k(), 1.0f) );
    }

    // Rotate 90 deg around Y axis.
    // A unit in X becomes a unit in -Z.
    {
        Quaternionf rotation = Quaternionf::make_rotation( DegreesToRadians(90.0f), 0.0f, 1.0f, 0.0f );
        Quaternionf encoded_point = Quaternionf::encode_point(1.0f, 0.0f, 0.0f);
        Quaternionf transformed_point = rotation * encoded_point * rotation.conjugate();

        assert( IsNear(transformed_point.w(), 0.0f) );
        assert( IsNear(transformed_point.i(), 0.0f) );
        assert( IsNear(transformed_point.j(), 0.0f) );
        assert( IsNear(transformed_point.k(), -1.0f) );
    }
}

void PerformTwoConsecutiveRotations()
{
    std::cout << __func__ << std::endl;

    {
        Quaternionf rotation_90_x = Quaternionf::make_rotation( DegreesToRadians(90.0f), 1.0f, 0.0f, 0.0f );
        Quaternionf rotation_90_y = Quaternionf::make_rotation( DegreesToRadians(90.0f), 0.0f, 1.0f, 0.0f );
        Quaternionf encoded_point = Quaternionf::encode_point(0.0f, 1.0f, 0.0f);
        Quaternionf transformed_point = passively_rotate_encoded_point(rotation_90_x, encoded_point);

        transformed_point = passively_rotate_encoded_point(rotation_90_y, transformed_point);

        assert( IsNear(transformed_point.w(), 0.0f) );
        assert( IsNear(transformed_point.i(), 1.0f) );
        assert( IsNear(transformed_point.j(), 0.0f) );
        assert( IsNear(transformed_point.k(), 0.0f) );
    }

    // Same thing, but compose the rotations first
    {
        Quaternionf rotation_90_x = Quaternionf::make_rotation( DegreesToRadians(90.0f), 1.0f, 0.0f, 0.0f );
        Quaternionf rotation_90_y = Quaternionf::make_rotation( DegreesToRadians(90.0f), 0.0f, 1.0f, 0.0f );
        Quaternionf composed_rotation = compose_rotations( rotation_90_x, rotation_90_y );
        Quaternionf encoded_point = Quaternionf::encode_point(0.0f, 1.0f, 0.0f);
        Quaternionf transformed_point = passively_rotate_encoded_point(composed_rotation, encoded_point);

        assert( IsNear(transformed_point.w(), 0.0f) );
        assert( IsNear(transformed_point.i(), 1.0f) );
        assert( IsNear(transformed_point.j(), 0.0f) );
        assert( IsNear(transformed_point.k(), 0.0f) );
    }
}

void TestPow()
{
    float angle = 90.0_deg_f;
    Quaternionf rotation = Quaternionf::make_rotation( angle, Vector3Df::unit_z() );
    Quaternionf exp0 = rotation.pow(0.0f);
    Quaternionf exp_0_5 = rotation.pow(0.5f);
    Quaternionf exp1 = rotation.pow(1.0f);
    Quaternionf exp_2_0 = rotation.pow(2.0f);
    Quaternionf exp_3_0 = rotation.pow(3.0f);
    Quaternionf two_rotations_multiplied{ rotation * rotation };
    Quaternionf three_rotations_multiplied{ rotation * rotation * rotation };

    assert( exp0 == Quaternionf::identity() );
    assert( exp_0_5 == Quaternionf::make_rotation(angle * 0.5f, Vector3Df::unit_z()) );
    assert( exp1 == rotation );
    assert( exp_2_0 == Quaternionf::make_rotation(angle * 2.0f, Vector3Df::unit_z()) );

    // Check that a quaternion squared via pow() is identical to multiplying by itself
    assert( exp_2_0 == two_rotations_multiplied );

    assert( exp_3_0 == three_rotations_multiplied );
}

void TestExp()
{
    assert( Quaternionf{1.0f}.exp().w() == std::exp(1.0f) );
    assert( Quaternionf{1.0f}.exp().imaginary() == Vector3Df::zero() );

    assert( Quaternionf{2.0f}.exp().w() == std::exp(2.0f) );
    assert( Quaternionf{2.0f}.exp().imaginary() == Vector3Df::zero() );

    assert( Quaternionf{3.2f}.exp().w() == std::exp(3.2f) );
    assert( Quaternionf{3.2f}.exp().imaginary() == Vector3Df::zero() );
}

void ExpAndLogAreInversesOfEachOther()
{
    auto a{ Quaternionf::identity() };
    auto b{ Quaternionf::make_rotation(36.3_deg_f, Vector3Df::unit_y()) };
    auto c{ Quaternionf::make_rotation(90.0_deg_f, Vector3Df{1.0f, 1.0f, 1.0f}) };

    assert( log( exp(a) ) == a );
    assert( exp( log(a) ) == a );

    assert( log( exp(b) ) == b );
    assert( exp( log(b) ) == b );

    assert( log( exp(c) ) == c );
    assert( exp( log(c) ) == c );
}

void TestSlerp()
{
    Vector3Df   z{ Vector3Df::unit_z() };
    Quaternionf begin = Quaternionf::identity();
    Quaternionf end = Quaternionf::make_rotation( 90.0_deg_f, z );

    // with only the endpoints
    {
        Quaternionf slerp_begin = slerp(begin, end, 0.0f);
        Quaternionf slerp_end = slerp(begin, end, 1.0f);

        assert( slerp_begin == begin );
        assert( slerp_end == end );
    }

    // 0 to 90 in 10 deg increments
    {
        float step_deg = 10.0f;
        float step_percentage = 1.0f / 9.0f;

        assert( slerp(begin, end, step_percentage * 0.0f) == begin );

        assert( slerp(begin, end, step_percentage * 0.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 0.0f), z) );
        assert( slerp(begin, end, step_percentage * 1.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 1.0f), z) );
        assert( slerp(begin, end, step_percentage * 2.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 2.0f), z) );
        assert( slerp(begin, end, step_percentage * 3.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 3.0f), z) );
        assert( slerp(begin, end, step_percentage * 4.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 4.0f), z) );
        assert( slerp(begin, end, step_percentage * 5.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 5.0f), z) );
        assert( slerp(begin, end, step_percentage * 6.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 6.0f), z) );
        assert( slerp(begin, end, step_percentage * 7.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 7.0f), z) );
        assert( slerp(begin, end, step_percentage * 8.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 8.0f), z) );
        assert( slerp(begin, end, step_percentage * 9.0f) == Quaternionf::make_rotation(DegreesToRadians(step_deg * 9.0f), z) );

        assert( slerp(begin, end, step_percentage * 9.0f) == end );
    }
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

    std::cout << "PASSED!" << std::endl;
}

}
/// @}