
include $(SIMSCRIPTS_DIR)/mkfiles/plusargs.mk

SRCDIR := $(SIM_DIR)/../../src

SRC= \
  Action.cpp \
  BitType.cpp \
  Bool.cpp \
  Chandle.cpp \
  Component.cpp \
  Constraint.cpp \
  ConstraintStmt.cpp \
  Exec.cpp \
  Expr.cpp \
  ExprCore.cpp \
  Graph.cpp \
  Import.cpp \
  ImportCall.cpp \
  IntType.cpp \
  MemoryStruct.cpp \
  Package.cpp \
  Param.cpp \
  ParamList.cpp \
  ResourceStruct.cpp \
  StreamStruct.cpp \
  String.cpp \
  Struct.cpp \
  Type.cpp \
\
  TypeRegistry.cpp 
  
SRC_ELAB = \
	Elaborator.cpp

LIB_TARGETS := libpsi.a libelab.a


CXXFLAGS += -I$(SRCDIR) -I$(SRCDIR)/static
CXXFLAGS += -I$(SRCDIR)/programmatic -I$(SRCDIR)/elaborator

USE_CXX11 := $(call get_plusarg,USE_CXX11,$(PLUSARGS))

ifeq (true,$(USE_CXX11))
RUN_CXXFLAGS += -std=c++11
endif

libpsi.a : $(SRC:.cpp=.o)
	$(Q)rm -f $@
	$(Q)$(AR) vcq $@ $^
	
libelab.a : $(SRC_ELAB:.cpp=.o)
	$(Q)rm -f $@
	$(Q)$(AR) vcq $@ $^

TEST_LIBS=$(BUILD_DIR)/libpsi.a $(BUILD_DIR)/libelab.a

include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk

%.o : $(SRCDIR)/static/%.cpp
	$(Q)$(CXX) $(CXXFLAGS) -c $^ -o $@
	
%.o : $(SRCDIR)/elaborator/%.cpp
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
