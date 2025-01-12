#include "ColorTypesTests.hpp"
#include "color/Types.hpp"
#include <cassert>
#include <iostream>


namespace ColorTypesTests
{

using namespace Color;
using namespace Math;

void DefaultConstructedRGBb()
{
    std::cout << __func__ << std::endl;
    
    RGBb object;

    assert( object.red() == 0 );
    assert( object.green() == 0 );
    assert( object.blue() == 0 );
}

void DefaultConstructedUnitRGBf()
{
    std::cout << __func__ << std::endl;
    
    UnitRGBf object;

    assert( object.red() == 0.0f );
    assert( object.green() == 0.0f );
    assert( object.blue() == 0.0f );
}

void ConstructingAUnitRGBfFromRGBb()
{
    std::cout << __func__ << std::endl;
    
    // Default (zero)
    {
        RGBb object;
        UnitRGBf unit_object{ object };

        assert( unit_object.red() == 0.0f );
        assert( unit_object.green() == 0.0f );
        assert( unit_object.blue() == 0.0f );
    }

    // Max (255)
    {
        UnitRGBf unit_object{ RGBb::max() };

        assert( unit_object.red() == 1.0f );
        assert( unit_object.green() == 1.0f );
        assert( unit_object.blue() == 1.0f );
    }

    // Midway (127)
    {
        RGBb origin{ 127, 127, 127 };
        UnitRGBf unit_object{ origin };

        assert( approximately_equal_to( unit_object.red(), 0.5f, 0.003f ) );
        assert( approximately_equal_to( unit_object.green(), 0.5f, 0.003f ) );
        assert( approximately_equal_to( unit_object.blue(), 0.5f, 0.003f ) );
    }
}

void MinValueUnitRGBf()
{
    std::cout << __func__ << std::endl;
    
    assert( UnitRGBf::min().red() == 0.0f );
    assert( UnitRGBf::min().green() == 0.0f );
    assert( UnitRGBf::min().blue() == 0.0f );
}

void MaxValueUnitRGBf()
{
    std::cout << __func__ << std::endl;
    
    assert( UnitRGBf::max().red() == 1.0f );
    assert( UnitRGBf::max().green() == 1.0f );
    assert( UnitRGBf::max().blue() == 1.0f );
}

void RGB()
{
    DefaultConstructedRGBb();
    DefaultConstructedUnitRGBf();
    MinValueUnitRGBf();
    MaxValueUnitRGBf();
    ConstructingAUnitRGBfFromRGBb();
}

void DefaultConstructedUnitHSV()
{
    std::cout << __func__ << std::endl;
    
    HSVf object;

    assert( object.hue().value() == 0.0f );
    assert( object.saturation() == 0.0f );
    assert( object.value() == 0.0f );
}

void NormallyConstructedUnitHSV()
{
    std::cout << __func__ << std::endl;
    
    HSVf object{ Degreef{ 0.5f }, 0.5, 0.5 };

    assert( object.hue().value() == 0.5f );
    assert( object.saturation() == 0.5f );
    assert( object.value() == 0.5f );
}

void MaxValueHSVf()
{
    std::cout << __func__ << std::endl;
    
    assert( HSVf::max().hue().value() == Degreef::modulus() );
    assert( HSVf::max().saturation() == 1.0f );
    assert( HSVf::max().value() == 1.0f );
}

void MinValueHSVf()
{
    std::cout << __func__ << std::endl;
    
    assert( HSVf::min().hue().value() == 0.0f );
    assert( HSVf::min().saturation() == 0.0f );
    assert( HSVf::min().value() == 0.0f );
}

void HSV()
{
    DefaultConstructedUnitHSV();
    NormallyConstructedUnitHSV();
    MaxValueHSVf();
    MinValueHSVf();
}

void Run()
{
    std::cout << "Running Color Types Tests..." << std::endl;

    RGB();
    HSV();

    std::cout << "PASSED!" << std::endl;
}

}