#include <iostream>
#include <cstdlib>
#include "Tests/QuaternionTests.hpp"
#include "Tests/DualNumberTests.hpp"
#include "Tests/DualQuaternionTests.hpp"
#include "Tests/SceneNodeTests.hpp"
#include "Tests/HierarchicalCoordinateSystemTests.hpp"
#include "Tests/AngleTests.hpp"


int main()
{
    std::cout << "Running Unit Tests!\n";

    AngleTests::Run();
    QuaternionTests::Run();
    DualNumberTests::Run();
    DualQuaternionTests::Run();
    SceneNodeTests::Run();
    HierarchicalCoordinateSystemTests::Run();

    std::cout << "All tests passed!\n";

    return EXIT_SUCCESS;
}
