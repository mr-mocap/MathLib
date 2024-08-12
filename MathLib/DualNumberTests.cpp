#include "DualNumberTests.hpp"
#include "math/Dual.hpp"
#include <cassert>
#include <iostream>


static bool IsNear(Dualf value_to_test, Dualf value_it_should_be, float epsilon = 0.0002f)
{
    return approximately_equal_to(value_to_test, value_it_should_be, epsilon);
}

namespace DualNumberTests
{

void IdentityDualIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Dualf identity = Dualf::identity();

    assert(identity.real == 1.0);
    assert(identity.dual == 0.0);
}

void ZeroDualIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Dualf zero = Dualf::zero();

    assert(zero.real == 0.0);
    assert(zero.dual == 0.0);
}

void MakePureDualSetsRealComponentToZero()
{
    std::cout << __func__ << std::endl;

    assert( make_pure_dual(3.0f).real == 0.0f );
}

void MakePureDualSetsDualComponentToGivenValue()
{
    std::cout << __func__ << std::endl;

    assert( make_pure_dual(3.3f).dual == 3.3f );
}

void MakePureDualSetsDualComponentToInputParameter()
{
    std::cout << __func__ << std::endl;

    assert( make_pure_dual(3.0f).dual == 3.0f );
}

void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
{
    std::cout << __func__ << std::endl;

    Dualf d1{ 1.0f, 3.0f  };
    Dualf d2{ 9.0f, 11.0f };

    assert( dot( d1, d2 ) == 42.0f );
}

void DualScalarSquareRootTimesItselfIsTheOriginalNumber()
{
    std::cout << __func__ << std::endl;

    Dualf original_number{ 3.456f, 86.332f };
    Dualf root = dualscalar_sqrt(original_number);
    Dualf root_squared = root * root;

    assert( IsNear(original_number, root_squared) );
}

void Run()
{
    std::cout << "Running Dual Number Tests..." << std::endl;

    IdentityDualIsAsExpected();
    ZeroDualIsAsExpected();
    MakePureDualSetsRealComponentToZero();
    MakePureDualSetsDualComponentToGivenValue();
    MakePureDualSetsDualComponentToInputParameter();
    DualScalarSquareRootTimesItselfIsTheOriginalNumber();

    std::cout << "PASSED!" << std::endl;
}
}