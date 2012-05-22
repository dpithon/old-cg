.PHONY: all clean purge install

all:
	$(MAKE) -C bpix all
	$(MAKE) -C 3d all
	$(MAKE) -C demos all

clean:
	$(MAKE) -C bpix clean
	$(MAKE) -C 3d clean
	$(MAKE) -C demos clean

purge: clean
	$(MAKE) -C bpix purge
	$(MAKE) -C 3d purge
	$(MAKE) -C demos purge

install:
	$(MAKE) -C bpix install
	$(MAKE) -C 3d install
