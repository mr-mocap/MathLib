default: all

all: 
	cd MathLib && $(MAKE) run_tests

run_tests:

.PHONY: clean
clean:
	cd MathLib && $(MAKE) clean
