
#********************************************************************
#* Compile rules
#********************************************************************


ifeq (true,$(QUIET))
REDIRECT:= >/dev/null 2>&1
else
endif

build : $(LIB_TARGETS) 


TESTEXE:=$(call get_plusarg,TESTEXE,$(PLUSARGS))


run : $(TESTEXE)$(EXEEXT)
	$(Q)-./$^ > run.log; \
	  if test $$? -eq 0; then echo "PASSED: $(TESTNAME)" > status.log; \
	  else echo "FAILED: $(TESTNAME)" > status; fi 

