# Makefile to create libpilal.a as well as
# test files

# Compiler options
# Calls: $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

PREFIX		=	.
CXX			=	g++
CXXFLAGS	= 	-Wall -W -pedantic-errors -g -Wno-unused-parameter # -Werror
CXXFLAGS	+= -Wmissing-braces -Wparentheses -ansi

# Directories

LIBDIR		=	$(PREFIX)/lib
BINDIR		=	$(PREFIX)/bin
SRCDIR		=	$(PREFIX)/src
PILDIR		=	$(SRCDIR)/pilal
SIMDIR		=	$(SRCDIR)/simplex


# Linker options
# Calls: $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o -$@

CC			=	g++

# Cleaning options

RM			= 	rm -rf

# Files

SRCF		=	$(wildcard $(SRCDIR)/*.cc) $(wildcard $(PILDIR)/*.cc) $(wildcard $(SIMDIR)/*.cc)
DEPS		=	$(SRCF:.cc=.d*)
OBJS		=	$(SRCF:.cc=.o)
BINS		=	$(BINDIR)/solver

# Targets
# all library clean wipe
.PHONY:	all clean wipe

all: $(BINDIR)/solver

$(BINDIR)/solver: $(OBJS)
	$(CC) $^ -o $@

# Remove $(OBJS) and $(LOBJS) --> No, update them when needed

clean:
	$(RM) $(OBJS) $(DEPS)

wipe:
	$(RM) $(OBJS) $(DEPS) $(BINS)

%.d: %.cc
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$ \

include $(SRCF:.cc=.d)
