#include "HierarchicalCoordinateSystemTests.hpp"
#include "math/HierarchicalCoordinateSystem.hpp"
#include "math/Conversions.hpp"
#include <cassert>
#include <iostream>


namespace HierarchicalCoordinateSystemTests
{
void DefaultConstructedState()
{
    std::cout << __func__ << std::endl;

    HierarchicalCoordinateSystemf scene;

    assert( scene.root().parent().expired() );
    assert( scene.root().children().empty() );
}

void CreatingAChildAddsToItsChildren()
{
    std::cout << __func__ << std::endl;

    HierarchicalCoordinateSystemf scene;

    assert( scene.root().parent().expired() );
    assert( scene.root().children().empty() );

    auto wp = scene.root().createChildNode( { 1.0f, 2.0f, 3.0f }, Quaternionf::make_rotation( DegreesToRadians(120.0f), { 1.0f, 1.0f, 1.0f } ) );

    assert( scene.root().children().size() == 1 );
    assert( wp.lock() == scene.root().children().back() );
    assert( scene.root().children().back()->parent().lock().get() == &scene.root() );
}

void ConvertingALocalCoordinateToAGlobalCoordinate()
{
    std::cout << __func__ << std::endl;

#if 0
    HierarchicalCoordinateSystemf scene;
    auto translation_only = scene.root().createChildNode( { 2.0f, 0.0f, 0.0f } );
    auto rotation_only = scene.root().createChildNode( Vector3Df::zero(), Quaternionf::make_rotation( DegreesToRadians(45.0f), 0.0f, 0.0f, 1.0f ) );
    //auto translation_and_rotation = scene.root().createChildNode();
    Vector3Df translation_only_test_point{ 1.0f, 2.0f, 3.0f };

    Vector3Df translation_point_to_global_space = translation_only.localToWorld( translation_only_test_point );

    assert( translation_point_to_global_space == Vector3Df{ 3.0f, 2.0f, 3.0f } );
#endif
}

void Run()
{
    std::cout << "Running HierarchicalCoordinateSystem Tests..." << std::endl;

    DefaultConstructedState();
    CreatingAChildAddsToItsChildren();

    std::cout << "PASSED!" << std::endl;
}
}