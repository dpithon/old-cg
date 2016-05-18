.PHONY: default prod dev cov profile purge clean deps conf init

CF_CMN=-std=c99 -pedantic -Wall -Wextra -Werror -pipe
CF_PRD=$(CFLAGS_CMN) -DNDEBUG -O2 -g0
CF_DEV=$(CFLAGS_CMN) -O0 -g2
CF_COV=$(CFLAGS_CMN) -O0 -g2 --coverage

LDF_CMN=-lm
LDF_PRD=$(LDF_CMN)
LDF_DEV=$(LDF_CMN)
LDF_COV=$(LDF_CMN) --coverage

MAKE=make --no-print-directory

BUILDDIR=build

OBJS=$(BUILDDIR)/pinhole.o\
     $(BUILDDIR)/demo1.o\
     $(BUILDDIR)/sampler.o\
     $(BUILDDIR)/scene.o\
     $(BUILDDIR)/log.o\
     $(BUILDDIR)/render.o\
     $(BUILDDIR)/plane.o\
     $(BUILDDIR)/sphere.o\
     $(BUILDDIR)/vmath.o\
     $(BUILDDIR)/ipoint.o\
     $(BUILDDIR)/material.o\
     $(BUILDDIR)/paraboloid.o\
     $(BUILDDIR)/cylinder.o\
     $(BUILDDIR)/pixmap.o\
     $(BUILDDIR)/cone.o\
     $(BUILDDIR)/stack.o\
     $(BUILDDIR)/quadric.o\
     $(BUILDDIR)/rgb.o\
     $(BUILDDIR)/pool.o


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
	@mkdir -p $(BUILDDIR)

deps: init
	@echo "DEPS"
	@$(CC) -MM src/*.c >$(BUILDDIR)/makefile.deps

clean:
	@echo "CLEAN"
	@rm -rf $(BUILDDIR)

purge: clean
	@echo "PURGE"
	@rm -rf $(BUILDDIR)

tags:
	rm -f tags
	ctags -R --exclude='.git' .

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
	@echo "GENHTML : file:///$(PWD)/$(BUILDDIR)/src/index.html"
	@genhtml -q $(BUILDDIR)/cov.info -o $(BUILDDIR)

$(BUILDDIR)/demo1: conf $(OBJS)
	@echo "LD $@"
	@$(LD) $(OBJS) -o $@ $(LDFLAGS) 

$(BUILDDIR)/%.o: src/%.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

-include $(BUILDDIR)/makefile.deps
