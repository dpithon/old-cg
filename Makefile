.PHONY: all clean purge install

all:
	$(MAKE) -C bpix all
	$(MAKE) -C geom all
	$(MAKE) -C demos all

clean:
	$(MAKE) -C bpix clean
	$(MAKE) -C geom clean
	$(MAKE) -C demos clean

purge: clean
	$(MAKE) -C bpix purge
	$(MAKE) -C geom purge
	$(MAKE) -C demos purge

install:
	$(MAKE) -C bpix install
	$(MAKE) -C geom install
