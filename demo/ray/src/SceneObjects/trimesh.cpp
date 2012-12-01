#include <cmath>
#include <assert.h>
#include <float.h>
#include "trimesh.h"

using namespace std;

Trimesh::~Trimesh() {
  for (Materials::iterator i = materials.begin(); i != materials.end(); ++i)
    delete *i;
}

// must add vertices, normals, and materials IN ORDER
void Trimesh::addVertex(const Vec3d &v) {
  vertices.push_back(v);
}

void Trimesh::addMaterial(Material *m) {
  materials.push_back(m);
}

void Trimesh::addNormal(const Vec3d &n) {
  normals.push_back(n);
}

// Returns false if the vertices a,b,c don't all exist
bool Trimesh::addFace(int a, int b, int c) {
  int vcnt = vertices.size();

  if (a >= vcnt || b >= vcnt || c >= vcnt)
    return false;

  TrimeshFace *newFace = new TrimeshFace(scene, new Material(*this->material), this, a, b, c);
  newFace->setTransform(this->transform);
  faces.push_back(newFace);
  return true;
}

char *
Trimesh::doubleCheck()
// Check to make sure that if we have per-vertex materials or normals
// they are the right number.
{
  if (!materials.empty() && materials.size() != vertices.size())
    return "Bad Trimesh: Wrong number of materials.";

  if (!normals.empty() && normals.size() != vertices.size())
    return "Bad Trimesh: Wrong number of normals.";

  return 0;
}

bool Trimesh::intersectLocal(const ray&r, isect&i) const {
  double tmin = 0.0;
  double tmax = 0.0;
  typedef Faces::const_iterator iter;
  bool have_one = false;

  for (iter j = faces.begin(); j != faces.end(); ++j) {
    isect cur;
    if ((*j)->intersectLocal(r, cur)) {
      if (!have_one || (cur.t < i.t)) {
        i = cur;
        have_one = true;
      }
    }
  }

  if (!have_one)
    i.setT(1000.0);

  return have_one;
}

// Intersect ray r with the triangle abc.  If it hits returns true,
// and puts the t parameter, barycentric coordinates, normal, object id,
// and object material in the isect object
bool TrimeshFace::intersectLocal(const ray& r, isect& i) const {
  const Vec3d& a = parent->vertices[ids[0]];
  const Vec3d& b = parent->vertices[ids[1]];
  const Vec3d& c = parent->vertices[ids[2]];

  // YOUR CODE HERE
  // The normal vector to the plane containing the triangle
  Vec3d n = (a-c) ^ (b-a);
  n.normalize();
  double d = -(n * a);

  // We have n * (r(t) - a) == 0 if the point r(t) is on the plane containing
  // the triangle (since r(t) - a is perpendicular with n). Since the dot
  // product is distributive over vector addition (source: Wikipedia), we
  // have: n * r(t) - n * a == 0
  // <=> n * (P + td) = n * a
  // <=> t = ((n * a) - (n * P)) / (n * d)
  // <=> t = (n * (a - P)) / (n * d)
  // The t parameter of the intersection point
  double t = - ((n * r.getPosition()) + d) / (n * r.getDirection());

  if (t < RAY_EPSILON) {
    return false;
  }
  else {
    // The intersection point
    Vec3d q = r.at(t);

    // Project the triangle and intersection point into an axis-aligned plane
    // such that area of the triangle is maximized
    // Coordinates of the points in 2D
    Vec2d A, B, C, Q;

    if (abs(n[0]) > abs(n[1]) && abs(n[0]) > abs(n[2])) {
      A = Vec2d(a[1], a[2]);
      B = Vec2d(b[1], b[2]);
      C = Vec2d(c[1], c[2]);
      Q = Vec2d(q[1], q[2]);
    } else if (abs(n[1]) > abs(n[2])) {
      A = Vec2d(a[0], a[2]);
      B = Vec2d(b[0], b[2]);
      C = Vec2d(c[0], c[2]);
      Q = Vec2d(q[0], q[2]);
    } else {
      A = Vec2d(a[0], a[1]);
      B = Vec2d(b[0], b[1]);
      C = Vec2d(c[0], c[1]);
      Q = Vec2d(q[0], q[1]);
    }

    // Determinant of the transformation matrix to find the barycentric coords
    double det = 1.0 /
                ((B[1] - C[1]) * (A[0] - C[0]) +
                  (C[0] - B[0]) * (A[1] - C[1]));

    // The barycentric coordinates at a, b, and c (source: Wikipedia)
    double u, v, w;
    u = ((B[1] - C[1]) * (Q[0] - C[0]) + (C[0] - B[0]) * (Q[1] - C[1])) * det;
    v = ((C[1] - A[1]) * (Q[0] - C[0]) + (A[0] - C[0]) * (Q[1] - C[1])) * det;
    w = 1 - u - v;

    if (u > 0 && v > 0 && w > 0) {
      // The intersection point is inside the triangle
      i.N = n;
      i.t = t;
      i.setObject(this);
      i.setBary(Vec3d(u, v, w));

      Material *mat;
      if (material != NULL) {
        mat = new Material(*(material));
      } else if (parent->material != NULL) {
        mat = new Material(*(parent->material));
      } else {
        mat = new Material();
      }
      assert(mat != NULL);
      i.setMaterial(*mat);

      return true;
    } else {
      // The intersection point is outside the triangle
      return false;
    }
  }
}

void Trimesh::generateNormals()
// Once you've loaded all the verts and faces, we can generate per
// vertex normals by averaging the normals of the neighboring faces.
{
  int cnt = vertices.size();
  normals.resize(cnt);
  int *numFaces = new int[ cnt ]; // the number of faces assoc. with each vertex
  memset(numFaces, 0, sizeof(int)*cnt);

  for (Faces::iterator fi = faces.begin(); fi != faces.end(); ++fi) {
    Vec3d faceNormal = (**fi).getNormal();

    for (int i = 0; i < 3; ++i) {
      normals[(**fi)[i]] += faceNormal;
      ++numFaces[(**fi)[i]];
    }
  }

  for (int i = 0; i < cnt; ++i) {
    if (numFaces[i])
      normals[i]  /= numFaces[i];
  }

  delete [] numFaces;
  vertNorms = true;
}

