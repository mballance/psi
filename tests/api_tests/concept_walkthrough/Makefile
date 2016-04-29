
SRCDIR:=../../../src

#  Constraint.cpp \
#  ConstraintStmt.cpp \
#  Param.cpp \
#  TypeExtension.cpp

#  BinaryExpr.cpp \

ifeq (,$(USE_CXX11))
USE_CXX11:=true
endif

ifeq (true,$(USE_CXX11))
CXXFLAGS += -std=c++11
endif

SRC= \
  Action.cpp \
  BitType.cpp \
  Bool.cpp \
  Component.cpp \
  Constraint.cpp \
  ConstraintStmt.cpp \
  DeclarationScope.cpp \
  Graph.cpp \
  Expr.cpp \
  ExprCore.cpp \
  Extend.cpp \
  IntType.cpp \
  IObjectType.cpp \
  MemoryStruct.cpp \
  Package.cpp \
  ResourceStruct.cpp \
  Struct.cpp \
  Type.cpp \
\
  TypeRegistry.cpp 



ifeq (true,$(USE_CXX11))
all : concept_walkthrough.exe $(SRC:.cpp=.o)
else
all : concept_walkthrough_no11.exe $(SRC:.cpp=.o)
endif

CXXFLAGS += -I$(SRCDIR) -I$(SRCDIR)/static

%.exe : $(SRC:.cpp=.o) %.o
	$(CXX) -o $@ $^

%.o : $(SRCDIR)/static/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean :
	rm -f *.exe *.o
