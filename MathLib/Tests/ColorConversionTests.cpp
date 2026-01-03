#include "ColorConversionTests.hpp"
#include <color/Conversions.hpp>
#include <cassert>
#include <iostream>


namespace ColorConversionTests
{

using namespace Color;
using namespace Math::Literals;

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

        assert( hsv_representation.hue() == 120.0_deg_f );
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

void ConvertingBasicHSVColorsToRGB()
{
    std::cout << __func__ << std::endl;
    
    {
        HSVf red{ 0.0_deg_f, 1.0f, 1.0f };
        UnitRGBf rgb_representation{ ToRGB( red ) };

        assert( rgb_representation.red() == 1.0f );
        assert( rgb_representation.green() == 0.0f );
        assert( rgb_representation.blue() == 0.0f );
    }
    
    {
        HSVf green{ 120.0_deg_f, 1.0f, 1.0f };
        UnitRGBf rgb_representation{ ToRGB( green ) };

        assert( rgb_representation.red() == 0.0f );
        assert( rgb_representation.green() == 1.0f );
        assert( rgb_representation.blue() == 0.0f );
    }

    {
        HSVf blue{ 240.0_deg_f, 1.0f, 1.0f };
        UnitRGBf rgb_representation{ ToRGB( blue ) };

        assert( rgb_representation.red() == 0.0f );
        assert( rgb_representation.green() == 0.0f );
        assert( rgb_representation.blue() == 1.0f );
    }
}

void ConvertingBasicCMYColorsToRGB()
{
    std::cout << __func__ << std::endl;
    
    {
        HSVf cyan{ 180.0_deg_f, 1.0, 1.0 };
        UnitRGBf rgb_representation{ ToRGB( cyan ) };

        assert( rgb_representation.red() == 0.0f );
        assert( rgb_representation.green() == 1.0f );
        assert( rgb_representation.blue() == 1.0f );
    }

    {
        HSVf magenta{ 300.0_deg_f, 1.0, 1.0 };
        UnitRGBf rgb_representation{ ToRGB( magenta ) };

        assert( rgb_representation.red() == 1.0f );
        assert( rgb_representation.green() == 0.0f );
        assert( rgb_representation.blue() == 1.0f );
    }

    {
        HSVf yellow{ 60.0_deg_f, 1.0, 1.0 };
        UnitRGBf rgb_representation{ ToRGB( yellow ) };

        assert( rgb_representation.red() == 1.0f );
        assert( rgb_representation.green() == 1.0f );
        assert( rgb_representation.blue() == 0.0f );
    }
}

void ConvertingOtherColorsToHSV()
{
    std::cout << __func__ << std::endl;
    
    {
        HSVf black{ 0.0_deg_f, 1.0, 0.0 };
        UnitRGBf rgb_representation{ ToRGB( black ) };

        assert( rgb_representation.red() == 0.0f );
        assert( rgb_representation.green() == 0.0f );
        assert( rgb_representation.blue() == 0.0f );
    }

    {
        HSVf white{ 0.0_deg_f, 0.0, 1.0 };
        UnitRGBf rgb_representation{ ToRGB( white ) };

        assert( rgb_representation.red() == 1.0f );
        assert( rgb_representation.green() == 1.0f );
        assert( rgb_representation.blue() == 1.0f );
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

    ConvertingBasicHSVColorsToRGB();
    ConvertingBasicCMYColorsToRGB();
    ConvertingOtherColorsToHSV();

    std::cout << "PASSED!" << std::endl;
}

}