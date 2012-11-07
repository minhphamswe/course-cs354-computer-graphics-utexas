/**
 * Implement rendering operations using OpenGL backend for various shapes
 */
#include <stdio.h>
#include <rendering/GLRenderer.h>
#include <shapes/shape.h>
#include <shapes/trianglemesh.h>

namespace ishi {
GLRenderer::GLRenderer() {}

GLRenderer::~GLRenderer() {}


void GLRenderer::visit(const Shape& s) {
  printf("GL Renderer visited a Shape\n");
}

void GLRenderer::visit(const TriangleMesh& tm) {
  printf("Visited a TriangleMesh\n");
  printf("Vertex 1: (%f %f %f)\n", tm.vertices[0].x, tm.vertices[0].y, tm.vertices[0].z);
}

}