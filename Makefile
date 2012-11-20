.PHONY: all clean purge install

all:
	$(MAKE) -C bpix all
	$(MAKE) -C vmath all
	$(MAKE) -C demos all

clean:
	$(MAKE) -C bpix clean
	$(MAKE) -C vmath clean
	$(MAKE) -C demos clean

purge: clean
	$(MAKE) -C bpix purge
	$(MAKE) -C vmath purge
	$(MAKE) -C demos purge

install:
	$(MAKE) -C bpix install
	$(MAKE) -C vmath install
