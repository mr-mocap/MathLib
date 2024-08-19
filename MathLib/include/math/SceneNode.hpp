#pragma once

#include "math/CoordinateSystem.hpp"
#include <memory>
#include <vector>
#include <algorithm>


template <class T> class SceneNode;

template <class T>
using SceneNodeList = std::vector< std::shared_ptr<SceneNode<T>> >;


template <class Type>
class SceneNode : public std::enable_shared_from_this<SceneNode<Type>>
{
    struct Private { explicit Private() = default; };

public:
    SceneNode(Private) { }
    SceneNode(Private ,
              std::weak_ptr<SceneNode> parent,
              const Vector3D<Type> &translation,
              const Quaternion<Type> &rotation)
        :
        _coordinate_system{ CoordinateSystem<Type>::make(rotation, translation) },
        _parent{parent}
    {
    }
   ~SceneNode()
    {
    }

    /** Creates a default-constructed SceneNode
     *
     *  @return shared_ptr<SceneNode>
     */
    static std::shared_ptr<SceneNode<Type>> make()
    {
        return std::make_shared<SceneNode<Type>>(Private{});
    }

    std::weak_ptr<SceneNode<Type>> parent() const { return _parent; }

    const SceneNodeList<Type> &children() const { return _children; }

    const DualQuaternion<Type> &coordinate_system() const { return _coordinate_system; }
          DualQuaternion<Type> &coordinate_system()       { return _coordinate_system; }

    std::weak_ptr<SceneNode<Type>> createChildNode(const Vector3D<Type>   &translation = Vector3D<Type>::zero(),
                                                   const Quaternion<Type> &rotation    = Quaternion<Type>::identity())
    {
        std::shared_ptr<SceneNode<Type>> new_node = make( this->weak_from_this(), translation, rotation );

        _children.push_back( new_node );
        return new_node;
    }

    /** Removes the given SceneNode from its list of children */
    void detachChild(std::shared_ptr<SceneNode<Type>> item_to_detach)
    {
        auto iter = std::ranges::find(_children, item_to_detach);

        if (iter != _children.end())
        {
            // Found!
            (*iter)->_parent.reset();
            _children.erase(iter);
        }
    }

    void attachChild(std::shared_ptr<SceneNode<Type>> node)
    {
        assert( std::ranges::find(_children, node) == _children.end() ); // It is currently not in the list of children!

        _children.push_back( node );
        node->_parent = this->weak_from_this();
    }

    Vector3D<Type> localToWorld(const Vector3D<Type> &local_coordinate) const
    {
        //CoordinateSystem<Type>::encode_point_as_quaternion( local_coordinates )
        return Vector3D<Type>::zero();
    }
protected:
    DualQuaternion<Type>           _coordinate_system = CoordinateSystem<Type>::make_origin();
    std::weak_ptr<SceneNode<Type>> _parent;
    SceneNodeList<Type>            _children;

    static std::shared_ptr<SceneNode<Type>> make(std::weak_ptr<SceneNode<Type>> parent,
                                                 const Vector3D<Type>     &translation,
                                                 const Quaternion<Type>   &rotation)
    {
        return std::make_shared<SceneNode<Type>>(Private{}, parent, translation, rotation);
    }

};


using SceneNodef = SceneNode<float>;
using SceneNoded = SceneNode<double>;
using SceneNodeld = SceneNode<long double>;
