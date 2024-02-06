#pragma once

#include <cinttypes>
#include <array>

namespace craftbot {

// Contains intersection information in the coordinate system which has the origin
// as the center of the hypersphere it produced it
template <size_t dim>
struct IntersectionDescriptor
{
    std::array<float, dim> m_PlaneNormal;  // in 3d would be a, b, c of the plane equation
    float m_PlaneConstant;                 // in 3d would be d of the plane equation

    std::array<float, dim> m_Center;  // the point on the hyperplane in the "center" of the intersection
    float m_Distance;                 // distance from the center on the hyperplane where the intersection points are in space
};

}  // namespace craftbot