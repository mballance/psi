
include ../etc/defs_rules.mk

ifeq (true,$(VERBOSE))
ANT_VERBOSE := -v
endif

all : 
	ant $(ANT_VERBOSE)

clean:
	$(Q)rm -rf doxydocs
	$(Q)rm -rf flatdocs
