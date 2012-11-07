/**
 * Implement rendering operations using OpenGL backend for various shapes
 */
#include <stdio.h>

#include <rendering/GLRenderer.h>

#include <core/point.h>
#include <shapes/shape.h>
#include <shapes/trianglemesh.h>

#include <GL/gl.h>
#include <GL/glut.h>

namespace ishi {
GLRenderer::GLRenderer() {}

GLRenderer::~GLRenderer() {}

void GLRenderer::Render(const Shape& s) {
//   printf("GL Renderer visited a Shape\n");
}

void GLRenderer::Render(const TriangleMesh& tm) {
//   printf("Visiting a TriangleMesh\n");
  Point *pt;

  // Save the modelview transformation state
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Go to the mesh
  glMultTransposeMatrixf(reinterpret_cast<float*>(
    tm.o2w.Matrix().m));

  // Draw the triangles in the mesh
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < tm.triangles.size(); i++) {
    pt = tm.triangles[i];
    glVertex3f(pt->x, pt->y, pt->z);
  }
  glEnd();

  // Draw the quads in the mesh
  glBegin(GL_QUADS);
  for (int i = 0; i < tm.quads.size(); i++) {
    pt = tm.quads[i];
    glVertex3f(pt->x, pt->y, pt->z);
  }
  glEnd();

  // Restore the modelview transformation state
  glPopMatrix();
}

}
