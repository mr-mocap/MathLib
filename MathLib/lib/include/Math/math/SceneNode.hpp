#pragma once

#include <Math/math/DualQuaternion.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <string_view>


/** @file
 * 
 *  Contains the definition of the SceneNode class
 *
 *  @hideincludegraph
 */

template <class T> class SceneNode;

/** @name Type Aliases
 * 
 *  @relates SceneNode
 */
template <class T>
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
template <class Type>
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
              const Math::BasicVector3D<Type>     &translation,
              const Math::BasicQuaternion<Type>   &rotation,
                    std::string_view          name)
        :
        _coordinate_system{ Math::BasicDualQuaternion<Type>::make_coordinate_system(rotation, translation.x, translation.y, translation.z) },
        _parent{parent},
        _name{name}
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

    const Math::BasicDualQuaternion<Type> &coordinate_system() const { return _coordinate_system; }
          Math::BasicDualQuaternion<Type> &coordinate_system()       { return _coordinate_system; }

    std::string_view name() const { return _name; }

    std::weak_ptr<SceneNode<Type>> createChildNode(const Math::BasicVector3D<Type>   &translation = Math::BasicVector3D<Type>::zero(),
                                                   const Math::BasicQuaternion<Type> &rotation    = Math::BasicQuaternion<Type>::identity(),
                                                         std::string_view        name        = std::string_view())
    {
        std::shared_ptr<SceneNode<Type>> new_node = make( this->weak_from_this(), translation, rotation, name );

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

    Math::BasicVector3D<Type> localToWorld(const Math::BasicVector3D<Type> &local_coordinate) const
    {
#if 1
        using namespace Math;

        BasicDualQuaternion<Type> transforms_to_parent{ concatenatedTransforms() };

        // NOTE: From here on out, we cuse the algebraically-simplified form of multiplying it out with DualQuaternions...
        BasicQuaternion<Type> encoded_point{ BasicQuaternion<Type>::encode_point( local_coordinate ) };
        BasicQuaternion<Type> encoded_translation{ BasicQuaternion<Type>::encode_point( transforms_to_parent.translation() ) };
        BasicDualQuaternion<Type> result{ BasicQuaternion<Type>::identity(), transforms_to_parent.real() * encoded_point * transforms_to_parent.real().conjugate() + encoded_translation };

        return result.dual().imaginary();
#else
        // General case using only BasicDualQuaternion operations.
        // TODO: Why doesn't this work?
        BasicDualQuaternion<Type> transforms_to_parent{ concatenatedTransforms() };
        BasicDualQuaternion<Type> encoded_point{ BasicDualQuaternion<Type>::encode_point(local_coordinate) };
        BasicDualQuaternion<Type> result{ transforms_to_parent * encoded_point * transforms_to_parent.conjugate() };

        return result.translation();
#endif
    }

    Math::BasicDualQuaternion<Type> concatenatedTransforms() const
    {
        if (_parent.expired())
            return _coordinate_system;
        else
            return _parent.lock()->concatenatedTransforms() * _coordinate_system;
    }
private:
    Math::BasicDualQuaternion<Type> _coordinate_system;
    std::weak_ptr<SceneNode<Type>>  _parent;
    SceneNodeList<Type>             _children;
    std::string                     _name;

    static std::shared_ptr<SceneNode<Type>> make(std::weak_ptr<SceneNode<Type>> parent,
                                                 const Math::BasicVector3D<Type>     &translation,
                                                 const Math::BasicQuaternion<Type>   &rotation,
                                                       std::string_view          name)
    {
        return std::make_shared<SceneNode<Type>>(Private{}, parent, translation, rotation, name);
    }
};


/** @name Type Aliases
 * 
 *  @relates SceneNode
 * 
 *  @{
 */
using SceneNodef = SceneNode<float>;
using SceneNoded = SceneNode<double>;
using SceneNodeld = SceneNode<long double>;
/// @}
