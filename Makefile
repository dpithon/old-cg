.PHONY: default prod dev cov profile purge clean deps conf init

CC=gcc
LD=gcc
MAKE=make --no-print-directory

############################################################################

ROOTDIR=$(abspath .)
SRCDIR=$(ROOTDIR)/src
BUILDDIR=$(ROOTDIR)/build

INCDIR=-I$(SRCDIR)\
       -I$(SRCDIR)/core\
       -I$(SRCDIR)/shapes\
       -I$(SRCDIR)/sys\
       -I$(SRCDIR)/materials\
       -I$(SRCDIR)/camera\
       -I$(SRCDIR)/scene

############################################################################

CSTD=-std=c99 -pedantic -fstrict-aliasing
CERR=-Wall -Wextra -Werror

############################################################################

CF_CMN=-pipe $(INCDIR) $(CSTD) $(CERR)
CF_PRD=$(CF_CMN) -DNDEBUG -O2 -g0
CF_DEV=$(CF_CMN) -O0 -g2
CF_COV=$(CF_CMN) -O0 -g2 --coverage

LDF_CMN=-lm
LDF_PRD=$(LDF_CMN)
LDF_DEV=$(LDF_CMN)
LDF_COV=$(LDF_CMN) --coverage

############################################################################

OBJS=$(BUILDDIR)/camera/pinhole.o\
     $(BUILDDIR)/camera/pixmap.o\
     $(BUILDDIR)/camera/render.o\
     $(BUILDDIR)/camera/sampler.o\
     $(BUILDDIR)/core/hit.o\
     $(BUILDDIR)/core/vmath.o\
     $(BUILDDIR)/materials/material.o\
     $(BUILDDIR)/scene/scene.o\
     $(BUILDDIR)/scene/stack.o\
     $(BUILDDIR)/shapes/cone.o\
     $(BUILDDIR)/shapes/cylinder.o\
     $(BUILDDIR)/shapes/paraboloid.o\
     $(BUILDDIR)/shapes/plane.o\
     $(BUILDDIR)/shapes/quadric.o\
     $(BUILDDIR)/shapes/shape.o\
     $(BUILDDIR)/shapes/sphere.o\
     $(BUILDDIR)/sys/dlist.o\
     $(BUILDDIR)/sys/log.o\
     $(BUILDDIR)/sys/pool.o\
     $(BUILDDIR)/sys/slist.o\
     $(BUILDDIR)/demo1.o

SOURCES=src/*.c\
	src/shapes/*.c\
       	src/sys/*.c\
       	src/camera/*.c\
       	src/materials/*.c\
       	src/scene/*.c\
       	src/core/*.c

############################################################################

default: dev

conf:
	@echo 
	@echo "CC = "$(CC)
	@echo "LD = "$(LD)
	@echo "CFLAGS = "$(CFLAGS)
	@echo "LDFLAG = "$(LDFLAGS)
	@echo

init:
	@echo "INIT"
	@mkdir -p $(BUILDDIR)/shapes\
	       	  $(BUILDDIR)/sys\
	       	  $(BUILDDIR)/camera\
	       	  $(BUILDDIR)/materials\
	       	  $(BUILDDIR)/scene\
	       	  $(BUILDDIR)/core

deps: init
	@echo "DEPS"
	@$(CC) -MM $(INCDIR) $(SOURCES) >$(BUILDDIR)/makefile.deps

clean:
	@echo "CLEAN"
	@rm -rf $(BUILDDIR)

purge: clean
	@echo "PURGE"
	@rm -rf $(BUILDDIR)

tags:
	rm -f tags
	cd src;ctags -R --exclude='.git' .

prod: deps
	@CFLAGS="$(CF_PRD)" LDFLAGS="$(LDF_PRD)" $(MAKE) $(BUILDDIR)/demo1

dev: deps
	@CFLAGS="$(CF_DEV)" LDFLAGS="$(LDF_DEV)" $(MAKE) $(BUILDDIR)/demo1

coverage: deps
	@CFLAGS="$(CF_COV)" LDFLAGS="$(LDF_COV)" $(MAKE) $(BUILDDIR)/demo1
	@echo "RUN"
	@cd $(BUILDDIR) && ./demo1
	@echo "LCOV"
	@lcov -q -c -d $(BUILDDIR) -o $(BUILDDIR)/cov.info
	@echo "GENHTML : file:///$(BUILDDIR)/src/index.html"
	@genhtml -q $(BUILDDIR)/cov.info -o $(BUILDDIR)

$(BUILDDIR)/demo1: conf $(OBJS)
	@echo "\nLD $@"
	@$(LD) $(OBJS) -o $@ $(LDFLAGS) 

$(BUILDDIR)/%.o: src/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/shapes/%.o: src/shapes/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/sys/%.o: src/sys/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/camera/%.o: src/camera/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/materials/%.o: src/materials/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/scene/%.o: src/scene/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/core/%.o: src/core/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

-include $(BUILDDIR)/makefile.deps
