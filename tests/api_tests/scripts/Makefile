
# VERBOSE:=true

include $(SIMSCRIPTS_DIR)/mkfiles/plusargs.mk

SRCDIR := $(SIM_DIR)/../../src

SRC= \
  Action.cpp \
  BitType.cpp \
  Bool.cpp \
  Chandle.cpp \
  Component.cpp \
  Constraint.cpp \
  Elaborator.cpp \
  Exec.cpp \
  Expr.cpp \
  ExprCore.cpp \
  ExprCoreIf.cpp \
  ExprCoreList.cpp \
  ExprList.cpp \
  Graph.cpp \
  GraphStmtSeq.cpp \
  If.cpp \
  Import.cpp \
  ImportCall.cpp \
  IntType.cpp \
  MemoryStruct.cpp \
  Package.cpp \
  ResourceStruct.cpp \
  StreamStruct.cpp \
  String.cpp \
  Struct.cpp \
  Type.cpp \
\
  TypeRegistry.cpp 
  
SRC_IMPL = \
  ActionImpl.cpp \
  BaseItemImpl.cpp \
  BinaryExprImpl.cpp  \
  ComponentImpl.cpp \
  ConstraintBlockImpl.cpp \
  LiteralImpl.cpp \
  ModelImpl.cpp \
  NamedItemImpl.cpp \
  NamedScopeItemImpl.cpp \
  PackageImpl.cpp \
  ScopeItemImpl.cpp \
  StructImpl.cpp
  
SRC_APPS = \
  PSI2XML.cpp

LIB_TARGETS := libapps.a libpsi.a libimpl.a


CXXFLAGS += -I$(SRCDIR)/psi
CXXFLAGS += -I$(SRCDIR)/../impl
CXXFLAGS += -I$(SRCDIR)/apps
CXXFLAGS += -g

USE_CXX11 := $(call get_plusarg,USE_CXX11,$(PLUSARGS))

ifeq (true,$(USE_CXX11))
RUN_CXXFLAGS += -std=c++11
endif

libpsi.a : $(SRC:.cpp=.o)
	$(Q)rm -f $@
	$(Q)$(AR) vcq $@ $^
	
libimpl.a : $(SRC_IMPL:.cpp=.o)
	$(Q)rm -f $@
	$(Q)$(AR) vcq $@ $^
	
libapps.a : $(SRC_APPS:.cpp=.o)
	$(Q)rm -f $@
	$(Q)$(AR) vcq $@ $^

TEST_LIBS=$(BUILD_DIR)/libapps.a $(BUILD_DIR)/libpsi.a $(BUILD_DIR)/libimpl.a

include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk

%.o : $(SRCDIR)/psi/classlib/%.cpp
	$(Q)$(CXX) $(CXXFLAGS) -c $^ -o $@
	
%.o : $(SRCDIR)/../impl/%.cpp
	$(Q)$(CXX) $(CXXFLAGS) -c $^ -o $@
	
%.o : $(SRCDIR)/apps/%.cpp
	$(Q)$(CXX) $(CXXFLAGS) -c $^ -o $@
	
%.o : $(SIM_DIR)/src/%.cpp
	$(Q)$(CXX) $(RUN_CXXFLAGS) $(CXXFLAGS) -c $^ -o $@
	
ifeq (true,$(QUIET))
COMPILE_REDIR:= > compile.log 2>&1
else
COMPILE_REDIR:= 2>&1 | tee compile.log
endif

$(TESTEXE)$(EXEEXT) : $(SIM_DIR)/src/$(TESTEXE).cpp $(SIM_DIR)/src/test_main.cpp $(TEST_LIBS)
	$(Q)$(CXX) -o $@ $^ $(RUN_CXXFLAGS) $(CXXFLAGS) $(BUILD_DIR)/libpsi.a $(COMPILE_REDIR)
