default: all

all: 
	cd MathLib && $(MAKE)

tests:
	cd MathLib && $(MAKE) tests

run_tests:
	cd MathLib && $(MAKE) run_tests

docs:
	cd MathLib && $(MAKE) docs

cleandocs:
	cd MathLib && $(MAKE) cleandocs

.PHONY: clean
clean:
	cd MathLib && $(MAKE) clean
