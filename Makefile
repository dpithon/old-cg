.PHONY: all clean purge

all:
	$(MAKE) -C bpix all
	$(MAKE) -C demos all

clean:
	$(MAKE) -C bpix clean
	$(MAKE) -C demos clean

purge: clean
	$(MAKE) -C bpix purge
	$(MAKE) -C demos purge
