.PHONY: all clean purge install

all:
	$(MAKE) -C bpix all
	$(MAKE) -C vmath all

test:
	$(MAKE) -C bpix/test all
	$(MAKE) -C vmath/test all

clean:
	$(MAKE) -C bpix clean
	$(MAKE) -C vmath clean
	$(MAKE) -C bpix/test clean
	$(MAKE) -C vmath/test clean

purge:
	$(MAKE) -C bpix purge
	$(MAKE) -C vmath purge
	$(MAKE) -C bpix/test purge
	$(MAKE) -C vmath/test purge

install:
	$(MAKE) -C bpix install
	$(MAKE) -C vmath install
