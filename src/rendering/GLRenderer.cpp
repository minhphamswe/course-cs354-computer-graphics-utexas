/**
 * Implement rendering operations using OpenGL backend for various shapes
 */
#include <stdio.h>
#include <rendering/GLRenderer.h>
#include <shapes/trianglemesh.h>

namespace ishi {

  void GLRenderer::visit(TriangleMesh &tm) {
    printf("Vertex 1: (%f %f %f)\n", tm.vertices[0].x, tm.vertices[0].y, tm.vertices[0].z);
  }
}