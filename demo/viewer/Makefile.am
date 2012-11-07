bin_PROGRAMS = viewer
AM_CPPFLAGS = -I$(srcdir)/src -Wall -g

checkdir = $(srcdir)
check_SCRIPTS = check-code cpplint.py

noinst_HEADERS = $(srcdir)/README.txt \
                 $(viewer_data) \
                 $(check_SCRIPTS)

viewer_datadir = $(srcdir)/data
viewer_data = $(viewer_datadir)/elk.obj \
              $(viewer_datadir)/teapot.obj \
              $(viewer_datadir)/sponza.obj

viewer_SOURCES = $(srcdir)/main.cpp \
                 $(srcdir)/common.h \
                 $(srcdir)/texture.cpp \
                 $(srcdir)/texture.h \
                 $(srcdir)/material.cpp \
                 $(srcdir)/material.h \
                 $(srcdir)/mesh.cpp \
                 $(srcdir)/mesh.h \
                 $(srcdir)/io.cpp \
                 $(srcdir)/io.h \
                 $(srcdir)/bb.h \
                 $(srcdir)/vec.h \
                 $(srcdir)/jpeglib.hpp \
                 $(srcdir)/src/core/point.cpp \
                 $(srcdir)/src/core/point.h \
                 $(srcdir)/src/core/vector.cpp \
                 $(srcdir)/src/core/vector.h \
                 $(srcdir)/src/core/bbox.cpp \
                 $(srcdir)/src/core/bbox.h \
                 $(srcdir)/src/core/matrix.cpp \
                 $(srcdir)/src/core/matrix.h \
                 $(srcdir)/src/core/transform.cpp \
                 $(srcdir)/src/core/transform.h \
                 $(srcdir)/src/shapes/shape.cpp \
                 $(srcdir)/src/shapes/shape.h \
                 $(srcdir)/src/shapes/trianglemesh.cpp \
                 $(srcdir)/src/shapes/trianglemesh.h \
                 $(srcdir)/src/rendering/renderer.cpp \
                 $(srcdir)/src/rendering/renderer.h \
                 $(srcdir)/src/rendering/GLRenderer.cpp \
                 $(srcdir)/src/rendering/GLRenderer.h

check_exclude = $(srcdir)/vec.h $(srcdir)/bb.h

check: all
	./viewer $(viewer_datadir)/teapot.obj
	$(checkdir)/check-code $(filter-out $(check_exclude), $(viewer_SOURCES))

valgrind_gensupp = --gen-suppressions=yes --demangle=no
memcheck_supp = --suppressions=$(srcdir)/lib_drm_intel.supp
memcheck_opts = --leak-check=full --track-origins=yes

verify: all
	valgrind $(valgrind_gensupp)--tool=memcheck $(memcheck_supp) $(memcheck_opts) ./viewer $(viewer_datadir)/elk.obj