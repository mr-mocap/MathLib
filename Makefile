default: tests

.PHONY: all
all: 
	@$(MAKE) --directory=MathLib --quiet

.PHONY: tests
tests:
	@$(MAKE) --directory=MathLib/Tests --quiet

.PHONY: docs
docs:
	@$(MAKE) --directory=MathLib docs --quiet

.PHONY: cleandocs
cleandocs:
	@$(MAKE) --directory=MathLib cleandocs --quiet

.PHONY: cleanlib
cleanlib:
	@$(MAKE) --directory=MathLib clean --quiet

.PHONY: clean
clean:
	@$(MAKE) --directory=MathLib clean --quiet
