
ifeq (,$(VERBOSE))
VERBOSE := false
else
ifeq (true,$(VERBOSE))
VERBOSE := true
else
VERBOSE := false
endif
endif

ifeq (true,$(VERBOSE))
ANT_VERBOSE := -v
endif

all : 
	ant $(ANT_VERBOSE)


