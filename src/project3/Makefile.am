BUILT_SOURCES = y.tab.cpp

AM_YFLAGS = -d

y.tab.cpp: bvh.y
	$(YACC) $(AM_YFLAGS) $<
	mv y.tab.c y.tab.cpp

y.tab.h: y.tab.cpp

lex.yy.cpp: bvh.l
	$(LEX) $<
	mv lex.yy.c lex.yy.cpp

bin_PROGRAMS = mocap

noinst_HEADERS = $(srcdir)/bvh.y \
                 $(srcdir)/bvh.l

mocap_CPPFLAGS = -I$(srcdir)/src
mocap_SOURCES = $(srcdir)/main.cpp \
                $(srcdir)/joint.cpp \
                $(srcdir)/bvh_cb_info.cpp \
                $(srcdir)/bvh_cb_info.h \
                $(srcdir)/bvh_defs.h \
                $(srcdir)/common.h \
                $(srcdir)/config.h \
                $(srcdir)/geom.h \
                $(srcdir)/joint_info.h \
                $(srcdir)/loader.h \
                $(srcdir)/mat.h \
                $(srcdir)/types.h \
                $(srcdir)/vec.h \
                $(srcdir)/joint.h \
                $(srcdir)/y.tab.cpp \
                $(srcdir)/y.tab.h \
                $(srcdir)/lex.yy.cpp	