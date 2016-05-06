
include etc/defs_rules.mk

all:
	$(Q)echo "Make Targets:"
	$(Q)echo "    dist - create a distribution package"

RULES:=1

INCLUDE:=src tests impl

dist:
	$(Q)$(MAKE) -C doc
	$(Q)rm -rf tmp ; mkdir -p tmp/psi-$(VERSION)
	$(Q)tar cf - $(INCLUDE) | (cd tmp/psi-$(VERSION) ; tar xf -) 
	$(Q)cp -r doc/doxydocs/html tmp/psi-$(VERSION)/doc
	$(Q)rm -rf tmp/psi-$(VERSION)/tests/api_tests/rundir
	$(Q)cd tmp ; tar czf ../psi-$(VERSION).tar.gz psi-$(VERSION)
	$(Q)rm -rf tmp

include etc/defs_rules.mk

	