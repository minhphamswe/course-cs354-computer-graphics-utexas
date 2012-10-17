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

checkdir = $(srcdir)
check_SCRIPTS = check-code cpplint.py

mocap_datadir = $(srcdir)/data

noinst_HEADERS = $(srcdir)/bvh.y \
                 $(srcdir)/bvh.l \
                 $(srcdir)/check-code \
                 $(srcdir)/cpplint.py \
                 $(srcdir)/data

mocap_CPPFLAGS = -I$(srcdir)/src -Wall -g
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
                $(srcdir)/lex.yy.cpp \
                $(srcdir)/src/core/point.cpp \
                $(srcdir)/src/core/point.h \
                $(srcdir)/src/core/vector.cpp \
                $(srcdir)/src/core/vector.h \
                $(srcdir)/src/core/transform.cpp \
                $(srcdir)/src/core/transform.h \
                $(srcdir)/src/core/matrix.cpp \
                $(srcdir)/src/core/matrix.h \
                $(srcdir)/src/core/bbox.cpp \
                $(srcdir)/src/core/bbox.h \
                $(srcdir)/src/core/common.h \
                $(srcdir)/src/core/geometry.h

exclude = $(srcdir)/y.tab.cpp \
          $(srcdir)/y.tab.h \
          $(srcdir)/lex.yy.cpp \
          $(srcdir)/vec.h \
          $(srcdir)/loader.h \
          $(srcdir)/bvh_cb_info.cpp \
          $(srcdir)/bvh_cb_info.h \
          $(srcdir)/bvh_defs.h \
          $(srcdir)/geom.h \
          $(srcdir)/types.h \
          $(srcdir)/joint_info.h

valgrind =
# valgrind --leak-check=yes --gen-suppressions=yes
# --log-file=log/memcheck.valgrind

check: all
	$(valgrind) ./mocap $(mocap_datadir)/01_01.bvh
	$(checkdir)/check-code $(filter-out $(exclude),$(mocap_SOURCES))