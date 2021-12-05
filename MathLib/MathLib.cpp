#include <iostream>
#include <cstdlib>
#include "UnitTests.h"


int main()
{
    std::cout << "Running Unit Tests!\n";

    TestQuaternion();
    TestDual();
    TestDualQuaternion();

    std::cout << "All tests passed!\n";
    return EXIT_SUCCESS;
}
