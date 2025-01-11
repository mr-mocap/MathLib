#include "ColorConversionTests.hpp"
#include "color/Conversions.hpp"
#include <cassert>
#include <iostream>


namespace ColorConversionTests
{

void ConvertingBasicRGBColorsToHSV()
{
    std::cout << __func__ << std::endl;
    
    {
        UnitRGBf red{ 1.0, 0.0, 0.0 };
        HSVf hsv_representation{ ToHSV( red ) };

        assert( hsv_representation.hue().value() == 0.0f );
        assert( hsv_representation.hueColor() == HSVf::Red );
        assert( hsv_representation.saturation() == 1.0f );
        assert( hsv_representation.value() == 1.0f );
    }

    {
        UnitRGBf green{ 0.0, 1.0, 0.0 };
        HSVf hsv_representation{ ToHSV( green ) };

        assert( hsv_representation.hue().value() == 120.0f );
        assert( hsv_representation.hueColor() == HSVf::Green );
        assert( hsv_representation.saturation() == 1.0f );
        assert( hsv_representation.value() == 1.0f );
    }

    {
        UnitRGBf blue{ 0.0, 0.0, 1.0 };
        HSVf hsv_representation{ ToHSV( blue ) };

        assert( hsv_representation.hue().value() == 240.0f );
        assert( hsv_representation.hueColor() == HSVf::Blue );
        assert( hsv_representation.saturation() == 1.0f );
        assert( hsv_representation.value() == 1.0f );
    }
}

void BlackHasZeroSaturationAndZeroValue()
{
    std::cout << __func__ << std::endl;

    UnitRGBf black{ 0.0, 0.0, 0.0 };
    HSVf hsv_representation{ ToHSV( black ) };

    // Hue is irrelevant (could be any hue)

    assert( hsv_representation.saturation() == 0.0f );
    assert( hsv_representation.value() == 0.0f );
}

void BlackHasHueOfZero()
{
    std::cout << __func__ << std::endl;

    UnitRGBf black{ 0.0, 0.0, 0.0 };
    HSVf hsv_representation{ ToHSV( black ) };

    // Not really important, but it HAS to be a hue
    assert( hsv_representation.hue().value() == 0.0f );
    assert( hsv_representation.hueColor() == HSVf::Red );
}

void WhiteHasSaturationOfZeroAndValueOfOne()
{
    std::cout << __func__ << std::endl;

    UnitRGBf white{ 1.0, 1.0, 1.0 };
    HSVf hsv_representation{ ToHSV( white ) };

    assert( hsv_representation.saturation() == 0.0f );
    assert( hsv_representation.value() == 1.0f );
}

void WhiteHasHueOfZero()
{
    std::cout << __func__ << std::endl;

    UnitRGBf white{ 1.0, 1.0, 1.0 };
    HSVf hsv_representation{ ToHSV( white ) };

    // Not really important, but it HAS to be a hue (could be any hue)
    assert( hsv_representation.hue().value() == 0.0f );
    assert( hsv_representation.hueColor() == HSVf::Red );
}

void GreyHasHueAndSaturationOfZeroAndValueOf50Percent()
{
    std::cout << __func__ << std::endl;

    UnitRGBf grey{ 0.5, 0.5, 0.5 };
    HSVf hsv_representation{ ToHSV( grey ) };

    // Not really important, but it HAS to be a hue (could be any hue)
    assert( hsv_representation.hue().value() == 0.0f );
    assert( hsv_representation.hueColor() == HSVf::Red );

    assert( hsv_representation.saturation() == 0.0f );
    assert( hsv_representation.value() == 0.5f );
}

void ConvertingBasicCMYColorsToHSV()
{
    std::cout << __func__ << std::endl;
    
    {
        UnitRGBf cyan{ 0.0, 1.0, 1.0 };
        HSVf hsv_representation{ ToHSV( cyan ) };

        assert( hsv_representation.hue().value() == 180.0f );
        assert( hsv_representation.hueColor() == HSVf::Cyan );
        assert( hsv_representation.saturation() == 1.0f );
        assert( hsv_representation.value() == 1.0f );
    }

    {
        UnitRGBf magenta{ 1.0, 0.0, 1.0 };
        HSVf hsv_representation{ ToHSV( magenta ) };

        assert( hsv_representation.hue().value() == 300.0f );
        assert( hsv_representation.hueColor() == HSVf::Magenta );
        assert( hsv_representation.saturation() == 1.0f );
        assert( hsv_representation.value() == 1.0f );
    }

    {
        UnitRGBf yellow{ 1.0, 1.0, 0.0 };
        HSVf hsv_representation{ ToHSV( yellow ) };

        assert( hsv_representation.hue().value() == 60.0f );
        assert( hsv_representation.hueColor() == HSVf::Yellow );
        assert( hsv_representation.saturation() == 1.0f );
        assert( hsv_representation.value() == 1.0f );
    }
}

void Run()
{
    std::cout << "Running Color Conversion Tests..." << std::endl;

    ConvertingBasicRGBColorsToHSV();
    BlackHasZeroSaturationAndZeroValue();
    BlackHasHueOfZero();
    WhiteHasSaturationOfZeroAndValueOfOne();
    WhiteHasHueOfZero();
    GreyHasHueAndSaturationOfZeroAndValueOf50Percent();
    ConvertingBasicCMYColorsToHSV();

    std::cout << "PASSED!" << std::endl;
}

}