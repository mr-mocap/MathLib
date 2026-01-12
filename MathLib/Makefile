default: lib

.PHONY: lib
lib:
	$(MAKE) --directory=lib --quiet

.PHONY: tests
tests:
	$(MAKE) --directory=Tests --quiet

.PHONY: clean
clean:
	$(MAKE) --directory=lib --quiet clean

.PHONY: docs
docs:
	@echo "Generating documentation..."
	@doxygen Documentation/Doxyfile
	@echo "DONE"

.PHONY: cleandocs
cleandocs:
	@echo "Removing generated documentation..."
	@rm -rf Documentation/html/* Documentation/latex/*

