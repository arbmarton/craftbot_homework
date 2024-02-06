#pragma once

#include "IntersectionDescriptor.h"

#include <optional>
#include <iostream>

namespace craftbot {

template <size_t dim>
struct RelationDescriptor
{
    bool m_Contains = false;
    bool m_Contained = false;
    std::optional<IntersectionDescriptor<dim>> m_Intersection;

    void print() const
    {
        if (m_Contains)
        {
            std::cout << "the left sphere contains the right one\n";
        }
        else if (m_Contained)
        {
            std::cout << "the right sphere contains the left one\n";
        }
        else if (m_Intersection)
        {
            std::cout << "the spheres intersect\n";
        }
        else
        {
            std::cout << "the spheres have no intersection\n";
        }
    }
};

}  // namespace craftbot
