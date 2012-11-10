/**
 * Implement rendering operations using OpenGL backend for various shapes
 */
#include <stdio.h>

#include <rendering/GLRenderer.h>

#include <core/point.h>
#include <core/shape.h>
#include <shapes/trianglemesh.h>
#include <shapes/triangle.h>
#include <shapes/quad.h>

#include <GL/gl.h>
#include <GL/glut.h>

namespace ishi {
GLRenderer::GLRenderer() {}

GLRenderer::~GLRenderer() {}

void GLRenderer::Render(const Shape& s) const {}

void GLRenderer::Render(const TriangleMesh& tm) const {
  Point p;
  Vector n;

  // Save the modelview transformation state
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Go to the mesh
  glMultTransposeMatrixf(reinterpret_cast<float*>(
    tm.ObjectToWorld->Matrix().m));

  // Draw the polygons in the mesh
  for (int i = 0; i < tm.polygons.size(); i++) {
    tm.polygons[i]->Render(*this);
  }

  // Restore the modelview transformation state
  glPopMatrix();
}

void GLRenderer::Render(const Triangle& t) const {
  Point p;
  Vector n;
  Point pt;

  int mat_index = t.tm->material_mapping[t.index];
  if (mat_index >= 0) {
    Texture tex = t.tm->materials[mat_index];

    Vector mat_ambient = tex.Ambient();
    Vector mat_diffuse = tex.Diffuse();
    Vector mat_specular = tex.Specular();
    float mat_shininess = tex.SpecularCoefficient();

    glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient.x);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse.x);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular.x);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess);
  }

  glBegin(GL_TRIANGLES);
    p = t.tm->Vertex(t.p1);
    n = t.tm->Normal(t.p1);
    if (mat_index >= 0) {
      pt = t.tm->textures[t.p1];
      glTexCoord3f(pt.x, pt.y, pt.z);
    }
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);

    p = t.tm->Vertex(t.p2);
    n = t.tm->Normal(t.p2);
    if (mat_index >= 0) {
      pt = t.tm->textures[t.p2];
      glTexCoord3f(pt.x, pt.y, pt.z);
    }
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);

    p = t.tm->Vertex(t.p3);
    n = t.tm->Normal(t.p3);
    if (mat_index >= 0) {
      pt = t.tm->textures[t.p3];
      glTexCoord3f(pt.x, pt.y, pt.z);
    }
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);
  glEnd();
}

void GLRenderer::Render(const Quad& q) const {
  Point p;
  Vector n;
  Point pt;

  int mat_index = q.tm->material_mapping[q.index];
  if (mat_index >= 0) {
    glBindTexture(GL_TEXTURE_2D, mat_index);
    Texture tex = q.tm->materials[mat_index];

    Vector mat_ambient = tex.Ambient();
    Vector mat_diffuse = tex.Diffuse();
    Vector mat_specular = tex.Specular();
    const float mat_shininess = tex.SpecularCoefficient();

    glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient.x);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse.x);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular.x);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess);
  }

  // Draw the quads in the mesh
  glBegin(GL_QUADS);
    p = q.tm->Vertex(q.p1);
    n = q.tm->Normal(q.p1);
    if (mat_index >= 0) {
      pt = q.tm->textures[q.p1];
      glTexCoord3f(pt.x, pt.y, pt.z);
    }
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);

    p = q.tm->Vertex(q.p2);
    n = q.tm->Normal(q.p2);
    if (mat_index >= 0) {
      pt = q.tm->textures[q.p2];
      glTexCoord3f(pt.x, pt.y, pt.z);
    }
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);

    p = q.tm->Vertex(q.p3);
    n = q.tm->Normal(q.p3);
    if (mat_index >= 0) {
      pt = q.tm->textures[q.p3];
      glTexCoord3f(pt.x, pt.y, pt.z);
    }
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);

    p = q.tm->Vertex(q.p4);
    n = q.tm->Normal(q.p4);
    if (mat_index >= 0) {
      pt = q.tm->textures[q.p4];
      glTexCoord3f(pt.x, pt.y, pt.z);
    }
    glNormal3f(n.x, n.y, n.z);
    glVertex3f(p.x, p.y, p.z);

  glEnd();
}

}   // namespace ishi
