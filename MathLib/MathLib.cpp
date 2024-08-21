#include <iostream>
#include <cstdlib>
#include "QuaternionTests.hpp"
#include "DualNumberTests.hpp"
#include "DualQuaternionTests.hpp"
#include "SceneNodeTests.hpp"
#include "HierarchicalCoordinateSystemTests.hpp"


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
