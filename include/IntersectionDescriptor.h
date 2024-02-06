#pragma once

#include <cinttypes>
#include <array>
#include <iostream>
#include <string>

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

    void print() const
    {
        std::cout << "Plane equation: ";
        for (size_t i = 0; i < m_PlaneNormal.size(); ++i)
        {
            std::cout << m_PlaneNormal[i] << 'x' << std::to_string(i + 1) << " + ";
        }
        std::cout << "= " << m_PlaneConstant << "\n";

        std::cout << "Center point on hyperplane relative to left sphere: ";
        for (size_t i = 0; i < m_Center.size(); ++i)
        {
            std::cout << m_Center[i] << 'x' << std::to_string(i + 1);
            if (i != m_Center.size() - 1)
            {
                std::cout << ", ";
            }
        }

        std::cout << "\nDistance on hyperplane from center: " << m_Distance << "\n\n";
    }
};

}  // namespace craftbot