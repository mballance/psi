
ifneq (1,$(RULES))

PSI_DIR  := $(shell cd $(dir $(lastword $(MAKEFILE_LIST))); pwd)
include $(PSI_DIR)/scripts/rules_defs.mk

LIB_TARGETS += $(LIBDIR)/libpsi_impl.a

PSI_IMPL_SRC := $(notdir $(wildcard $(PSI_DIR)/contrib/api_impl/*.cpp))


else

psi : $(LIBDIR)/libpsi.a $(LIBDIR)/libpsi_apps.a $(LIBDIR)/libpsi_impl.a

$(PSI_BUILDDIR)/%.o : $(PSI_DIR)/impl/%.cpp
	$(Q)if test ! -d $(PSI_BUILDDIR); then mkdir -p $(PSI_BUILDDIR); fi
	$(DO_CXX) -I$(PSI_DIR)/impl -I$(PSI_DIR)/src/psi
	
$(LIBDIR)/libpsi_impl.a : $(foreach o,$(PSI_IMPL_SRC:.cpp=.o),$(PSI_BUILDDIR)/$(o))
	$(Q)if test ! -d $(LIBDIR); then mkdir -p $(LIBDIR); fi
	$(MK_AR)

include $(PSI_DIR)/scripts/rules_defs.mk

endif
