
ifneq (1,$(RULES))

PSI_SRC_DIR := $(shell cd $(dir $(lastword $(MAKEFILE_LIST))); pwd)
PSI_BUILDDIR := $(BUILDDIR)/psi

# ifeq (Cygwin,$(UNAME_O))
# PSI_SRC_DIR := $(shell cygpath -w $(PSI_SRC_DIR) | sed -e 's^\\^/^g')
# endif

LIB_TARGETS += $(LIBDIR)/libpsi.a $(LIBDIR)/libpsi_apps.a

PSI_API_HEADERS := $(notdir $(wildcard $(PSI_SRC_DIR)/psi/api/*.h))
PSI_CL_HEADERS := $(notdir $(wildcard $(PSI_SRC_DIR)/psi/classlib/*.h))
PSI_APPS_HEADERS := $(notdir $(wildcard $(PSI_SRC_DIR)/apps/*.h))

PSI_CL_SRC := $(notdir $(wildcard $(PSI_SRC_DIR)/psi/classlib/*.cpp))
PSI_APPS_SRC := $(notdir $(wildcard $(PSI_SRC_DIR)/apps/*.cpp))

INST_TARGETS += $(foreach h,$(PSI_API_HEADERS),$(INCDIR)/api/$(h))
INST_TARGETS += $(foreach h,$(PSI_APPS_HEADERS),$(INCDIR)/apps/$(h))
INST_TARGETS += $(INCDIR)/psi.h $(INCDIR)/psi_api.h

else

$(INCDIR)/api/%.h : $(PSI_SRC_DIR)/psi/api/%.h
	$(DO_INST)
	
$(INCDIR)/apps/%.h : $(PSI_SRC_DIR)/apps/%.h
	$(DO_INST)

$(INCDIR)/%.h : $(PSI_SRC_DIR)/psi/%.h
	$(DO_INST)

$(LIBDIR)/libpsi.a : $(foreach o,$(PSI_CL_SRC:.cpp=.o),$(PSI_BUILDDIR)/$(o))
	$(MKDIRS)
	$(MK_AR)

$(PSI_BUILDDIR)/%.o : $(PSI_SRC_DIR)/psi/classlib/%.cpp
	$(Q)if test ! -d $(PSI_BUILDDIR); then mkdir -p $(PSI_BUILDDIR); fi
	$(DO_CXX) -I$(PSI_SRC_DIR)/psi 
	
$(LIBDIR)/libpsi_apps.a : $(foreach o,$(PSI_APPS_SRC:.cpp=.o),$(PSI_BUILDDIR)/$(o))
	$(MKDIRS)
	$(MK_AR)

$(PSI_BUILDDIR)/%.o : $(PSI_SRC_DIR)/apps/%.cpp
	$(Q)if test ! -d $(PSI_BUILDDIR); then mkdir -p $(PSI_BUILDDIR); fi
	$(DO_CXX) -I$(PSI_SRC_DIR)/psi -I$(PSI_SRC_DIR)/apps 

endif
