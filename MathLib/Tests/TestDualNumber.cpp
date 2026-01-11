#include <Math/math/Dual.hpp>
#include <Math/math/Checks.hpp>
#include <cassert>
#include <iostream>
#include <cstdlib>

/** @file
 * 
 *  @hideincludegraph
 */

/** @defgroup DualNumberTests Dual Number Unit Tests
 * 
 *  Here are all the unit tests used to exercise the Dual class
 * 
 *  @ingroup UnitTests
 * 
 *  @{
 */


/** Contains the unit tests for Dual
 * 
 */
namespace DualNumberTests
{

using namespace Math;

/** Verify the representation of a Dual's identity representation
 */
void IdentityDualIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Dualf identity = Dualf::identity();

    CHECK_IF_EQUAL(identity.real, 1.0f);
    CHECK_IF_EQUAL(identity.dual, 0.0f);
}

/** Verify the representation of a Dual's zero representation
 */
void ZeroDualIsAsExpected()
{
    std::cout << __func__ << std::endl;

    Dualf zero = Dualf::zero();

    CHECK_IF_EQUAL(zero.real, 0.0f);
    CHECK_IF_EQUAL(zero.dual, 0.0f);
}

/** Verify that @c make_pure sets @c real() to zero
 */
void MakePureDualSetsRealComponentToZero()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Dualf::make_pure(3.0f).real, 0.0f );
}

/** Verify that @c make_pure sets @c dual() to the given value
 */
void MakePureDualSetsDualComponentToGivenValue()
{
    std::cout << __func__ << std::endl;

    CHECK_IF_EQUAL( Dualf::make_pure(3.3f).dual, 3.3f );
}

/** Verifies the @c dot() function
 * 
 */
void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
{
    std::cout << __func__ << std::endl;

    Dualf d1{ 1.0f, 3.0f  };
    Dualf d2{ 9.0f, 11.0f };

    CHECK_IF_EQUAL( dot( d1, d2 ), 42.0f );
}

/** Verifies the @c dualscalar_sqrt() function
 * 
 */
void DualScalarSquareRootTimesItselfIsTheOriginalNumber()
{
    std::cout << __func__ << std::endl;

    Dualf original_number{ 3.456f, 86.332f };
    Dualf root = dualscalar_sqrt(original_number);
    Dualf root_squared = root * root;

    CHECK_IF_EQUAL( original_number, root_squared );
}

void OperatorEquality()
{
    Dual d( 12.0 );

    assert( d == 12.0 );
    assert( 12.0 == d );
    assert( d == Dual( 12.0 ) );
}

void OperatorMultiply()
{
    Dual d( 16.0 );
    Dual r = d * 2.0;

    assert( r == 32.0 );
    assert( r == Dual( 32.0 ) );
    assert( 32.0 == r );
    assert( Dual( 32.0 ) == r );
}

void TestOperators()
{
    OperatorEquality();
    OperatorMultiply();
}

/** Run all of the unit tests in this namespace
 * 
 */
void Run()
{
    std::cout << "Running Dual Number Tests..." << std::endl;

    IdentityDualIsAsExpected();
    ZeroDualIsAsExpected();
    MakePureDualSetsRealComponentToZero();
    MakePureDualSetsDualComponentToGivenValue();
    DualScalarSquareRootTimesItselfIsTheOriginalNumber();
    TestOperators();

    std::cout << "PASSED!" << std::endl;
}
}
/// @}

int main(void)
{
    DualNumberTests::Run();
    return EXIT_SUCCESS;
}