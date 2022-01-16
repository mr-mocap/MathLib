#include "UnitTests.h"
#include <cassert>

#define _USE_MATH_DEFINES 1
#include <math.h>


bool IsNear(float value_to_test, float value_it_should_be, float epsilon)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}

bool IsNear(Quaternionf value_to_test, Quaternionf value_it_should_be, float epsilon)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}

bool IsNear(Dualf value_to_test, Dualf value_it_should_be, float epsilon)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}


namespace Q
{

    void UnitQuaternionIsAsExpected()
    {
        Quaternionf unit = Quaternionf::unit();

        assert(unit.w() == 1.0);
        assert(unit.i() == 0.0);
        assert(unit.j() == 0.0);
        assert(unit.k() == 0.0);
    }

    void ZeroQuaternionIsAsExpected()
    {
        Quaternionf zero = Quaternionf::zero();

        assert(zero.w() == 0.0);
        assert(zero.i() == 0.0);
        assert(zero.j() == 0.0);
        assert(zero.k() == 0.0);
    }

    void QuaternionIsConstructedAsExpected()
    {
        Quaternionf q{ 1.0, 2.0, 3.0, 4.0 };

        assert(q.w() == 1.0);
        assert(q.i() == 2.0);
        assert(q.j() == 3.0);
        assert(q.k() == 4.0);
    }

    void QuaternionAddsPerComponent()
    {
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
        Quaternionf q_original{ 2.0, 4.0, 6.0, 8.0 };
        Quaternionf q_copy{ q_original };

        assert(q_original == q_copy);
    }

    void ConjugateInvertsTheImaginaryComponents()
    {
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
        Quaternionf arbitrary_value1{ 6.0, 7.0, 8.0, 9.0 };

        assert(arbitrary_value1.conjugate().conjugate() == arbitrary_value1);
    }

    void RotatingA3DPointByUnitRotationLeavesPointUnchanged()
    {
        // The rotation must be of unit length
        Quaternionf unit_rotation = Quaternionf::unit();
        const float point[3] = { 1.0, 3.0, 7.0 };

        // Place 3D point in the imaginary part, leaving the real part as 0.0
        Quaternionf value_to_rotate{ 0.0, point[0], point[1], point[2] };

        assert((unit_rotation * value_to_rotate * unit_rotation.conjugate()) == value_to_rotate);
    }

    void IJKUnitQuaternionsAreDefined()
    {
        assert( (Quaternionf::unit_i() == Quaternionf{ 0.0, 1.0, 0.0, 0.0 }) );
        assert( (Quaternionf::unit_j() == Quaternionf{ 0.0, 0.0, 1.0, 0.0 }) );
        assert( (Quaternionf::unit_k() == Quaternionf{ 0.0, 0.0, 0.0, 1.0 }) );
    }

    void ISquaredIsNegativeOne()
    {
        Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
        Quaternionf i = Quaternionf::unit_i();

        assert( (i * i) == negative_1 );
    }

    void JSquaredIsNegativeOne()
    {
        Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
        Quaternionf j = Quaternionf::unit_j();

        assert( (j * j) == negative_1 );
    }

    void KSquaredIsNegativeOne()
    {
        Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };
        Quaternionf k = Quaternionf::unit_k();

        assert( (k * k) == negative_1 );
    }

    void IJKIsNegativeOne()
    {
        Quaternionf negative_1{ -1.0, 0.0, 0.0, 0.0 };

        assert( (Quaternionf::unit_i() * Quaternionf::unit_j() * Quaternionf::unit_k()) == negative_1 );
    }

    void IJEqualsK()
    {
        assert( (Quaternionf::unit_i() * Quaternionf::unit_j()) == Quaternionf::unit_k() );
    }

    void JIEqualsNegativeK()
    {
        Quaternionf negative_k{ 0.0, 0.0, 0.0, -1.0 };

        assert( (Quaternionf::unit_j() * Quaternionf::unit_i()) == negative_k );
    }
    void JKEqualsI()
    {
        assert( (Quaternionf::unit_j() * Quaternionf::unit_k()) == Quaternionf::unit_i() );
    }

    void KJEqualsNegativeI()
    {
        Quaternionf negative_i{ 0.0, -1.0, 0.0, 0.0 };

        assert( (Quaternionf::unit_k() * Quaternionf::unit_j()) == negative_i );
    }

    void KIEqualsJ()
    {
        Quaternionf result = Quaternionf::unit_k() * Quaternionf::unit_i();

        assert( (Quaternionf::unit_k() * Quaternionf::unit_i()) == Quaternionf::unit_j() );
    }

    void IKEqualsNegativeJ()
    {
        Quaternionf negative_j{ 0.0, 0.0, -1.0, 0.0 };
        Quaternionf result = Quaternionf::unit_i() * Quaternionf::unit_k();

        assert( (Quaternionf::unit_i() * Quaternionf::unit_k()) == negative_j );
    }

    void HasOperatorNegate()
    {
        assert( (-Quaternionf::unit()   == Quaternionf{ -1.0,  0.0,  0.0,  0.0 }) );
        assert( (-Quaternionf::unit_i() == Quaternionf{  0.0, -1.0,  0.0,  0.0 }) );
        assert( (-Quaternionf::unit_j() == Quaternionf{  0.0,  0.0, -1.0,  0.0 }) );
        assert( (-Quaternionf::unit_k() == Quaternionf{  0.0,  0.0,  0.0, -1.0 }) );

        assert( (-Quaternionf(1.0f, -2.2f, 3.0f, -4.0f) == Quaternionf(-1.0f, 2.2f, -3.0f, 4.0f)) );
    }

    void OperatorPlusAndMinusAreInverses()
    {
        Quaternionf::value_type starting_value = 0;
        Quaternionf::value_type value = 6;
        Quaternionf::value_type added_value = starting_value + value;
        Quaternionf::value_type subtracted_value = starting_value - value;

        assert( (added_value - value) == starting_value );
        assert( (subtracted_value + value) == starting_value );
    }

    void NormIsEquivalentToDistance()
    {
        // Show that sqrt(4) == 2.
        // i.e. qrt) of a^2 + b^2 + c^2 + d^2 == 2
        // i.e. a^2 + b^2 + c^2 + d^2 == 4
        assert( (Quaternionf{ 1.0, 1.0, 1.0, 1.0 }.norm() == 2.0f) );

        assert( (Quaternionf{ 2.0, 2.0, 2.0, 2.0 }.norm() == 4.0f) );
        assert( (Quaternionf{ 1.0, 2.0, 3.0, 4.0 }.norm() == std::sqrt(30.0f)) ); // 1^2 + 2^2 + 3^2 + 4^2
    }

    void UnitQuaternionHasNormOfOne()
    {
        assert( Quaternionf::unit().norm() == 1.0f );
        assert( Quaternionf::unit_i().norm() == 1.0f );
        assert( Quaternionf::unit_j().norm() == 1.0f );
        assert( Quaternionf::unit_k().norm() == 1.0f );
    }

    void DividingByAScalarDividesEachComponent()
    {
        assert( ((Quaternionf{1.0f, 2.0f, 3.0f, 4.0f} / 2.0f) == Quaternionf{1.0f / 2.0f, 2.0f / 2.0f, 3.0f / 2.0f, 4.0f / 2.0f}) );
        assert( ((Quaternionf{1.0f, 2.0f, 3.0f, 4.0f} / 3.0f) == Quaternionf{1.0f / 3.0f, 2.0f / 3.0f, 3.0f / 3.0f, 4.0f / 3.0f}) );
    }

    void MultiplyingByItsOwnInverseProducesUnity()
    {
        Quaternionf q1{ 6.3f, 2.2f, 1.1f, 0.0f };
        Quaternionf q1_inverse = q1.inverse();
        Quaternionf q1_product = q1_inverse * q1;
        Quaternionf q1_product_reversed = q1 * q1_inverse;

        assert( IsNear(q1_product, Quaternionf::unit()) );
        assert( IsNear(q1_product_reversed, Quaternionf::unit()) );
        assert( IsNear(q1_product_reversed, q1_product) );
    }

    void InverseOfAUnitQuaternionIsItsConjugate()
    {
        assert(Quaternionf::unit_real().inverse() == Quaternionf::unit_real().conjugate());
        assert(Quaternionf::unit_i().inverse() == Quaternionf::unit_i().conjugate());
        assert(Quaternionf::unit_j().inverse() == Quaternionf::unit_j().conjugate());
        assert(Quaternionf::unit_k().inverse() == Quaternionf::unit_k().conjugate());
    }

    void UnitQuaternionIsNear1()
    {
        assert( Quaternionf::unit().isUnit() );
    }

    void MakePureQuaternionSetsRealComponentToZero()
    {
        assert( make_pure_quaternion( std::make_tuple( 1.0f, 2.0f, 3.0f ) ).real() == 0.0f );
    }

    void MakePureQuaternionSetsImaginaryVectorToInputParameters()
    {
        Quaternionf pure_q = make_pure_quaternion( std::tuple{1.0f, 2.0f, 3.0f} );

        assert( pure_q.i() == 1.0f );
        assert( pure_q.j() == 2.0f );
        assert( pure_q.k() == 3.0f );
    }

    void ImaginaryReturnsIJK()
    {
        Quaternionf pure_q = make_pure_quaternion( std::tuple{1.0f, 2.0f, 3.0f} );

        assert( std::get<0>(pure_q.imaginary()) == 1.0f );
        assert( std::get<1>(pure_q.imaginary()) == 2.0f );
        assert( std::get<2>(pure_q.imaginary()) == 3.0f );
    }

    void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
    {
        Quaternionf q1{ 1.0f, 2.0f,  3.0f,  4.0f };
        Quaternionf q2{ 9.0f, 10.0f, 11.0f, 12.0f };

        assert( dot( q1, q2 ) == 110.0f );
    }

    void MultiplyingAQuaternionByItsConjugateProducesAPureRealNumber()
    {
        Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
        Quaternionf product = q * q.conjugate();

        assert( IsNear(product.i(), 0.0f ) );
        assert( IsNear(product.j(), 0.0f ) );
        assert( IsNear(product.k(), 0.0f ) );
    }

    void MagnitudeSquaredIsValueOfRealPartOfProductOfAQuaternionAndItsConjugate()
    {
        Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
        Quaternionf product = q * q.conjugate();
        float       m_squared = q.magnitudeSquared();

        assert(IsNear( m_squared, std::abs(product.real()) ));
    }

    void MagnitudeIsAbsoluteValueOfRealPartOfProductOfAQuaternionAndItsConjugate()
    {
        Quaternionf q{ 3.5f, -45.668f, 113.443f, 6.332f};
        Quaternionf product = q * q.conjugate();
        float       magnitude = q.magnitude();

        assert(IsNear( magnitude, std::abs(product.real()) ));
    }

    void DivisionIsJustMultiplyingByTheInverse()
    {
        Quaternionf q{ 9.0f, 10.0f, 11.0f, 12.0f };
        Quaternionf q2{ 3.5f, -45.668f, 113.443f, 6.332f};
        Quaternionf q_dividedby_q2 = q / q2;
        Quaternionf q_times_inverse_of_q2 = q * q2.inverse();

        assert( IsNear(q_dividedby_q2, q_times_inverse_of_q2) );
    }
}

void TestQuaternion()
{
    using namespace Q;

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
}

namespace D
{
    void UnitDualIsAsExpected()
    {
        Dualf unit = Dualf::unit();

        assert(unit.real == 1.0);
        assert(unit.dual == 0.0);
    }

    void ZeroDualIsAsExpected()
    {
        Dualf zero = Dualf::zero();

        assert(zero.real == 0.0);
        assert(zero.dual == 0.0);
    }

    void MakePureDualSetsRealComponentToZero()
    {
        assert( make_pure_dual(3.0f).real == 0.0f );
    }

    void MakePureDualSetsDualComponentToInputParameter()
    {
        assert( make_pure_dual(3.0f).dual == 3.0f );
    }

    void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
    {
        Dualf d1{ 1.0f, 3.0f  };
        Dualf d2{ 9.0f, 11.0f };

        assert( dot( d1, d2 ) == 42.0f );
    }

    void DualScalarSquareRootTimesItselfIsTheOriginalNumber()
    {
        Dualf original_number{ 3.456f, 86.332f };
        Dualf root = dualscalar_sqrt(original_number);
        Dualf root_squared = root * root;

        assert( IsNear(original_number, root_squared) );
    }
}

void TestDual()
{
    using namespace D;

    UnitDualIsAsExpected();
    ZeroDualIsAsExpected();
    MakePureDualSetsRealComponentToZero();
    MakePureDualSetsDualComponentToInputParameter();
    DualScalarSquareRootTimesItselfIsTheOriginalNumber();
}

namespace DQ
{
    void PureRotationHasZeroTranslation()
    {
        assert(make_dualquaternion_rotation(0.0f, std::tuple{0.0f, 1.0f, 0.0f} ).dual == Quaternionf::zero());
        assert(make_dualquaternion_rotation(float(M_PI_4), std::tuple{0.0f, 0.0f, 1.0f}).dual == Quaternionf::zero());
        assert(make_dualquaternion_rotation(float(M_PI_2), std::tuple{1.0f, 0.0f, 0.0f}).dual == Quaternionf::zero());
    }

    void PureTranslationHasIdentityRotation()
    {
        assert(make_dualquaternion_translation( std::tuple{ 1.0f, 2.0f, 3.0f } ).real == Quaternionf::unit());
    }

    void MagnitudeOfNormalizedDualQuaternionIsOne()
    {
        DualQuaternionf a{ Quaternionf{6.0f, 22.34f, -3.12f, 100.04f}, Quaternionf{1.0f, -43.1113f, -6.0f, 0.0f} };
        DualQuaternionf normalized_a = normalized(a);

        assert( IsNear( dualquaternion_norm(normalized_a), Dualf::unit() ) );
        assert( !is_unit(a) );
    }
}

void TestDualQuaternion()
{
    using namespace DQ;

    PureRotationHasZeroTranslation();
    PureTranslationHasIdentityRotation();
    MagnitudeOfNormalizedDualQuaternionIsOne();
}