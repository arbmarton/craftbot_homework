#pragma once

#include "IntersectionDescriptor.h"
#include "RelationDescriptor.h"

#include <cinttypes>
#include <array>
#include <string>
#include <cassert>

namespace craftbot {

template <size_t dim>
class HyperSphere
{
public:
    HyperSphere() = delete;
    HyperSphere(const std::array<float, dim>& coordinates, const float radius)
        : m_Points(coordinates)
        , m_Radius(radius)
    {
        static_assert(dim > 0, "HyperSphere dimensions must be > 0");
        assert(m_Radius > 0.0f);
    }

    RelationDescriptor<dim> relationTo(const HyperSphere<dim>& rhs) const
    {
        RelationDescriptor<dim> ret;
        if (contains(rhs))
        {
            ret.m_Contains = true;
            return ret;
        }
        else if (rhs.contains(*this))
        {
            ret.m_Contained = true;
            return ret;
        }

        float sum = 0.0f;
        for (size_t i = 0; i < dim; ++i)
        {
            const float diff = m_Points[i] - rhs.m_Points[i];
            sum += diff * diff;
        }

        const float distance = sqrtf(sum);
        const bool intersection = distance <= (m_Radius + rhs.m_Radius);

        if (intersection)
        {
            ret.m_Intersection = calculateIntersection(rhs);
        }
        return ret;
    }

    bool contains(const HyperSphere<dim>& rhs) const
    {
        for (size_t i = 0; i < m_Points.size(); ++i)
        {
            if (rhs.m_Points[i] - rhs.m_Radius <= m_Points[i] - m_Radius || rhs.m_Points[i] + rhs.m_Radius >= m_Points[i] + m_Radius)
            {
                return false;
            }
        }
        return true;
    }

private:
    std::array<float, dim> m_Points;
    float m_Radius;

    // calculations based on:
    // https://math.stackexchange.com/a/1218805
    // https://math.stackexchange.com/a/1039272
    //
    // High level algorithm:
    // 1. Write the equations of the 2 spheres, where this sphere's center is the origin
    // 2. Substract the 2 equations from eachother, this results in the equation of a plane
    // 3. Calculate the distance of the plane from the center of this sphere
    // 4. Determine the point in the hyperplane which is between the 2 spheres, and determine the
    //    distance in the hyperplane from this point where the intersection lies
    IntersectionDescriptor<dim> calculateIntersection(const HyperSphere<dim>& rhs) const
    {
        float c = m_Radius * m_Radius - rhs.m_Radius * rhs.m_Radius;
        for (const auto elem : rhs.m_Points)
        {
            c += elem * elem;
        }
        c /= 2;  // this is the constant in the plane equation

        std::array<float, dim> vectorFromLhsToRhs; // vector from this sphere to rhs
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

        ret.m_Distance = sqrtf(m_Radius * m_Radius - planeDistance * planeDistance); // r in the mathoverflow link
        for (size_t i = 0; i < dim; ++i)
        {
            ret.m_Center[i] = (planeDistance / denominator) * ret.m_PlaneNormal[i]; // c in the mathoverflow link
        }

        return ret;
    }
};

}  // namespace craftbot