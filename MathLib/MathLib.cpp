#include <iostream>
#include <cstdlib>
#include "QuaternionTests.hpp"
#include "DualNumberTests.hpp"
#include "DualQuaternionTests.hpp"
#include "CoordinateSystemTests.hpp"


int main()
{
    std::cout << "Running Unit Tests!\n";

    QuaternionTests::Run();
    DualNumberTests::Run();
    DualQuaternionTests::Run();
    CoordinateSystemTests::Run();

    std::cout << "All tests passed!\n";

    return EXIT_SUCCESS;
}
