#include "HierarchicalCoordinateSystemTests.hpp"
#include "math/HierarchicalCoordinateSystem.hpp"
#include "math/Conversions.hpp"
#include <cassert>
#include <iostream>
#include <format>


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

static std::shared_ptr<SceneNodef> GenerateHierarchicalSkeleton(HierarchicalCoordinateSystemf &world)
{
    std::shared_ptr<SceneNodef> waist{ world.root().createChildNode( Vector3Df::zero(), Quaternionf::identity(), "waist" ) };

    // Lower parts
    std::shared_ptr<SceneNodef> left_upper_leg{ waist->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "left_upper_leg" ) };
    std::shared_ptr<SceneNodef> right_upper_leg{ waist->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "right_upper_leg" ) };

    std::shared_ptr<SceneNodef> left_lower_leg{ left_upper_leg->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "left_lower_leg" ) };
    std::shared_ptr<SceneNodef> right_lower_leg{ right_upper_leg->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "right_lower_leg" ) };

    std::shared_ptr<SceneNodef> left_foot{ left_lower_leg->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "left_foot" ) };
    std::shared_ptr<SceneNodef> right_foot{ right_lower_leg->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "right_foot" ) };

    // Upper parts
    std::shared_ptr<SceneNodef> torso_1{ waist->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "torso_1" ) };
    std::shared_ptr<SceneNodef> torso_2{ torso_1->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "torso_2" ) };
    std::shared_ptr<SceneNodef> torso_3{ torso_2->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "torso_3" ) };

    std::shared_ptr<SceneNodef> left_upper_arm{ torso_3->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "left_upper_arm" ) };
    std::shared_ptr<SceneNodef> right_upper_arm{ torso_3->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "right_upper_arm" ) };

    std::shared_ptr<SceneNodef> left_lower_arm{ left_upper_arm->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "left_lower_arm" ) };
    std::shared_ptr<SceneNodef> right_lower_arm{ right_upper_arm->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "right_lower_arm" ) };

    std::shared_ptr<SceneNodef> left_hand{ left_lower_arm->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "left_hand" ) };
    std::shared_ptr<SceneNodef> right_hand{ right_lower_arm->createChildNode( Vector3Df::zero(), Quaternionf::identity(), "right_hand" ) };

    return waist;
}

int NumParents(std::shared_ptr<SceneNodef> node, std::shared_ptr<SceneNodef> relative_to)
{
    if (node == relative_to)
        return 0; // We are relative to this, so 0 by definition!

    if (node->parent().use_count() == 0)
        return 0; // No parent!

    return NumParents(node->parent().lock(), relative_to) + 1;
}

void PrintNode(std::shared_ptr<SceneNodef> node, std::shared_ptr<SceneNodef> relative_to)
{
    int num_parents = NumParents(node, relative_to);

    for (int i = 0; i < num_parents; ++i)
        std::cout << '\t';

    std::cout << std::format("{}", node->name()) << std::endl;
}

void PrintHierarchyRecursive(std::shared_ptr<SceneNodef> root, std::shared_ptr<SceneNodef> relative_to = nullptr)
{
    PrintNode(root, relative_to);
    for (auto child : root->children())
        PrintHierarchyRecursive(child, relative_to);
}

void PrintHierarchy(std::shared_ptr<SceneNodef> root)
{
    PrintHierarchyRecursive(root, root);
}

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

void ConstructSkeleton()
{
    std::cout << __func__ << std::endl;

    HierarchicalCoordinateSystemf world;

    std::shared_ptr<SceneNodef> skeleton{ GenerateHierarchicalSkeleton(world) };

    PrintHierarchy(skeleton);
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
    ConstructSkeleton();

    std::cout << "PASSED!" << std::endl;
}
}
/// @}