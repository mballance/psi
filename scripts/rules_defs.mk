
ifneq (1,$(RULES))

PSI_SCRIPTS_DIR := $(shell cd $(dir $(lastword $(MAKEFILE_LIST))); pwd)
PSI_ROOT_DIR    := $(shell dirname $(PSI_SCRIPTS_DIR))
PSI_CONTRIB_DIR := $(PSI_ROOT_DIR)/contrib
PSI_INCLUDE_DIR := $(PSI_ROOT_DIR)/include
PSI_SCHEMA_DIR  := $(PSI_ROOT_DIR)/schema

ifeq (,$(BUILDDIR))
BUILDDIR := $(PSI_CONTRIB_DIR)/../build
endif

ifeq (,$(PKGS_SRCDIR))
PKGS_SRCDIR := $(PSI_CONTRIB_DIR)/../pkgs_src
endif

PSI_BUILDDIR := $(BUILDDIR)/psi

LIBXML_VERSION:=2.9.3
LIBXML_SRC:=$(PKGS_SRCDIR)/libxml2-sources-$(LIBXML_VERSION).tar.gz
LIBXML_URL:=ftp://xmlsoft.org/libxml2/libxml2-sources-$(LIBXML_VERSION).tar.gz

PSS_SCHEMA_O=PSSModelXsd.o

# ifeq (Cygwin,$(UNAME_O))
# PSI_SRC_DIR := $(shell cygpath -w $(PSI_SRC_DIR) | sed -e 's^\\^/^g')
# endif

LIB_TARGETS += $(LIBDIR)/libpsi.a $(LIBDIR)/libpsi_apps.a 
# $(BUILDDIR)/libxml2.build

PSI_API_HEADERS := $(notdir $(wildcard $(PSI_INCLUDE_DIR)/api/*.h))
PSI_CL_HEADERS := $(notdir $(wildcard $(PSI_INCLUDE_DIR)/classlib/*.h))
PSI_APPS_HEADERS := $(notdir $(wildcard $(PSI_CONTRIB_DIR)/apps/*.h))

PSI_CL_SRC := $(notdir $(wildcard $(PSI_CONTRIB_DIR)/classlib_impl/*.cpp))
PSI_APPS_SRC += $(notdir $(wildcard $(PSI_CONTRIB_DIR)/apps/*.cpp))
PSI_APPS_SRC += PSSModel.cpp

INST_TARGETS += $(foreach h,$(PSI_API_HEADERS),$(INCDIR)/api/$(h))
INST_TARGETS += $(foreach h,$(PSI_CL_HEADERS),$(INCDIR)/classlib/$(h))
INST_TARGETS += $(foreach h,$(PSI_APPS_HEADERS),$(INCDIR)/apps/$(h))
INST_TARGETS += $(INCDIR)/psi.h $(INCDIR)/psi_api.h

else

$(BUILDDIR)/libxml2.build : $(LIBXML_SRC)
	$(Q)if test ! -d $(BUILDDIR); then mkdir -p $(BUILDDIR); fi
	$(Q)cd $(BUILDDIR) ; rm -rf build_libxml2 ; mkdir build_libxml2
	$(Q)cd $(BUILDDIR)/build_libxml2; tar xvf $^
	$(Q)cd $(BUILDDIR)/build_libxml2; `pwd`/libxml2-$(LIBXML_VERSION)/configure \
	    --prefix=`pwd`/inst --disable-shared
	$(Q)cd $(BUILDDIR)/build_libxml2; $(MAKE) ; $(MAKE) install
	$(Q)touch $@

$(LIBXML_SRC) : 
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)cd `dirname $@`; wget --no-check-certificate $(LIBXML_URL)

$(INCDIR)/api/%.h : $(PSI_INCLUDE_DIR)/classlib/api/%.h
	$(DO_INST)
	
$(INCDIR)/classlib/%.h : $(PSI_INCLUDE_DIR)/classlib/api/%.h
	$(DO_INST)
	
$(INCDIR)/apps/%.h : $(PSI_SRC_DIR)/apps/%.h
	$(DO_INST)

$(INCDIR)/%.h : $(PSI_SRC_DIR)/psi/%.h
	$(DO_INST)

$(LIBDIR)/libpsi.a : $(foreach o,$(PSI_CL_SRC:.cpp=.o),$(PSI_BUILDDIR)/$(o))
	$(MKDIRS)
	$(MK_AR)
	
vpath %.cpp $(PSI_CONTRIB_DIR)/apps $(PSI_CONTRIB_DIR)/classlib_impl $(PSI_CONTRIB_DIR)/api_impl

$(PSI_BUILDDIR)/%.o : %.cpp
	$(Q)if test ! -d $(PSI_BUILDDIR); then mkdir -p $(PSI_BUILDDIR); fi
	$(DO_CXX) -I$(PSI_INCLUDE_DIR)
	
$(PSI_BUILDDIR)/%.o : $(PSI_BUILDDIR)/%.cpp
	$(Q)if test ! -d $(PSI_BUILDDIR); then mkdir -p $(PSI_BUILDDIR); fi	
	$(DO_CXX) -I$(PSI_SRC_DIR)/psi 
	
$(PSI_BUILDDIR)/%.cpp : $(PSI_SCHEMA_DIR)/%.xsd
	$(Q)cat $^ | perl $(PSI_SRC_DIR)/../scripts/stringify.pl $(basename $(notdir $^)) > $@
	
$(LIBDIR)/libpsi_apps.a : $(foreach o,$(PSI_APPS_SRC:.cpp=.o),$(PSI_BUILDDIR)/$(o))
	$(MKDIRS)
	$(MK_AR)

$(PSI_BUILDDIR)/%.o : $(PSI_SRC_DIR)/apps/%.cpp
	$(Q)if test ! -d $(PSI_BUILDDIR); then mkdir -p $(PSI_BUILDDIR); fi
	$(DO_CXX) -I$(PSI_SRC_DIR)/psi -I$(PSI_SRC_DIR)/apps 

endif
