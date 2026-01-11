#TEST_OBJS = MathLib.o \
#			Tests/ColorTypesTests.o \
#			Tests/ColorConversionTests.o \
#            Tests/AngleTests.o \
#			Tests/Vector2DTests.o \
#			Tests/Vector3DTests.o \
#            Tests/DualNumberTests.o \
#            Tests/QuaternionTests.o \
#            Tests/DualQuaternionTests.o \
#            Tests/SceneNodeTests.o \
#            Tests/HierarchicalCoordinateSystemTests.o

default: lib

.PHONY: lib
lib:
	cd lib && $(MAKE)

.PHONY: tests
tests:
	cd Tests && $(MAKE)

.PHONY: clean
clean:
	cd lib && $(MAKE) clean

.PHONY: docs
docs:
	echo "Generating documentation..."
	doxygen Documentation/Doxyfile

.PHONY: cleandocs
cleandocs:
	echo "Removing generated documentation..."
	rm -rf Documentation/html/* Documentation/latex/*

