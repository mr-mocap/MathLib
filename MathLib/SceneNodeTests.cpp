#include "SceneNodeTests.hpp"
#include "math/SceneNode.hpp"
#include "math/Quaternion.hpp"
#include "math/Conversions.hpp"
#include <cassert>
#include <iostream>


namespace SceneNodeTests
{

void DefaultConstructedState()
{
    std::cout << __func__ << std::endl;

    auto node = SceneNodef::make();

    assert( node->parent().expired() ); // No parent
    assert( node->children().empty() ); // No children
}

void CanCreateChildNode()
{
    std::cout << __func__ << std::endl;

    // Via weak_ptr
    {
        std::shared_ptr<SceneNodef> node = SceneNodef::make();
        std::weak_ptr<SceneNodef> child_node = node->createChildNode({ 1.0f, 2.0f, 3.0f }, Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f ));

        assert( !child_node.expired() );
        assert( !child_node.lock()->parent().expired() );
        assert(  child_node.lock()->parent().lock() == node); // Child's parent() is the node it was created from
        assert(  child_node.lock()->parent().lock()->children().size() == 1 ); // It is the only child in the parent
        assert(  child_node.lock()->parent().lock()->children().front() == child_node.lock() ); // That only child is the newly created node
        assert(  node->children().size() == 1 );
        assert( !node->children().empty() );
        assert( std::ranges::find( node->children(), child_node.lock() ) != node->children().end() );
    }

    // Via shared_ptr
    {
        std::shared_ptr<SceneNodef> node = SceneNodef::make();
        std::shared_ptr<SceneNodef> child_node{ node->createChildNode({ 1.0f, 2.0f, 3.0f }, Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f )) };

        assert(  child_node );
        assert( !child_node->parent().expired() );
        assert(  child_node->parent().lock() == node);
        assert(  child_node->parent().lock()->children().size() == 1 );
        assert(  child_node->parent().lock()->children().front() == child_node );
        assert(  node->children().size() == 1 );
        assert( !node->children().empty() );
        assert( std::ranges::find( node->children(), child_node ) != node->children().end() );
    }
}

void DetachChild()
{
    std::cout << __func__ << std::endl;

    std::shared_ptr<SceneNodef> node = SceneNodef::make();
    std::shared_ptr<SceneNodef> child_node{ node->createChildNode({ 1.0f, 2.0f, 3.0f }, Quaternionf::make_rotation( DegreesToRadians(45.0f), 1.0f, 0.0f, 0.0f )) };

    assert( std::ranges::find( node->children(), child_node ) != node->children().end() ); // child_node IS in node->children()
    assert( !child_node->parent().expired() );
    assert(  child_node->parent().use_count() == 1 );
    assert(  child_node->parent().lock() == node );

    node->detachChild( child_node );

    assert( std::ranges::find( node->children(), child_node ) == node->children().end() ); // No longer in node's children()
    assert( child_node->parent().expired() );
    assert( child_node->parent().use_count() == 0 );
}

void AttachChild()
{
    std::cout << __func__ << std::endl;

    std::shared_ptr<SceneNodef> node = SceneNodef::make();
    std::shared_ptr<SceneNodef> child_node = SceneNodef::make();

    assert( std::ranges::find(node->children(), child_node) == node->children().end() ); // child_node is not in node's children()
    assert( child_node->parent().expired() );
    assert( child_node->parent().use_count() == 0 );

    node->attachChild(child_node);

    assert( std::ranges::find(node->children(), child_node) != node->children().end() ); // child_node IS in node's children()
    assert( !child_node->parent().expired() );
    assert(  child_node->parent().use_count() == 1 );
    assert(  child_node->parent().lock() == node );
}

void Run()
{
    std::cout << "Running SceneNode Tests..." << std::endl;

    DefaultConstructedState();
    CanCreateChildNode();
    DetachChild();
    AttachChild();

    std::cout << "PASSED!" << std::endl;
}
}
