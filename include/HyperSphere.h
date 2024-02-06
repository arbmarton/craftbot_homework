#pragma once

#include "IntersectionDescriptor.h"
#include "RelationDescriptor.h"

#include <cinttypes>
#include <array>
#include <string>
#include <iostream>

//constexpr bool printLogs = true;

namespace craftbot {

template <size_t dim>
class HyperSphere
{
public:
    HyperSphere(const std::array<float, dim>& coordinates, const float radius)
        : m_Points(coordinates)
        , m_Radius(radius)
    {
        static_assert(dim > 0, "HyperSphere dimensions must be > 0");
    }

    RelationDescriptor<dim> relationTo(const HyperSphere<dim>& rhs) const
    {
        float sum = 0.0f;
        for (size_t i = 0; i < dim; ++i)
        {
            const float diff = m_Points[i] - rhs.m_Points[i];
            sum += diff * diff;
        }

        const float distance = sqrtf(sum);
        const bool intersection = distance <= (m_Radius + rhs.m_Radius);

        //if (printLogs)
        //{
        //    std::cout << "The spheres are " << std::to_string(distance) << " distance apart. \n";
        //    std::cout << std::boolalpha << "Intersection: " << intersection << "\n";
        //}

        RelationDescriptor<dim> ret;

        if (contains(rhs))
        {
            ret.m_Contains = true;
        }
        else if (rhs.contains(*this))
        {
            ret.m_Contained = true;
        }
        else if (intersection)
        {
            ret.m_Intersection = calculateIntersection(rhs);
        }

        return ret;
    }

    bool contains(const HyperSphere<dim>& rhs) const
    {
        for (size_t i = 0; i < m_Points.size(); ++i)
        {
            if (rhs.m_Points[i] - rhs.m_Radius < m_Points[i] - m_Radius || rhs.m_Points[i] + m_Radius > m_Points[i] + m_Radius)
            {
                return false;
            }
        }
        return true;
    }

private:
    std::array<float, dim> m_Points;
    float m_Radius;

    IntersectionDescriptor<dim> calculateIntersection(const HyperSphere<dim>& rhs) const
    {
        float c = m_Radius * m_Radius - rhs.m_Radius * rhs.m_Radius;
        for (const auto elem : rhs.m_Points)
        {
            c += elem * elem;
        }
        c /= 2;

        std::array<float, dim> vectorFromLhsToRhs;
        for (size_t i = 0; i < vectorFromLhsToRhs.size(); ++i)
        {
            vectorFromLhsToRhs[i] = rhs.m_Points[i] - m_Points[i];
        }

        IntersectionDescriptor<dim> ret;
        ret.m_PlaneNormal = vectorFromLhsToRhs;
        ret.m_PlaneConstant = c;

        float planeDistance = ret.m_PlaneConstant;
        float sqrtSum = 0.0f;
        for (size_t i = 0; i < vectorFromLhsToRhs.size(); ++i)
        {
            sqrtSum += vectorFromLhsToRhs[i] * vectorFromLhsToRhs[i];
        }
        const float denominator = sqrtf(sqrtSum);
        planeDistance /= denominator;

        ret.m_Distance = sqrtf(m_Radius * m_Radius - planeDistance * planeDistance);
        for (size_t i = 0; i < dim; ++i)
        {
            ret.m_Center[i] = (planeDistance / denominator) * ret.m_PlaneNormal[i];
        }

        return ret;
    }
};

}  // namespace craftbot