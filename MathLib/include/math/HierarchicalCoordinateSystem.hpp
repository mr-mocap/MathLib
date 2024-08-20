#pragma once

#include "math/SceneNode.hpp"
#include <memory>


template <class Type>
class HierarchicalCoordinateSystem
{
public:
    HierarchicalCoordinateSystem()
        :
    _root_node( SceneNode<Type>::make() )
    {
    }

    const SceneNode<Type> &root() const { return *_root_node; }
          SceneNode<Type> &root()       { return *_root_node; }
private:
    std::shared_ptr<SceneNode<Type>> _root_node;
};


using HierarchicalCoordinateSystemf = HierarchicalCoordinateSystem<float>;
using HierarchicalCoordinateSystemd = HierarchicalCoordinateSystem<double>;
using HierarchicalCoordinateSystemld = HierarchicalCoordinateSystem<long double>;