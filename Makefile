.PHONY: default prod dev gcov gprof clang purge clean deps conf init

OBJSDIR=/tmp/.cgobjs
OBJS=$(OBJSDIR)/pinhole.o\
     $(OBJSDIR)/demo1.o\
     $(OBJSDIR)/sampler.o\
     $(OBJSDIR)/scene.o\
     $(OBJSDIR)/log.o\
     $(OBJSDIR)/render.o\
     $(OBJSDIR)/plane.o\
     $(OBJSDIR)/sphere.o\
     $(OBJSDIR)/vmath.o\
     $(OBJSDIR)/ipoint.o\
     $(OBJSDIR)/material.o\
     $(OBJSDIR)/paraboloid.o\
     $(OBJSDIR)/cylinder.o\
     $(OBJSDIR)/pixmap.o\
     $(OBJSDIR)/cone.o\
     $(OBJSDIR)/stack.o\
     $(OBJSDIR)/quadric.o\
     $(OBJSDIR)/rgb.o\
     $(OBJSDIR)/pool.o


default: dev

conf:
	@echo
	@echo "########################################################################"
	@echo "CC     :" $(CC)
	@echo "LD     :" $(LD)
	@echo "CFLAGS :" $(CFLAGS)
	@echo "LDFLAG :" $(LDFLAGS)
	@echo "########################################################################"
	@echo

init:
	@mkdir -p $(OBJSDIR)
	@echo "INIT"

deps: init
	@$(CC) -MM src/*.c >$(OBJSDIR)/makefile.deps
	@echo "DEPS"

clean:
	@rm -rf $(OBJSDIR) *.gcda *.gcno *.info *.bak *.pnm
	@echo "CLEAN"

purge: clean
	@rm -rf demo1 demo1.gif html x11colors
	@echo "PURGE"

tags:
	rm -f tags
	ctags -R --exclude='.git' .

prod: deps
	@CC=gcc LD=gcc CFLAGS="-Wall -Wextra -Werror -std=c99 -pedantic -pipe -DNDEBUG -O2 -g0" LDFLAGS="-lm" $(MAKE) --no-print-directory demo1

dev: deps
	@CC=gcc LD=gcc CFLAGS="-Wall -Wextra -Werror -std=c99 -pedantic -pipe -O0 -g2" LDFLAGS="-lm" $(MAKE) --no-print-directory demo1

demo1: conf $(OBJS)
	@$(LD) $(OBJS) -o $@ $(LDFLAGS) 
	@echo "LD $@"

$(OBJSDIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "CC $<"

-include $(OBJSDIR)/makefile.deps
