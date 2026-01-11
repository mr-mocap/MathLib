default: all

.PHONY: all
all: 
	cd MathLib && $(MAKE)

.PHONY: tests
tests:
	cd MathLib && $(MAKE) tests

.PHONY: docs
docs:
	cd MathLib && $(MAKE) docs

.PHONY: cleandocs
cleandocs:
	cd MathLib && $(MAKE) cleandocs

.PHONY: cleanlib
cleanlib:
	cd MathLib && $(MAKE) clean

.PHONY: clean
clean:
	cd MathLib && $(MAKE) clean