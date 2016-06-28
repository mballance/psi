
ifneq (1,$(RULES))
VERSION:=0.4

ifneq (true,$(VERBOSE))
VERBOSE:=false
endif

PSI_ETC_DIR := $(shell cd $(dir $(lastword $(MAKEFILE_LIST))); pwd)
PSI_DIR := $(dir $(PSI_ETC_DIR))

ifeq (,$(BUILDDIR))
BUILDDIR := $(PSI_DIR)/build
endif

ifeq (,$(BUILDRESULT))
BUILDRESULT := $(PSI_DIR)/build/psi
endif

BINDIR := $(BUILDRESULT)/bin
LIBDIR := $(BUILDRESULT)/lib
INCDIR := $(BUILDRESULT)/include

define MKDIRS
$(Q)if test ! -d $(BINDIR); then mkdir -p $(BINDIR); fi
$(Q)if test ! -d $(LIBDIR); then mkdir -p $(LIBDIR); fi
$(Q)if test ! -d $(INCDIR); then mkdir -p $(INCDIR); fi
endef

OBJDIR := $(BUILDDIR)/obj


ifeq (false,$(VERBOSE))
Q:=@
TMSG:=@echo

define MK_AR 
@rm -f $@
@echo "$(AR) $@"
@$(AR) cq $@ $^
endef

else # Verbose mode
TMSG:=#

define MK_AR 
rm -f $@
$(AR) vcq $@ $^
endef

endif

define DO_CXX
$(TMSG) "CXX $^"
$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
$(Q)$(CXX) -c $(CXXFLAGS) -o $@ $^
endef

define DO_CXXLINK
$(TMSG) "CXXLINK $@"
$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
$(Q)$(CXX) $(CXXFLAGS) -o $@ $^
endef

define DO_INST
$(TMSG) "install: $@"
$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
$(Q)cp $^ $@
endef

else # RULES

endif
