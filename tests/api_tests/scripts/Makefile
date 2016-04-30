
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
  DeclarationScope.cpp \
  Graph.cpp \
  Exec.cpp \
  Expr.cpp \
  ExprCore.cpp \
  Extend.cpp \
  Import.cpp \
  ImportCall.cpp \
  IntType.cpp \
  IObjectType.cpp \
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

LIB_TARGETS := libpsi.a


CXXFLAGS += -I$(SRCDIR) -I$(SRCDIR)/static

USE_CXX11 := $(call get_plusarg,USE_CXX11,$(PLUSARGS))

ifeq (true,$(USE_CXX11))
RUN_CXXFLAGS += -std=c++11
endif

libpsi.a : $(SRC:.cpp=.o)
	rm -f $@
	$(AR) vcq $@ $^


include $(SIMSCRIPTS_DIR)/mkfiles/common_sim.mk

%.o : $(SRCDIR)/static/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	
%.o : $(SIM_DIR)/src/%.cpp
	echo "USE_CXX11=$(USE_CXX11)"
	echo "PLUSARGS=$(PLUSARGS)"
	$(CXX) $(RUN_CXXFLAGS) $(CXXFLAGS) -c $^ -o $@
	
ifeq (true,$(QUIET))
$(TESTEXE)$(EXEEXT) : $(SIM_DIR)/src/$(TESTEXE).cpp
	$(Q)$(CXX) -o $@ $^ $(RUN_CXXFLAGS) $(CXXFLAGS) $(BUILD_DIR)/libpsi.a > compile.log 2>&1
else
$(TESTEXE)$(EXEEXT) : $(SIM_DIR)/src/$(TESTEXE).cpp
	$(Q)$(CXX) -o $@ $^ $(RUN_CXXFLAGS) $(CXXFLAGS) $(BUILD_DIR)/libpsi.a 2>&1 | tee compile.log
endif
