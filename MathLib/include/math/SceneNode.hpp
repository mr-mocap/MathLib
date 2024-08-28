#pragma once

#include "math/DualQuaternion.hpp"
#include <memory>
#include <vector>
#include <algorithm>


/** @file
 * 
 *  Contains the definition of the SceneNode class
 *
 *  @hideincludegraph
 */

template <class T> class SceneNode;

template <class T = float>
using SceneNodeList = std::vector< std::shared_ptr<SceneNode<T>> >;


/** Represents a transformation node in a hierarcy, or acyclic graph, structure
 *   
 *   @tparam Type Use a basic type here for specializing the class for float, double, or long double.
 *           Defaults to float.
 * 
 *  @headerfile "math/SceneNode.hpp"
 * 
 *  @see SceneNodef
 *       SceneNoded
 *       SceneNodeld
 */
template <class Type = float>
class SceneNode : public std::enable_shared_from_this<SceneNode<Type>>
{
    struct Private { explicit Private() = default; };

public:
    /** Default constructor
     * 
     *  @note I only want some other class to be able to create these, which
     *        is why I am using this curious technique.  However, it also needs to
     *        be public because of std::make_shared().
     */
    SceneNode(Private) { }

    /** Construct with the given translation and rotation
     * 
     *  @note This is also meant to not be called by the user.
     * 
     *  @see createChildNode
     */
    SceneNode(Private ,
              std::weak_ptr<SceneNode>  parent,
              const Vector3D<Type>     &translation,
              const Quaternion<Type>   &rotation)
        :
        _coordinate_system{ DualQuaternion<Type>::make_coordinate_system(rotation, translation.x, translation.y, translation.z) },
        _parent{parent}
    {
    }
    ~SceneNode() = default;

    /** @name Creation Functions
     *  @{
     */
    /** Creates a default-constructed SceneNode
     *
     *  @return shared_ptr<SceneNode>
     */
    static std::shared_ptr<SceneNode<Type>> make()
    {
        return std::make_shared<SceneNode<Type>>(Private{});
    }
    /// @}

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
#if 1
        DualQuaternion<Type> transforms_to_parent{ concatenatedTransforms() };

        // NOTE: From here on out, we cuse the algebraically-simplified form of multiplying it out with DualQuaternions...
        Quaternion<Type> encoded_point{ Quaternion<Type>::encode_point( local_coordinate ) };
        Quaternion<Type> encoded_translation{ Quaternion<Type>::encode_point( transforms_to_parent.translation() ) };
        DualQuaternion<Type> result{ Quaternion<Type>::identity(), transforms_to_parent.real() * encoded_point * transforms_to_parent.real().conjugate() + encoded_translation };

        return result.dual().imaginary();
#else
        // General case using only DualQuaternion operations.
        // TODO: Why doesn't this work?
        DualQuaternion<Type> transforms_to_parent{ concatenatedTransforms() };
        DualQuaternion<Type> encoded_point{ DualQuaternion<Type>::encode_point(local_coordinate) };
        DualQuaternion<Type> result{ transforms_to_parent * encoded_point * transforms_to_parent.conjugate() };

        return result.translation();
#endif
    }

    DualQuaternion<Type> concatenatedTransforms() const
    {
        if (_parent.expired())
            return _coordinate_system;
        else
            return _parent.lock()->concatenatedTransforms() * _coordinate_system;
    }
private:
    DualQuaternion<Type>           _coordinate_system;
    std::weak_ptr<SceneNode<Type>> _parent;
    SceneNodeList<Type>            _children;

    static std::shared_ptr<SceneNode<Type>> make(std::weak_ptr<SceneNode<Type>> parent,
                                                 const Vector3D<Type>     &translation,
                                                 const Quaternion<Type>   &rotation)
    {
        return std::make_shared<SceneNode<Type>>(Private{}, parent, translation, rotation);
    }

};


/** @name Type Aliases
 * 
 *  @{
 */
using SceneNodef = SceneNode<float>;
using SceneNoded = SceneNode<double>;
using SceneNodeld = SceneNode<long double>;
/// @}
