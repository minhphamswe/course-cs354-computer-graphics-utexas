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

void GLRenderer::Render(const Shape& s) const {
//   printf("GL Renderer visited a Shape\n");
}

void GLRenderer::Render(const TriangleMesh& tm) const {
//   printf("Visiting a TriangleMesh\n");
  Point p;
  Vector n;

  // Save the modelview transformation state
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Go to the mesh
  glMultTransposeMatrixf(reinterpret_cast<float*>(
    tm.o2w.Matrix().m));

  // Draw the triangles in the mesh
  glBegin(GL_TRIANGLES);
//   glBegin(GL_LINES);
  for (int i = 0; i < tm.triangles.size(); i++) {
    p = tm.Vertex(tm.triangles[i]);
    n = tm.Normal(tm.triangles[i]);
//     glTexCoord2f();
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);
  }
  glEnd();

  // Draw the quads in the mesh
  glBegin(GL_QUADS);
//   glBegin(GL_LINES);
  for (int i = 0; i < tm.quads.size(); i++) {
    p = tm.Vertex(tm.quads[i]);
    n = tm.Normal(tm.quads[i]);
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);
  }
  glEnd();


  // TODO: Remove debug
//   glBegin(GL_LINES);
//   for (int i = 0; i < tm.triangles.size(); i++) {
//     p = tm.Vertex(tm.triangles[i]);
//     n = tm.Normal(tm.triangles[i]);
//     glVertex3f(p.x, p.y, p.z);
//     glVertex3f(p.x + n.x, p.y + n.y, p.z + n.z);
//   }
//
//   for (int i = 0; i < tm.quads.size(); i++) {
//     p = tm.Vertex(tm.quads[i]);
//     n = tm.Normal(tm.quads[i]);
//     glVertex3f(p.x, p.y, p.z);
//     glVertex3f(p.x + n.x, p.y + n.y, p.z + n.z);
//   }
//   glEnd();

  // Restore the modelview transformation state
  glPopMatrix();
}
}
