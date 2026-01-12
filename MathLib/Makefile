default: lib

.PHONY: lib
lib:
	@cd lib && $(MAKE)

.PHONY: tests
tests:
	@cd Tests && $(MAKE)

.PHONY: clean
clean:
	@cd lib && $(MAKE) clean

.PHONY: docs
docs:
	@echo "Generating documentation..."
	@doxygen Documentation/Doxyfile
	@echo "DONE"

.PHONY: cleandocs
cleandocs:
	@echo "Removing generated documentation..."
	@rm -rf Documentation/html/* Documentation/latex/*

