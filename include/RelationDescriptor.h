#pragma once

#include "IntersectionDescriptor.h"

#include <optional>

template <size_t dim>
struct RelationDescriptor
{
    bool m_Contains = false;
    bool m_Contained = false;
    std::optional<IntersectionDescriptor<dim>> m_Intersection;
};