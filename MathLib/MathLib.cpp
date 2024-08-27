#include <iostream>
#include <cstdlib>
#include "Tests/QuaternionTests.hpp"
#include "Tests/DualNumberTests.hpp"
#include "Tests/DualQuaternionTests.hpp"
#include "Tests/SceneNodeTests.hpp"
#include "Tests/HierarchicalCoordinateSystemTests.hpp"


int main()
{
    std::cout << "Running Unit Tests!\n";

    QuaternionTests::Run();
    DualNumberTests::Run();
    DualQuaternionTests::Run();
    SceneNodeTests::Run();
    HierarchicalCoordinateSystemTests::Run();

    std::cout << "All tests passed!\n";

    return EXIT_SUCCESS;
}
