
# VERBOSE:=true

BUILDDIR := $(BUILD_DIR)
LIBDIR := $(BUILDDIR)
PSI_BUILDDIR := $(BUILDDIR)

SRCDIR := $(SIM_DIR)/../../src

ifeq (true,$(VERBOSE))
define DO_CXX
$(Q)$(CXX) -c -o $@ $^ $(CXXFLAGS)
endef
define MK_AR
$(Q)rm -f $@
$(Q)$(AR) vcq $@ $^
endef 
else # End Verbose
define DO_CXX
$(Q)echo "CXX $^"
$(Q)$(CXX) -c -o $@ $^ $(CXXFLAGS)
endef
define MK_AR
$(Q)rm -f $@
$(Q)echo "ar $@"
$(Q)$(AR) cq $@ $^
endef 
endif


include $(SIMSCRIPTS_DIR)/mkfiles/plusargs.mk
include $(SIM_DIR)/../../rules_defs.mk


CXXFLAGS += -I$(SRCDIR)/psi
CXXFLAGS += -I$(SRCDIR)/../impl
CXXFLAGS += -I$(SRCDIR)/apps
CXXFLAGS += -I/usr/include/libxml2
CXXFLAGS += -g

USE_CXX11 := $(call get_plusarg,USE_CXX11,$(PLUSARGS))

ifeq (true,$(USE_CXX11))
RUN_CXXFLAGS += -std=c++11
endif

#ifeq (true,$(USE_CXX11))
#TEST_LIBS=$(BUILD_DIR)/libpsi_apps.a $(BUILD_DIR)/libpsi_11.a $(BUILD_DIR)/libpsi_impl.a
#else
TEST_LIBS=$(BUILD_DIR)/libpsi_apps.a $(BUILD_DIR)/libpsi.a $(BUILD_DIR)/libpsi_impl.a
#endif

include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk
include $(SIM_DIR)/../../rules_defs.mk

	
ifeq (true,$(QUIET))
COMPILE_REDIR:= > compile.log 2>&1
else
COMPILE_REDIR:= 2>&1 | tee compile.log
endif

$(TESTEXE)$(EXEEXT) : $(SIM_DIR)/src/$(TESTEXE).cpp $(SIM_DIR)/src/test_main.cpp $(TEST_LIBS)
	$(Q)$(CXX) -o $@ $^ $(RUN_CXXFLAGS) $(CXXFLAGS) $(BUILD_DIR)/libpsi.a -lexpat -lxml2 $(COMPILE_REDIR)

	