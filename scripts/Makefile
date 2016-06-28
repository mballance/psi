
include ../etc/defs_rules.mk
include ../src/rules_defs.mk


RULES:=1

all: $(LIB_TARGETS) $(EXE_TARGETS) $(INST_TARGETS)
	$(Q)echo "Make Targets:"
	$(Q)echo "    dist - create a distribution package"
	
INCLUDE:=src tests impl LICENSE ChangeLog.txt rules_defs.mk

dist:
	$(Q)$(MAKE) -C doc
	$(Q)rm -rf tmp
	$(Q)mkdir -p tmp/psi-$(VERSION)
	$(Q)mkdir -p tmp/psi-$(VERSION)/doc
	$(Q)tar cf - $(INCLUDE) | (cd tmp/psi-$(VERSION) ; tar xf -) 
	$(Q)cp -r doc/doxydocs/html tmp/psi-$(VERSION)/doc/html
	$(Q)rm -rf tmp/psi-$(VERSION)/tests/api_tests/rundir
	$(Q)cd tmp ; tar czf ../psi-$(VERSION).tar.gz psi-$(VERSION)
	$(Q)rm -rf tmp
	
clean:
	$(Q)rm -rf tests/api_tests/rundir
	$(Q)rm -rf tmp Debug
	$(Q)$(MAKE) -C doc clean

include ../src/rules_defs.mk
include ../etc/defs_rules.mk

	