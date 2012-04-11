.PHONY: all clean purge

all:
	$(MAKE) -C gpix all
	$(MAKE) -C demos all

clean:
	$(MAKE) -C gpix clean
	$(MAKE) -C demos clean

purge: clean
	$(MAKE) -C gpix purge
	$(MAKE) -C demos purge
