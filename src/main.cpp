#include "HyperSphere.h"

#include <iostream>

using namespace craftbot;

int main()
{
    const HyperSphere<3> s1{ { 0.0f, 0.0f, 0.0f }, 1.0f };
    const HyperSphere<3> s2{ { 1.0f, 1.0f, 1.0f }, 10.0f };
    const auto relation = s1.relationTo(s2);
    relation.print();

    //std::cout << std::boolalpha << s1.intersects(s2) << "\n";
    //HyperSphere<4> s2(std::array<float, 4>{2.0f, 3.0f, 4.0f}, 3.0f);
    //std::cout << "sdfsdfdsf\n";
}