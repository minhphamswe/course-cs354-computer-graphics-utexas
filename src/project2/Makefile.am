bin_PROGRAMS = billiards

billiards_CPPFLAGS = -I$(top_srcdir)/lib -I$(top_srcdir)/src
billiards_LDFLAGS = -lglut -lGLU -lGL -lm
billiards_SOURCES = main.cpp ball.cpp \
                    ../core/point.cpp \
                    ../core/color.cpp \
                    ../core/vector.cpp \
                    ../core/matrix.cpp \
                    ../core/transform.cpp \
                    ../physics/object.cpp \
                    ../physics/sphere.cpp \
                    ../physics/collission.cpp \
                    ../shapes/disk.cpp
