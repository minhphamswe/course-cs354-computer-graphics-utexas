bin_PROGRAMS = ray

AM_CPPFLAGS = -Wall -g

ray_SOURCES = \
              $(srcdir)/src/main.cpp \
              $(srcdir)/src/general.h \
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

OPTS = -r 10 -w 512
OPTS_SIMPLE = -r 10 -w 512

check-scenes: all
	./ray $(OPTS) scenes/box.ray             scenes/box.bmp
	./ray $(OPTS) scenes/box_png.ray         scenes/box_png.bmp
	./ray $(OPTS) scenes/cone.ray            scenes/cone.bmp
	./ray $(OPTS) scenes/cylinder.ray        scenes/cylinder.bmp
	./ray $(OPTS) scenes/easy2.ray           scenes/easy2.bmp
	./ray $(OPTS) scenes/hitchcock.ray       scenes/hitchcock.bmp
	./ray $(OPTS) scenes/reflection.ray      scenes/reflection.bmp
	./ray $(OPTS) scenes/reflection1.ray     scenes/reflection1.bmp
	./ray $(OPTS) scenes/scene.ray           scenes/scene.bmp
	./ray $(OPTS) scenes/scene_blank.ray     scenes/scene_blank.bmp
	./ray $(OPTS) scenes/scene_mirror.ray    scenes/scene_mirror.bmp
	./ray $(OPTS) scenes/sphere.ray          scenes/sphere.bmp
	./ray $(OPTS) scenes/sphere1.ray         scenes/sphere1.bmp
	./ray $(OPTS) scenes/sphere_box.ray      scenes/sphere_box.bmp
	./ray $(OPTS) scenes/spheres.ray         scenes/spheres.bmp
	./ray $(OPTS) scenes/spheres1.ray        scenes/spheres1.bmp
	./ray $(OPTS) scenes/spheres_test1.ray   scenes/spheres_test1.bmp
	./ray $(OPTS) scenes/tentacles.ray       scenes/tentacles.bmp
	./ray $(OPTS) scenes/texture_box.ray     scenes/texture_box.bmp
	./ray $(OPTS) scenes/texture_box_png.ray scenes/texture_box_png.bmp
	./ray $(OPTS) scenes/trans.ray           scenes/trans.bmp

check-simple: all
	./ray $(OPTS_SIMPLE) scenes/simple/box.ray                     scenes/simple/box.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/box_cyl_opaque_shadow.ray   scenes/simple/box_cyl_opaque_shadow.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/box_cyl_reflect.ray         scenes/simple/box_cyl_reflect.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/box_cyl_transp_shadow.ray   scenes/simple/box_cyl_transp_shadow.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/box_dist_atten.ray          scenes/simple/box_dist_atten.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/cyl_ambient.ray             scenes/simple/cyl_ambient.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/cyl_diff_spec.ray           scenes/simple/cyl_diff_spec.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/cyl_diffuse.ray             scenes/simple/cyl_diffuse.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/cyl_emissive.ray            scenes/simple/cyl_emissive.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/cylinder_refract.ray        scenes/simple/cylinder_refract.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/cylinder_refract_simple.ray scenes/simple/cylinder_refract_simple.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_reflect.ray          scenes/simple/sphere_reflect.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract.ray          scenes/simple/sphere_refract.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract2.ray         scenes/simple/sphere_refract2.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract3.ray         scenes/simple/sphere_refract3.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract4.ray         scenes/simple/sphere_refract4.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract5.ray         scenes/simple/sphere_refract5.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract6.ray         scenes/simple/sphere_refract6.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract_simple.ray   scenes/simple/sphere_refract_simple.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/texture_map.ray             scenes/simple/texture_map.bmp
	./ray $(OPTS_SIMPLE) scenes/simple/texture_map_png.ray         scenes/simple/texture_map_png.bmp

check-polymesh: all
	./ray $(OPTS) scenes/polymesh/cube.ray          scenes/polymesh/cube.bmp
	./ray $(OPTS) scenes/polymesh/dragon.ray        scenes/polymesh/dragon.bmp
	./ray $(OPTS) scenes/polymesh/dragon1.ray       scenes/polymesh/dragon1.bmp
	./ray $(OPTS) scenes/polymesh/dragon2.ray       scenes/polymesh/dragon2.bmp
	./ray $(OPTS) scenes/polymesh/dragon3.ray       scenes/polymesh/dragon3.bmp
	./ray $(OPTS) scenes/polymesh/dragon4.ray       scenes/polymesh/dragon4.bmp
	./ray $(OPTS) scenes/polymesh/dragon5.ray       scenes/polymesh/dragon5.bmp
	./ray $(OPTS) scenes/polymesh/easy1.ray         scenes/polymesh/easy1.bmp
	./ray $(OPTS) scenes/polymesh/easy3.ray         scenes/polymesh/easy3.bmp
	./ray $(OPTS) scenes/polymesh/easy3a.ray        scenes/polymesh/easy3a.bmp
	./ray $(OPTS) scenes/polymesh/easy4.ray         scenes/polymesh/easy4.bmp
	./ray $(OPTS) scenes/polymesh/easy5.ray         scenes/polymesh/easy5.bmp
	./ray $(OPTS) scenes/polymesh/recurse_depth.ray scenes/polymesh/recurse_depth.bmp
	./ray $(OPTS) scenes/polymesh/shell.ray         scenes/polymesh/shell.bmp
	./ray $(OPTS) scenes/polymesh/sier.ray          scenes/polymesh/sier.bmp
	./ray $(OPTS) scenes/polymesh/simple.ray        scenes/polymesh/simple.bmp
	./ray $(OPTS) scenes/polymesh/trimesh1.ray      scenes/polymesh/trimesh1.bmp
	./ray $(OPTS) scenes/polymesh/trimesh2.ray      scenes/polymesh/trimesh2.bmp
	./ray $(OPTS) scenes/polymesh/trimesh3.ray      scenes/polymesh/trimesh3.bmp
	./ray $(OPTS) scenes/polymesh/turtle.ray        scenes/polymesh/turtle.bmp
	./ray $(OPTS) scenes/polymesh/z-polytest.ray    scenes/polymesh/z-polytest.bmp

check: check-simple check-scenes check-polymesh

MEMCHECK = --leak-check=full --show-reachable=yes
MEMCHECK_LOG = memcheck

memcheck-scenes: all
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/box.ray             scenes/box.bmp             &> scenes/box_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/box_png.ray         scenes/box_png.bmp         &> scenes/box_png_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/cone.ray            scenes/cone.bmp            &> scenes/cone_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/cylinder.ray        scenes/cylinder.bmp        &> scenes/cylinder_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/easy2.ray           scenes/easy2.bmp           &> scenes/easy2_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/hitchcock.ray       scenes/hitchcock.bmp       &> scenes/hitchcock_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/reflection.ray      scenes/reflection.bmp      &> scenes/reflection_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/reflection1.ray     scenes/reflection1.bmp     &> scenes/reflection1_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/scene.ray           scenes/scene.bmp           &> scenes/scene_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/scene_blank.ray     scenes/scene_blank.bmp     &> scenes/scene_blank_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/scene_mirror.ray    scenes/scene_mirror.bmp    &> scenes/scene_mirror_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/sphere.ray          scenes/sphere.bmp          &> scenes/sphere_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/sphere1.ray         scenes/sphere1.bmp         &> scenes/sphere1_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/sphere_box.ray      scenes/sphere_box.bmp      &> scenes/sphere_box_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/spheres.ray         scenes/spheres.bmp         &> scenes/spheres_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/spheres1.ray        scenes/spheres1.bmp        &> scenes/spheres1_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/spheres_test1.ray   scenes/spheres_test1.bmp   &> scenes/spheres_test1_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/tentacles.ray       scenes/tentacles.bmp       &> scenes/tentacles_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/texture_box.ray     scenes/texture_box.bmp     &> scenes/texture_box_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/texture_box_png.ray scenes/texture_box_png.bmp &> scenes/texture_box_png_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/trans.ray           scenes/trans.bmp           &> scenes/trans_$(MEMCHECK_LOG).log

memcheck-simple: all
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/box.ray                     scenes/simple/box.bmp                     &> scenes/simple/box_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/box_cyl_opaque_shadow.ray   scenes/simple/box_cyl_opaque_shadow.bmp   &> scenes/simple/box_cyl_opaque_shadow_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/box_cyl_reflect.ray         scenes/simple/box_cyl_reflect.bmp         &> scenes/simple/box_cyl_reflect_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/box_cyl_transp_shadow.ray   scenes/simple/box_cyl_transp_shadow.bmp   &> scenes/simple/box_cyl_transp_shadow_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/box_dist_atten.ray          scenes/simple/box_dist_atten.bmp          &> scenes/simple/box_dist_atten_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/cyl_ambient.ray             scenes/simple/cyl_ambient.bmp             &> scenes/simple/cyl_ambient_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/cyl_diff_spec.ray           scenes/simple/cyl_diff_spec.bmp           &> scenes/simple/cyl_diff_spec_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/cyl_diffuse.ray             scenes/simple/cyl_diffuse.bmp             &> scenes/simple/cyl_diffuse_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/cyl_emissive.ray            scenes/simple/cyl_emissive.bmp            &> scenes/simple/cyl_emissive_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/cylinder_refract.ray        scenes/simple/cylinder_refract.bmp        &> scenes/simple/cylinder_refract_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/cylinder_refract_simple.ray scenes/simple/cylinder_refract_simple.bmp &> scenes/simple/cylinder_refract_simple_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_reflect.ray          scenes/simple/sphere_reflect.bmp          &> scenes/simple/sphere_reflect_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract.ray          scenes/simple/sphere_refract.bmp          &> scenes/simple/sphere_refract_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract2.ray         scenes/simple/sphere_refract2.bmp         &> scenes/simple/sphere_refract2_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract3.ray         scenes/simple/sphere_refract3.bmp         &> scenes/simple/sphere_refract3_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract4.ray         scenes/simple/sphere_refract4.bmp         &> scenes/simple/sphere_refract4_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract5.ray         scenes/simple/sphere_refract5.bmp         &> scenes/simple/sphere_refract5_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract6.ray         scenes/simple/sphere_refract6.bmp         &> scenes/simple/sphere_refract6_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/sphere_refract_simple.ray   scenes/simple/sphere_refract_simple.bmp   &> scenes/simple/sphere_refract_simple_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/texture_map.ray             scenes/simple/texture_map.bmp             &> scenes/simple/texture_map_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS_SIMPLE) scenes/simple/texture_map_png.ray         scenes/simple/texture_map_png.bmp         &> scenes/simple/texture_map_png_$(MEMCHECK_LOG).log

memcheck-polymesh: all
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/cube.ray          scenes/polymesh/cube.bmp          &> scenes/polymesh/cube_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/dragon.ray        scenes/polymesh/dragon.bmp        &> scenes/polymesh/dragon_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/dragon1.ray       scenes/polymesh/dragon1.bmp       &> scenes/polymesh/dragon1_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/dragon2.ray       scenes/polymesh/dragon2.bmp       &> scenes/polymesh/dragon2_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/dragon3.ray       scenes/polymesh/dragon3.bmp       &> scenes/polymesh/dragon3_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/dragon4.ray       scenes/polymesh/dragon4.bmp       &> scenes/polymesh/dragon4_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/dragon5.ray       scenes/polymesh/dragon5.bmp       &> scenes/polymesh/dragon5_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/easy1.ray         scenes/polymesh/easy1.bmp         &> scenes/polymesh/easy1_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/easy3.ray         scenes/polymesh/easy3.bmp         &> scenes/polymesh/easy3_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/easy3a.ray        scenes/polymesh/easy3a.bmp        &> scenes/polymesh/easy3a_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/easy4.ray         scenes/polymesh/easy4.bmp         &> scenes/polymesh/easy4_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/easy5.ray         scenes/polymesh/easy5.bmp         &> scenes/polymesh/easy5_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/recurse_depth.ray scenes/polymesh/recurse_depth.bmp &> scenes/polymesh/recurse_depth_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/shell.ray         scenes/polymesh/shell.bmp         &> scenes/polymesh/shell_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/sier.ray          scenes/polymesh/sier.bmp          &> scenes/polymesh/sier_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/simple.ray        scenes/polymesh/simple.bmp        &> scenes/polymesh/simple_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/trimesh1.ray      scenes/polymesh/trimesh1.bmp      &> scenes/polymesh/trimesh1_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/trimesh2.ray      scenes/polymesh/trimesh2.bmp      &> scenes/polymesh/trimesh2_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/trimesh3.ray      scenes/polymesh/trimesh3.bmp      &> scenes/polymesh/trimesh3_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/turtle.ray        scenes/polymesh/turtle.bmp        &> scenes/polymesh/turtle_$(MEMCHECK_LOG).log
	valgrind $(MEMCHECK) ./ray $(OPTS) scenes/polymesh/z-polytest.ray    scenes/polymesh/z-polytest.bmp    &> scenes/polymesh/z-polytest_$(MEMCHECK_LOG).log

memcheck: memcheck-scenes memcheck-simple memcheck-polymesh
