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

    assert(make_dualquaternion_rotation(0.0f, 0.0f, 1.0f, 0.0f).dual == Quaternionf::zero());
    assert(make_dualquaternion_rotation(float(M_PI_4), 0.0f, 0.0f, 1.0f).dual == Quaternionf::zero());
    assert(make_dualquaternion_rotation(float(M_PI_2), 1.0f, 0.0f, 0.0f).dual == Quaternionf::zero());
}

void PureTranslationHasIdentityRotation()
{
    std::cout << __func__ << std::endl;

    assert(make_dualquaternion_translation(1.0f, 2.0f, 3.0f).real == Quaternionf::identity());
}

void MagnitudeOfNormalizedDualQuaternionIsOne()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf a{ Quaternionf{6.0f, 22.34f, -3.12f, 100.04f}, Quaternionf{1.0f, -43.1113f, -6.0f, 0.0f} };
    DualQuaternionf normalized_a = normalized(a);

    assert( IsNear( dualquaternion_norm(normalized_a), Dualf::identity() ) );
    assert( !is_unit(a) );
}

void MagnitudeIsTheNumberMultipliedByItsConjugate()
{
    std::cout << __func__ << std::endl;

    DualQuaternionf a{ make_coordinate_system( Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f ), 10.0f, 10.0f, 10.0f ) };
    DualQuaternionf a_times_conjugate{ a * dualquaternion_conjugate(a) };
    Dualf mag_a = dualquaternion_magnitude(a);
    Dualf mag_a_times_conjugate = dualquaternion_magnitude(a_times_conjugate);

    assert( IsNear(mag_a, mag_a_times_conjugate) );
}

void UnitCondition()
{
    std::cout << __func__ << std::endl;

    // TODO
#if 0
#if 0
    DualQuaternionf a{ make_coordinate_system( Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f ), 10.0f, 10.0f, 10.0f ) };
    DualQuaternionf conjugate_real{ conjugate(a.real), a.dual };
    DualQuaternionf conjugate_dual{ conjugate(a.dual), a.real };
    DualQuaternionf sum = conjugate_real + conjugate_dual;


    assert( is_unit(a) );
    assert( sum.real == Quaternionf::zero() );
    assert( sum.dual == Quaternionf::zero() );
#else
    DualQuaternionf rotation{ make_dualquaternion_rotation( Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f ) ) };
    DualQuaternionf translation{ make_dualquaternion_translation(10.0f, 0.0f, 0.0f) };
    DualQuaternionf combination = translation * rotation;
#endif
#endif
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

    std::cout << "PASSED!" << std::endl;
}
}