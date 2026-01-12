default: all

.PHONY: all
all: 
	@$(MAKE) --directory=MathLib --quiet
#	@cd MathLib && $(MAKE)

.PHONY: tests
tests:
	@$(MAKE) --directory=MathLib/Tests --quiet
#	@cd MathLib && $(MAKE) tests

.PHONY: docs
docs:
	@$(MAKE) --directory=MathLib docs --quiet
#	@cd MathLib && $(MAKE) docs

.PHONY: cleandocs
cleandocs:
	@$(MAKE) --directory=MathLib cleandocs --quiet
#	@cd MathLib && $(MAKE) cleandocs

.PHONY: cleanlib
cleanlib:
	@$(MAKE) --directory=MathLib clean --quiet
#	@cd MathLib && $(MAKE) clean

.PHONY: clean
clean:
	@$(MAKE) --directory=MathLib clean --quiet
#	@cd MathLib && $(MAKE) clean
