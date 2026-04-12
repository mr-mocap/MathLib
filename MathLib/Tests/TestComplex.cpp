#include <Math/math/Complex.hpp>
#include <Math/math/Conversions.hpp>
#include <Math/math/Checks.hpp>
#include <cassert>
#include <iostream>
#include <cstdlib>

/** @file
 * 
 *  @hideincludegraph
 */

/** @defgroup ComplexTests Complex Unit Tests
 * 
 *  Here are all the unit tests used to exercise the Complex class
 * 
 *  @ingroup UnitTests
 * 
 *  @{
 */


/** Contains the unit tests for Complex
 * 
 */
namespace ComplexTests
{

using namespace Math;
using namespace Math::Literals;

void TestRotationAtRegularIntervals(Complexf begin, Degreef amount_of_rotation, int num_equal_steps)
{
    Complexf end_rotation{ Complexf::make_rotation(amount_of_rotation) };
    float step_percentage = 1.0f / num_equal_steps;

    for (int iCurrentStep = 0; iCurrentStep < num_equal_steps; ++iCurrentStep)
    {
        float    current_percentage{ step_percentage * iCurrentStep };
        Degreef  current_rotation_amount{ amount_of_rotation * current_percentage };
        Complexf new_rotation{ Complexf::make_rotation(current_rotation_amount) };
        Complexf slerp_result = slerp(begin, end_rotation, current_percentage);

        CHECK_IF_EQUAL( slerp_result, new_rotation);
    }
    Complexf slerp_result = slerp(begin, end_rotation, 1.0f);

    CHECK_IF_EQUAL( slerp_result, end_rotation);
}

/// @{
void UnitComplexIsAsExpected()
{
    Complexf unit = Complexf::identity();

    CHECK_IF_EQUAL(unit.real(), 1.0f);
    CHECK_IF_EQUAL(unit.i(), 0.0f);
}

void ZeroComplexIsAsExpected()
{
    Complexf zero = Complexf::zero();

    CHECK_IF_EQUAL(zero.real(), 0.0f);
    CHECK_IF_EQUAL(zero.i(), 0.0f);
}

void ComplexIsConstructedAsExpected()
{
    Complexf c{ 1.0, 2.0 };

    CHECK_IF_EQUAL(c.real(), 1.0f);
    CHECK_IF_EQUAL(c.i(), 2.0f);
}

void ComplexAddsPerComponent()
{
    Complexf c_left{ 1.0, 2.0 };
    Complexf c_right{ 5.0, 6.0 };
    Complexf c_result = c_left + c_right;

    CHECK_IF_EQUAL(c_result.real(), 6.0f);
    CHECK_IF_EQUAL(c_result.i(), 8.0f);
}

void OperatorEqualsComparesMatchingComponents()
{ 
    Complexf c_original{ 1.0, 2.0 };
    Complexf c_tocompareagainst{ 1.0, 2.0 };

    CHECK_IF_EQUAL(c_original, c_tocompareagainst);
    CHECK_IF_EQUAL(c_original.real(), c_tocompareagainst.real());
    CHECK_IF_EQUAL(c_original.i(), c_tocompareagainst.i());
}
    
void OperatorNotEqualsIsOppositeOfEquals()
{
    Complexf c_original{ 1.0, 2.0 };
    Complexf c_tocompareagainst{ 1.0, 2.0 };
    Complexf c_different4{ -1.0, -2.0 };
    Complexf c_different3{ 99.0, 2.0 };
    Complexf c_different2{ 1.0, 12.0 };
    Complexf c_different1{ 100.0, 2.0 };

    CHECK_IF_EQUAL(c_original, c_tocompareagainst);

    assert( (c_original != c_tocompareagainst) == false );

    // Now test for each component individually
    CHECK_IF_NOT_EQUAL(c_original, c_different1);
    CHECK_IF_NOT_EQUAL(c_original, c_different2);
    CHECK_IF_NOT_EQUAL(c_original, c_different3);
    CHECK_IF_NOT_EQUAL(c_original, c_different4);
}

void CopyOperatorIsImplemented()
{
    Complexf q_original{ 2.0, 4.0 };
    Complexf q_copy{ q_original };

    CHECK_IF_EQUAL(q_original, q_copy);
}

void ConjugateInvertsTheImaginaryComponent()
{
    Complexf arbitrary_value1{ 1.0, 2.0 };
    Complexf arbitrary_value2{ 1.0, -2.0 };
    Complexf arbitrary_value3{ 1.0, 2.0 };

    Complexf expected_value1{ 1.0, -2.0 };
    Complexf expected_value2{ 1.0, 2.0 };
    Complexf expected_value3{ 1.0, -2.0 };

    CHECK_IF_EQUAL(arbitrary_value1.conjugate(), expected_value1);
    CHECK_IF_EQUAL(arbitrary_value2.conjugate(), expected_value2);
    CHECK_IF_EQUAL(arbitrary_value3.conjugate(), expected_value3);
}

void ConjugateIsItsOwnInverse()
{
    Complexf arbitrary_value1{ 6.0, 7.0 };

    CHECK_IF_EQUAL(arbitrary_value1.conjugate().conjugate(), arbitrary_value1);
}

void IUnitCoomplexIsDefined()
{
    CHECK_IF_EQUAL( Complexf::unit_i(), Complexf{ 0.0, 1.0 } );
}

void ISquaredIsNegativeOne()
{
    Complexf negative_1{ -1.0, 0.0 };
    Complexf i = Complexf::unit_i();

    CHECK_IF_EQUAL( i * i, negative_1 );
}

void HasOperatorNegate()
{
    CHECK_IF_EQUAL( -Complexf::identity(), Complexf{ -1.0,  0.0 } );
    CHECK_IF_EQUAL( -Complexf::unit_i(),   Complexf{  0.0, -1.0 } );

    CHECK_IF_EQUAL( -Complexf(1.0f, -2.2f), Complexf(-1.0f, 2.2f) );
}

void OperatorPlusAndMinusAreInverses()
{
    Complexf::value_type starting_value = 0;
    Complexf::value_type value = 6;
    Complexf::value_type added_value = starting_value + value;
    Complexf::value_type subtracted_value = starting_value - value;

    CHECK_IF_EQUAL( added_value - value, starting_value );
    CHECK_IF_EQUAL( subtracted_value + value, starting_value );
}

void NormIsEquivalentToDistance()
{
    CHECK_IF_EQUAL( Complexf{ 1.0, 1.0 }.norm(), std::sqrt(1.0f + 1.0f) );

    CHECK_IF_EQUAL( Complexf{ 2.0, 2.0 }.norm(), std::sqrt(4.0f + 4.0f) );
    CHECK_IF_EQUAL( Complexf{ 1.0, 2.0 }.norm(), std::sqrt(1.0f + 4.0f) ); // 1^2 + 2^2
}

void UnitComplexHasNormOfOne()
{
    CHECK_IF_EQUAL( Complexf::identity().norm(), 1.0f );
    CHECK_IF_EQUAL( Complexf::unit_i().norm(), 1.0f );
}

void DividingByAScalarDividesEachComponent()
{
    {
        Complexf a(1.0f, 2.0f);
        Complexf a_div = a / 2.0f;
        Complexf b(1.0f / 2.0f, 2.0f / 2.0f);

        CHECK_IF_EQUAL( a_div, b );
    }
    {
        Complexf a(1.0f, 2.0f);
        Complexf a_div = a / 3.0f;
        Complexf b(1.0f / 3.0f, 2.0f / 3.0f);

        CHECK_IF_EQUAL( a_div, b );
    }
}

void MultiplyingByAScalarMultipliesEachComponent()
{
    {
        Complexf a(1.0f, 2.0f);
        Complexf a_mul = a * 2.0f;
        Complexf b(1.0f * 2.0f, 2.0f * 2.0f);

        CHECK_IF_EQUAL( a_mul, b );
    }
    {
        Complexf a(1.0f, 2.0f);
        Complexf a_mul = a * 3.0f;
        Complexf b(1.0f * 3.0f, 2.0f * 3.0f);

        CHECK_IF_EQUAL( a_mul, b );
    }
}

void MultiplyingByItsOwnInverseProducesUnity()
{
    Complexf c1{ 6.3f, 2.2f };
    Complexf c1_inverse = c1.inverse();
    Complexf c1_product = c1_inverse * c1;
    Complexf c1_product_reversed = c1 * c1_inverse;

    CHECK_IF_EQUAL( c1_product, Complexf::identity() );
    CHECK_IF_EQUAL( c1_product_reversed, Complexf::identity() );
    CHECK_IF_EQUAL( c1_product_reversed, c1_product );
}

void InverseOfAUnitComplexIsItsConjugate()
{
    CHECK_IF_EQUAL(Complexf::unit_real().inverse(), Complexf::unit_real().conjugate());
    CHECK_IF_EQUAL(Complexf::unit_i().inverse(), Complexf::unit_i().conjugate());
}

void UnitComplexIsNear1()
{
    assert( Complexf::identity().isUnit() );
    CHECK_IF_EQUAL( Complexf::identity().norm(), 1.0f );
}

void MakePureComplexSetsRealComponentToZero()
{
    CHECK_IF_EQUAL( Complexf::make_pure( 2.0f ).real(), 0.0f );
}

void MakePureComplexSetsImaginaryToInputParameter()
{
    CHECK_IF_EQUAL( Complexf::make_pure( 2.0f ).imaginary(), 2.0f );
}

void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
{
    Complexf c1{ 1.0f, 2.0f };
    Complexf c2{ 9.0f, 10.0f };

    CHECK_IF_EQUAL( dot( c1, c2 ), 29.0f );
}

void MultiplyingAComplexByItsConjugateProducesAPureRealNumber()
{
    Complexf c{ 3.5f, -45.668f };
    Complexf product = c * c.conjugate();

    CHECK_IF_EQUAL( product.real(), 2097.81616f );
    CHECK_IF_EQUAL( product.imaginary(), 0.0f );
}

void MagnitudeSquaredIsValueOfRealPartOfProductOfAComplexAndItsConjugate()
{
    Complexf c{ 3.5f, 113.443f };
    Complexf product = c * c.conjugate();
    float    m_squared = c.magnitudeSquared();

    CHECK_IF_EQUAL( m_squared, std::abs(product.real()) );
}

void MakingARotationIsAccurate()
{
    // Rotate 90 deg
    {
        Complexf rotation = Complexf::make_rotation( Degreef(90.0f) );
        Complexf encoded_point = Complexf::encode_point(0.0f, 1.0f);
        Complexf transformed_point = rotation * encoded_point;

        CHECK_IF_EQUAL( transformed_point.real(), -1.0f );
        CHECK_IF_EQUAL( transformed_point.imaginary(), 0.0f );
    }

    {
        Complexf rotation = Complexf::make_rotation( Degreef(90.0f) );
        Complexf encoded_point = Complexf::encode_point(1.0f, 0.0f);
        Complexf transformed_point = rotation * encoded_point;

        CHECK_IF_EQUAL( transformed_point.real(), 0.0f );
        CHECK_IF_EQUAL( transformed_point.imaginary(), 1.0f );
    }
}

void PerformTwoConsecutiveRotations()
{
    {
        Complexf rotation_90 = Complexf::make_rotation( Degreef(90.0f) );
        Complexf encoded_point = Complexf::encode_point(3.0f, 0.0f);
        Complexf transformed_point = passively_rotate_encoded_point(rotation_90, encoded_point);

        transformed_point = passively_rotate_encoded_point(rotation_90, transformed_point);

        CHECK_IF_EQUAL( transformed_point.real(), -3.0f );
        CHECK_IF_EQUAL( transformed_point.imaginary(), 0.0f );
    }

    // Same thing, but compose the rotations first
    {
        Complexf rotation_45 = Complexf::make_rotation( Degreef(45.0f) );
        Complexf composed_rotation = compose_rotations( rotation_45, rotation_45 );
        Complexf encoded_point = Complexf::encode_point(0.0f, 8.0f);
        Complexf transformed_point = passively_rotate_encoded_point(composed_rotation, encoded_point);

        CHECK_IF_EQUAL( transformed_point.real(), -8.0f );
        CHECK_IF_EQUAL( transformed_point.imaginary(), 0.0f );
    }
}

void TestPow()
{
    auto angle = 90.0_deg_f;
    Complexf rotation = Complexf::make_rotation( angle );
    Complexf exp0 = rotation.pow(0.0f);
    Complexf exp_0_5 = rotation.pow(0.5f);
    Complexf exp1 = rotation.pow(1.0f);
    Complexf exp_2_0 = rotation.pow(2.0f);
    Complexf exp_3_0 = rotation.pow(3.0f);
    Complexf two_rotations_multiplied{ rotation * rotation };
    Complexf three_rotations_multiplied{ rotation * rotation * rotation };

    CHECK_IF_EQUAL( exp0, Complexf::identity() ); // Any number to the zero power should be 1
    CHECK_IF_EQUAL( exp_0_5, Complexf::make_rotation( angle * 0.5f ) );
    CHECK_IF_EQUAL( exp1, rotation );
    CHECK_IF_EQUAL( exp_2_0, Complexf::make_rotation( angle * 2.0f ) );

    // Check that a complex squared via pow() is identical to multiplying by itself
    CHECK_IF_EQUAL( exp_2_0, two_rotations_multiplied );

    CHECK_IF_EQUAL( exp_3_0, three_rotations_multiplied );
}

void TestExp()
{
    CHECK_IF_EQUAL( Complexf{1.0f}.exp().real(), std::exp(1.0f) );
    CHECK_IF_EQUAL( Complexf{1.0f}.exp().imaginary(), 0.0f );

    CHECK_IF_EQUAL( Complexf{2.0f}.exp().real(), std::exp(2.0f) );
    CHECK_IF_EQUAL( Complexf{1.0f}.exp().imaginary(), 0.0f );

    CHECK_IF_EQUAL( Complexf{3.2f}.exp().real(), std::exp(3.2f) );
    CHECK_IF_EQUAL( Complexf{1.0f}.exp().imaginary(), 0.0f );
}

void ExpAndLogAreInversesOfEachOther()
{
    auto a{ Complexf::identity() };
    auto b{ Complexf::make_rotation(36.3_deg_f) };
    auto c{ Complexf::make_rotation(90.0_deg_f) };

    CHECK_IF_EQUAL( log( exp(a) ), a );
    CHECK_IF_EQUAL( exp( log(a) ), a );

    CHECK_IF_EQUAL( log( exp(b) ), b );
    CHECK_IF_EQUAL( exp( log(b) ), b );

    CHECK_IF_EQUAL( log( exp(c) ), c );
    CHECK_IF_EQUAL( exp( log(c) ), c );
}

void TestSlerp()
{
    Complexf begin = Complexf::identity();
    Complexf end   = Complexf::make_rotation( 90.0_deg_f );

    // with only the endpoints
    {
        Complexf slerp_begin = slerp(begin, end, 0.0f);
        Complexf slerp_end   = slerp(begin, end, 1.0f);

        CHECK_IF_EQUAL( slerp_begin, begin );
        CHECK_IF_EQUAL( slerp_end, end );
    }

    // 0 to 90 in 10 deg increments
    TestRotationAtRegularIntervals(begin, 90.0_deg_f, 9);

    // 0 to 180 in 10 deg increments
    TestRotationAtRegularIntervals(begin, 180.0_deg_f, 18);
}
#if 0
void IsNaNIsTrueWhenAtLeastOneMemberIsNaN()
{
    assert( Quaternionf(NAN).isNaN() );
    assert( Quaternionf(NAN, 0.0f, 0.0f, 0.0f).isNaN() );
    assert( Quaternionf(3.2f, NAN, 0.0f, 0.0f).isNaN() );
    assert( Quaternionf(3.2f, 0.0f, NAN, 0.0f).isNaN() );
    assert( Quaternionf(3.2f, 0.0f, 0.0f, NAN).isNaN() );
    assert( !Quaternionf(3.2f, 4.6f, 0.0f, 1.1f).isNaN() );
}

void IsInfIsTrueWhenAtLeastOneMemberIsInf()
{
    assert( Quaternionf(INFINITY).isInf() );
    assert( Quaternionf(INFINITY, 0.0f, 0.0f, 0.0f).isInf() );
    assert( Quaternionf(3.2f, INFINITY, 0.0f, 0.0f).isInf() );
    assert( Quaternionf(3.2f, 0.0f, INFINITY, 0.0f).isInf() );
    assert( Quaternionf(3.2f, 0.0f, 0.0f, INFINITY).isInf() );
    assert( !Quaternionf(3.2f, 4.6f, 0.0f, 1.1f).isInf() );
}

void DivideByZeroProducesInf()
{
    Quaternionf result{ Quaternionf::identity() / 0.0f };

    assert( result.isInf() );
}
#endif
/// @}

/** Run all of the unit tests in this namespace
 * 
 */
void Run()
{
    UnitComplexIsAsExpected();
    ZeroComplexIsAsExpected();
    ComplexIsConstructedAsExpected();
    ComplexAddsPerComponent();
    OperatorEqualsComparesMatchingComponents();
    OperatorNotEqualsIsOppositeOfEquals();
    CopyOperatorIsImplemented();
    ConjugateInvertsTheImaginaryComponent();
    ConjugateIsItsOwnInverse();
    IUnitCoomplexIsDefined();
    ISquaredIsNegativeOne();
    HasOperatorNegate();
    OperatorPlusAndMinusAreInverses();
    NormIsEquivalentToDistance();
    UnitComplexHasNormOfOne();
    DividingByAScalarDividesEachComponent();
    MultiplyingByAScalarMultipliesEachComponent();
    MultiplyingByItsOwnInverseProducesUnity();
    InverseOfAUnitComplexIsItsConjugate();
    UnitComplexIsNear1();
    MakePureComplexSetsRealComponentToZero();
    MakePureComplexSetsImaginaryToInputParameter();
    DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues();
    MultiplyingAComplexByItsConjugateProducesAPureRealNumber();
    MagnitudeSquaredIsValueOfRealPartOfProductOfAComplexAndItsConjugate();
    MakingARotationIsAccurate();
    PerformTwoConsecutiveRotations();
    TestPow();
    TestExp();
    ExpAndLogAreInversesOfEachOther();
    TestSlerp();
#if 0
    IsNaNIsTrueWhenAtLeastOneMemberIsNaN();
    IsInfIsTrueWhenAtLeastOneMemberIsInf();
    DivideByZeroProducesInf();
#endif
}

}
/// @}

int main(void)
{
    ComplexTests::Run();
    return EXIT_SUCCESS;
}