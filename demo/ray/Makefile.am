bin_PROGRAMS = ray

AM_CPPFLAGS = -Wall -g

ray_SOURCES = \
	      $(srcdir)/src/main.cpp \
	      $(srcdir)/src/general.h \
	      $(srcdir)/src/getopt.cpp \
	      $(srcdir)/src/getopt.h \
	      $(srcdir)/src/RayTracer.cpp \
	      $(srcdir)/src/RayTracer.h \
	      $(srcdir)/src/ui/CommandLineUI.cpp \
	      $(srcdir)/src/ui/CommandLineUI.h \
	      $(srcdir)/src/ui/GraphicalUI.cpp \
	      $(srcdir)/src/ui/GraphicalUI.h \
	      $(srcdir)/src/ui/TraceGLWindow.cpp \
	      $(srcdir)/src/ui/TraceGLWindow.h \
	      $(srcdir)/src/ui/debuggingView.cpp \
	      $(srcdir)/src/ui/debuggingView.h \
	      $(srcdir)/src/ui/debuggingWindow.cxx \
	      $(srcdir)/src/ui/debuggingWindow.h \
	      $(srcdir)/src/ui/glObjects.cpp \
	      $(srcdir)/src/ui/ModelerCamera.cpp \
	      $(srcdir)/src/ui/ModelerCamera.h \
	      $(srcdir)/src/ui/TraceUI.h \
	      $(srcdir)/src/fileio/bitmap.cpp \
	      $(srcdir)/src/fileio/bitmap.h \
	      $(srcdir)/src/fileio/buffer.cpp \
	      $(srcdir)/src/fileio/buffer.h \
	      $(srcdir)/src/fileio/pngimage.cpp \
	      $(srcdir)/src/fileio/pngimage.h \
	      $(srcdir)/src/parser/Token.cpp \
	      $(srcdir)/src/parser/Token.h \
	      $(srcdir)/src/parser/Tokenizer.cpp \
	      $(srcdir)/src/parser/Tokenizer.h \
	      $(srcdir)/src/parser/Parser.cpp \
	      $(srcdir)/src/parser/Parser.h \
	      $(srcdir)/src/parser/ParserException.cpp \
	      $(srcdir)/src/parser/ParserException.h \
	      $(srcdir)/src/scene/bbox.h \
	      $(srcdir)/src/scene/camera.cpp \
	      $(srcdir)/src/scene/camera.h \
	      $(srcdir)/src/scene/light.cpp \
	      $(srcdir)/src/scene/light.h \
	      $(srcdir)/src/scene/material.cpp \
	      $(srcdir)/src/scene/material.h \
	      $(srcdir)/src/scene/ray.cpp \
	      $(srcdir)/src/scene/ray.h \
	      $(srcdir)/src/scene/scene.cpp \
	      $(srcdir)/src/scene/scene.h \
	      $(srcdir)/src/vecmath/vec.h \
	      $(srcdir)/src/vecmath/mat.h \
	      $(srcdir)/src/SceneObjects/Box.cpp \
	      $(srcdir)/src/SceneObjects/Box.h \
	      $(srcdir)/src/SceneObjects/Cone.cpp \
	      $(srcdir)/src/SceneObjects/Cone.h \
	      $(srcdir)/src/SceneObjects/Cylinder.cpp \
	      $(srcdir)/src/SceneObjects/Cylinder.h \
	      $(srcdir)/src/SceneObjects/trimesh.cpp \
	      $(srcdir)/src/SceneObjects/trimesh.h \
	      $(srcdir)/src/SceneObjects/Sphere.cpp \
	      $(srcdir)/src/SceneObjects/Sphere.h \
	      $(srcdir)/src/SceneObjects/Square.cpp \
	      $(srcdir)/src/SceneObjects/Square.h

MEMCHECK = --leak-check=full
OPTS = -r 1

check-scenes: all
	./ray $(OPTS) scenes/box.ray scenes/box.bmp
	./ray $(OPTS) scenes/box_png.ray scenes/box_png.bmp
	./ray $(OPTS) scenes/cone.ray scenes/cone.bmp
	./ray $(OPTS) scenes/cylinder.ray scenes/cylinder.bmp
	./ray $(OPTS) scenes/easy2.ray scenes/easy2.bmp
	./ray $(OPTS) scenes/hitchcock.ray scenes/hitchcock.bmp
	./ray $(OPTS) scenes/reflection.ray scenes/reflection.bmp
	./ray $(OPTS) scenes/reflection1.ray scenes/reflection1.bmp
	./ray $(OPTS) scenes/scene.ray scenes/scene.bmp
	./ray $(OPTS) scenes/scene_blank.ray scenes/scene_blank.bmp
	./ray $(OPTS) scenes/scene_mirror.ray scenes/scene_mirror.bmp
	./ray $(OPTS) scenes/sphere.ray scenes/sphere.bmp
	./ray $(OPTS) scenes/sphere1.ray scenes/sphere1.bmp
	./ray $(OPTS) scenes/sphere_box.ray scenes/sphere_box.bmp
	./ray $(OPTS) scenes/spheres.ray scenes/spheres.bmp
	./ray $(OPTS) scenes/spheres1.ray scenes/spheres1.bmp
	./ray $(OPTS) scenes/spheres_test1.ray scenes/spheres_test1.bmp
	./ray $(OPTS) scenes/tentacles.ray scenes/tentacles.bmp
	./ray $(OPTS) scenes/texture_box.ray scenes/texture_box.bmp
	./ray $(OPTS) scenes/texture_box_png.ray scenes/texture_box_png.bmp
	./ray $(OPTS) scenes/trans.ray scenes/trans.bmp

check-polymesh: all
	./ray $(OPTS) scenes/polymesh/cube.ray scenes/polymesh/cube.bmp
	./ray $(OPTS) scenes/polymesh/dragon.ray scenes/polymesh/dragon.bmp
	./ray $(OPTS) scenes/polymesh/dragon1.ray scenes/polymesh/dragon1.bmp
	./ray $(OPTS) scenes/polymesh/dragon2.ray scenes/polymesh/dragon2.bmp
	./ray $(OPTS) scenes/polymesh/dragon3.ray scenes/polymesh/dragon3.bmp
	./ray $(OPTS) scenes/polymesh/dragon4.ray scenes/polymesh/dragon4.bmp
	./ray $(OPTS) scenes/polymesh/dragon5.ray scenes/polymesh/dragon5.bmp
	./ray $(OPTS) scenes/polymesh/easy1.ray scenes/polymesh/easy1.bmp
	./ray $(OPTS) scenes/polymesh/easy3.ray scenes/polymesh/easy3.bmp
	./ray $(OPTS) scenes/polymesh/easy3a.ray scenes/polymesh/easy3a.bmp
	./ray $(OPTS) scenes/polymesh/easy4.ray scenes/polymesh/easy4.bmp
	./ray $(OPTS) scenes/polymesh/easy5.ray scenes/polymesh/easy5.bmp
	./ray $(OPTS) scenes/polymesh/recurse_depth.ray scenes/polymesh/recurse_depth.bmp
	./ray $(OPTS) scenes/polymesh/shell.ray scenes/polymesh/shell.bmp
	./ray $(OPTS) scenes/polymesh/sier.ray scenes/polymesh/sier.bmp
	./ray $(OPTS) scenes/polymesh/simple.ray scenes/polymesh/simple.bmp
	./ray $(OPTS) scenes/polymesh/trimesh1.ray scenes/polymesh/trimesh1.bmp
	./ray $(OPTS) scenes/polymesh/trimesh2.ray scenes/polymesh/trimesh2.bmp
	./ray $(OPTS) scenes/polymesh/trimesh3.ray scenes/polymesh/trimesh3.bmp
	./ray $(OPTS) scenes/polymesh/turtle.ray scenes/polymesh/turtle.bmp
	./ray $(OPTS) scenes/polymesh/z-polytest.ray scenes/polymesh/z-polytest.bmp

check: check-polymesh

memcheck: all
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/box.ray scenes/box.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/box_png.ray scenes/box_png.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/cone.ray scenes/cone.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/cylinder.ray scenes/cylinder.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/easy2.ray scenes/easy2.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/hitchcock.ray scenes/hitchcock.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/reflection.ray scenes/reflection.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/reflection1.ray scenes/reflection1.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/scene.ray scenes/scene.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/scene_blank.ray scenes/scene_blank.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/scene_mirror.ray scenes/scene_mirror.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/sphere.ray scenes/sphere.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/sphere1.ray scenes/sphere1.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/sphere_box.ray scenes/sphere_box.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/spheres.ray scenes/spheres.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/spheres1.ray scenes/spheres1.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/spheres_test1.ray scenes/spheres_test1.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/tentacles.ray scenes/tentacles.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/texture_box.ray scenes/texture_box.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/texture_box_png.ray scenes/texture_box_png.bmp
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/trans.ray scenes/trans.bmp
