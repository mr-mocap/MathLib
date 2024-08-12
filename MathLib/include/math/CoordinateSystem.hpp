#pragma once

#include "math/DualQuaternion.hpp"
#include "math/Vector.hpp"
#include "math/types.hpp"
#include <cassert>

/** @file
 *  
 */


/** A class containing various methods dealing with a coordinate system
 *
 */
template <class T>
class CoordinateSystem
{
public:

    /** Creates a DualQuaternion that has only a rotation encoded within it
     *  
     *  @param radians The angle of rotation (in radians) to encode
     *  @param axis    The axis of rotation to encode
     *  
     *  @post output.real.isUnit() == true
     *        output.dual.isZero() == true
     */
    constexpr static DualQuaternion<T> make_rotation(T radians, const Vector3D<T> &axis)
    {
        return make_dualquaternion_rotation(radians, axis.x, axis.y, axis.z);
    }

    /** Creates a DualQuaternion that has only a rotation encoded within it
     *  
     *  @param rotation The rotation to encode
     *  
     *  @post output.real.isUnit() == true
     *        output.dual.isZero() == true
     */
    constexpr static DualQuaternion<T> make_rotation(const Quaternion<T> &rotation)
    {
        return make_dualquaternion_rotation(rotation);
    }

    /** Creates a DualQuaternion that has only a translation encoded within it
     *  
     *  @param translation The translation to encode
     *  
     *  @post output.real.isZero() == true
     *        output.dual.isPure() == true
     */
    constexpr static DualQuaternion<T> make_translation(const Vector3D<T> &translation)
    {
        return make_dualquaternion_translation(translation.x, translation.y, translation.z);
    }

    constexpr static Vector3D<T> translation_of(const DualQuaternion<T> &coordinate_system)
    {
        assert( coordinate_system.real.isUnit() );

        Quaternion<T> translation_decoded = T{2} * coordinate_system.dual * coordinate_system.real.conjugate();
        auto [x, y, z] = translation_decoded.imaginary();

        return Vector3D<T>{ x, y, z };
    }

    /** Creates a coordinate system out of a rotation and a translation
     *  
     *  @param rotation    The rotation to encode
     *  @param translation The translation to encode
     */
    constexpr static DualQuaternion<T> make(const Quaternion<T> &rotation, const Vector3D<T> &translation)
    {
        return make_coordinate_system(rotation, translation.x, translation.y, translation.z);
    }

    /** Create a coordinate system representing no change
     *  
     *  @return A DualQuaternion representation of the global coordinate system
     */
    constexpr static DualQuaternion<T> make_origin()
    {
        return make_identity_dualquaternion<T>();
    }

    constexpr static DualQuaternion<T> translate(const DualQuaternion<T> &coordinate_system, const Vector3D<T> &translation)
    {
        return coordinate_system * make_translation(translation);
    }

    constexpr static DualQuaternion<T> rotate(const DualQuaternion<T> &coordinate_system, const Quaternion<T> &rotation)
    {
        return coordinate_system * make_rotation(rotation);
    }

    constexpr static Vector3D<T> unit_x_axis() { return { T{1}, T{0}, T{0} }; }
    constexpr static Vector3D<T> unit_y_axis() { return { T{0}, T{1}, T{0} }; }
    constexpr static Vector3D<T> unit_z_axis() { return { T{0}, T{0}, T{1} }; }
};


using CoordinateSystemf = CoordinateSystem<float>;
using CoordinateSystemd = CoordinateSystem<double>;
using CoordinateSystemld = CoordinateSystem<long double>;