#include "HierarchicalCoordinateSystemTests.hpp"
#include "math/HierarchicalCoordinateSystem.hpp"
#include "math/Conversions.hpp"
#include <cassert>
#include <iostream>


/** @file
 * 
 *  @hideincludegraph
 */

/** @defgroup HierarchicalCoordinateSystemTestsPage HierarchicalCoordinateSystem Unit Tests
 * 
 *  Here are all the unit tests used to exercise the HierarchicalCoordinateSystem class
 * 
 *  @ingroup UnitTests
 * 
 *  @{
 */

/** Contains the unit tests for HierarchicalCoordinateSystem
 * 
 */
namespace HierarchicalCoordinateSystemTests
{

void DefaultConstructedState()
{
    std::cout << __func__ << std::endl;

    HierarchicalCoordinateSystemf scene;

    assert( scene.root().parent().expired() );
    assert( scene.root().children().empty() );
}

void CreatingAChildAddsToTheNodesChildren()
{
    std::cout << __func__ << std::endl;

    HierarchicalCoordinateSystemf scene;

    assert( scene.root().parent().expired() );
    assert( scene.root().children().empty() );

    auto wp = scene.root().createChildNode( { 1.0f, 2.0f, 3.0f }, Quaternionf::make_rotation( 120.0_deg_f, { 1.0f, 1.0f, 1.0f } ) );

    assert( scene.root().children().size() == 1 );
    assert( wp.lock() == scene.root().children().back() );
    assert( scene.root().children().back()->parent().lock().get() == &scene.root() );
}

void ConvertingALocalCoordinateToAGlobalCoordinate()
{
    std::cout << __func__ << std::endl;

    // One child node that has only a translation
    {
        HierarchicalCoordinateSystemf scene;

        std::shared_ptr<SceneNodef> translation_only{ scene.root().createChildNode( { 2.0f, 0.0f, 0.0f } ) };
        Vector3Df translation_only_test_point{ 0.0f, 2.0f, 3.0f };
        Vector3Df translation_point_to_global_space{ translation_only->localToWorld(translation_only_test_point) };
        Vector3Df expected_global_point{ 2.0f, 2.0f, 3.0f };

        assert( translation_point_to_global_space != translation_only_test_point );
        assert( translation_point_to_global_space == expected_global_point );
    }

    // One child node that has only a rotation
    {
        HierarchicalCoordinateSystemf scene;

        Quaternionf rotation{ Quaternionf::make_rotation( 30.0_deg_f, Vector3Df::unit_x() ) };
        std::shared_ptr<SceneNodef> rotation_only{ scene.root().createChildNode(Vector3Df::zero(), rotation ) };
        Vector3Df test_point{ 0.0f, 2.0f, 3.0f };
        Vector3Df point_to_global_space{ rotation_only->localToWorld(test_point) };
        Vector3Df expected_global_point{ (rotation * Quaternionf::encode_point( test_point ) * rotation.conjugate()).imaginary() };

        assert( point_to_global_space != test_point );
        assert( point_to_global_space == expected_global_point );
    }
}

/** Run all of the unit tests in this namespace
 * 
 */
void Run()
{
    std::cout << "Running HierarchicalCoordinateSystem Tests..." << std::endl;

    DefaultConstructedState();
    CreatingAChildAddsToTheNodesChildren();
    ConvertingALocalCoordinateToAGlobalCoordinate();

    std::cout << "PASSED!" << std::endl;
}
}
/// @}