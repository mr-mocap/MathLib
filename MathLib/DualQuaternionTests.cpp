#include "DualNumberTests.hpp"
#include "math/DualQuaternion.h"
#include "math/types.h"
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

void PureRotationHasZeroTranslation()
{
    assert(make_dualquaternion_rotation(0.0f, triple<float>{0.0f, 1.0f, 0.0f} ).dual == Quaternionf::zero());
    assert(make_dualquaternion_rotation(float(M_PI_4), triple<float>{0.0f, 0.0f, 1.0f}).dual == Quaternionf::zero());
    assert(make_dualquaternion_rotation(float(M_PI_2), triple<float>{1.0f, 0.0f, 0.0f}).dual == Quaternionf::zero());
}

void PureTranslationHasIdentityRotation()
{
    assert(make_dualquaternion_translation( triple<float>{ 1.0f, 2.0f, 3.0f } ).real == Quaternionf::unit());
}

void MagnitudeOfNormalizedDualQuaternionIsOne()
{
    DualQuaternionf a{ Quaternionf{6.0f, 22.34f, -3.12f, 100.04f}, Quaternionf{1.0f, -43.1113f, -6.0f, 0.0f} };
    DualQuaternionf normalized_a = normalized(a);

    assert( IsNear( dualquaternion_norm(normalized_a), Dualf::unit() ) );
    assert( !is_unit(a) );
}

void Run()
{
    std::cout << "Running Dual Quaternion Tests..." << std::endl;

    PureRotationHasZeroTranslation();
    PureTranslationHasIdentityRotation();
    MagnitudeOfNormalizedDualQuaternionIsOne();

    std::cout << "PASSED!" << std::endl;
}
}