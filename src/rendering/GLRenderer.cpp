/**
 * Implement rendering operations using OpenGL backend for various shapes
 */
#include <stdio.h>
#include <rendering/GLRenderer.h>
#include <core/point.h>
#include <shapes/shape.h>
#include <shapes/trianglemesh.h>

#include <GL/gl.h>

namespace ishi {
GLRenderer::GLRenderer() {}

GLRenderer::~GLRenderer() {}

void GLRenderer::Render(const Shape& s) {
//   printf("GL Renderer visited a Shape\n");
}

void GLRenderer::Render(const TriangleMesh& tm) {
//   printf("Visiting a TriangleMesh\n");
  Point *p;

  glBegin(GL_TRIANGLES);
  for (int i = 0; i < tm.triangles.size(); i++) {
    p = tm.triangles[i];
//     printf("Vertex %d: (%f %f %f)\n", i, p->x, p->y, p->z);
    glVertex3f(p->x, p->y, p->z);
  }
  glEnd();
}

}
