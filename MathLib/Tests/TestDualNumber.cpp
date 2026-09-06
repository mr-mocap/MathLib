#include <Math/math/Dual.hpp>
#include <Math/math/Checks.hpp>
#include <cstdlib>
#include <numbers>
#include <cassert>
#include <iostream>

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
    Dualf identity = Dualf::identity();

    CHECK_IF_EQUAL(identity.real, 1.0f);
    CHECK_IF_EQUAL(identity.dual, 0.0f);
}

/** Verify the representation of a Dual's zero representation
 */
void ZeroDualIsAsExpected()
{
    Dualf zero = Dualf::zero();

    CHECK_IF_EQUAL(zero.real, 0.0f);
    CHECK_IF_EQUAL(zero.dual, 0.0f);
}

/** Verify that @c make_pure sets @c real() to zero
 */
void MakePureDualSetsRealComponentToZero()
{
    CHECK_IF_EQUAL( Dualf::make_pure(3.0f).real, 0.0f );
}

/** Verify that @c make_pure sets @c dual() to the given value
 */
void MakePureDualSetsDualComponentToGivenValue()
{
    CHECK_IF_EQUAL( Dualf::make_pure(3.3f).dual, 3.3f );
}

/** Verifies the @c dot() function
 * 
 */
void DotProductMultiplesCorrespondingElementsAndThenSumsTheResultingValues()
{
    Dualf d1{ 1.0f, 3.0f  };
    Dualf d2{ 9.0f, 11.0f };

    CHECK_IF_EQUAL( dot( d1, d2 ), 42.0f );
}

/** Verifies the @c dualscalar_sqrt() function
 * 
 */
void DualScalarSquareRootTimesItselfIsTheOriginalNumber()
{
    Dualf original_number{ 3.456f, 86.332f };
    Dualf root = dualscalar_sqrt(original_number);
    Dualf root_squared = root * root;

    CHECK_IF_EQUAL( original_number, root_squared );
}

void OperatorEquality()
{
    Dual d( 12.0 );

    CHECK_IF_EQUAL( d, 12.0 );
    CHECK_IF_EQUAL( 12.0, d );
    CHECK_IF_EQUAL( d, Dual( 12.0 ) );
}

void OperatorMultiply()
{
    Dual d( 16.0 );
    Dual r = d * 2.0;

    CHECK_IF_EQUAL( r, 32.0 );
    CHECK_IF_EQUAL( r, Dual( 32.0 ) );
    CHECK_IF_EQUAL( 32.0, r );
    CHECK_IF_EQUAL( Dual( 32.0 ), r );
}

void OperatorAddition()
{
    Dual a( 2.0, 3.0 );
    Dual b( 4.0, 5.0 );
    Dual result = a + b;

    CHECK_IF_EQUAL( result.real, 6.0 );
    CHECK_IF_EQUAL( result.dual, 8.0 );
}

void OperatorSubtraction()
{
    Dual a( 2.0, 3.0 );
    Dual b( 4.0, 5.0 );
    Dual result = a - b;

    CHECK_IF_EQUAL( result.real, -2.0 );
    CHECK_IF_EQUAL( result.dual, -2.0 );
}

void OperatorSin()
{
    Dual a( std::numbers::pi / 2.0, 1.0 );
    Dual result = sin( a );

    CHECK_IF_EQUAL( result.real, 1.0 );
    CHECK_IF_EQUAL( result.dual, 0.0 );
}

void OperatorCos()
{
    Dual a( 0.0, 1.0 );
    Dual result = cos( a );

    CHECK_IF_EQUAL( result.real, 1.0 );
    CHECK_IF_EQUAL( result.dual, 0.0 );
}

void TestOperators()
{
    OperatorEquality();
    OperatorMultiply();
    OperatorAddition();
    OperatorSubtraction();
    OperatorSin();
    OperatorCos();
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