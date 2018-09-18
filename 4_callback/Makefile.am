AM_CPPFLAGS = -iquote $(top_builddir) -iquote $(top_srcdir) -iquote $(top_srcdir)/cwds

bin_PROGRAMS = simple_screen

simple_screen_SOURCES = AsyncSerial.cpp main.cpp
simple_screen_CXXFLAGS = @LIBCWD_R_FLAGS@ -pthread
simple_screen_LDADD = ../cwds/libcwds_r.la -lboost_system

# --------------- Maintainer's Section

if MAINTAINER_MODE
distclean-local:
	rm -f *.s *.ii

clean-local:
endif

MAINTAINERCLEANFILES = $(srcdir)/Makefile.in
