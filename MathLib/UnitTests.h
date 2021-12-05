#pragma once

#include "math/DualQuaternion.h"

void TestQuaternion();

void TestDual();

void TestDualQuaternion();

bool IsNear(float value_to_test, float value_it_should_be, float epsilon = 0.0001f);
bool IsNear(Quaternionf value_to_test, Quaternionf value_it_should_be, float epsilon = 0.0001f);
bool IsNear(Dualf value_to_test, Dualf value_it_should_be, float epsilon = 0.0001f);
