#include "DualNumberTests.hpp"
#include "math/DualQuaternion.hpp"
#include "math/types.hpp"
#include "math/Conversions.hpp"
#include <tuple>
#include <cassert>
#include <iostream>

#define _USE_MATH_DEFINES 1
#include <math.h>


static bool IsNear(Dualf value_to_test, Dualf value_it_should_be, float epsilon = 0.0002f)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}

namespace DualQuaternionTests
{

/** @addtogroup DualQuaternionTests
 *   
 *  @ingroup Tests
 */
/// @{
void PureRotationHasZeroTranslation()
{
    std::cout << __func__ << std::endl;

    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(0.0f, 0.0f, 1.0f, 0.0f) ).dual() == Quaternionf::zero());
    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(float(M_PI_4), 0.0f, 0.0f, 1.0f) ).dual() == Quaternionf::zero());
    assert( DualQuaternionf::make_rotation( Quaternionf::make_rotation(float(M_PI_2), 1.0f, 0.0f, 0.0f) ).dual() == Quaternionf::zero());
}

void PureTranslationHasIdentityRotation()
{
    std::cout << __func__ << std::endl;

    assert( DualQuaternionf::make_translation(1.0f, 2.0f, 3.0f).real() == Quaternionf::identity());
}

void MagnitudeOfNormalizedDualQuaternionIsOne()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf a{ Quaternionf{6.0f, 22.34f, -3.12f, 100.04f}, Quaternionf{1.0f, -43.1113f, -6.0f, 0.0f} };
    DualQuaternionf normalized_a = a.normalized();

    assert( IsNear( normalized_a.norm(), Dualf::identity() ) );
    assert( !a.is_unit() );
}

void MagnitudeIsTheNumberMultipliedByItsConjugate()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf a{ Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f ),
                       10.0f, 10.0f, 10.0f
                     };
    DualQuaternionf a_times_conjugate{ a * a.conjugate() };
    Dualf mag_a = a.magnitude();
    Dualf mag_a_times_conjugate = a_times_conjugate.magnitude();

    assert( IsNear(mag_a, mag_a_times_conjugate) );
}

void UnitCondition()
{
    std::cout << __func__ << std::endl;

    Quaternionf q_rotation{ Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f ) };
    DualQuaternionf a{ DualQuaternionf::make_coordinate_system( q_rotation, 10.0f, 10.0f, 10.0f ) };
    DualQuaternionf conjugate_real{ a.real().conjugate(), a.dual()};
    DualQuaternionf conjugate_dual{ a.dual().conjugate(), a.real()};
    DualQuaternionf sum = conjugate_real + conjugate_dual;


    assert( a.magnitude() == Dualf{ 1.0f } );
    assert( a.is_unit() );
    //assert( sum == DualQuaternionf::zero() );
}

void HowToCombineASeparateRotationAndTranslation()
{
    Quaternionf q_rotation{ Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f ) };
    DualQuaternionf rotation{ DualQuaternionf::make_rotation( q_rotation ) };
    DualQuaternionf translation{ DualQuaternionf::make_translation(10.0f, 0.0f, 0.0f) };
    DualQuaternionf combination = translation * rotation;
    DualQuaternionf constructed_combination = translation * rotation;

    assert( combination == constructed_combination );
    assert( combination.real() == q_rotation );
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

    std::cout << "PASSED!" << std::endl;
}
}