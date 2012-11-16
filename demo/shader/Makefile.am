bin_PROGRAMS = shader

AM_CPPFLAGS = -Wall \
              -I$(srcdir)/cg4cpp/include \
              -I$(srcdir)/glew/include \
              -I/usr/include/boost -g

shader_SOURCES = \
                 $(srcdir)/glew/src/glew.c \
                 $(srcdir)/glew/include/GL/glew.h \
                 $(srcdir)/glew/include/GL/glxew.h \
                 $(srcdir)/glew/include/GL/wglew.h \
                 $(srcdir)/shader_scene/request_vsync.c \
                 $(srcdir)/shader_scene/request_vsync.h \
                 $(srcdir)/cg4cpp/src/inverse.cpp \
                 $(srcdir)/cg4cpp/include/Cg/inverse.hpp \
                 $(srcdir)/cg4cpp/src/normalize.cpp \
                 $(srcdir)/cg4cpp/include/Cg/normalize.hpp \
                 $(srcdir)/cg4cpp/src/sqrt.cpp \
                 $(srcdir)/cg4cpp/include/Cg/sqrt.hpp \
                 $(srcdir)/shader_scene/countof.h \
                 $(srcdir)/shader_scene/glmatrix.cpp \
                 $(srcdir)/shader_scene/glmatrix.hpp \
                 $(srcdir)/shader_scene/global.hpp \
                 $(srcdir)/shader_scene/main.cpp \
                 $(srcdir)/shader_scene/matrix_stack.cpp \
                 $(srcdir)/shader_scene/matrix_stack.hpp \
                 $(srcdir)/shader_scene/menus.cpp \
                 $(srcdir)/shader_scene/menus.hpp \
                 $(srcdir)/shader_scene/scene.cpp \
                 $(srcdir)/shader_scene/scene.hpp \
                 $(srcdir)/shader_scene/texture.cpp \
                 $(srcdir)/shader_scene/texture.h \
                 $(srcdir)/shader_scene/trackball.c \
                 $(srcdir)/shader_scene/trackball.h \
                 $(srcdir)/stb/stb_image.c \
                 $(srcdir)/stb/stb_image.h
