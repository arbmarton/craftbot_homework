#include "HyperSphere.h"

#include <iostream>

using namespace craftbot;

#define N 3

int main()
{
    for (int i = -5; i < 10; ++i)
    {
        const HyperSphere<N> s1{ { 0.0f, 0.0f, 0.0f }, 1.0f };
        const HyperSphere<N> s2{ { float(i), 1.0f, 1.0f }, 1.0f };
        const auto relation = s1.relationTo(s2);
        relation.print();
    }
}