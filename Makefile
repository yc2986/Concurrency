# Master Makefile

all:
	$(MAKE) -C Chapter-1
#$(MAKE) -C Chapter-2

clean:
	$(MAKE) -C Chapter-1 clean
#$(MAKE) -C Chapter-2 clean