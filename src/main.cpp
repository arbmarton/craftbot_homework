#include "HyperSphere.h"

#include <iostream>


int main()
{
    HyperSphere<2> s1{ { 0.0f, 0.0f }, 1.0f };
    HyperSphere<2> s2{ { -1.0f, -1.0f }, 1.0f };
    s1.relationTo(s2);
    //std::cout << std::boolalpha << s1.intersects(s2) << "\n";
    //HyperSphere<4> s2(std::array<float, 4>{2.0f, 3.0f, 4.0f}, 3.0f);
    //std::cout << "sdfsdfdsf\n";
}