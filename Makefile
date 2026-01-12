default: tests

.PHONY: all
all: 
	@$(MAKE) --directory=MathLib --quiet

.PHONY: tests
tests:
	@$(MAKE) --directory=MathLib/Tests --quiet

.PHONY: docs
docs:
	@$(MAKE) --directory=MathLib --quiet docs

.PHONY: cleandocs
cleandocs:
	@$(MAKE) --directory=MathLib --quiet cleandocs

.PHONY: cleanlib
cleanlib:
	@$(MAKE) --directory=MathLib --quiet clean

.PHONY: clean
clean:
	@$(MAKE) --directory=MathLib --quiet clean

.PHONY: cleantests
cleantests:
	@$(MAKE) --directory=MathLib/Tests --quiet clean